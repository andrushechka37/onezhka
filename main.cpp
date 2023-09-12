#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

// unite two sorts
// rewrite comparator to work without trash
// quicker sorts
// OneginFile
// [ FILE* input_...,
//   String* ....
//   char* buffer;
//   ]
// OneginFileCtor(OneginFile*, )
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
int give_size_of_file(FILE * file);
int cleaner(char * text);
void record_of_pointers(char **pointers, char * text, int number_of_strcs, int len);
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

void sort(struct string * pointers_len[]);
int comparator(char * str1, char * str2);
void record_to_file(Onegin_file * onezhka, FILE * file);
// int reversed_comparator(char * str1, char * str2);
// void reversed_sort(char ** pointers);

int main(int argc, const char *argv[]) {
//     FILE *pfile = NULL;
//     //argc = 2;
//     if (argc == 2) {
//         pfile = fopen(argv[1], "rb");
//     } else {
//         printf("can not open file, error"); //
//         return 0;
//     }      //cannot open the file
//
//     int len = give_size_of_file(pfile);
//     char *buffer = (char*)calloc(len, sizeof(char) + 1);
//
//     fread(buffer, 1, len, pfile);
//
//     int number_of_strcs = cleaner(buffer);
//     char **pointers = (char**)calloc(number_of_strcs, sizeof(char*));
//     record_of_pointers(pointers, buffer,number_of_strcs, len);
    Onegin_file onezhka = {NULL, "input.txt", NULL, NULL, NULL};
    OneginFileCtor(&onezhka);
    int i = 0;
    while(onezhka.pointers_len[i].pointer != NULL) {
        puts(onezhka.pointers_len[i].pointer);
        i++;
    }

    FILE * file = fopen("output.txt", "wb");
    sort(&onezhka.pointers_len);//check^
    record_to_file(&onezhka, file);
    // reversed_sort(pointers);
    // record_to_file(pointers, file);

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

void sort(struct string * pointers_len[]) {
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
