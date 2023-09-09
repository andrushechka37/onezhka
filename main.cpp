#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
int give_size_of_file(FILE * file);
int cleaner(char * text);
void record_of_pointers(char **pointers, char * text, int number_of_strcs);
int main(int argc, const char *argv[]) {
    FILE *pfile = NULL;
    argc = 2;
    if (argc == 2) {
        pfile = fopen("input_file.txt", "rb");
    } else {
        printf("no file, error");
    }      //cannot open the file
    char *original = (char*)calloc(give_size_of_file(pfile), sizeof(char) + 1);
    fread(original, 1, give_size_of_file(pfile), pfile);
    printf("%s", original);
    int number_of_strcs = cleaner(original);
    char **pointers = (char**)calloc(number_of_strcs, sizeof(char*));
    record_of_pointers(pointers, original,number_of_strcs);

    for(int i = 0; *(pointers + i) != 0; i++) {
        puts(*(pointers + i));
    }


}


int give_size_of_file(FILE * file) {
    struct stat buff;
    fstat(fileno(file), &buff);
    return buff.st_size;
}
int cleaner(char * text) {
    int count_arrays = 0;
    for(int i = 0; *(text + i) != '\0'; i++) {
        if(*(text + i) == '\r') {
            count_arrays++;
            i++;
            *(text + i) = '\0';
            *(text + 1 + i) = '\0';
            continue;
        }
        if(*(text + i) == '\n') {
            *(text + i) = '\0';
            count_arrays++;
        }
    }
    return count_arrays + 1;
}

void record_of_pointers(char **pointers, char * text, int number_of_strcs) {
    int i = 1;
    int j = 1;
    *pointers = text;
    while(j < number_of_strcs - 1) {
        if (*(text + i - 1) == '\0' && *(text + i) != '\0') {
            *(pointers + j) = (text + i);
            j++;
            printf("pointer to %c number %d\n", *(text + i), j);
        }
        i++;
    }
}
