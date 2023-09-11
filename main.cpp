#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

// unite two sorts
// rewrite comparator to work without trash
// quicker sorts

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
        printf("no file, error");
        return 0;
    }      //cannot open the file

    int len = give_size_of_file(pfile);
    char *buffer = (char*)calloc(len, sizeof(char) + 1);

    fread(buffer, 1, len, pfile);

    int number_of_strcs = cleaner(buffer);
    char **pointers = (char**)calloc(number_of_strcs, sizeof(char*));
    record_of_pointers(pointers, buffer,number_of_strcs, len);

    FILE * file = fopen("output.txt", "wb");
    sort(pointers);
    record_to_file(pointers, file);
    reversed_sort(pointers);
    record_to_file(pointers, file);

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

void record_to_file(char ** pointers, FILE * file) {
    for(int i = 0; *(pointers + i) != NULL; i++) {
        fwrite(*(pointers + i), 1, strlen(*(pointers + i)), file);
        char newline = '\n';
        fwrite(&newline, 1, 1, file);
    }
    char devider[] = "<----------------(:*******:)------------------------devide---------------(:**********:)----------------------------->";
    fwrite(&devider, strlen(devider), 1, file);
    char newline = '\n';
    fwrite(&newline, 1, 1, file);
}

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
