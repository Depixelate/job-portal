#pragma once
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "form_types.c"

void read_index(char *file_name, char buf[][MAX_LENGTH], int *num_lines) {
    FILE *file;
    *num_lines = 0;
    
    // Open the file
    file = NULL;
	while(file == NULL) {
		file = fopen(file_name, "r");
	}
	

    
    // Read lines from the file and store them in the array
    while (fgets(buf[*num_lines], MAX_LENGTH, file) != NULL) {
		char *line = buf[*num_lines];
		int len = strlen(line);
		if(line[len-1] == '\n') {
			line[len-1] = '\0';
		}
        (*num_lines)++;
    }
    
    // Close the file
    fclose(file);
}

void read_index_test() {
	char lines[MAX_LINES][MAX_LENGTH];
	int num_lines;
	read_index("example/seeker_form.txt", lines, &num_lines);
	for(int i = 0; i < num_lines; i++) {
		printf("%s", lines[i]);
	}
}

// void main() {
// 	read_index_test();
// }

void read(const char *path, char *file_buf) {
	FILE *fp = fopen(path, "r");
	file_buf[0] = '\0';
	char *end = file_buf;
	while(fgets(end, 4096, fp) != NULL) {
		end = file_buf + strlen(file_buf);
	}
	fclose(fp);
}

void read_test() {
	char form[MAX_LENGTH*MAX_LINES];
	read("example/opening_form.txt", form);
	printf("%s", form);
	fflush(stdout);
}

void write(const char *path, const char *file_content) {
	FILE *fp = fopen(path,"w");
	if (fp==NULL)
		printf("Error at Write Module: couldn't open file.");
	fputs(file_content, fp);	
	fclose(fp);
}

void write_test() {
    char path[100]="test.txt",file_content[100]="Hey, How are you";
	char buf[100];
    write (path,file_content);
	read(path, buf);
	assert(strcmp(buf, file_content) == 0);
}

// TODO: read test

/*
void main() {
	write_test();
}
*/


void get_good_form_name(char *path, char good_form_name[]){
	char form_names[MAX_LINES][MAX_LENGTH];
	int num_forms;
	read_index(path, form_names, &num_forms);
	char form_name[MAX_LENGTH];
	while (true) {
		bool is_valid_name = true;
		printf("Enter your form's name: ");
		fgets(form_name, MAX_LENGTH, stdin);
		form_name[strlen(form_name)-1] = '\0';
				
		for(int i = 0; i < num_forms; i++) {
			if(strcmp(form_name, form_names[i]) == 0) {
				printf("Form name already taken! Try again!\n");
                is_valid_name = false;
				break;
			} 
		}
		if(is_valid_name) {
			break;
		}
	}
	strcpy(good_form_name, form_name);
}

void get_good_form_name_test() {
	char buf[100];
	printf("Application\n");
	get_good_form_name("example/Applicants/index.txt", buf);
	printf("%s\n", buf);
	printf("Opening\n");
	get_good_form_name("example/Job Openings/index.txt", buf);
	printf("%s\n", buf);
}


void get_good_form_path(char *path, char good_form_path[]){
	char form_names[MAX_LINES][MAX_LENGTH];
	int num_forms;
	read_index(path, form_names, &num_forms);
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
	char *last_slash = strrchr(path, '/') + 1;
	int num_chars = last_slash - path;
	strncpy(good_form_path, path, num_chars);
	good_form_path[num_chars] = '\0';
	strcat(strcat(good_form_path, form_name), ".txt");
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

// void main() {
// 	get_good_form_path_test();
// }


// creates a copy of the form specified by form_path, in the directory specified by directory
void create_form_copy(char *directory, char *form_path) {
	char good_form_name[MAX_LENGTH];
	char index_path[MAX_LENGTH];
	strcpy(index_path, directory);
	get_good_form_name(strcat(index_path,"/index.txt"), good_form_name);
	char form_text[MAX_LENGTH*MAX_LINES];
	read(form_path, form_text);
	char new_form_path[MAX_LENGTH];
	strcpy(new_form_path, directory);
	strcat(strcat(strcat(new_form_path, "/"), good_form_name), ".txt");
	write(new_form_path, form_text);
	FILE *fp = fopen(index_path, "a");
	fprintf(fp, "%s\n", good_form_name);
	fclose(fp);
}

void create_form_test() {
	printf("Application\n");
	create_form_copy("example/Applicants", "example/seeker_form.txt");
	printf("Opening\n");
	create_form_copy("example/Job Openings", "example/opening_form.txt");
}

// void main() {
// 	create_form_test();
// }


