#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define SUBJECT_NAME_SIZE 64
#define SUBJECT_ID_SIZE 8

typedef unsigned char bype;

typedef struct _Subject_Payload{
    char SUBJECT_ID[SUBJECT_ID_SIZE];                // ID of subject ex: IT3100
    char SUBJECT_NAME[SUBJECT_NAME_SIZE];            // Name of Subject
    bype term;                                       // Term recomment of Subject *** using 99 for make head empty ***
    bype credit_hour;                                // Credit hour of Subject
    bype ratio;                                      // Ratio calculate
    struct _Subject_Payload* link;                   // Link to another subject with same type
}Subject_Payload;

typedef struct{
    Subject_Payload* buffer;                         // Store Heap Memory of Pooling
    int16_t curroffset;                              // Store current pointer 
    int16_t capacity;                                // size of Pool
}Subject_Pooling;

typedef struct{
    char Subject_Type_Name[SUBJECT_NAME_SIZE];       // Name of Subject Type
    Subject_Payload head;                            // Head of Subject
}Subject_Type_Payload;

typedef struct{
    int16_t capacity_type_subject;                   // Size of subject type list
    Subject_Type_Payload* list_type_subject;         // List of subject type
}Data_Payload;

typedef enum{
    INT_T,
    DOUBLE_T,
    STRING_T,
    STRUCT_T,
    NULL_T
}DataType;

typedef struct{
    void* data;                                      // Pointer to raw data
    size_t size;                                     // Size of data
    DataType type;                                   // type of raw data
}ResponseMessage;

// standard data date 7/20/2025 referent in table subject of hanoi university of science and technology,
// major : Computer Science (IT1)
// gen : 68 (2023)
typedef enum {
    co_so_nganh,                                      // Major subject type
    dai_cuong,                                        // General subject type
    the_thao,                                         // Sport subject type
    ly_luat_chinh_tri,                                // Political Theory + General Law subject type
    tu_chon,                                          // Supplementary knowledge block subject type
    thuc_tap,                                         // Intern
    modunI,                                           // Software technology
    modunII,                                          // Information system
    modunIII,                                         // Intelligent data analysis
    modunIV,                                          // Business application development
    modunV,                                           // Smart application development
    do_an_tot_nghiep,                                 // Thesis
    sizeSubjectType
} index_subject_type;

typedef enum{
    rt_50,                                            // 50% Final term calculate
    rt_60,                                            // 60% Final term calculate
    rt_70                                             // 70% Final term calculate
}ratio_subject_t;

/////// Global Variable //////////////////////
extern Subject_Pooling subject_pooling;
extern const char* name_SJ_t[];
extern bype ratio_map[];


/////// POOLING API //////////////////////
int isPoolEmpty();
void Init_Pool(int16_t size);
Subject_Payload* Allocate_Pool(const Subject_Payload src);
int Pop_Pool(Subject_Payload* ret);
int Detroy_Pool();
int Clear_Pool();
/////// Init File API  //////////////////////
int Check_Environment();
int Write_Environment();