#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

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

// enum OneginFileError??

static int give_size_of_file(FILE * file);
static int split_to_c_str(Onegin_file * onezhka);
static void record_of_pointers(char **pointers, char * text, int number_of_strcs, int len);

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
    int number_of_strcs = split_to_c_str(onezhka);
    onezhka->pointers = (char**)calloc(number_of_strcs, sizeof(char*));

    record_of_pointers(onezhka->pointers, onezhka->buffer,number_of_strcs, len);
    onezhka ->pointers_len = (struct string*) calloc(number_of_strcs + 1, sizeof(string));

    for(int i = 0; onezhka->pointers[i] != NULL; i++) {
        onezhka->pointers_len[i].pointer = onezhka->pointers[i];
        onezhka->pointers_len[i].len = strlen(onezhka->pointers[i]);
    }
    onezhka->output_file = fopen(onezhka->output_file_name, "wb");

}

static int give_size_of_file(FILE * file) {
    struct stat buff;
    fstat(fileno(file), &buff);
    return buff.st_size;
}

static int split_to_c_str(Onegin_file * onezhka) {
    int count_arrays = 0;
    for(int i = 0; onezhka->buffer[i] != '\0'; i++) {
        if(onezhka->buffer[i] == '\r') {
            count_arrays++;
            onezhka->buffer[i] = '\0';
            onezhka->buffer[i + 1] = '\0';
            i++;
            continue;
        }
        if(onezhka->buffer[i] == '\n') {
            onezhka->buffer[i] = '\0';
            count_arrays++;
        }
    }
    return count_arrays + 1;
}

static void record_of_pointers(char **pointers, char * text, int number_of_strcs, int len) {
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

void Onegin_fileDtor(Onegin_file * onezhka) {
    fclose(onezhka->input_file);
    fclose(onezhka->output_file);
    free(onezhka->pointers_len);
    free(onezhka->pointers);
    free(onezhka->buffer);
}

void record_to_file(Onegin_file * onezhka) {
    for(int i = 0; onezhka->pointers_len[i].pointer != NULL; i++) {
        fwrite(onezhka->pointers_len[i].pointer, 1, strlen(onezhka->pointers_len[i].pointer), onezhka->output_file);
        char newline = '\n';
        fwrite(&newline, 1, 1, onezhka->output_file);
    }
    char divider[] = "<----------------(:*******:)------------------------divide---------------(:*******:)----------------------------->";
    fwrite(&divider, strlen(divider), 1, onezhka->output_file);
    char newline = '\n';
    fwrite(&newline, 1, 1, onezhka->output_file);
}
