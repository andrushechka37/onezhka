#include <string.h>
#include <stdio.h>

// struct String
// {
//    char* str;
//    int len;
//}
// String* strings = calloc(...);
// strings[0].len
// unite two sorts
// rewrite comparator to work without trash
// quicker sorts
// OneginFileDtor(OneginFile*)
struct string {
    char * pointer;
    int len;
};
struct Onegin_file {
    FILE * pfile;
    const char * txtfile;
    char* *pointers;
    char* buffer;
    struct string* pointers_len;
};

int reversed_comparator(string* str1, string* str2) {
    int i = str1.len - 1; //save len
    int j = str2.len - 1;
    do {
        if(*(str1.pointer+i) != *(str2.pointer+j)) {
            return (*(str1.pointer+i) - *(str2->pointer+j));
        }
    i--;
    j--;
    } while (*(str1.pointer+i) != '\0' && *(str2.pointer+j) != '\0');
    return 0;
}
void reversed_sort(Onegin_file * onezhka) {
    for (int i = 0; onezhka->pointers_len[i].pointer != NULL; i++) {
        for (int j = 1; onezhka->pointers_len[j].pointer != NULL; j++) {
            if (reversed_comparator(onezhka->pointers_len[j - 1].pointer, onezhka->pointers_len[j].pointer > 0)) {
                char * temp = onezhka->pointers_len[j - 1].pointer;
                onezhka->pointers_len[j - 1].pointer = onezhka->pointers_len[j].pointer;
                onezhka->pointers_len[j].pointer = temp;
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

void sort(string* *pointers_len) {
    for (int i = 0; pointers_len[i]->pointer != NULL; i++) {
        for (int j = 1; pointers_len[j]->pointer != NULL; j++) {
            if (comparator(pointers_len[j - 1]->pointer, pointers_len[j]->pointer) > 0) {
                char * temp = pointers_len[j - 1]->pointer;
                pointers_len[j - 1]->pointer = pointers_len[j]->pointer;
                pointers_len[j]->pointer = temp;
            }
        }
    }
}
