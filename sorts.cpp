#include <string.h>
#include <stdio.h>


// TODO: THIS SHOULD HAVE A HEADER FILE, I CANNOT EMPHASIZE ENOUGH

// swap((void*), (void*), size_t)
// swap(string* lhs, string* rhs)
// {}
// struct string* ptr
// ptr->pointer =
// *(ptr + i)
// ptr[i]
// (*ptr).pointer

struct string {
    char * pointer;
    int len;
};

struct Onegin_file { // TODO: This is why you need header files!
    FILE * input_file;
    const char * input_file_name;
    char* *pointers;
    char* buffer;
    struct string* pointers_len;
};

int comparator(string str1, string str2) { // TODO: Maybe you can do it in a simpler way?
    int i = 0;
    do {
        if(*(str1.pointer+i) != *(str2.pointer+i)) {
            return (*(str1.pointer+i) - *(str2.pointer+i));
        }
    i++; // TODO: Indent...
    } while (*(str1.pointer+i) != '\0' && *(str2.pointer+i) != '\0');
    return 0;
}

void swap(string* lhs, string* rhs) {
    string temp = *lhs;
    *lhs = *rhs;
    *rhs = temp;
}

void sorts(Onegin_file * onezhka, int (*comparator)(string, string)) { // TODO: name your variables in function pointers
    for (int i = 0; onezhka->pointers_len[i].pointer != NULL; i++) {
        for (int j = 1; onezhka->pointers_len[j].pointer != NULL; j++) { // TODO: fix your bubble sort
            if (comparator(onezhka->pointers_len[j - 1], onezhka->pointers_len[j]) > 0) {
                swap(&onezhka->pointers_len[j - 1], &onezhka->pointers_len[j]);
            }
        }
    }
}


int reversed_comparator(string str1, string str2) {
    int i = str1.len - 1;
    int j = str2.len - 1;
    do {
        if(*(str1.pointer+i) != *(str2.pointer+j)) { // TODO: *(array + index) <=> array[index]
            return (*(str1.pointer+i) - *(str2.pointer+j));
        }
    i--; // TODO: Indent...
    j--; // TODO: Indent...
    } while (*(str1.pointer+i) != '\0' && *(str2.pointer+j) != '\0');
    return 0;
}

int comparator_for_pointers(string str1, string str2) {
    return str1.pointer-str2.pointer; // TODO: use spaces
}

