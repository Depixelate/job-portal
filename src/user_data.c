#include <string.h>
#include "utils.c"

#define MAX_TITLE_LENGTH 50
#define MAX_TITLES 20
#define MAX_LOC 5
#define MAX_LOCATION_LENGTH 20

typedef struct{
	int min_sal;		//this is score for min sal
	int score;
}MinSalaryCons;

typedef struct{
	int work_hours;		//this is score for working hours
	int score;
}MaxHours;

typedef struct{
	char shift;		//this is score for day or night shift
	int score;
}ShiftCons;

typedef struct{
    char titles[MAX_TITLES][MAX_TITLE_LENGTH];
    int len;
}Titles;

typedef struct{
	Titles titles;
	int score;
}TitlesCons;

typedef struct{
    char loc[MAX_LOC][MAX_LOCATION_LENGTH];	
    int len;
}Locs;

typedef struct{
	Locs locs;
	int score;
}LocCons;



typedef struct{
	TitlesCons titles;
	MinSalaryCons min_sal;
	ShiftCons shift;
	LocCons prefferred_location;
	MaxHours max_hours;
}AppCons;


#define MAX_MAJORS 5
#define MAX_MAJOR_LENGTH 50
#define NUM_CERT_LISTS 3
#define MAX_CERT_LIST_LENGTH 100 
#define MAX_CERT_LENGTH MAX_MAJOR_LENGTH

typedef struct {
    int max_age;
    int score;
} MaxAgeCon;

typedef struct {
    char majors[MAX_MAJORS][MAX_MAJOR_LENGTH];
    int len;
} Majors;

typedef struct {
    Majors majors;
    int score;
} MinEduLvl;

typedef struct {
    MinEduLvl bachelors, masters, phd, post_doc;
} MinEduCon;

typedef struct {
    char certs[MAX_CERT_LIST_LENGTH][MAX_CERT_LENGTH];
    int len;
} Certs;

typedef struct {
    Certs certs;
    int score;
} EqCerts;

typedef struct {
    EqCerts cert_lists[NUM_CERT_LISTS];
} CertCon;

typedef struct {
    DictStrInt field_years_exp;
    int score;
} ExpCon;

typedef struct {
    int max_age;
    int score;
} MaxAgeCon;

typedef struct {
    MaxAgeCon max_age;
    MinEduCon min_edu;
    CertCon cert_lists;
    ExpCon years_exp;
} EmpCons;
//TODO: Define Constraints.

typedef struct {
    Majors bachelors, masters, phd, post_doc;
} LevelsEdu;

typedef struct {
    char title[100];
    char employer_name[100];
    char address[100];
    int salary;
    char start_date[30];
    char end_date[30];
    char other_details[1000];
} ProjDetail;


#define MAX_MAJOR_LENGTH 50
#define NUM_CERTS_LISTS 3
#define MAX_CERT_LIST_LENGTH 100 
#define MAX_CERT_LENGTH MAX_MAJOR_LENGTH

typedef struct {
    char majors[MAX_MAJORS][MAX_MAJOR_LENGTH];
    int score;
} MinEduLvl;

typedef struct {
    MinEduLvl bach, mast, phd, post;
} MinEduCon;

typedef struct {
    char certs[MAX_CERT_LIST_LENGTH][MAX_CERT_LENGTH];
    int score;
} EqCerts;

typedef struct {
    EqCerts cert_lists[NUM_CERT_LISTS];
} CertCon;

typedef struct {
    DictStrInt field_years_exp;
    int score;
} ExpCon;

typedef struct {
    MaxAgeCon max_age;
    MinEduCon min_edu;
    CertCon cert_lists;
    ExpCon years_exp;
} EmpCons;

typedef struct {
    char name[40];
    int age;
    char gender; //'M' or 'F'#define MAX_MAJORS 5
    char email[40];
    char phone_no[15];
    LevelsEdu levelsEdu;
    Certs certs;
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