#include <string.h>
#define _CONST_SUBJECT

#define SIZE_BASE_COMMAND 64

#include "../backend_api.h"

Subject_Pooling subject_pooling = {0};

bype ratio_map[] = {50,60,70};

const char* name_SJ_t[] = {
        "co_so_nganh", "dai_cuong", "the_thao", "ly_luat_chinh_tri", 
        "tu_chon", "thuc_tap", "modunI", "modunII", 
        "modunIII", "modunIV", "modunV", "do_an_tot_nghiep"
};

// command available
const char* command[] = {
    "-c", "-s", "-t","-ac","-backup","restore","reset"
};

typedef enum{
    check,
    setup,
    table,
    acount,
    backup,
    restore,
    reset,
    invalid
}command_index;

int IsPoolEmpty(){
    return subject_pooling.curroffset == 0;
}

void Init_Pool(int16_t size){
    subject_pooling.buffer = (Subject_Payload*) malloc(size * sizeof(Subject_Payload));
    subject_pooling.capacity = size;
    subject_pooling.curroffset = 0;
}

Subject_Payload* Allocate_Pool(const Subject_Payload src){
    if(subject_pooling.curroffset >= subject_pooling.capacity){
        printf("[Alert] Buffer Pooling Subject Payload is full\n");
        return NULL;
    }
    subject_pooling.buffer[subject_pooling.curroffset++] = src;
    return &subject_pooling.buffer[subject_pooling.curroffset-1];
}

int Pop_Pool(Subject_Payload* ret){
    if(IsPoolEmpty()){
        printf("[Alert] Buffer Pooling is Empty\n");
        return 0;
    }

    *ret = subject_pooling.buffer[subject_pooling.curroffset--];
    return 1;
}

int Detroy_Pool(){
    if(subject_pooling.buffer == NULL){
        printf("[Alert] Pooling have not been allocate allocate\n");
        return 0;
    }

    free(subject_pooling.buffer);
    subject_pooling.buffer = NULL;
    subject_pooling.capacity = subject_pooling.curroffset = 0;
    return 1;
}

int Clear_Pool(){
    if(IsPoolEmpty()){
        printf("[Alert] Buffer Pooling is Empty\n");
        return 0;
    }

    subject_pooling.curroffset = 0;
}

int Write_Environment(){
    // standard data date 7/20/2025 referent in table of subject of hanoi university of science and technology,
    // major : Computer Science (IT1)
    // gen : 68 (2023)

    // type define
    typedef struct{
        int x,y,z;
    }pair;

    // Open File For Write
    #ifdef _WIN32
        #include <direct.h>
        _mkdir("file");
        _mkdir("file\\standardFile");
    #else
        #include <sys/stat.h>
        mkdir("file", 0777);
        mkdir("file/standardFile", 0777);
    #endif
    FILE* file = fopen("file/standardFile/standard_data.edbj", "wb");
    if (!file) {
        perror("[Error] Failed to create file");
        return 0;
    }

    printf("[FUNC] Write Standard File Default\n");

    // Init Main Data Storate
    Data_Payload data = (Data_Payload){.capacity_type_subject = sizeSubjectType, .list_type_subject = NULL};
    Subject_Type_Payload list[data.capacity_type_subject];
    for(int i = 0; i < data.capacity_type_subject; i++) list[i].head.term = 99;
    data.list_type_subject = list;

    // Init Name of Type Subject
    for(int i = co_so_nganh; i < sizeSubjectType; i++){
        strncpy(list[i].Subject_Type_Name,name_SJ_t[i],SUBJECT_NAME_SIZE);
    }

    // Init Pooling
    Init_Pool(512);

    #include "macro/const_subject.c"

    
    // write all data to file
    int32_t magic_b = 0x12345678; // using for check endainness
    fwrite(&magic_b,1,4,file);
    fwrite(&data.capacity_type_subject,1,2,file);
    Subject_Payload* curr = NULL;
    bype temp_b = 0x00;
    bype each_size[data.capacity_type_subject];
    memset(each_size,0,data.capacity_type_subject);
    // write n (n = capacity of type subject) for store size of each type subject
    for(int i = 0; i < data.capacity_type_subject ;i++) fwrite(&temp_b,1,1,file);
    for(int i = 0; i < data.capacity_type_subject; i++){
        fwrite(&data.list_type_subject[i].Subject_Type_Name,1,SUBJECT_NAME_SIZE,file);
        curr = &data.list_type_subject[i].head;
        if(curr->term == 99){
            temp_b = 0x00;
            fwrite(&temp_b,1,1,file);
            continue;
        }
        temp_b = 0x0f;
        while(curr){
            fwrite(&temp_b,1,1,file);
            fwrite(&curr->term,1,1,file);
            fwrite(&curr->credit_hour,1,1,file);
            fwrite(&ratio_map[curr->ratio],1,1,file);
            fwrite(curr->SUBJECT_ID,1,SUBJECT_ID_SIZE,file);
            fwrite(curr->SUBJECT_NAME,1,SUBJECT_NAME_SIZE,file);
            each_size[i]++;
            curr = curr->link;
        }
        temp_b = 0x00;
        fwrite(&temp_b,1,1,file);
    }

    fseek(file,6,SEEK_SET); // Set File Pointer to Offset 6 for write size

    // write size of each type 1 bype by 1 type
    for(int i = 0 ; i < data.capacity_type_subject; i++){
        fwrite(&each_size[i],1,1,file);
    }

    // Free Pool
    Detroy_Pool();

    // File close
    fclose(file);

    printf("[FUNC] Completed Write File\n");
    return 1;
}

// check if dont have standard file it's will write it again
int Check_Environment(){
    FILE* file = fopen("file/standardFile/standard_data.edbj", "rb");
    if(file){
        printf("[Alert] File Ok\n");
        fclose(file);
        return 0;
    }
    printf("[Alert] Something wrong with your file\n");
    fclose(file);
    Write_Environment();
    return 1;
}

bype command__$[SIZE_BASE_COMMAND] = {0};
bype count__$ = 0;

void init_register(){
    count__$ = 0;
}

command_index valid_command(const char op[]){
    int str_len = 0;
    for(command_index i = check; i < invalid ; i++){
        str_len = strlen(command[i]);
        str_len = strncmp(op,command[i],str_len);
        if(str_len == 0) return i;
    }
    return invalid;
}

/*
    return:
        -1 for invaild arg
        0  for error
        1  for normaly
*/
int parse_arg(const char* arg){
    /*
        -c for checking ex: check cpa, check not pass subject...
         └── arg: type of check
        -s for set up data: set score
         └── arg: subject-id score-midterm score-midterm
        -t for show table
         └── arg: empty for show all | (comming soon) "filter or sort"
        -ac for login or logout
         ├── arg: type [name]
         └── type: -li [name] (for login), -lo (for logout),-dt (for show detail)
        -backup for back up data
        -restore for restore data
        -reset for reset file data base to default
    */
}

void System_Call_(char* arg,size_t len,ResponseMessage* res){
    init_register();
}