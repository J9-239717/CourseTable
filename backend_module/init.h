#include <string.h>
#include "format.h"

// check if dont have standard file it's will write it again
void Check_Environment(){
    FILE* file = fopen("file/standardFile/standard_data.edbj", "rb");
    if(file){
        printf("File Ok\n");
        return;
    }

}

void Write_Environment(){
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
        return;
    }

    // Init Main Data Storate
    Data_Payload data = (Data_Payload){.capacity_type_subject = sizeSubjectType, .list_type_subject = NULL};
    Subject_Type_Payload list[data.capacity_type_subject];
    for(int i = 0; i < data.capacity_type_subject; i++) list[i].head.term = 0;
    data.list_type_subject = list;

    // Init Name of Type Subject
    for(int i = co_so_nganh; i < sizeSubjectType; i++){
        strncpy(list[i].Subject_Type_Name,name_SJ_t[i],SUBJECT_NAME_SIZE);
    }

    // Init Pooling
    Init_Pool(256);

    {
        // co so nganh
        pair arr[] = {
            {1,3,rt_50},
            {2,2,rt_60},
            {3,3,rt_70},
            {4,2,rt_60},
            {4,3,rt_60},
            {4,3,rt_50},
            {5,3,rt_50},
            {3,2,rt_70},
            {6,2,rt_60},
            {5,2,rt_50},
            {4,3,rt_60},
            {5,2,rt_60},
            {5,3,rt_60},
            {5,3,rt_60},
            {6,2,rt_50},
            {7,3,rt_50},
            {6,3,rt_60},
            {8,2,rt_60},
            {6,2,rt_50},
        };
        char* name[] = {
            "Introduction to IT and Communications",
            "Data Structures and Algorithms",
            "Computer Architecture",
            "Programming Techniques",
            "Principles of Operating Systems",
            "Computer Networks",
            "Database Systems",
            "Object-Oriented Programming",
            "System Analysis and Design",
            "Project I",
            "Introduction to Artificial Intelligence",
            "Applied Algorithms",
            "Introduction to Software Engineering",
            "Introduction to Machine Learning and Data Mining",
            "Project II",
            "Project III",
            "Introduction to Information Security",
            "IT Project Management",
            "Deep Learning and Its Applications"
        };
        char* ID[] = {
            "IT2000",
            "IT3011",
            "IT3030",
            "IT3040",
            "IT3070",
            "IT3080",
            "IT3090",
            "IT3100",
            "IT3120",
            "IT3150",
            "IT3160",
            "IT3170",
            "IT3180",
            "IT3190",
            "IT3930",
            "IT3940",
            "IT4015",
            "IT4244",
            "IT4653"
        };
        int size = sizeof(arr) / sizeof(arr[0]);

        Subject_Payload *curr = NULL, *temp = NULL;
        temp = Allocate_Pool(
            (Subject_Payload){
                .term = arr[0].x,
                .credit_hour = arr[0].y,
                .ratio = arr[0].z,
                .link = NULL
            }
        );
        strncpy(temp->SUBJECT_ID,ID[0],SUBJECT_ID_SIZE);
        strncpy(temp->SUBJECT_NAME,name[0],SUBJECT_NAME_SIZE);
        list[co_so_nganh].head = *temp;
        curr = &list[co_so_nganh].head;
        for(int i = 1; i < size; i++){
            temp = Allocate_Pool(
                (Subject_Payload){
                    .term = arr[i].x,
                    .credit_hour = arr[i].y,
                    .ratio = arr[i].z,
                    .link = NULL
                }
            );
            strncpy(temp->SUBJECT_ID,ID[i],SUBJECT_ID_SIZE);
            strncpy(temp->SUBJECT_NAME,name[i],SUBJECT_NAME_SIZE);

            curr->link = temp;
            curr = curr->link;
        }
    }

    // write all data to file
    int32_t magic_b = 0x12345678; // using for check endainness
    fwrite(&magic_b,1,4,file);
    fwrite(&data.capacity_type_subject,1,2,file);
    Subject_Payload* curr = NULL;
    bype temp_b = 0x00;
    for(int i = 0; i < data.capacity_type_subject; i++){
        fwrite(&data.list_type_subject[i].Subject_Type_Name,1,SUBJECT_NAME_SIZE,file);
        curr = &data.list_type_subject[i].head;
        if(curr->term == 0){
            temp_b = 0x00;
            fwrite(&temp_b,1,1,file);
            continue;
        }
        temp_b = 0x0f;
        while(curr){
            fwrite(&temp_b,1,1,file);
            fwrite(&curr->term,1,1,file);
            fwrite(&curr->credit_hour,1,1,file);
            fwrite(&curr->ratio,1,1,file);
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
}