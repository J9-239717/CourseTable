#ifdef _CONST_SUBJECT

// general subject
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
{
    pair arr[] = {
        {1,4,rt_50},
        {2,3,rt_50},
        {1,4,rt_50},
        {2,3,rt_50},
        {3,3,rt_50},
        {1,4,rt_50},
        {3,3,rt_50},
        {3,2,rt_50},
        {2,3,rt_70},
        {3,3,rt_70},
    };

    char* ID[] = {
        "IT1108",
        "IT3020",
        "MI1111",
        "MI1121",
        "MI1131",
        "MI1141",
        "MI2020",
        "MI3052",
        "PH1110",
        "PH1120"
    };

    char* name[] = {
        "Introduction to Programming",
        "Discrete Mathematics",
        "Calculus I",
        "Calculus II",
        "Calculus III",
        "Algebra",
        "Probability and Statistics",
        "Introduction to Optimization Methods",
        "General Physics I",
        "General Physics II"
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
    list[dai_cuong].head = *temp;
    curr = &list[dai_cuong].head;
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
{
    pair arr[] = {
        {1,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
        {0,0,rt_50},
    };

    char* ID[] = {
        "PE1014",
        "PE1015",
        "PE1024",
        "PE2101",
        "PE2102",
        "PE2103",
        "PE2151",
        "PE2201",
        "PE2202",
        "PE2203",
        "PE2251",
        "PE2252",
        "PE2253",
        "PE2261",
        "PE2301",
        "PE2302",
        "PE2303",
        "PE2401",
        "PE2402",
        "PE2403",
        "PE2501",
        "PE2502",
        "PE2503",
        "PE2601",
        "PE2701",
        "PE2801",
        "PE2901",
        "PE3101",
        "PE3102",
        "PE3103",
        "PE3104",
        "PE3105",
        "PE3201",
        "PE3202",
        "PE3203",
        "PE3204",
        "PE3205",
        "PE3301",
        "PE3302",
        "PE3303",
        "PE3304",
        "PE3305",
    };

    char* name [] = {
        "Theoretical Physical Education and Sports",
        "Freehand Gymnastics",
        "Swimming",
        "Volleyball 1",
        "Volleyball 2",
        "Volleyball 3",
        "Aerobics",
        "Football 1",
        "Football 2",
        "Football 3",
        "Taekwondo 1",
        "Taekwondo 2",
        "Taekwondo 3",
        "Karate",
        "Basketball 1",
        "Basketball 2",
        "Basketball 3",
        "Table Tennis 1",
        "Table Tennis 2",
        "Table Tennis 3",
        "Badminton 1",
        "Badminton 2",
        "Badminton 3",
        "Running",
        "High Jump",
        "Long Jump",
        "Parallel Bars, Uneven Bars",
        "Advanced Volleyball 1",
        "Advanced Volleyball 2",
        "Advanced Volleyball 3",
        "Advanced Volleyball 4",
        "Advanced Volleyball 5",
        "Advanced Football 1",
        "Advanced Football 2",
        "Advanced Football 3",
        "Advanced Football 4",
        "Advanced Football 5",
        "Advanced Basketball 1",
        "Advanced Basketball 2",
        "Advanced Basketball 3",
        "Advanced Basketball 4",
        "Advanced Basketball 5",
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
    list[the_thao].head = *temp;
    curr = &list[the_thao].head;
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
{
    pair arr[] = {
        {2,2,rt_50},
        {3,3,rt_50},
        {4,2,rt_50},
        {5,2,rt_50},
        {6,2,rt_50},
        {7,2,rt_50}
    };
    char* ID[] = {
        "EM1170",
        "SSH1111",
        "SSH1121",
        "SSH1131",
        "SSH1141",
        "SSH1151"
    };
    char* name[] = {
        "General Law",
        "Marxist-Leninist Philosophy",
        "Marxist-Leninist Political Economy",
        "Scientific Socialism",
        "History of the Communist Party of Vietnam",
        "Ho Chi Minh's Ideology"
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
    list[ly_luat_chinh_tri].head = *temp;
    curr = &list[ly_luat_chinh_tri].head;
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
{
    // co so nganh
    pair arr[] = {
        {0,2,rt_50},
        {0,2,rt_70},
        {0,2,rt_70},
        {0,2,rt_50},
        {0,2,rt_50},
        {0,2,rt_60},
        {4,3,rt_50},
        {0,2,rt_50},
        {0,2,rt_50},
        {0,2,rt_50}
    };
    char* ID[] = {
        "CH2021",
        "ED3220",
        "ED3280",
        "EM1010",
        "EM1180",
        "ET3262",
        "IT2030",
        "ME3123",
        "ME3124",
        "TEX3123"
    };
    char* name[] = {
        "Innovation and Entrepreneurship",
        "Soft Skills",
        "Applied Psychology",
        "General Management",
        "Business Culture and Entrepreneurial Spirit",
        "Technological Thinking and Engineering Design",
        "Technical Writing and Presentation",
        "Industrial Art Design",
        "Product Promotion Design",
        "Industrial Art Design"
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
    list[tu_chon].head = *temp;
    curr = &list[tu_chon].head;
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
{
    // co so nganh
    pair arr[] = {
        {6,2,rt_50}
    };
    char* name[] = {
        "Technical Internship"
    };
    char* ID[] = {
        "IT4991"
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
    list[thuc_tap].head = *temp;
    curr = &list[thuc_tap].head;
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
{
    // co so nganh
    pair arr[] = {
        {7, 3, rt_60},
        {7, 3, rt_50},
        {7, 2, rt_60},
        {7, 2, rt_60}
    };
    char* name[] = {
        "User Interface and User Experience",
        "Software Design and Construction",
        "Software Quality Assurance",
        "Mobile Application Development"
    };
    char* ID[] = {
        "IT4441",
        "IT4490",
        "IT4501",
        "IT4785"
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
    list[modunI].head = *temp;
    curr = &list[modunI].head;
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
{
    // co so nganh
    pair arr[] = {
        {7, 2, rt_60},
        {7, 3, rt_60},
        {7, 2, rt_60},
        {7, 3, rt_70}
    };
    char* name[] = {
        "Decision Support Systems",
        "Information Systems Architecture and Applications",
        "Distributed Systems and Applications",
        "Information Retrieval"
    };
    char* ID[] = {
        "IT4341",
        "IT4350",
        "IT4611",
        "IT4863"
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
    list[modunII].head = *temp;
    curr = &list[modunII].head;
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
{
    // co so nganh
    pair arr[] = {
        {7, 2, rt_50},
        {7, 3, rt_70},
        {7, 2, rt_60},
        {7, 3, rt_60}
    };
    char* name[] = {
        "Deep Learning and Applications",
        "Evolutionary Computing",
        "Introduction to Data Science",
        "Big Data Storage and Processing"
    };
    char* ID[] = {
        "IT4653",
        "IT4906",
        "IT4930",
        "IT4931"
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
    list[modunIII].head = *temp;
    curr = &list[modunIII].head;
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
{
    // co so nganh
    pair arr[] = {
        {6, 3, rt_60},
        {7, 3, rt_60}
    };
    char* name[] = {
        "Web Technology and Online Services",
        "Cross-Platform Application Development"
    };
    char* ID[] = {
        "IT4409",
        "IT4788"
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
    list[modunIV].head = *temp;
    curr = &list[modunIV].head;
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
{
    // co so nganh
    pair arr[] = {
        {7, 3, rt_50},
        {6, 3, rt_50}
    };
    char* name[] = {
        "Recommender Systems",
        "Optimization and Planning"
    };
    char* ID[] = {
        "IT4613",
        "IT4663"
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
    list[modunV].head = *temp;
    curr = &list[modunV].head;
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
{
    // co so nganh
    pair arr[] = {
        {8, 6, rt_50}
    };
    char* name[] = {
        "Bachelor's Graduation Project"
    };
    char* ID[] = {
        "IT4995"
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
    list[do_an_tot_nghiep].head = *temp;
    curr = &list[do_an_tot_nghiep].head;
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

#endif