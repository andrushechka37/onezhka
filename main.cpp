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

int give_size_of_file(FILE * file);
int cleaner(char * text);
void record_of_pointers(char **pointers, char * text, int number_of_strcs, int len);
void sort(char* * pointers);
int comparator(char * str1, char * str2);
void record_to_file(char ** pointers, FILE * file);
int reversed_comparator(char * str1, char * str2);
void reversed_sort(char ** pointers);

int main(int argc, const char *argv[]) {
    FILE *pfile = NULL;
    //argc = 2;
    if (argc == 2) {
        pfile = fopen(argv[1], "rb");
    } else {
        printf("can not open file, error"); //
        return 0;
    }      //cannot open the file

    int len = give_size_of_file(pfile);
    char *buffer = (char*)calloc(len, sizeof(char) + 1);

    fread(buffer, 1, len, pfile);

    int number_of_strcs = cleaner(buffer);
    char **pointers = (char**)calloc(number_of_strcs, sizeof(char*));
    record_of_pointers(pointers, buffer,number_of_strcs, len);

    FILE * file = fopen("output.txt", "wb");
    sort(pointers);//check^
    record_to_file(pointers, file);
    reversed_sort(pointers);
    record_to_file(pointers, file);

    // ??
    for(int i = 0; *(pointers + i) != NULL; i++) {
        for(int j = 1; *(pointers + j) != NULL; j++) {
            if (*(pointers + j - 1) > *(pointers + j)) {
                char * temp = *(pointers + j - 1);
                *(pointers + j - 1) = *(pointers + j);
                *(pointers + j) = temp;

            }
        }
    }
    record_to_file(pointers, file);
}

