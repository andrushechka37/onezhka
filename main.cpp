#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

//parse to files
// unite two sorts
// rewrite comparator to work without trash
// quicker sorts(shell sort)
// OneginFileDtor(OneginFile*)
//work with errors
//split to str work with onegin file
//static functions
//record of pointers with onegin and rewrite
//swap
struct string {
    char * pointer; //maybe rename
    int len;
};

struct Onegin_file {
    FILE * input_file;
    const char * input_file_name;
    char* *pointers;
    char* buffer;
    struct string* pointers_len;
    const char * output_file_name;
    FILE * output_file;
};

//void swap(string* lhs, string* rhs);
int give_size_of_file(FILE * file);
int split_to_c_str(char * text);
void record_of_pointers(char **pointers, char * text, int number_of_strcs, int len);
void OneginFileCtor(Onegin_file * onezhka, const char * input_file_name, const char * output_file_name);

void sort_strings_by_begin(Onegin_file * onezhka);
int comparator(char * str1, char * str2);
void record_to_file(Onegin_file * onezhka, FILE * file);
int reversed_comparator(string *str1, string* str2);
void reversed_sort(Onegin_file * onezhka);


int main(int argc, const char *argv[]) {
    Onegin_file onezhka = {};
    OneginFileCtor(&onezhka, "input.txt", "output.txt");


    sort_strings_by_begin(&onezhka);//check^
    record_to_file(&onezhka, onezhka.output_file);

    reversed_sort(&onezhka);
    record_to_file(&onezhka, onezhka.output_file);

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



// enum OneginFileError??
void OneginFileCtor(Onegin_file * onezhka, const char * input_file_name, const char * output_file_name) {
    onezhka->input_file_name = input_file_name;
    onezhka->output_file_name = output_file_name;
    onezhka->input_file = fopen(onezhka->input_file_name, "rb");

    // INPUT_FILE_OPEN_ERROR = -100
    if(onezhka->input_file == NULL) {
        return;
    }

    // get_file_size
    int len = give_size_of_file(onezhka->input_file);
    onezhka->buffer = (char*)calloc(len + 1, sizeof(char));

    // MEM_ALLOC_ERROR
    fread(onezhka->buffer, 1, len, onezhka->input_file);
    int number_of_strcs = split_to_c_str(onezhka->buffer);
    onezhka->pointers = (char**)calloc(number_of_strcs, sizeof(char*));

    record_of_pointers(onezhka->pointers, onezhka->buffer,number_of_strcs, len);
    onezhka ->pointers_len = (struct string*) calloc(number_of_strcs + 1, sizeof(string));

    for(int i = 0; onezhka->pointers[i] != NULL; i++) {
        onezhka->pointers_len[i].pointer = onezhka->pointers[i];
        onezhka->pointers_len[i].len = strlen(onezhka->pointers[i]);
    }
    onezhka->output_file = fopen(onezhka->output_file_name, "wb");

}













int give_size_of_file(FILE * file) {
    struct stat buff;
    fstat(fileno(file), &buff);
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
            //printf("pointer to %c number %d\n", *(text + i), j);
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
    char divider[] = "<----------------(:*******:)------------------------divide---------------(:*******:)----------------------------->";
    fwrite(&divider, strlen(divider), 1, file);
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


// void swap(string* lhs, string* rhs) {
//     string* temp = lhs;
//     lhs = rhs;
//     rhs = temp;
// }
void sort_strings_by_begin(Onegin_file * onezhka) {
    for (int i = 0; onezhka->pointers_len[i].pointer != NULL; i++) {
        for (int j = 1; onezhka->pointers_len[j].pointer != NULL; j++) {
            if (comparator(onezhka->pointers_len[j - 1].pointer, onezhka->pointers_len[j].pointer) > 0) {
                //swap(&onezhka->pointers_len[j - 1], &onezhka->pointers_len[j]);
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
    int i = str1.len - 1;
    int j = str2.len - 1;
    do {
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
