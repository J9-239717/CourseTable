#define CLAY_IMPLEMENTATION
#define RENDERER_IMPLEMENTATION
#define DEBUG
#include "clay.h"
#include "renderer.h"

#define HANDLE_TYPING
#include "typing.c"

typedef struct{
    Arena arena;                    // For UI text allocations 
    bool typing;                    // State Typing
    bool init;                      // Do the state already init
    bool error;                     // For show Error texts
}Environment;
Environment env = {0};
float Broad_UI_Size = 0.7f;         // this it Percent of Broad UI Size


typedef enum{
    row,
    column
}direction;

typedef enum{
    text,
    element
}type_attribute;

typedef struct UI_tree_t{
    union data_box_t
    {
        ComponentOptions componentOption;
        char* text;
    }data_box;
    direction direction;
    type_attribute att;
    struct UI_tree_t *child,*slibing;
}UI_tree;
UI_tree *ui__tree;
UI_tree *global_ptr;

typedef enum{
    input,
    output
}cmd_tage;

typedef struct node_command_t{
    char* buffer;
    cmd_tage tage;
    struct node_command_t* next;
}node_command;

typedef struct{
    Arena arena;
    node_command* data;
    bool changed;
}Tree_Structure;
Tree_Structure tree_structure = {0};

typedef struct list_command_t{
    Arena box_allocate;
    node_command* node;
}list_command;

list_command list_cmd = {0};

void Reset_List(){
    ArenaReset(&list_cmd.box_allocate);
    list_cmd.node = NULL;
}

node_command* create_node_command(cmd_tage tage,Arena* allo){
    node_command* new = (node_command*) ArenaAlloc(allo,sizeof(node_command));
    new->buffer = NULL;
    new->next = NULL;
    new->tage = tage;
    return new;
}

char* string_allocate(const char* src,size_t len,Arena *allo){
    char* new = (char*) ArenaAlloc(allo,len+1);
    strncpy(new,src,len);
    new[len+1] = '\0';
    return new;
}

UI_tree* CreateNodeUiTree(void){
    UI_tree* temp = (UI_tree*)calloc(1,sizeof(UI_tree));
    temp->child = temp->slibing = NULL;
    return temp;
}

int Add_Child_(UI_tree* src,UI_tree* new){
    if(src->child){
        // TODO: show error later
        // already have child
        return 0;
    }

    src->child = new;
    return 1;
}

int Add_Slibing_(UI_tree* src,UI_tree* new){
    if(!src->slibing){
        // First Slibing
        src->slibing = new;
    }else{
        UI_tree* curr = src;
        while(curr->slibing){
            curr = curr->slibing;
        }
        curr->slibing = new;
    }
    return 1;
}

void Add_Node_Tree_Structure(Tree_Structure* tree,node_command* node){
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

void Genarate_Tree_Structure(Tree_Structure* tree_structure,UI_tree* node,int deep){
    if(!node) return;
    char buffer__[deep+3];
    buffer__[0] = '\0';
    char buffer_[64];
    char buffer = ' ';
    if(deep > 0){
        buffer__[0] = ' ';
        buffer__[1] = 'r';
        for(int i = 2; i < deep+2;i++){
            buffer__[i] = 'l';
        }
    }
    if(node == global_ptr) buffer = '<';
    if(node->att == element){
        printf("[%d]\n", node->direction);
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

    char* str_temp = string_allocate(buffer_,strlen(buffer_),&tree_structure->arena);
    node_command* node_temp = create_node_command(input,&tree_structure->arena);
    node_temp->buffer = str_temp;
    Add_Node_Tree_Structure(tree_structure,node_temp);

    Genarate_Tree_Structure(tree_structure,node->child,deep+1);

    UI_tree *curr = node->slibing,*temp = NULL;
    while(curr){
        Genarate_Tree_Structure(tree_structure,curr,deep);
        curr = curr->slibing;
    }
}

static inline void Gen_Tree_UI(){
    Genarate_Tree_Structure(&tree_structure,ui__tree,0);
    printf("[FUNC] Already Gennarate Tree Structure\n");
}

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

void FreeUiTree(){
    FreeNodeUiTree(ui__tree);
    printf("[Func] Already Free UI Tree\n");
}

Clay_TextElementConfig textConfig = (Clay_TextElementConfig){
    .fontId = FONT_24,
    .fontSize = 24,
    .textColor = CREAM
};


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

void UI_Tree(){
    char width_[10] = {0};
    sprintf(width_, "percent-%.1f", 1 - Broad_UI_Size);
    Column(
        .id = "UI Tree Container",
        .h = "grow-0",
        .w = width_,
        .bg = NEUTRAL_950,
        .border = (Border){
            .width = "a-3",
            .color = NEUTRAL_200
        }
    ){
        // TODO: impiment directory show with pointer
    }
}

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

void Draw(){
    Clay_RenderCommandArray renderCommand = CreateLayout();

    BeginDrawing();
    {
        Clay_Raylib_Render(renderCommand, renderer.fonts);
    }
    EndDrawing();
    ArenaReset(&env.arena);
}

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

void Update(){
    handleTyping();
    if(IsKeyPressed(KEY_ENTER)){
        int argc = Parse_Command();
        resetStringBuffer();
        // try print
        node_command* curr = list_cmd.node;
        printf("Command is: \n");
        for(int i = 0; i < argc; i++,curr = curr->next){
            printf("  - %s\n", curr->buffer);
        }
        Reset_List();
    }

    if(tree_structure.changed){
        Gen_Tree_UI();
        tree_structure.changed = false;

        node_command* curr = tree_structure.data;
        while (curr)
        {
            printf("%s", curr->buffer);
            curr = curr->next;
        }
    }
}

char dummy_text[] = "Xang is \nGay Lord";

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
    tree_structure.arena = ArenaInit(40096);
    tree_structure.data = NULL;
    tree_structure.changed = true;

    // Init Data Dummy
    ui__tree = CreateNodeUiTree();
    ui__tree->att = element;
    ui__tree->data_box.componentOption = \
    (ComponentOptions){
        .id = "dummy test",
        .w = "grow-0",
        .h = "grow-0",
    };
    ui__tree->direction = row;
    UI_tree *dummy_child = CreateNodeUiTree();
    ui__tree->child = dummy_child;

    dummy_child->att = text;
    dummy_child->data_box.text = dummy_text;

    UI_tree *dummy_slibing = CreateNodeUiTree();
    ui__tree->slibing = dummy_slibing;

    dummy_slibing->att = element;
    dummy_slibing->direction = row;
    dummy_slibing->data_box.componentOption = \
    (ComponentOptions){
        .id = "dummy test 2",
        .w = "grow-0",
        .h = "grow-0",
        .border = (Border){
            .color = GREEN_200,
            .width = "a-3"
        }
    };

    global_ptr = dummy_slibing;
}

void clear(){
    ArenaFree(&env.arena);
    ArenaFree(&list_cmd.box_allocate);
    ArenaFree(&tree_structure.arena);
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