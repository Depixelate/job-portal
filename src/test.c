/* Just used for testing bits of C code, nothing important here */

#include <stdio.h>
#include <stdbool.h>

int main() {
    char buf[1000];
    int num_chars_read = 0;
    fgets(buf, 1000, stdin);
    char new_buf[1000] = "iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii";
    sscanf(buf, "%[^:]:%n", new_buf, &num_chars_read);
    printf("%s, %d", new_buf, num_chars_read);
}