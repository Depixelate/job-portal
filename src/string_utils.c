#pragma once
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

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

// void main() {
//     string_utils_test();
// }