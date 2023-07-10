// Check for newline, then check for %d.%d.%d., then read everything upto colon, then read rest of text as key-value pairs until newline %d.%d.%d.%d.
#pragma once

#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "form_types.c"
#include "handle_forms.c"
#include "string_utils.c"

/* returns whether the beginning of a line matches a question number, and if so returns the question number and index of the beginning of the prompt */ 

typedef struct {
    char (*lines)[MAX_LENGTH];
    Question *cur_question;
    int cur_line;
    int cur_line_index;
    DictStrQ *form;
} State;

bool is_q_begin(char *line, char *q_num, int *question_index) {
    int tot_chars_read = 0;
    q_num[0] = '\0';
    while(true) {

        int chars_read = -1;

        char *cur_str_pos = line + tot_chars_read;
        char *cur_q_num_pos = q_num + tot_chars_read;

        sscanf(cur_str_pos, "%[0123456789].%n", cur_q_num_pos, &chars_read); // Check if it matches question number format

        bool rest_not_qnum = (chars_read == -1);

        if(rest_not_qnum) {
            break;
        }

        strcat(cur_q_num_pos, ".");

        tot_chars_read += chars_read;
    }

    bool qnum_not_empty = tot_chars_read != 0;
    bool whitespace_after_valid = isspace(line[tot_chars_read]);
    if(qnum_not_empty && whitespace_after_valid) {
        *question_index = tot_chars_read+1; // question starts after space following question number
        return true;
    }

    return false;
}

typedef enum {
    READ_QUESTION,
    READ_RESPONSE
} Mode;

void to_next_line(State *s) {
    s->cur_line += 1;
    s->cur_line_index = 0;
}

Mode parse_response(State *s) {
    char new_q_num[MAX_QNO_CHARS];
    if(s->cur_line_index == 0 && is_q_begin(s->lines[s->cur_line], new_q_num, &s->cur_line_index)) {
        s->cur_question = dict_str_q_new_ptr(s->form, new_q_num);
        strcpy(s->cur_question->number, new_q_num);
        s->cur_question->prompt[0] = '\0';
        return READ_QUESTION;
    } 

    char key[MAX_KEY_LEN] = "", value[MAX_VAL_STR_LEN] = "";
    //dict_str_str_next_ptrs(&(s->cur_question->response), &key, &value);
    sscanf(s->lines[s->cur_line] + s->cur_line_index, "%[^:]:%[^\n]", key, value);

    if(!has_only_spaces(key)) {
        dict_str_str_add(&(s->cur_question->response), mut_trim(key), mut_trim(value));
    }

    to_next_line(s);    

    return READ_RESPONSE;
}

Mode parse_question(State *s) {
    char *cur_pos_prompt = s->cur_question->prompt + strlen(s->cur_question->prompt);
    int num_chars_read = -1;
    char *cur_pos_line = s->lines[s->cur_line] + s->cur_line_index;
    sscanf(cur_pos_line, "%[^:]:%n", cur_pos_prompt, &num_chars_read);

    if(num_chars_read != -1) { // colon
        s->cur_line_index += num_chars_read;
        strcpy(s->cur_question->prompt, mut_trim(s->cur_question->prompt));
        return READ_RESPONSE;
    }

    char *prompt_end = cur_pos_prompt + num_chars_read;
    prompt_end[1] = '\0';
    prompt_end[0] = '\n';
    
    to_next_line(s);

    return READ_QUESTION;
}

/* takes lines of form, returns a dictionary with question numbers as keys and the questions as values */
void parse_form(char path[100], char lines[MAX_LINES][MAX_LENGTH], int num_lines, DictStrQ *form) {
    dict_str_q_init(form);
    Question path_q = {.number = "0.", .prompt = "Path", .response = {0}};
    dict_str_str_init(&path_q.response);
    dict_str_str_add(&path_q.response, path, "");
    dict_str_q_add(form, "0.", &path_q);
    char q_num[MAX_QNO_CHARS];
    int temp;

    if(!is_q_begin(lines[0], q_num, &temp)) {
        printf("Error! Invalid Form given to parse_form!\n");
        return;
    }

    Mode cur_mode = READ_RESPONSE;
    State s = {.lines = lines, .cur_question = NULL, .cur_line = 0, .cur_line_index = 0, .form = form};

    while(s.cur_line < num_lines) {
        switch(cur_mode) {
            case READ_RESPONSE:
                cur_mode = parse_response(&s);
                break;

            case READ_QUESTION:
                cur_mode = parse_question(&s);
                break;
        }
    }
}

void parse_form_test() {
    char lines[MAX_LINES][MAX_LENGTH];
    int num_lines;
    read_index("example/opening_form.txt", lines, &num_lines);
    DictStrQ form;
    dict_str_q_init(&form);
    parse_form("example/opening_form.txt", lines, num_lines, &form);
    dict_str_q_print(&form);
}

// int main() {
//     parse_form_test();
//     return 0;
// }