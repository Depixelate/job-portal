#include <string.h>
#include <stdbool.h>

#define MAX_KV_PAIRS 25
#define MAX_KEY_LEN 100
#define MAX_VAL_STR_LEN 100

typedef struct {
    char keys[MAX_KV_PAIRS][MAX_KEY_LEN];
    int values[MAX_KV_PAIRS];
    int len;
} DictStrInt;

void dict_str_int_init(DictStrInt *dict) {
    dict->len = 0;
}

void dict_str_int_add(DictStrInt *dict, char *key,  int value) {
    strcpy(dict->keys[dict->len], key);
    dict->values[dict->len] = value;
    dict->len += 1;
}

bool dict_str_int_get(DictStrInt *dict, char *key, int *value) {
    for(int i = 0; i < dict->len; i++) {
        if (strcmp(dict->keys[i], key) == 0) {
            value = &dict->values[i];
            return true;
        }
    }
    return false;
}

typedef struct {
    char keys[MAX_KV_PAIRS][MAX_KEY_LEN];
    char values[MAX_KV_PAIRS][MAX_VAL_STR_LEN];
    int len;
} DictStrStr;

void dict_str_str_init(DictStrStr *dict) {
    dict->len = 0;
}

void dict_str_str_add(DictStrStr *dict, char *key,  char *value) {
    strcpy(dict->keys[dict->len], key);
    strcpy(dict->values[dict->len], value);
    dict->len += 1;
}

char *dict_str_str_set(DictStrStr *dict, char *key) {
    dict->len += 1;
    int new_last_index = dict->len - 1;
    strcpy(dict->keys[new_last_index], key);
    return dict->values[new_last_index];
}

//returns true or false depending on if key 
bool dict_str_str_get(DictStrInt *dict, char *key, char *value) {
    for(int i = 0; i < dict->len; i++) {
        if (strcmp(dict->keys[i], key) == 0) {
            value = &dict->values[i];
            return true;
        }
    }
    return false;
}

