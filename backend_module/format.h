#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define SUBJECT_NAME_SIZE 64
#define SUBJECT_ID_SIZE 8

typedef unsigned char bype;

typedef struct _Subject_Payload{
    char SUBJECT_ID[SUBJECT_ID_SIZE];                // ID of subject ex: IT3100
    char SUBJECT_NAME[SUBJECT_NAME_SIZE];            // Name of Subject
    bype term;                                       // Term recomment of Subject *** using 0 for make head empty ***
    bype credit_hour;                                // Credit hour of Subject
    bype ratio;                                      // Ratio calculate
    struct _Subject_Payload* link;                   // Link to another subject with same type
}Subject_Payload;

typedef struct{
    Subject_Payload* buffer;
    int16_t curroffset;
    int16_t capacity;
}Subject_Pooling;

Subject_Pooling subject_pooling = {0};

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

typedef struct{
    char Subject_Type_Name[SUBJECT_NAME_SIZE];       // Name of Subject Type
    Subject_Payload head;                            // Head of Subject
}Subject_Type_Payload;

typedef struct{
    int16_t capacity_type_subject;                   // Size of subject type list
    Subject_Type_Payload* list_type_subject;         // List of subject type
}Data_Payload;

// standard data date 7/20/2025 referent in table of subject of hanoi university of science and technology,
// major : Computer Science (IT1)
// gen : 68 (2023)
typedef enum {
    co_so_nganh,
    dai_cuong,
    the_thao,
    ly_luat_chinh_tri,
    tu_chon,
    thuc_tap,
    modunI,
    modunII,
    modunIII,
    modunIV,
    modunV,
    do_an_tot_nghiep,
    sizeSubjectType
} index_subject_type;

typedef enum{
    rt_50,
    rt_60,
    rt_70 
}ratio_subject_t;

const char* name_SJ_t[] = {
        "co_so_nganh", "dai_cuong", "the_thao", "ly_luat_chinh_tri", 
        "tu_chon", "thuc_tap", "modunI", "modunII", 
        "modunIII", "modunIV", "modunV", "do_an_tot_nghiep"
};

void Check_Environment();
void Write_Environment();