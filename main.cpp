#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

// TODO: add TODO:
// quicker sorts(shell sort)

// rewrite comparator to work without trash

//work with errors // TODO: style this comment properly

struct string {
    char * string; // TODO: rename
    int len;
};

struct Onegin_file { // TODO: delete this
    FILE * input_file;
    const char * input_file_name; // TODO: why

    // TODO: extract this ---------------------
    char* *pointers; // TODO: rename
    struct string* pointers_len; // TODO: rename
    char* buffer; // TODO: rename
    // TODO: ----------------------------------

    const char * output_file_name;
    FILE * output_file;
};

// TODO: sort (imperative)
void sorts(Onegin_file * onezhka, int (*comparator)(string, string));

// TODO: compare (imperative), use verbs in imperative
int comparator(string str1, string str2);
int reversed_comparator(string str1, string str2);

// TODO: the same
int comparator_for_pointers(string str1, string str2);

void Onegin_fileDtor(Onegin_file * onezhka); // TODO: what is this (I mean naming style)
void record_to_file(Onegin_file * onezhka); // TODO: what is this (I mean naming style)
void OneginFileCtor(Onegin_file * onezhka, const char * input_file_name, const char * output_file_name); // TODO: what is this (I mean naming style)

int main(int argc, const char *argv[]) {
    Onegin_file onezhka = {};
    OneginFileCtor(&onezhka, argv[1], argv[2]);

    sorts(&onezhka, comparator); // check^
    record_to_file(&onezhka);

    sorts(&onezhka, reversed_comparator);
    record_to_file(&onezhka);

    sorts(&onezhka, comparator_for_pointers);
    record_to_file(&onezhka);

    Onegin_fileDtor(&onezhka);
}
