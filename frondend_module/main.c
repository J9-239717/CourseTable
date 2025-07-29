#define CLAY_IMPLEMENTATION
#define RENDERER_IMPLEMENTATION
#define HANDLE_TYPING
#define UI_
#define DEBUG

#include "clay.h"
#include "renderer.h"
#include "typing.c"

typedef struct {
    Arena arena;                    // For UI text allocations
    bool typing;                    // State Typing
    bool init;                      // Do the state already init
    bool error;                     // For show Error texts
}State;
State state = {0};
int8_t selection_index = 0;

typedef struct message_box_t{
    char* buffer;                   // buffer pointer to text
    char* title;                    // title of massage
    char* meta;                     // meta data
    struct message_box_t* next;     // link list
}message_box;

typedef struct{
    Arena arena;                    // For Allocate Message System text Store
    message_box *message;           // Message link list
}Message_store;

Message_store history_message = {0};

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

char* MessageHistory_Allocate(char* src,size_t size){
    char* buffer = (char*)ArenaAlloc(&history_message.arena, size);
    strncpy(buffer, src, size);
    return buffer;
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
                if(IsKeyPressed(KEY_ENTER)){
                    // Pass String Buffer to Message History
                    if(history_message.message->buffer == NULL){    
                        // Fist Message
                        history_message.message->buffer = MessageHistory_Allocate(string_buffer.buffer,string_buffer.pt);
                        history_message.message->meta = MessageHistory_Allocate("Input Message",15);
                        history_message.message->title = MessageHistory_Allocate("Command",9);
                        history_message.message->next = NULL;
                    }else{
                        message_box* temp = (message_box*)malloc(sizeof(message_box));
                        temp->buffer = MessageHistory_Allocate(string_buffer.buffer,string_buffer.pt);
                        temp->meta = MessageHistory_Allocate("Input Message",15);
                        temp->title = MessageHistory_Allocate("Command",9);
                        temp->next = history_message.message;
                        history_message.message = temp;
                    }
                    resetStringBuffer();
                }
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

void MessageBoxInit(message_box* src){
    src->buffer = NULL;
    src->meta = NULL;
    src->title = NULL;
    src->next = NULL;
}

void init(){
    // Init State
    state.arena = ArenaInit(40096);
    state.typing = false;
    state.init = true;
    state.error = false;

    // Init History Message
    history_message.arena = ArenaInit(65536);
    history_message.message = (message_box*)malloc(sizeof(message_box));
    MessageBoxInit(history_message.message);
}

void FreeMessage(){
    message_box *temp = NULL, *curr = history_message.message;
    while(curr != NULL){
        temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(history_message.message);
}

void clear(){
    ArenaFree(&state.arena);
    ArenaFree(&history_message.arena);
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