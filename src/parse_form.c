// Check for newline, then check for %d.%d.%d., then read everything upto colon, then read rest of text as key-value pairs until newline %d.%d.%d.%d.

#include <string.h>
#include <ctype.h>
#include "form_types.c"

#define MAX_LINES 200
#define MAX_LENGTH 200

bool is_q_begin(char *line, char *q_num, int *question_index) {
    int tot_chars_read = 0;
    while(true) {
        int chars_read = 0;
        sscanf(line+tot_chars_read, "%[0123456789].%n", q_num + tot_chars_read, &chars_read);
        if(chars_read == 0) {
            if(tot_chars_read != 0 && isspace(line[tot_chars_read+1])) {
                return true;
            } else {
                return false;
            }
        } else {
            tot_chars_read += chars_read;
        }
    }
}

typedef enum {
    READ_QUESTION,
    READ_RESPONSE
} Mode;

void parse_form(char lines[MAX_LINES][MAX_LENGTH], int num_lines, DictStrQ *form) {
    Mode cur_mode = READ_RESPONSE;
    Question *cur_question = NULL;
    int cur_line = 0;
    int cur_line_index = 0;
    while(cur_line < num_lines) {
        char new_q_num[MAX_QNO_CHARS] = "";
        if(cur_mode == READ_RESPONSE) {
            if(cur_line_index == 0 && is_q_begin(lines[cur_line], new_q_num, cur_line_index)) {
                cur_question = dict_str_q_new_ptr(form, new_q_num);
                strcpy(cur_question->number, new_q_num);
                cur_mode = READ_QUESTION;
            } else {
                char *key, *value;
                dict_str_str_next_ptrs(&(cur_question->response), &key, &value);
                sscanf(lines[cur_line] + cur_line_index, "%[^:]:%[^\n]", cur_question->response, key, value);
                cur_line += 1;
                cur_line_index = 0;
            }
        } else if(cur_mode == READ_QUESTION) {
            char *prompt = cur_question->prompt + strlen(cur_question->prompt);
            int num_chars_read = 0;
            sscanf(lines[cur_line] + cur_line_index, "%[^:]:%n", prompt, &num_chars_read);
            if(num_chars_read == 0) { //no colon
                cur_line_index = 0;
                cur_line += 1;
            } else { // there was a colon
                cur_line_index += num_chars_read;
                cur_mode = READ_RESPONSE;
            }
        }
    }
}