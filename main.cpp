#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

// quicker sorts(shell sort)
// rewrite comparator to work without tras
//work with errors

struct string {
    char * pointer;
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

void all_sorts_in_one(Onegin_file * onezhka, int (*comparator)(string, string));
int comparator(string str1, string str2);
int reversed_comparator(string str1, string str2);
int comparator_for_pointers(string str1, string str2);

void Onegin_fileDtor(Onegin_file * onezhka);
void record_to_file(Onegin_file * onezhka);
void OneginFileCtor(Onegin_file * onezhka, const char * input_file_name, const char * output_file_name);

int main(int argc, const char *argv[]) {
    Onegin_file onezhka = {};
    OneginFileCtor(&onezhka, argv[1], argv[2]);


    all_sorts_in_one(&onezhka, comparator);//check^
    record_to_file(&onezhka);

    all_sorts_in_one(&onezhka, reversed_comparator);
    record_to_file(&onezhka);

    all_sorts_in_one(&onezhka, comparator_for_pointers);
    record_to_file(&onezhka);

    Onegin_fileDtor(&onezhka);
}
