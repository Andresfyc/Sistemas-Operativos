#ifndef _STUDENT_
#define _STUDENT_

#include <stdio.h>

#define MAX_CHARS_NIF  9

typedef struct {
    int student_id; 
    char NIF[MAX_CHARS_NIF+1];  
    char* first_name;
    char* last_name;
} student_t;


student_t* parse_records(char* records[], int nr_records);
int dump_entries(student_t* entries, int nr_entries, FILE* students);
student_t* read_student_file(FILE* students, int* nr_entries);
char* loadstr(FILE* students);

#endif