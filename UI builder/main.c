#define CLAY_IMPLEMENTATION
#define RENDERER_IMPLEMENTATION
#define DEBUG
#include "clay.h"
#include "renderer.h"

#define HANDLE_TYPING
#include "typing.c"

typedef struct{
    Arena arena;                                // For UI text allocations 
    bool typing;                                // State Typing
    bool init;                                  // Do the state already init
    bool error;                                 // For show Error texts
}Environment;
Environment env = {0};
float Broad_UI_Size = 0.7f;                     // this it Percent of Broad UI Size

typedef enum{
    row,
    column
}direction;                                     // Direction of Component

typedef enum{
    text,
    element
}type_attribute;                                // Type of Component

typedef struct UI_tree_t{
    union data_box_t                            // Box of Data
    {
        ComponentOptions componentOption;       // Component Option
        char* text;                             // Raw Data Text for Text Type
    }data_box;
    direction direction;                        // Direction Component
    type_attribute att;                         // Type Attribute
    struct UI_tree_t *parent,*child,*slibing;   // Tree Pointer
}UI_tree;
UI_tree *ui__tree;                              // Ui Main Tree
UI_tree *global_ptr;                            // Global Pointer

typedef enum{
    input,
    output
}cmd_tage;                                      // Command Type

typedef struct node_command_t{
    char* buffer;                               // Raw Text Data
    cmd_tage tage;                              // Tage of Command
    struct node_command_t* next;                // Link
}node_command;

typedef struct{
    Arena arena;                                // Memmory Allocate
    node_command* data;                         // Link List
    bool changed;                               // Boolean to Re-Gennerate
}List_String_Tree;
List_String_Tree list_tree_structure = {0};            // List of String For Gennerate UI Tree

// Reset List String Tree UI
void Reset_List_Tree_Structure(){
    ArenaReset(&list_tree_structure.arena);
    list_tree_structure.data = NULL;
}

typedef struct list_command_t{
    Arena box_allocate;                         // Memmory Allocate
    node_command* node;                         // Link list
}list_command;

list_command list_cmd = {0};                    // List of String Command Input and Uing For Showing Output

// Reset List String Command
void Reset_List_Command(){
    ArenaReset(&list_cmd.box_allocate);
    list_cmd.node = NULL;
}

// Create Node Command
node_command* create_node_command(cmd_tage tage,Arena* allo){
    node_command* new = (node_command*) ArenaAlloc(allo,sizeof(node_command));
    new->buffer = NULL;
    new->next = NULL;
    new->tage = tage;
    return new;
}

// Allocate String using in Arena allocate
char* string_allocate(const char* src,size_t len,Arena *allo){
    char* new = (char*) ArenaAlloc(allo,len+1);
    strncpy(new,src,len);
    new[len+1] = '\0';
    return new;
}

// Create UI Tree Node
UI_tree* CreateNodeUiTree(void){
    UI_tree* temp = (UI_tree*)calloc(1,sizeof(UI_tree));
    temp->child = temp->slibing = temp->parent = NULL;
    return temp;
}

// Add Node Command To List String Tree
void Add_Node_Tree_Structure(List_String_Tree* tree,node_command* node){
    if(tree->data == NULL){
        // First node
        tree->data = node;
    }else{
        node_command* curr = tree->data;
        while(curr->next){
            curr = curr->next;
        }
        curr->next = node;
    }
}

