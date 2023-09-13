#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int give_size_of_file(FILE * file) {
    struct stat buff;
    fstat(fileno(file), &buff); //check
    return buff.st_size;
}

int split_to_c_str(char * text) {
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


void record_to_file(char ** pointers, FILE * file) {
    for(int i = 0; *(pointers + i) != NULL; i++) {
        fwrite(*(pointers + i), 1, strlen(*(pointers + i)), file);
        char newline = '\n';
        fwrite(&newline, 1, 1, file);
    }
    char devider[] = "<----------------(:*******:)------------------------divide---------------(:**********:)----------------------------->";
    fwrite(&devider, strlen(devider), 1, file);
    char newline = '\n';
    fwrite(&newline, 1, 1, file);
}
