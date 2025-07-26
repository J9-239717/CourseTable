#include <string.h>
#define _CONST_SUBJECT

#include "../backend_api.h"

Subject_Pooling subject_pooling = {0};

bype ratio_map[] = {50,60,70};

const char* name_SJ_t[] = {
        "co_so_nganh", "dai_cuong", "the_thao", "ly_luat_chinh_tri", 
        "tu_chon", "thuc_tap", "modunI", "modunII", 
        "modunIII", "modunIV", "modunV", "do_an_tot_nghiep"
};

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
            curr = curr->link;
        }
        temp_b = 0x00;
        fwrite(&temp_b,1,1,file);
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
