#define CLAY_IMPLEMENTATION
#define RENDERER_IMPLEMENTATION

#include "clay.h"
#include "renderer.h"


void Test(){
    Clay_TextElementConfig *textConfig = CLAY_TEXT_CONFIG(
        {
            .fontId = FONT_24,
            .fontSize = 24,
            .textColor = CREAM
        }
    );
    Clay_TextElementConfig *textHeaderConfig = CLAY_TEXT_CONFIG(
        {
            .fontId = FONT_24,
            .fontSize = 24,
            .textColor = CREAM
        }
    );
    Box(
        .id = "Body",
        .pt = 42,
        .align = "tc",
        .w = "grow-0",
        .h = "grow-0",
        .bg = NEUTRAL_950
    ){
        Column(
            .bg = NEUTRAL_950,
            .pb = 7,
            .w = "fit-450",
            .gap = 8,
            .borderRadius = "a-lg"
        ){
            Row(
                .id = "Top-Row",
                .bg = NEUTRAL_950,
                .w = "grow-0",
                .pt = 10,
                .pb = 5,
                .pl = 9,
                .pr = 7,
                .gap = 5,
                .borderRadius = "t-lg"
            ){
                TextS("COURSES TABLE \n", textHeaderConfig);
                Separator(.px = 3);
                TextS("Program", textConfig);
            }
        }
    }
}

Clay_RenderCommandArray CreateLayout(){
    Clay_BeginLayout();
    {
        Test();
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

}

void update(){
    return;
}

int main(){
    {
        RenderOptions options = {
            .width = 800,
            .height = 600,
            .windowName = "Clay Renderer",
            .fontPath = "./res/ComicMono.ttf"
        };
        RenderSetup(options, update, draw);
    }
    
}