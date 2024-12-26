#include <ctype.h>
#include <string.h>
// Louis Romeo
// CSC 352 Assg10
// Date: 12/5/2024
// Purpose:
char *trimWhitespace(char *str) {
    if (!str) return NULL;

    // Trim leading whitespace
    while (isspace((unsigned char)*str)) str++;

    // If the string is empty after trimming
    if (*str == '\0') return str;

    // Trim trailing whitespace
    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    // Null-terminate the string
    *(end + 1) = '\0';

    return str;
}
