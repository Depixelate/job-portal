#pragma once
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#define LEN(X) sizeof(X)/sizeof(X[0])

#ifdef _WIN32
#include <string.h>
#define strcasecmp _stricmp
#else // assuming POSIX or BSD compliant system
#include <strings.h>
#endif

// returns pointer to new trimmed str. Note for right trimming we modify the string to add a null terminator at the first right whitespace
const char *l_trim(const char *str) {
    const char *start = str;
    for(;isspace(*start);start+=1){}
    return start;
}

char *mut_r_trim(char *str) {
    char *end = str+strlen(str);
    for(;isspace(*(end-1));end-=1){}
    end[0] = '\0';
    return str;
}

char *mut_trim(char *str) {
    return mut_r_trim(l_trim(str));
}

char *immut_trim(char *buf, const char *str) {
    strcpy(buf, l_trim(str));
    mut_r_trim(buf);
    return buf;
}

bool has_only_spaces(const char *str) {
    for(int i = 0; i < strlen(str); i++) {
        if(!isspace(str[i])) {
            return false;
        }
    }

    return true;
}

void string_utils_test() {
    char buf[100] = "  hi mom, how are you?\t \n";
    char new_buf[100];
    immut_trim(new_buf, buf);
    printf("immut_trim() = \"%s\"\n", new_buf);
    strcpy(buf,mut_trim(buf));
    printf("mut_trim() = \"%s\"\n", buf);
    printf("has_only_spaces(\" \\n \\t \") = %d\n", has_only_spaces(" \n \t "));
    printf("has_only_spaces(\" Hi mother! \") = %d\n", has_only_spaces(" Hi Mother "));
    char new_new_buf[10] = " ";
    printf("mut_trim(\" \") = \"%s\"\n",mut_trim(new_new_buf)); 
}

bool contains(char *strings, int string_length, int num_strings, char *find_string) {
    for(char *string = strings; string - strings < string_length*num_strings; string += string_length) {
        if(strcasecmp(string, find_string) == 0) {
            return true;
        }
    }
    return false;
}

void contains_test() {
    char strings[10][15] = {"Hi", "Hello", "What's for lunch?"};
    printf("%d %d %d\n", LEN(strings), LEN(strings[0]), contains(strings[0], LEN(strings), LEN(strings[0]), "hii"));
}

void main() {
    contains_test();
}

// void main() {
//     string_utils_test();
// }