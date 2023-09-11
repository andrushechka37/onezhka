#include <string.h>
#include <stdio.h>
int reversed_comparator(char * str1, char * str2) {
    int i = strlen(str1) - 1;
    int j = strlen(str2) - 1;
    do {
        if(*(str1+i) != *(str2+j)) {
            return (*(str1+i) - *(str2+j));
        }
    i--;
    j--;
    } while (*(str1+i) != '\0' && *(str2+j) != '\0');
    return 0;
}
void reversed_sort(char ** pointers) {
    for (int i = 0; *(pointers + i) != NULL; i++) {
        for (int j = 1; *(pointers + j) != NULL; j++) {
            if (reversed_comparator(*(pointers + j - 1), *(pointers + j)) > 0) {
                char * temp = *(pointers + j - 1);
                *(pointers + j - 1) = *(pointers + j);
                *(pointers + j) = temp;
            }
        }
    }
}

int comparator(char * str1, char * str2) {
    int i = 0;
    do {
        if(*(str1+i) != *(str2+i)) {
            return (*(str1+i) - *(str2+i));
        }
    i++;
    } while (*(str1+i) != '\0' && *(str2+i) != '\0');
    return 0;
}

void sort(char* * pointers) {
    for (int i = 0; *(pointers + i) != NULL; i++) {
        for (int j = 1; *(pointers + j) != NULL; j++) {
            if (comparator(*(pointers + j - 1), *(pointers + j)) > 0) {
                char * temp = *(pointers + j - 1);
                *(pointers + j - 1) = *(pointers + j);
                *(pointers + j) = temp;
            }
        }
    }
}
