#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_WORD_LEN 64
// Author: Louis Romeo
// CSC 352
// Assignment 6 Problem 1
// Purpose: Reads in a sequence of words from the input stream, groups them into sets
// where each set consists of words that are anagrams of each other,
// and prints out the resulting anagrams one group per line as specified.

// Node for storing individual words
typedef struct WordNode {
    char word[MAX_WORD_LEN + 1];
    struct WordNode *next;
} WordNode;

// Node for storing groups of anagrams
typedef struct AnagramGroup {
    char sorted[MAX_WORD_LEN + 1];
    WordNode *words;
    struct AnagramGroup *next;
} AnagramGroup;

// Function to create a new WordNode
WordNode* create_word_node(char *word) {
    WordNode *new_node = (WordNode *)malloc(sizeof(WordNode));
    if (new_node == NULL) {
        perror("Failed to allocate memory");
        exit(1);
    }
    int i = 0;
    while (word[i] != '\0') {
        new_node->word[i] = word[i];
        i++;
    }
    new_node->word[i] = '\0';
    new_node->next = NULL;
    return new_node;
}

// Function to create a new AnagramGroup
AnagramGroup* create_anagram_group(char *sorted, char *word) {
    AnagramGroup *new_group = (AnagramGroup *)malloc(sizeof(AnagramGroup));
    if (new_group == NULL) {
        perror("Failed to allocate memory");
        exit(1);
    }
    int i = 0;
    while (sorted[i] != '\0') {
        new_group->sorted[i] = sorted[i];
        i++;
    }
    new_group->sorted[i] = '\0';
    new_group->words = create_word_node(word);
    new_group->next = NULL;
    return new_group;
}

// Custom string functions
int str_len(char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

void str_copy(char *dest, char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

int str_cmp(char *str1, char *str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
        i++;
    }
    return str1[i] - str2[i];
}

void sort_string(char *str) {
    int len = str_len(str);
    for (int i = 0; i < len - 1; ++i) {
        for (int j = i + 1; j < len; ++j) {
            if (str[i] > str[j]) {
                char temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
}

void to_lowercase(char *str) {
    for (int i = 0; str[i]; ++i) {
        str[i] = tolower(str[i]);
    }
}

int is_alphabetic(char *str) {
    for (int i = 0; str[i]; ++i) {
        if (!isalpha(str[i])) {
            return 0;
        }
    }
    return 1;
}

// Find or add an anagram group
AnagramGroup* find_or_add_group(AnagramGroup **head, char *sorted, char *word) {
    AnagramGroup *current = *head;
    AnagramGroup *prev = NULL;

    // Check if group already exists
    while (current != NULL) {
        if (str_cmp(current->sorted, sorted) == 0) {
            // Add word to existing group
            WordNode *word_node = create_word_node(word);
            WordNode *temp = current->words;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = word_node;
            return *head;
        }
        prev = current;
        current = current->next;
    }

    // Create a new group
    AnagramGroup *new_group = create_anagram_group(sorted, word);
    if (prev == NULL) {
        *head = new_group;
    } else {
        prev->next = new_group;
    }
    return *head;
}

// Print anagram groups
void print_anagram_groups(AnagramGroup *head) {
    AnagramGroup *current = head;
    while (current != NULL) {
        WordNode *word_node = current->words;
        while (word_node != NULL) {
            printf("%s", word_node->word);
            word_node = word_node->next;
            if (word_node != NULL) {
                printf(" ");
            }
        }
        printf("\n");
        current = current->next;
    }
}

// Free memory for words
void free_words(WordNode *head) {
    while (head != NULL) {
        WordNode *temp = head;
        head = head->next;
        free(temp);
    }
}

// Free memory for anagram groups
void free_groups(AnagramGroup *head) {
    while (head != NULL) {
        AnagramGroup *temp = head;
        head = head->next;
        free_words(temp->words);
        free(temp);
    }
}

// Read a word from input, skipping extra whitespace
int read_word(char *word) {
    int c, i = 0;

    // Skip leading whitespace
    while ((c = getchar()) != EOF && isspace(c));

    // If end of input, return 0
    if (c == EOF) {
        return 0;
    }

    // Read the word
    do {
        if (isalpha(c)) {
            if (i < MAX_WORD_LEN) {
                word[i++] = c;
            }
        } else {
            // Stop reading on non-alphabetic character
            break;
        }
    } while ((c = getchar()) != EOF && !isspace(c));

    word[i] = '\0';
    return 1;
}

int main() {
    AnagramGroup *head = NULL;
    char word[MAX_WORD_LEN + 1];
    int error_flag = 0;

    // Read words from input, handling extra whitespace
    while (read_word(word)) {
        if (!is_alphabetic(word)) {
            fprintf(stderr, "Error: Non-alphabetic string \"%s\" encountered.\n", word);
            error_flag = 1;
            continue;
        }

        // Create sorted version of the word
        char sorted_word[MAX_WORD_LEN + 1];
        str_copy(sorted_word, word);
        to_lowercase(sorted_word);
        sort_string(sorted_word);

        // Find or add an anagram group
        find_or_add_group(&head, sorted_word, word);
    }

    // Print anagram groups
    print_anagram_groups(head);

    // Free allocated memory
    free_groups(head);

    // Exit with appropriate status
    if (error_flag) {
        return 1;
    }
    return 0;
}
