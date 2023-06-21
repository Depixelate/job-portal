#include <string.h>
#include <stdbool.h>

typedef struct {
    char keys[100][100];
    int values[100];
    int len;
} DictStrInt;

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

