#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINES 300
#define MAX_LENGTH 300

void read_index(char *file_name, char buf[][MAX_LENGTH], int *num_lines) {
    FILE *file;
    *num_lines = 0;
    
    // Open the file
    file = fopen(file_name, "r");

    
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
	file_buf = "";
	char *end = file_buf;
	while(fgets(end, 4096, fp) != NULL) {
		end = file_buf + strlen(file_buf);
	}
	fclose(fp);
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
				printf("Invalid form name! Try again!\n");
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

void get_good_form_name_rec(char *path, char good_form_name[]){
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
			printf("Invalid form name! Try again!\n");
		}
	}
	strcpy(good_form_name, form_name);
}

void get_good_form_name_test_rec() {
	char buf[100];
	printf("Application\n");
	get_good_form_name_rec("example/Applicants/index.txt", buf);
	printf("%s\n", buf);
	printf("Opening\n");
	get_good_form_name_rec("example/Job Openings/index.txt", buf);
	printf("%s\n", buf);
}

// void main() {
// 	get_good_form_name_test_rec();
// }