// Genarate List String reference in Main UI Tree for show on screen
void Genarate_Tree_Structure(List_String_Tree* list_tree_structure,UI_tree* node,int deep){
    if(!node) return;
    char buffer__[deep+2];
    buffer__[0] = '\0';
    char buffer_[64];
    char buffer = ' ';
    if(deep > 0){
        int i = 0;
        for(i = 0; i < deep; i++){
            buffer__[i] = 's';
        }
        buffer__[i] = 'c';
        buffer__[i+1] = '\0';
    }
    if(node == global_ptr) buffer = '<';
    if(node->att == element){
        switch (node->direction)
        {
            case row:{
                sprintf(buffer_, "%s%s  %c\n",buffer__,"[Row]",buffer);
            }
            break;
            case column:{
                sprintf(buffer_, "%s%s  %c\n",buffer__,"[Column]",buffer);
            }
            break;
            default:{
                sprintf(buffer_, "%s%s  %c\n",buffer__,"[Unknow]",buffer);
            }
            break;
        }
    }else if(node->att == text){
        sprintf(buffer_, "%s%s  %c\n",buffer__,"[Text]",buffer);
    }

    char* str_temp = string_allocate(buffer_,strlen(buffer_),&list_tree_structure->arena);
    node_command* node_temp = create_node_command(input,&list_tree_structure->arena);
    node_temp->buffer = str_temp;
    Add_Node_Tree_Structure(list_tree_structure,node_temp);

    Genarate_Tree_Structure(list_tree_structure,node->child,deep+1);
    Genarate_Tree_Structure(list_tree_structure,node->slibing,deep);
}

// Function all recursive Generate Tree
static inline void Gen_Tree_UI(){
    Genarate_Tree_Structure(&list_tree_structure,ui__tree,0);
    printf("[FUNC] Already Gennarate Tree Structure\n");
}

// Free Main UI tree
void FreeNodeUiTree(UI_tree* node){
    if(!node) return;

    UI_tree *curr = node,*temp = NULL;
    while(curr){
        FreeNodeUiTree(curr->child);
        temp = curr;
        curr = curr->slibing;
        free(temp);
    }
}

// Function call recursive Free Main UI tree
void FreeUiTree(){
    FreeNodeUiTree(ui__tree);
    printf("[Func] Already Free UI Tree\n");
}


Clay_TextElementConfig textConfig = \
    (Clay_TextElementConfig){                    // Text Element Config
        .fontId = FONT_24,                       
        .fontSize = 24,
        .textColor = CREAM
    };

// Function Change Main UI tree to CLAY(...) macro
void TreeComponent(UI_tree* node){
    if(!node) return;

    UI_tree *curr = node,*temp = NULL;

    while(curr){
        if(curr->att == element){
            if(curr->direction == row){
                CLAY(ParseComponentOptions(curr->data_box.componentOption, rowDefaultOptions)){
                    TreeComponent(curr->child);
                }
            }else if(curr->direction == column){
                CLAY(ParseComponentOptions(curr->data_box.componentOption, columnDefaultOptions)){
                    TreeComponent(curr->child);
                }
            }
        }else if(curr->att == text){
            Clay_String str = (Clay_String){
                .length = strlen(curr->data_box.text),
                .chars = curr->data_box.text
            };
            Clay__OpenTextElement(str,&textConfig);
        }

        curr = curr->slibing;
    }
}

// Box of Command input
void CommandBox(){
    Row(
        .id = "Pointer",
        .w = "grow-0",
        .gap = 5,
        .h = "fixed-55",
        .bg = NEUTRAL_950,
        .align = "c",
        .borderRadius = "a-xl",
        .border = (Border){
            .width = "a-3",
            .color = NEUTRAL_200
        }
    ){
        Separator(
            .px = 1,
            .w = "fixed-25"
        );
        TextS(">", &textConfig);
        Row(
            .id = "Task",
            .w = "fixed-500",
            .gap = 5,
        ){
            Separator(
                .px = 2,
                .w = "Fixed-10"
            );
            if(!isBufferEmpty()){
                Text(F(&env.arena, "%s", string_buffer.buffer),&textConfig);
            }
        }
    }
}

// Board Show UI dynamic
void BoardUI(){
    char width_[10] = {0};
    sprintf(width_, "percent-%.1f", Broad_UI_Size);
    Column(
        .id = "Board UI Container",
        .h = "grow-0",
        .w = width_,
        .bg = NEUTRAL_950,
        .border = (Border){
            .width = "a-3",
            .color = NEUTRAL_200
        }
    ){
        Margin(
            .id = "Margin For board",
            .p = 10,
        ){
            TreeComponent(ui__tree);
        }
    }
}

