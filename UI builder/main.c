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

typedef struct{
    ComponentOptions data;
    ComponentOptions *child,*slibing;
}UI_tree;

Clay_TextElementConfig textConfig = (Clay_TextElementConfig){
    .fontId = FONT_24,
    .fontSize = 24,
    .textColor = CREAM
};

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

void BroadUI(){
    char width_[10] = {0};
    sprintf(width_, "percent-%.1f", Broad_UI_Size);
    Column(
        .id = "Broad UI Container",
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
                BroadUI();
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

void Init(){
    // Init ENV
    env.arena = ArenaInit(40096);
    env.typing = false;
    env.init = true;
    env.error = false;

    // Init String Buffer Typing
    string_buffer.pt = 0;
    string_buffer.buffer[string_buffer.pt] = '\0';
}

void clear(){
    ArenaFree(&env.arena);
}

int main(){
    Init();
    {
        RenderOptions options = {
            .width = 1600,
            .height = 900,
            .windowName = "UI Building",
            .fontPath = "../res/DejaVuSansMono-Bold.ttf"
        };
        RenderSetup(options, Update, Draw);
    }
    clear();
}