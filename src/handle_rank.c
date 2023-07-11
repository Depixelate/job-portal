#pragma once
#include "handle_forms.c"
#include "user_data.c"
#include "rank.c"

void get_good_form_path(char *index_path, char good_form_path[]){
	char form_names[MAX_LINES][MAX_LENGTH];
	int num_forms;
	read_index(index_path, form_names, &num_forms);
	char form_name[MAX_LENGTH];
	while (true) {
		bool is_valid_name = false;
		printf("Enter your form's name: ");
		fgets(form_name, MAX_LENGTH, stdin);
		form_name[strlen(form_name)-1] = '\0';
				
		for(int i = 0; i < num_forms; i++) {
			if(strcmp(form_name, form_names[i]) == 0) {
                is_valid_name = true;
				break;
			} 
		}
		if(is_valid_name) {
			break;
		} else {
			printf("Form name doesn't exist! Try again!\n");
		}
	}
	index_to_path(index_path, form_name, good_form_path);
}

void get_good_form_path_test() {
	char buf[100];
	printf("Application\n");
	get_good_form_path("example/Applicants/index.txt", buf);
	printf("%s\n", buf);
	printf("Opening\n");
	get_good_form_path("example/Job Openings/index.txt", buf);
	printf("%s\n", buf);
}

void get_form(char *path, DictStrQ *form) {
    char lines[MAX_LINES][MAX_LENGTH];
    int num_lines = 0;
    read_index(path, lines, &num_lines);
    DictStrQ form;
    dict_str_q_init(&form);
    parse_form(path, lines, num_lines, &form);
}


void get_opening(char *path, Opening *opening) {
    DictStrQ form;
    get_form(path, &form);
    form_to_opening(&form, opening);
}


void get_seeker(char *path, Seeker *seeker) {
    DictStrQ form;
    get_form(path, &form);
    form_to_seeker(&form, seeker);
}

void get_paths(char *index_path, char paths[MAX_OPENINGS][PATH_LEN], int *num_paths) {
    read_index(index_path, paths, num_paths);
    for(int i = 0; i < *num_paths; i++) {
        char buf[100];
        strcpy(buf, paths[i]);
        index_to_path(index_path, buf, paths[i]);
    }
}

//returns single seeker referred to by path, and all openings as structs
void get_seeker_and_openings(char *seeker_path, Seeker *seeker, Opening openings[], int *len) {
    char form_paths[MAX_OPENINGS][PATH_LEN];
    get_paths("example/Job Openings/index.txt", form_paths, len);
    get_seeker(seeker_path, seeker);
    for(int i = 0; i < *len; i++) {
        get_opening(form_paths[i], &openings[i]);
    }
}

void get_opening_and_seekers(char *opening_path, Opening *opening, Seeker seekers[], int *len) {
    char form_paths[MAX_OPENINGS][PATH_LEN];
    get_paths("example/Applicants/index.txt", form_paths, len);
    get_opening(opening_path, opening);
    for(int i = 0; i < *len; i++) {
        get_seeker(form_paths[i], &seekers[i]);
    }
}

void handle_seekers() {
    char path[PATH_LEN];
	get_good_form_path("example/Applicants/index.txt", path);
    Seeker seeker = {0};
    Opening openings[MAX_OPENINGS] = {0};
    int len = 0;
    get_seeker_and_openings(path, &seeker, openings, &len);
    rank_job_openings(&seeker, openings, len);
}

void handle_openings() {
    char path[PATH_LEN];
	get_good_form_path("example/Job Openings/index.txt", path);
    Opening opening = {0};
    Seeker seekers[MAX_SEEKERS] = {0};
    int len = 0;
    get_opening_and_seekers(path, &opening, seekers, &len);
    rank_seekers(&opening, seekers, len);
}