// ascii = '└──'
void TreeLine_(){
    CLAY({
        .layout = CLAY__INIT(Clay_LayoutConfig) {
            .sizing = {
                .width = CLAY_SIZING_FIXED(30),
                .height = CLAY_SIZING_FIXED(20)
            },
            .childAlignment = {
                .x = CLAY_ALIGN_X_LEFT,
                .y = CLAY_ALIGN_Y_TOP
            },
            .layoutDirection = CLAY_TOP_TO_BOTTOM,
            .childGap = 0
        }
    }) {
            // VerticalLine
            CLAY({
                .backgroundColor = {245, 230, 210, 255},
                .layout = CLAY__INIT(Clay_LayoutConfig) {
                    .sizing = {
                        .width = CLAY_SIZING_FIXED(2),
                        .height = CLAY_SIZING_FIXED(10)
                    }
                }
            });
            // HorizontalLine
            CLAY({
                .backgroundColor = {245, 230, 210, 255},
                .layout = CLAY__INIT(Clay_LayoutConfig) {
                    .sizing = {
                        .width = CLAY_SIZING_FIXED(20),
                        .height = CLAY_SIZING_FIXED(2)
                    }
                }
            });
        }
}

// show tree structure to screen
void UI_Tree(){
    char width_[10] = {0};
    sprintf(width_, "percent-%.1f", 1 - Broad_UI_Size);
    Row(
        .id = "UI Tree Container",
        .h = "grow-0",
        .w = width_,
        .bg = NEUTRAL_950,
        .border = (Border){
            .width = "a-3",
            .color = NEUTRAL_200
        },
    ){
        Margin(
            .id = "Margin for UI tree",
            .p = 10
        ){
            Column(
                .h = "grow-0",
                .w = "grow-0", 
            ){
                char* ch = NULL;
                node_command* curr = list_tree_structure.data;
                while(curr){
                    Row(
                        .h = "fixed-23",
                        .w = "grow-0"
                    ){
                        ch = curr->buffer;
                        if(*ch == 's' || *ch == 'c'){
                            while(*ch != '['){
                                if(*ch == 's'){
                                    Separator(
                                        .w = "fixed-10"
                                    );
                                }else if(*ch == 'c'){
                                    TreeLine_();
                                }
                                ch++;
                            }
                        }
                        Clay_String str = \
                        (Clay_String){
                            .length = strlen(ch),
                            .chars = ch
                        };
                        Clay__OpenTextElement(str,&textConfig);
                        curr = curr->next;
                    }
                }
            }
        }
    }
}

// Main Container Create Interface
Clay_RenderCommandArray CreateLayout(){
    Clay_BeginLayout();
    {
        Column(
            .id = "Main Column",
            .h = "grow-0",
            .w = "grow-0"
        ){
            CommandBox();
            Row(
                .id = "Bottom Container",
                .h = "grow-0",
                .w = "grow-0",
                .bg = NEUTRAL_950,
                .border = (Border){
                    .width = "a-3",
                    .color = NEUTRAL_200
                }
            ){
                BoardUI();
                UI_Tree();
            }
        }
    }
    return Clay_EndLayout();
}

// Draw function
void Draw(){
    Clay_RenderCommandArray renderCommand = CreateLayout();

    BeginDrawing();
    {
        Clay_Raylib_Render(renderCommand, renderer.fonts);
    }
    EndDrawing();
    ArenaReset(&env.arena);
}

