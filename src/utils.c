#pragma once
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

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


//returns true or false depending on if key present.
bool dict_str_int_get(DictStrInt *dict, char *key, int *value) {
    for(int i = 0; i < dict->len; i++) {
        if (strcmp(dict->keys[i], key) == 0) {
            *value = dict->values[i];
            return true;
        }
    }
    return false;
}

void dict_str_int_clear(DictStrInt *dict) {
    dict -> len = 0;
}

void dict_str_int_print(DictStrInt *dict) {
    printf("{");
    for(int i = 0; i < dict->len; i++) {
        printf("\"%s\" : %d, ", dict->keys[i], dict->values[i]);
    }
    printf("}\n");
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

char *dict_str_str_new_ptr(DictStrStr *dict, char *key) {
    dict->len += 1;
    int new_last_index = dict->len - 1;
    strcpy(dict->keys[new_last_index], key);
    char *value = dict->values[new_last_index];
    value[0] = '\0';
    return value;
}

void dict_str_str_next_ptrs(DictStrStr *dict, char **key, char **value) {
    dict->len += 1;
    int last_index = dict->len - 1;
    *key = dict->keys[last_index];
    (*key)[0] = '\0';
    *value = dict->values[last_index];
    (*value)[0] = '\0';
}

//returns true or false depending on if key 
bool dict_str_str_get(DictStrStr *dict, char *key, char **value) {
    for(int i = 0; i < dict->len; i++) {
        if (strcmp(dict->keys[i], key) == 0) {
            *value = dict->values[i];
            return true;
        }
    }
    return false;
}


void dict_str_str_clear(DictStrStr *dict) {
    dict -> len = 0;
}

void dict_str_str_print(DictStrStr *dict) {
    printf("{");
    for(int i = 0; i < dict->len; i++) {
        printf("\"%s\" : \"%s\", ", dict->keys[i], dict->values[i]);
    }
    printf("}\n");
}

void dict_str_str_test() {
    DictStrStr dict;
    dict_str_str_init(&dict);   
    dict_str_str_add(&dict, "hi", "hello");
    char* val;
    dict_str_str_get(&dict, "hi", &val);
    dict_str_str_add(&dict, "bye", "goodbye");
    dict_str_str_get(&dict, "hi", &val);
    dict_str_str_print(&dict);
    dict_str_str_get(&dict, "hi", &val); 
    printf("%s\n", val);
    dict_str_str_add(&dict, "foo", "bar");
    dict_str_str_print(&dict);
    dict_str_str_get(&dict, "hi", &val);
    printf("%s\n", val);
    printf("Enter a value: ");
    scanf("%[^\n]", dict_str_str_new_ptr(&dict, "a_key"));
    dict_str_str_print(&dict);
    char *key, *value;
    dict_str_str_next_ptrs(&dict, &key, &value);
    printf("Enter key and value: ");
    scanf("%[^,],%[^\n]", key, value);
    dict_str_str_print(&dict); 
}

void dict_str_int_test() {
    DictStrInt dict;
    dict_str_int_init(&dict);   
    dict_str_int_add(&dict, "hi", 10);
    int val;
    dict_str_int_get(&dict, "hi", &val);
    dict_str_int_add(&dict, "bye", 15);
    dict_str_int_get(&dict, "hi", &val);
    dict_str_int_print(&dict);
    dict_str_int_get(&dict, "hi", &val); 
    printf("%d\n", val);
    dict_str_int_add(&dict, "foo", 25);
    dict_str_int_print(&dict);
    dict_str_int_get(&dict, "foo", &val);
    printf("%d\n", val);
    printf("Enter a value: ");
    //scanf("%d", dict_str_int_new_ptr(&dict, "a_key"));
    dict_str_int_print(&dict);
    //dict_str_int_next_ptrs(&dict, &key, &value);
    //printf("Enter key and value: ");
    //scanf("%[^,],%[^\n]", key, value);
    dict_str_int_print(&dict);
}

// void main() {
//     dict_str_int_test();
// }