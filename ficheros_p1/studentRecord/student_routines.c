#include <stdio.h>
#include <stdlib.h>


#include "student_record.h"

student_t* parse_records(char* records[], int nr_records);
int dump_entries(student_t* entries, int nr_entries, FILE* students);
student_t* read_student_file(FILE* students, int* nr_entries);
char* loadstr(FILE* students);