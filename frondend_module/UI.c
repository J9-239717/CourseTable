#ifdef UI_

typedef enum {
    Start_page,
    Login_page,
    Help_page,
    CPA_page,
    Table_page,
    Check_NotPass_page,
    Main_page,
    Course_next_page
}PAGE_NUMBER;

PAGE_NUMBER page_state = Login_page;

#define SIZE_ARRAY(X) sizeof(X) / sizeof(X[0])

const char* page_name[] = {
    "Table Course",
    "Check CPA",
    "Check Not Pass Subject",
    "What Should Register Next",
    "Help"
};

#define SIZE_PAGE 5

#define space_y_column_250 Row(.bg = NEUTRAL_950,.h = "fixed-250"){}

Clay_TextElementConfig textError = (Clay_TextElementConfig) {
    .fontId = FONT_24,
    .fontSize = 24,
    .textColor = RED_500
};

Clay_TextElementConfig textDetail = (Clay_TextElementConfig){
    .fontId = FONT_22,
    .fontSize = 22,
    .textColor = GRAY_500
};

Clay_TextElementConfig textTitle = (Clay_TextElementConfig){
    .fontId = FONT_24,
    .fontSize = 24,
    .textColor = (Clay_Color){255, 255, 255, 255}
};

void MainPage(){
    Clay_TextElementConfig *textConfig = CLAY_TEXT_CONFIG(
        {
            .fontId = FONT_24,
            .fontSize = 24,
            .textColor = CREAM
        }
    );
    Box(
        .id = "Body",
        .align = "tc",
        .w = "grow-0",
        .h = "grow-0",
        .bg = NEUTRAL_950
    ){
        Column(
            .id = "Main Column",
            .bg = NEUTRAL_950,
            .pb = 7,
            .w = "grow-0",
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
                Separator(.px = 3);
                TextS("COURSES TABLE Program", textConfig);
                Separator(.px = 3);
            }

            if(state.typing){
            // Write Task Component
                Row(
                    .id = "Pointer",
                    .w = "grow-0",
                    .gap = 5,
                    .h = "fixed-55",
                    .bg = NEUTRAL_200,
                    .align = "cc",
                    .borderRadius = "a-xl"
                ){
                    Row(
                        .id = "box-in-typing",
                        .bg = NEUTRAL_950,
                        .w = "percent-0.99",
                        .h = "fixed-50",
                        .borderRadius = "a-l",
                        .align = "c"
                    ){
                        Separator(
                            .px = 1,
                            .w = "fixed-25"
                        );
                        TextS(">", textConfig);
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
                                Text(F(&state.arena, "%s", string_buffer.buffer),textConfig);
                            }
                        }
                    }
                }
                if(history_message.message->buffer != NULL){
                    message_box* curr = history_message.message;
                    int i = 0;
                    while(curr != NULL){
                        char* id__ = (char*) ArenaAlloc(&state.arena, 25);
                        sprintf(id__, "History Message %d", i);
                        i++;
                        Column(
                            .id = id__,
                            .h = "fixed-55",
                            .w = "grow-0",
                        ){
                            Row(
                                .h = "grow-0",
                                .w = "grow-0"
                            ){
                                TextS("  $~  ", textConfig);
                                Row(
                                    .h = "fixed-22",
                                    .w = "fixed-100",
                                    .bg = GREEN_500,
                                    .align = "tc"
                                ){
                                    Clay_String str = \
                                    (Clay_String){
                                        .length = strlen(curr->title),
                                        .chars = curr->title
                                    };
                                    Text(str,&textTitle);
                                }
                            }
                        }
                        curr = curr->next;
                    }
                }
            }else{
                // Scrolling choose page to go
                Row(
                    .w = "grow-0",
                    .align = "tc"
                ){
                    Separator(.px = 10);
                    Column(
                        .bg = NEUTRAL_900,
                        .pb = 7,
                        .w = "fixed-450",
                        .gap = 8,
                        .borderRadius = "a-lg"
                    ){
                        Row(
                            .id = "Scroll header",
                            .bg = NEUTRAL_800,
                            .w = "grow-0",
                            .pt = 10,
                            .pb = 5,
                            .pl = 9,
                            .pr = 7,
                            .gap = 5,
                            .borderRadius = "t-lg"
                        ){
                            Separator(.px =2);
                            TextS("Welecome", textConfig);
                            Separator(.px =2);
                        }

                        Column(
                            .id = "ContainerScroll",
                            .w = "grow-0",
                            .gap = 5,
                            .scroll = "v"
                        ){
                            for(int i = 0 ; i < SIZE_ARRAY(page_name); i++){
                                Box(
                                    .bg = i == selection_index ? NEUTRAL_600 : NEUTRAL_900,
                                    .w = "grow-0", 
                                    .px = 10, 
                                    .pt = 4, 
                                    .pb = 2
                                ){
                                    Text(F(&state.arena, "%s", page_name[i]), textConfig);
                                }
                            }
                        }
                    }
                    Separator(.px = 10);
                }
            }
        }
    }
}

int8_t LoginPage(){
    Clay_TextElementConfig *textConfig = CLAY_TEXT_CONFIG(
        {
            .fontId = FONT_24,
            .fontSize = 24,
            .textColor = CREAM
        }
    );
    Box(
        .id = "Body",
        .align = "tc",
        .w = "grow-0",
        .h = "grow-0",
        .bg = NEUTRAL_950
    ){
        Column(
            .id = "Main Column",
            .bg = NEUTRAL_950,
            .pb = 7,
            .w = "grow-0",
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
                Separator(.px = 3);
                TextS("COURSES TABLE Program", textConfig);
                Separator(.px = 3);
            }
            space_y_column_250;
            Row(
                .id = "Header-typing",
                .w = "grow-0",
                .bg = NEUTRAL_800
            ){
                Separator(.px = 2);
                TextS("Please Enter file name to Login", textConfig);
                Separator(.px = 2);
            }
            Row(
                .id = "typing-contrainer",
                .w = "grow-0",
                .h = "fixed-55",
                .bg = NEUTRAL_200,
                .align = "cc",
                .borderRadius = "a-xl"
            ){
                Row(
                    .id = "box-in-typing",
                    .bg = NEUTRAL_950,
                    .w = "percent-0.99",
                    .h = "fixed-50",
                    .borderRadius = "a-xl",
                    .align = "c"
                ){
                    Separator(
                        .px = 1,
                        .w = "fixed-25"
                    );
                    TextS(">", textConfig);
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
                            Text(F(&state.arena, "%s", string_buffer.buffer),textConfig);
                        }
                    }
                }
            }
            TextS("     Enter -NEW first if want to create new file or -IN if want to Login",textConfig);
            if(state.error){
                TextS("     Please enter name of file correctly or enter something correctly", &textError);
            }
        }
    }
}

#endif