// Parse Command input to list string
int Parse_Command(){
    char* c = string_buffer.buffer;
    int count = 0, i = 0,count_arg = 0;
    char temp[1024] = {0};
    while( *c != '\0' && count <= string_buffer.pt){
        if(*c == ' '){
            temp[i] = '\0';
            node_command* temp_ = create_node_command(input,&list_cmd.box_allocate);
            temp_->buffer = string_allocate(temp,strlen(temp),&list_cmd.box_allocate);
            
            if(!list_cmd.node){
                // fist command
                list_cmd.node = temp_;
            }else{
                node_command* curr = list_cmd.node;
                while(curr->next){
                    curr = curr->next;
                }
                curr->next = temp_;
            }

            i = 0;
            temp[0] = '\0';
            count_arg++;
        }else{
            temp[i++] = *c;
        }
        count++;
        c++;
    }

    // last cmd
    if(i > 0){
        temp[i] = '\0';
        node_command* temp_ = create_node_command(input,&list_cmd.box_allocate);
        temp_->buffer = string_allocate(temp,strlen(temp),&list_cmd.box_allocate);
        
        if(!list_cmd.node){
            // fist command
            list_cmd.node = temp_;
        }else{
            node_command* curr = list_cmd.node;
            while(curr->next){
                curr = curr->next;
            }
            curr->next = temp_;
        }
        count_arg++;
    }
    return count_arg;
}

// Handle Command input
void Handle_Command(int argc,node_command* node){
    node_command* curr = node;
    while(curr != NULL){
        if(strncmp(curr->buffer,"PT",2) == 0){ // move global pointer
                curr = curr->next;
                if(!curr){
                    error_pt:
                    printf("[ERROR] something wrong please check argument of PT is [-B|-N|-C|-D]\n");
                    return;
                }
                if(strncmp(curr->buffer, "-P",2) == 0){ // move to parent
                    if(!global_ptr->parent) return;
                    global_ptr = global_ptr->parent;
                }else if(strncmp(curr->buffer, "-S",2) == 0){ // move to slibing
                    if(!global_ptr->slibing) return;
                    global_ptr = global_ptr->slibing;
                }else if(strncmp(curr->buffer, "-C",2) == 0){ // move to child
                    if(!global_ptr->child) return;
                    global_ptr = global_ptr->child;
                }else if(strncmp(curr->buffer,"-R",2) == 0){ // reset to root
                    global_ptr = ui__tree;
                }else{
                    goto error_pt;
                }
                list_tree_structure.changed = true;
        }else if(strncmp(curr->buffer,"NODE",4) == 0){
                curr = curr->next;
                if(!curr){
                    error_node:
                    printf("[ERROR] something wrong please check argument of NODE is [-NEW] [-F|-C|-S] [-R|-C|-T]\n");
                    return;
                }

                if(strncmp(curr->buffer,"-NEW",4) == 0){ // new node
                    curr = curr->next;
                        if(!curr || !curr->next){ // Handle not enough parameter
                            goto error_node;
                            return;
                        }
                        if(strncmp(curr->next->buffer,"TEXT",4) == 0 && !curr->next->next){ // Handle not enough parameter for text
                            printf("[ERROR] Please Enter string if using argument TEXT\n");
                            return;
                        }
                    UI_tree* temp = NULL;
                    temp = CreateNodeUiTree();
                    // default component option
                    temp->data_box.componentOption = \
                        (ComponentOptions){
                            .w = "grow-0",
                            .h = "grow-0",
                            .border = (Border){
                                .width = "a-3",
                                .color = CREAM
                            }
                        };

                    if(!global_ptr||strncmp(curr->buffer,"-N",2) == 0){// new node or first node
                        if(global_ptr){
                                // already have node
                                // Waring if have child or slibing it cant create new node
                                // Should delete all child and slibing first
                                if(global_ptr->child){
                                    printf("[ERROR] should delte all child on current node first\n");
                                    free(temp);
                                    return;
                                }
                            UI_tree* free_node = global_ptr;
                            UI_tree *curr = NULL,*prev = NULL;
                            if(global_ptr->parent){
                                temp->parent = global_ptr->parent;
                                curr = global_ptr->parent->child;
                            }else{
                                curr = ui__tree;
                            }
                            
                            while(curr){
                                if(curr == free_node){
                                    if(prev == NULL){
                                        // first slibing
                                        temp->slibing = curr->slibing;
                                    }else{
                                        // between node
                                        prev->slibing = temp;
                                        temp->slibing = curr->slibing;
                                    }
                                    global_ptr = temp;
                                    break;
                                }
                                prev = curr;
                                curr = curr->slibing;
                            }
                            if(!curr){
                                printf("[ERROR] something wrong unknow behavior error\n");
                                free(temp);
                                return;
                            }
                            if(ui__tree == free_node){ // handle if it root node
                                ui__tree = temp;
                            }
                            free(free_node);
                        }else{
                            // first node
                            firstNode:
                            global_ptr = ui__tree = temp;
                        }
                }else if(strncmp(curr->buffer,"-C",2) == 0){ // child
                        if(!global_ptr) goto firstNode; // handle frist node
                        if(global_ptr->child){  // handle if have child 
                            printf("[ERROR] already have child please delete it first\n");
                            free(temp);
                            return;
                        }
                    global_ptr->child = temp;
                    temp->parent = global_ptr;
                }else if(strncmp(curr->buffer,"-S",2) == 0){ // slibing
                        if(!global_ptr) goto firstNode; // handle frist node
                    UI_tree* curr = global_ptr->slibing;
                    if(!curr){
                        // first slibing
                        global_ptr->slibing = temp;
                        temp->parent = global_ptr->parent;
                    }else{
                        // between slibing
                        while(curr->slibing) curr = curr->slibing;
                        curr->slibing = temp;
                        temp->parent = curr->parent;
                    }
                }else{
                    goto error_node;
                }

                curr = curr->next; // next parameter

                if(strncmp(curr->buffer,"-R",3) == 0){ // row
                    temp->att = element;
                    temp->direction = row;
                }else if(strncmp(curr->buffer,"-C",6) == 0){ // column
                    temp->att = element;
                    temp->direction = column;
                }else if(strncmp(curr->buffer,"-T",4) == 0){ // text
                    temp->att = text;
                    curr = curr->next;
                    temp->data_box.text = string_allocate(curr->buffer,strlen(curr->buffer),&env.arena);
                }else{
                    free(temp);
                    goto error_node;
                }
            }
            list_tree_structure.changed = true;
        }
        else{
            printf("[ERROR] %s is invalid command\n", curr->buffer);
        }

        curr = curr->next;
    }
}

