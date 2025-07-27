#define CLAY_IMPLEMENTATION
#define RENDERER_IMPLEMENTATION
#define HANDLE_TYPING
#define UI_
#define DEBUG

#include "clay.h"
#include "renderer.h"
#include "typing.c"

typedef struct {
    Arena arena; // For UI text allocations
    bool typing;
    bool init;
    bool error; // For show Error texts
}State;
State state = {0};
int8_t selection_index = 0;

#include "UI.c"


Clay_RenderCommandArray CreateLayout(){
    Clay_BeginLayout();
    {
        switch (page_state)
        {
        case Login_page:
                if(!state.init){
                    state.typing = true; // make sure this page should typing
                    state.init = true;
                }
            LoginPage();
            break;
        default:
                if(!state.init){
                    state.typing = false; // default of this page
                    state.init = true;
                }
            MainPage();
            break;
        }
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

    // Debug
    if(IsKeyPressed(KEY_F1)){
        if(page_state == Login_page){
            page_state = Main_page;
        }else{
            page_state = Login_page;
        }
        state.init = false;
    }

    switch (page_state)
    {
        case Login_page: {
            handleTyping();
            if(IsKeyPressed(KEY_ENTER)){ // TODO: should handle login logic
                if(isBufferEmpty()){ // check if it's empty
                    state.error = true;
                    break;
                }
                page_state = Main_page;
                state.init = false;
                state.error = false;
            }
        }
        case Main_page: {
            // Handle change state typing
            if(IsKeyPressed(KEY_EQUAL)){
                state.typing = !state.typing;
                resetStringBuffer();
            }
            // Handle typing
            if(state.typing){
                handleTyping();
            }else{
                // choose page
                if(IsKeyPressed(KEY_UP)){
                    selection_index--;
                    if(selection_index < 0) selection_index = 0;
                }

                if(IsKeyPressed(KEY_DOWN)){
                    selection_index++;
                    if(selection_index >= SIZE_PAGE) selection_index = SIZE_PAGE -1;
                }
            }
        }
        default:
            break;
    }
    return;
}

void init(){
    state.arena = ArenaInit(40096);
    state.typing = false;
    state.init = true;
    state.error = false;
}

void clear(){
    ArenaFree(&state.arena);
}

int main(){
    init();
    {
        RenderOptions options = {
            .width = 1600,
            .height = 900,
            .windowName = "Courses Visual Program",
            .fontPath = "../res/Pixellettersfull-BnJ5.ttf"
        };
        RenderSetup(options, update, draw);
    }
    clear();
}