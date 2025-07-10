#ifdef UI_

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
                Row(
                    .id = "Pointer",
                    .w = "grow-0",
                    .gap = 5
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
                        .bg = NEUTRAL_800
                    ){
                        Separator(
                            .px = 2,
                            .w = "Fixed-10"
                        );
                        if(!isEmpty()){
                            Text(F(&state.arena, "%s", string_buffer.buffer),textConfig);
                        }
                    }
                }
            }

            Column(
                .id = "ContainerScroll",
                .w = "grow-0",
                .gap = 5,
                .scroll = "v"
            ){
                
            }
        }
    }
}

#endif