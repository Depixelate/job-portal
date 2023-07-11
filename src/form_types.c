#pragma once
#include "dict.c"
#include "string_utils.c"

#define MAX_QNO_CHARS 10
#define MAX_PROMPT_CHARS 200
#define MAX_LINES 200
#define MAX_LENGTH 200
#define MAX_FORM_QUESTIONS 100

typedef struct {
    char number[MAX_QNO_CHARS];
    char prompt[MAX_PROMPT_CHARS];
    DictStrStr response;
} Question;

void question_init(Question *q) {
    q->number[0] = '\0';
    q->prompt[0] = '\0';
    dict_str_str_init(&q->response);
}

void _question_print(Question *q) {
    printf("{num:\"%s\", prompt:\"%s\", response: ", q->number, q->prompt);
    _dict_str_str_print(&q->response);
    printf("}");
}

void question_print(Question *q) {
    _question_print(q);
    printf("\n");
}

typedef struct {
    char keys[MAX_FORM_QUESTIONS][MAX_KEY_LEN];
    Question values[MAX_FORM_QUESTIONS];
    int len;
} DictStrQ;

void dict_str_q_init(DictStrQ *dict) {
    dict->len = 0;
}

void dict_str_q_add(DictStrQ *dict, char *key,  Question *value) {
    strcpy(dict->keys[dict->len], key);
    dict->values[dict->len] = *value;
    dict->len += 1;
}

void dict_str_q_clear(DictStrQ *dict) {
    dict->len = 0;
}

Question *dict_str_q_new_ptr(DictStrQ *dict, char *key) {
    dict->len += 1;
    int new_last_index = dict->len - 1;
    strcpy(dict->keys[new_last_index], key);
    question_init(&dict->values[new_last_index]);
    return &(dict->values[new_last_index]);
}

void dict_str_q_next_ptrs(DictStrQ *dict, char **key, Question **value) {
    dict->len += 1;
    int last_index = dict->len - 1;
    *key = dict->keys[last_index];
    (*key)[0] = '\0';
    question_init(&dict->values[last_index]);
    *value = &dict->values[last_index];
}

//returns true or false depending on if key present
bool dict_str_q_get(DictStrQ *dict, char *key, Question **value) {
    for(int i = 0; i < dict->len; i++) {
        if (strcasecmp(dict->keys[i], key) == 0) {
            *value = &dict->values[i];
            return true;
        }
    }
    return false;
}

void _dict_str_q_print(DictStrQ *dict) {
    printf("{\n");
    for(int i = 0; i < dict->len; i++) {
        printf("\"%s\" : ", dict->keys[i]);
        question_print(&dict->values[i]);
    }
    printf("}");
}

void dict_str_q_print(DictStrQ *dict) {
    _dict_str_q_print(dict);
    printf("\n");
}

void dict_str_q_test() {
    DictStrQ dict;
    Question q1 = {"1.", "hello: ", {{"is it me you're looking for?"}, {""}, 1}}, q2 = {"2.", "goodbye: ", {{"I'm going away"}, {""}, 1}}, q3 = {"3.", "why: ", {{"Come back!"}, {"no"}, 1}};
    dict_str_q_init(&dict);   
    dict_str_q_add(&dict, "1.", &q1);
    Question *value;
    dict_str_q_get(&dict, "1.", &value);
    question_print(value);
    dict_str_q_add(&dict, "2.", &q2);
    dict_str_q_get(&dict, "2.", &value);
    question_print(value);
    dict_str_q_print(&dict);
    dict_str_q_add(&dict, "3.", &q3);
    dict_str_q_print(&dict);
    dict_str_q_get(&dict, "3.", &value);
    question_print(value);
    Question *q4 = dict_str_q_new_ptr(&dict, "4.");
    strcpy(q4->number, "4.");
    strcpy(q4->prompt, "what do you want?");
    dict_str_str_add(&q4->response, "I'll be back", "-Arnold Schwarznegger");
    dict_str_q_print(&dict);
    char *key;
    dict_str_q_next_ptrs(&dict, &key, &value);
    char *response_key, *response_value;
    dict_str_str_next_ptrs(&(value->response), &response_key, &response_value);
    printf("Enter q.no, prompt, response key and value: ");
    scanf(" %[^ ] %[^:]: %[^:]:%[^\n]", value->number, value->prompt, response_key, response_value);
    strcpy(key, value->number);
    dict_str_q_print(&dict);
}

// void main() {
//     dict_str_q_test();
// }