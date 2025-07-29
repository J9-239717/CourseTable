#ifdef HANDLE_TYPING

#include <stdio.h>

#define Size_of_Str_Buffer 1024

typedef struct{
    char buffer[Size_of_Str_Buffer];
    int8_t pt;
}String_buffer;
String_buffer string_buffer = {0};

int isBufferEmpty(){
    return string_buffer.pt == 0 ? 1 : 0;
}

void resetStringBuffer(){
    string_buffer.pt = 0;
}

int isBufferFull(int offset){
    return string_buffer.pt + offset >= Size_of_Str_Buffer ? 1 : 0;
}

void handleTyping(){
    if(IsKeyPressed(KEY_A) && !isBufferFull(1)){
        string_buffer.buffer[string_buffer.pt++] = 'A';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_B) && !isBufferFull(1)){
        string_buffer.buffer[string_buffer.pt++] = 'B';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_C) && !isBufferFull(1)){
        string_buffer.buffer[string_buffer.pt++] = 'C';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_D) && !isBufferFull(1)){
        string_buffer.buffer[string_buffer.pt++] = 'D';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_E) && !isBufferFull(1)){
        string_buffer.buffer[string_buffer.pt++] = 'E';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_F) && !isBufferFull(1)){
        string_buffer.buffer[string_buffer.pt++] = 'F';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_G) && !isBufferFull(1)){
        string_buffer.buffer[string_buffer.pt++] = 'G';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_H) && !isBufferFull(1)){
        string_buffer.buffer[string_buffer.pt++] = 'H';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_I) && !isBufferFull(1)){
        string_buffer.buffer[string_buffer.pt++] = 'I';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_J) && !isBufferFull(1)){
        string_buffer.buffer[string_buffer.pt++] = 'J';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_K) && !isBufferFull(1)){
        string_buffer.buffer[string_buffer.pt++] = 'K';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_L) && !isBufferFull(1)){
        string_buffer.buffer[string_buffer.pt++] = 'L';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_M) && !isBufferFull(1)){
        string_buffer.buffer[string_buffer.pt++] = 'M';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_N) && !isBufferFull(1)){
        string_buffer.buffer[string_buffer.pt++] = 'N';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_O) && !isBufferFull(1)){
        string_buffer.buffer[string_buffer.pt++] = 'O';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_P) && !isBufferFull(1)){
        string_buffer.buffer[string_buffer.pt++] = 'P';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_Q) && !isBufferFull(1)){
        string_buffer.buffer[string_buffer.pt++] = 'Q';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_R) && !isBufferFull(1)){
        string_buffer.buffer[string_buffer.pt++] = 'R';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_S) && !isBufferFull(1)){
        string_buffer.buffer[string_buffer.pt++] = 'S';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_T) && !isBufferFull(1)){
        string_buffer.buffer[string_buffer.pt++] = 'T';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_U) && !isBufferFull(1)){
        string_buffer.buffer[string_buffer.pt++] = 'U';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_V) && !isBufferFull(1)){
        string_buffer.buffer[string_buffer.pt++] = 'V';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_W) && !isBufferFull(1)){
        string_buffer.buffer[string_buffer.pt++] = 'W';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_X) && !isBufferFull(1)){
        string_buffer.buffer[string_buffer.pt++] = 'X';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_Y) && !isBufferFull(1)){
        string_buffer.buffer[string_buffer.pt++] = 'Y';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_Z) && !isBufferFull(1)){
        string_buffer.buffer[string_buffer.pt++] = 'Z';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_SPACE) && !isBufferFull(1)){
        string_buffer.buffer[string_buffer.pt++] = ' ';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_MINUS) && !isBufferFull(1)){
        string_buffer.buffer[string_buffer.pt++] = '-';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_BACKSPACE)){
        string_buffer.pt--;
        if(string_buffer.pt < 0){
            string_buffer.pt = 0;
        }
        string_buffer.buffer[string_buffer.pt] = '\0';
    }
}


#endif