#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

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
int give_size_of_file(FILE * file);
int cleaner(char * text);
void record_of_pointers(char **pointers, char * text, int number_of_strcs, int len);
void OneginFileCtor(Onegin_file * onezhka);

void sort(Onegin_file * onezhka);
int comparator(char * str1, char * str2);
void record_to_file(Onegin_file * onezhka, FILE * file);
int reversed_comparator(string *str1, string* str2);
void reversed_sort(Onegin_file * onezhka);


int main(int argc, const char *argv[]) {
    Onegin_file onezhka = {NULL, "input.txt", NULL, NULL, NULL};
    OneginFileCtor(&onezhka);
    FILE * file = fopen("output.txt", "wb");
    sort(&onezhka);//check^
    record_to_file(&onezhka, file);
    reversed_sort(&onezhka);
    record_to_file(&onezhka, file);

//     // ??
//     for(int i = 0; *(pointers + i) != NULL; i++) {
//         for(int j = 1; *(pointers + j) != NULL; j++) {
//             if (*(pointers + j - 1) > *(pointers + j)) {
//                 char * temp = *(pointers + j - 1);
//                 *(pointers + j - 1) = *(pointers + j);
//                 *(pointers + j) = temp;
//
//             }
//         }
//     }
//     record_to_file(pointers, file);
}



void OneginFileCtor(Onegin_file * onezhka) {
    onezhka->pfile = fopen(onezhka->txtfile, "rb");
    if(onezhka->pfile == NULL) {
        return;
    }
    int len = give_size_of_file(onezhka->pfile);
    onezhka->buffer = (char*)calloc(len, sizeof(char) + 1);
    fread(onezhka->buffer, 1, len, onezhka->pfile);
    int number_of_strcs = cleaner(onezhka->buffer);
    onezhka->pointers = (char**)calloc(number_of_strcs, sizeof(char*));
    record_of_pointers(onezhka->pointers, onezhka->buffer,number_of_strcs, len);
    onezhka ->pointers_len = (struct string*) calloc(number_of_strcs + 1, sizeof(string));
    for(int i = 0; onezhka->pointers[i] != NULL; i++) {
        onezhka->pointers_len[i].pointer = onezhka->pointers[i];
        onezhka->pointers_len[i].len = strlen(onezhka->pointers[i]);
    }

}













int give_size_of_file(FILE * file) {
    struct stat buff;
    fstat(fileno(file), &buff); //check
    return buff.st_size;
}

int cleaner(char * text) {
    int count_arrays = 0;
    for(int i = 0; *(text + i) != '\0'; i++) {
        if(*(text + i) == '\r') {
            count_arrays++;
            *(text + i) = '\0';
            *(text + 1 + i) = '\0';
            i++;
            continue;
        }
        if(*(text + i) == '\n') {
            *(text + i) = '\0';
            count_arrays++;
        }
    }
    return count_arrays + 1;
}

void record_of_pointers(char **pointers, char * text, int number_of_strcs, int len) {
    int i = 1;
    int j = 1;
    *pointers = text;
    while((j < number_of_strcs - 1) && (i < len)) {
        if (*(text + i - 1) == '\0' && *(text + i) != '\0') {
            *(pointers + j) = (text + i);
            j++;
            printf("pointer to %c number %d\n", *(text + i), j);
        }
        i++;
    }
}

void record_to_file(Onegin_file * onezhka, FILE * file) {
    for(int i = 0; onezhka->pointers_len[i].pointer != NULL; i++) {
        fwrite(onezhka->pointers_len[i].pointer, 1, strlen(onezhka->pointers_len[i].pointer), file);
        char newline = '\n';
        fwrite(&newline, 1, 1, file);
    }
    char devider[] = "<----------------(:*******:)------------------------divide---------------(:*******:)----------------------------->";
    fwrite(&devider, strlen(devider), 1, file);
    char newline = '\n';
    fwrite(&newline, 1, 1, file);
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

void sort(Onegin_file * onezhka) {
    for (int i = 0; onezhka->pointers_len[i].pointer != NULL; i++) {
        for (int j = 1; onezhka->pointers_len[j].pointer != NULL; j++) {
            if (comparator(onezhka->pointers_len[j - 1].pointer, onezhka->pointers_len[j].pointer) > 0) {
                char * temp = onezhka->pointers_len[j - 1].pointer;
                onezhka->pointers_len[j - 1].pointer = onezhka->pointers_len[j].pointer;
                onezhka->pointers_len[j].pointer = temp;
                int temp_len = onezhka->pointers_len[j - 1].len;
                onezhka->pointers_len[j - 1].len = onezhka->pointers_len[j].len;
                onezhka->pointers_len[j].len = temp_len;
            }
        }
    }
}



int reversed_comparator(string str1, string str2) {
    int i = str1.len - 1; //save len
    int j = str2.len - 1;
    do {
        printf("%c   %c     \n", *(str1.pointer+i),*(str2.pointer+j) );
        if(*(str1.pointer+i) != *(str2.pointer+j)) {
            return (*(str1.pointer+i) - *(str2.pointer+j));
        }
    i--;
    j--;
    } while (*(str1.pointer+i) != '\0' && *(str2.pointer+j) != '\0');
    return 0;
}
void reversed_sort(Onegin_file * onezhka) {
    for (int i = 0; onezhka->pointers_len[i].pointer != NULL; i++) {
        for (int j = 1; onezhka->pointers_len[j].pointer != NULL; j++) {
            if (reversed_comparator(onezhka->pointers_len[j - 1], onezhka->pointers_len[j]) > 0) {
                char * temp = onezhka->pointers_len[j - 1].pointer;
                onezhka->pointers_len[j - 1].pointer = onezhka->pointers_len[j].pointer;
                onezhka->pointers_len[j].pointer = temp;
                int temp_len = onezhka->pointers_len[j - 1].len;
                onezhka->pointers_len[j - 1].len = onezhka->pointers_len[j].len;
                onezhka->pointers_len[j].len = temp_len;
            }
        }
    }
}
