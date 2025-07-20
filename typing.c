#ifdef HANDLE_TYPING

#include <stdio.h>

typedef struct{
    char buffer[1024];
    int8_t pt;
}String_buffer;
String_buffer string_buffer = {0};

int isBufferEmpty(){
    return string_buffer.pt == 0 ? 1 : 0;
}

void resetStringBuffer(){
    string_buffer.pt = 0;
}

void handleTyping(){
    if(IsKeyPressed(KEY_A)){
        string_buffer.buffer[string_buffer.pt++] = 'A';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_B)){
        string_buffer.buffer[string_buffer.pt++] = 'B';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_C)){
        string_buffer.buffer[string_buffer.pt++] = 'C';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_D)){
        string_buffer.buffer[string_buffer.pt++] = 'D';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_E)){
        string_buffer.buffer[string_buffer.pt++] = 'E';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_F)){
        string_buffer.buffer[string_buffer.pt++] = 'F';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_G)){
        string_buffer.buffer[string_buffer.pt++] = 'G';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_H)){
        string_buffer.buffer[string_buffer.pt++] = 'H';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_I)){
        string_buffer.buffer[string_buffer.pt++] = 'I';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_J)){
        string_buffer.buffer[string_buffer.pt++] = 'J';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_K)){
        string_buffer.buffer[string_buffer.pt++] = 'K';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_L)){
        string_buffer.buffer[string_buffer.pt++] = 'L';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_M)){
        string_buffer.buffer[string_buffer.pt++] = 'M';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_N)){
        string_buffer.buffer[string_buffer.pt++] = 'N';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_O)){
        string_buffer.buffer[string_buffer.pt++] = 'O';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_P)){
        string_buffer.buffer[string_buffer.pt++] = 'P';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_Q)){
        string_buffer.buffer[string_buffer.pt++] = 'Q';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_R)){
        string_buffer.buffer[string_buffer.pt++] = 'R';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_S)){
        string_buffer.buffer[string_buffer.pt++] = 'S';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_T)){
        string_buffer.buffer[string_buffer.pt++] = 'T';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_U)){
        string_buffer.buffer[string_buffer.pt++] = 'U';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_V)){
        string_buffer.buffer[string_buffer.pt++] = 'V';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_W)){
        string_buffer.buffer[string_buffer.pt++] = 'W';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_X)){
        string_buffer.buffer[string_buffer.pt++] = 'X';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_Y)){
        string_buffer.buffer[string_buffer.pt++] = 'Y';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_Z)){
        string_buffer.buffer[string_buffer.pt++] = 'Z';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_SPACE)){
        string_buffer.buffer[string_buffer.pt++] = ' ';
        string_buffer.buffer[string_buffer.pt] = '\0';
    }

    if(IsKeyPressed(KEY_MINUS)){
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