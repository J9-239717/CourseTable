#define CLAY_IMPLEMENTATION
#define RENDERER_IMPLEMENTATION
#define HANDLE_TYPING
#define UI_

#include "clay.h"
#include "renderer.h"
#include "typing.c"

typedef struct {
    Arena arena; // For UI text allocations
    bool typing;
}State;
State state = {0};
int8_t selection_index = 0;

#include "UI.c"


Clay_RenderCommandArray CreateLayout(){
    Clay_BeginLayout();
    {
        MainPage();
    }
    return Clay_EndLayout();
}

void draw(){
    Clay_RenderCommandArray renderCommand = CreateLayout();

    BeginDrawing();
    {
        Clay_Raylib_Render(renderCommand, renderer.fonts);
    }
    EndDrawing();
    ArenaReset(&state.arena);
}

void update(){
    if(IsKeyPressed(KEY_EQUAL)){
        state.typing = !state.typing;
        resetStringBuffer();
    }

    if(state.typing){
        handleTyping();
    }else{
        // choose page
        if(IsKeyPressed(KEY_APOSTROPHE)){
            selection_index--;
            if(selection_index < 0) selection_index = 0;
        }

        if(IsKeyPressed(KEY_SEMICOLON)){
            selection_index++;
            if(selection_index >= SIZE_PAGE) selection_index = SIZE_PAGE -1;
        }
    }
    return;
}

void init(){
    state.arena = ArenaInit(40096);
    state.typing = false;
}

int main(){
    init();
    {
        RenderOptions options = {
            .width = 1600,
            .height = 900,
            .windowName = "Courses Visual Program",
            .fontPath = "./res/ComicMono.ttf"
        };
        RenderSetup(options, update, draw);
    }
    
}