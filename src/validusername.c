#include<stdio.h>
#include<string.h>
#include<stdbool.h>
void get_good_form_name(char *path, char good_form_name[]){
	char *str;
	char formnames[100][100];
	int num_forms = read_index(path, formnames);
	char formname[100];
	while (true) {
		bool is_valid_name = true;
		printf("Enter your form's name: ");
		fgets(formname, 100, stdin);
				
		for(int i = 0; i < num_forms; i++) {
			if(strcmp(formname, formnames[i]) == 0) {
				printf("Invalid form name! Try again!\n");
                                is_valid_name = false;
				break;
			} 
		}
		if(!is_valid_name) {
			break;
		}
	}
	strcpy(good_form_name, formname);
}

