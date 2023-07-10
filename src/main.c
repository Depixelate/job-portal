#include "handle_forms.c"
#include "parse_form.c"
#include "form_to_data.c"
#include "input.c"

typedef enum {
    EMPLOYER = 1,
    SEEKER
} UserType;

typedef enum {
    CREATE_FORM = 1,
    GET_RECOMMENDATIONS
} Action;


int main() {
    printf("Welcome to the Job Portal!\n");
    printf("What kind of user are you?\n");
    printf("1. Employer: \n");
    printf("2. Job Seeker: \n");
    UserType user_type = atoi(input("Enter your choice: "));
    printf("What would like to do: \n");
    printf("1. Create New Form: \n");
    printf("2. Get Recommendations: \n");
    Action action = atoi(input("Enter your choice: "));

    if(user_type == EMPLOYER && action == CREATE_FORM) {
	    create_form_copy("example/Job Openings", "example/opening_form.txt");
    } else if(user_type == EMPLOYER && action == GET_RECOMMENDATIONS) {

    } else if(user_type == SEEKER && action == CREATE_FORM) {
        create_form_copy("example/Applicants", "example/seeker_form.txt");
    } else {

    }

    return 0;
}