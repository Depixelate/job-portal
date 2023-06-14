#include<stdio.h>

void write(char *path,char *filecontent){
     
	FILE *ptr;
	ptr=fopen(path,"w");
	if (ptr==NULL)
		printf("Error at Write Module: couldn't open file.");
	fputs(filecontent,ptr);	
}

void main(){
    char path[100]="/home/sel-22/vignesh/test.txt",filecontent[100]="hi how r u i m fine wht abt u  i here to sperw :";
    write (path,filecontent);
}
