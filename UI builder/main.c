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

typedef struct{
    Arena arena;
}Tree_Structure;

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

UI_tree* CreateNodeUiTree(void){
    UI_tree* temp = (UI_tree*)calloc(1,sizeof(UI_tree));
    temp->child = temp->slibing = NULL;
    return temp;
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

void Update(){
    handleTyping();
}

char dummy_text[] = "Xang is Gay Lord";

void Init(){
    // Init ENV
    env.arena = ArenaInit(40096);
    env.typing = false;
    env.init = true;
    env.error = false;

    // Init String Buffer Typing
    string_buffer.pt = 0;
    string_buffer.buffer[string_buffer.pt] = '\0';

    // Init Data Dummy
    ui__tree = CreateNodeUiTree();
    ui__tree->att = element;
    ui__tree->data_box.componentOption = \
    (ComponentOptions){
        .id = "dummy test",
        .w = "grow-0",
        .h = "grow-0",
        .border = (Border){
            .width = "a-3",
            .color = GREEN_200
        }
    };
    ui__tree->direction = row;
    UI_tree *dummy_child = CreateNodeUiTree();
    ui__tree->child = dummy_child;

    dummy_child->att = text;
    dummy_child->data_box.text = dummy_text;
}

void clear(){
    ArenaFree(&env.arena);
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