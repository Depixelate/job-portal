#include <string.h>
#include "utils.c"

typedef struct {
    char bachelors[5][25];
    char masters[5][25];
    char phd[5][25];
    char post_doc[5][25];
} LevelsEdu;

typedef struct {
    char title[100];
    char employer_name[100];
    char address[100];
    int salary;
    char start_date[30];
    char end_date[30];
    char other_detals[1000];
} ProjDetail;



typedef struct {
    char name[40];
    int age;
    char gender; //'M' or 'F'
    char email[40];
    char phone_no[15];
    LevelsEdu levelsEdu;
    char cert_names[10][100];
    DictStrInt years_exp;
    ProjDetail proj_details[3];
    char extra_info[1000];
    AppCons desireable_cons;
    AppCons compulsory_cons;
} Seeker;

typedef struct {
    char employer_name[100];
    char title[100];
    int salary;
    char location[100];
    char shift; //'D'(ay), 'N'(ight), 'B'(oth)
    int hours;
    char extra_info[1000];
    EmpCons desireable_cons;
    EmpCons compulsory_cons;
} Opening;

//TODO: Define Constraints.