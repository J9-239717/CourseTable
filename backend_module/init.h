#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
    Data_Payload data = (Data_Payload){.capacity_type_subject = sizeSubjectType, .list_type_subject = NULL};
    Subject_Type_Payload list[data.capacity_type_subject] = {0};
    data.list_type_subject = list;
    for(int i = co_so_nganh; i < sizeSubjectType; i++){
        strncpy(list[i].Subject_Type_Name,name_SJ_t[i],SUBJECT_NAME_SIZE);
    }


    typedef struct{
        int x,y,z;
    }pair;
    {
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
    }
}