// Update Function
void Update(){
    handleTyping();
    if(IsKeyPressed(KEY_ENTER)){
        int argc = Parse_Command();
        Handle_Command(argc,list_cmd.node);
        resetStringBuffer();
        Reset_List_Command();
    }

    if(list_tree_structure.changed){
        Reset_List_Tree_Structure();
        Gen_Tree_UI();
        list_tree_structure.changed = false;
    }
}

// Init Data and Memmory Allocate
void Init(){
    // Init ENV
    env.arena = ArenaInit(40096);
    env.typing = false;
    env.init = true;
    env.error = false;

    // Init String Buffer Typing
    string_buffer.pt = 0;
    string_buffer.buffer[string_buffer.pt] = '\0';

    // Init Command List
    list_cmd.box_allocate = ArenaInit(40096);
    list_cmd.node = NULL;

    // Init Tree Structure
    list_tree_structure.arena = ArenaInit(40096);
    list_tree_structure.data = NULL;
    list_tree_structure.changed = true;

    // Init Data Dummy
    ui__tree = NULL;
    global_ptr = NULL;
}

// Free Data
void clear(){
    ArenaFree(&env.arena);
    ArenaFree(&list_cmd.box_allocate);
    ArenaFree(&list_tree_structure.arena);
    FreeUiTree();
}

int main(){
    Init();
    {
        RenderOptions options = {
            .width = 1600,
            .height = 900,
            .windowName = "UI Building",
            .fontPath = "../../res/DejaVuSansMono-Bold.ttf"
        };
        RenderSetup(options, Update, Draw);
    }
    clear();
}