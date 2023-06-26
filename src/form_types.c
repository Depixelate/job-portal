#include "utils.c"

#define MAX_QNO_CHARS 10
#define MAX_QUESTION_CHARS 200
#define MAX_ANS_KV_PAIRS 10

typedef struct {
    char number[MAX_QNO_CHARS];
    char question[MAX_QUESTION_CHARS];
    DictStrStr responses;
} Question;

typedef struct {
    char keys[MAX_KV_PAIRS][MAX_KEY_LEN];
    Question values[MAX_KV_PAIRS];
    int len;
} DictStrQ;

void dict_str_str_init(DictStrQ *dict) {
    dict->len = 0;
}

void dict_str_q_add(DictStrQ *dict, char *key,  Question *value) {
    strcpy(dict->keys[dict->len], key);
    dict->values[dict->len] = *value;
    dict->len += 1;
}

Question *dict_str_q_new_ptr(DictStrQ *dict, char *key) {
    dict->len += 1;
    int new_last_index = dict->len - 1;
    strcpy(dict->keys[new_last_index], key);
    return &(dict->values[new_last_index]);
}

//returns true or false depending on if key present
bool dict_str_q_get(DictStrQ *dict, char *key, Question *value) {
    for(int i = 0; i < dict->len; i++) {
        if (strcmp(dict->keys[i], key) == 0) {
            value = &dict->values[i];
            return true;
        }
    }
    return false;
}