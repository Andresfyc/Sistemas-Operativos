#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "student_record.h"


char use[] = "Usage: ./student-records -f file [ -h | -l | -c | -a | -q [ -i|-n ID] ] ] [ list of records ] \n";

student_t *parse_records(char *records[], int nr_records)
{
	FILE* passwd;
	char line[MAX_CHARS_NIF+1];
	student_t* records;
	student_t* cur_records;
	int line_count=0;
	char* token;
	char* lineptr;
	student_t token_id;
	int entry_idx;

	/*if ((passwd=fopen("/etc/passwd","r"))==NULL) {
		fprintf(stderr, "/etc/passwd could not be opened: ");
		perror(NULL);
		return NULL;
	}*/

	/* Calcula el número de líneas */
	//while (fgets(line, MAX_PASSWD_LINE + 1, passwd) != NULL)
		//line_count++;

	/* Indicador de posición de rebobinado */
	//fseek(passwd,0,SEEK_SET);

	records=malloc(sizeof(student_t)*line_count);
	/* cero llenar la matriz de estructuras */
	//memset(entries,0,sizeof(passwd_entry_t)*line_count);

	/* Analizar archivo*/
	entry_idx=0;
	while (fgets(line, MAX_CHARS_NIF + 1, passwd) != NULL) {
		/* Señale el principio de la línea */
		lineptr=line;
		//token_id=student_id;
		cur_records=&records[entry_idx];

		while((token = strsep(&lineptr, ":"))!=NULL) {
			switch(token_id) {
			case LOGIN_NAME_IDX:
				strcpy(cur_entry->login_name,token);
				break;
			case ENCRYPTED_PASS_IDX:
				cur_entry->optional_encrypted_passwd=clone_string(token);
				break;
			case UID_IDX:
				if (sscanf(token,"%d",&cur_entry->uid)!=1) {
					fprintf(stderr, "No se pudo analizar el campo UID en la línea %d de /etc/passwd. ficha es %s\n",entry_idx+1, token);
					return NULL;
				}
				break;
			case GID_IDX:
				if (sscanf(token,"%d",&cur_entry->gid)!=1) {
					fprintf(stderr, "No se pudo analizar el campo GID en la línea %d de /etc/passwd. ficha es %s\n",entry_idx+1, token);
					return NULL;
				}
				break;
			case USER_NAME_IDX:
				cur_entry->user_name=clone_string(token);
				break;
			case USER_HOME_IDX:
				cur_entry->user_home=clone_string(token);
				break;
			case USER_SHELL_IDX:
				/* remove new line from token */
				token[strlen(token)-1]='\0';
				cur_entry->user_shell=clone_string(token);
				break;
			default:
				break;
			}
			token_id++;
		}
		if (token_id!=NR_FIELDS_PASSWD) {
			fprintf(stderr, "No se pudieron procesar todos los tokens de la línea %d de /etc/passwd\n",entry_idx+1);
			return NULL;
		}

		entry_idx++;
	}
	(*nr_entries)=line_count;
	return entries;
}


int dump_entries(student_t *entries, int nr_entries, FILE *students)
{
	int nr_entries;
	int i;
	char* records;
	student_t* ent=parse_passwd(records,&nr_entries);

	if (!ent)
		return EXIT_FAILURE;

	for (i=0; i<nr_entries; i++) {
		student_t* e=&ent[i]; /* Apunta a la entrada actual */
		switch (entries->output_mode) {
		case VERBOSE_MODE:
			fprintf(options->outfile,"[Entry #%d]\n",i);
			fprintf(options->outfile,"\tlogin=%s\n\tenc_pass=%s\n\t"
			        "uid=%d\n\tgid=%d\n\tuser_name=%s\n\t"
			        "home=%s\n\tshell=%s\n",
			        e->login_name, e->optional_encrypted_passwd,
			        e->uid, e->gid,e->user_name,
			        e->user_home, e->user_shell);
			break;
		case PIPE_MODE:
			fprintf(options->outfile,"|%s|%s|%d|%d|%s|%s|%s|\n",
			        e->login_name, e->optional_encrypted_passwd,
			        e->uid, e->gid,e->user_name,
			        e->user_home, e->user_shell);
		}

	}
	free_entries(entries,nr_entries);
	return EXIT_SUCCESS;
}


student_t *read_student_file(FILE *students, int *nr_entries)
{

}

char *loadstr(FILE *students)
{

}


int main(int argc, char *argv[])
{

	if (argc < 2)
	{
		fprintf(stderr, "> ERROR: %s", use);
		exit(EXIT_FAILURE);
	}

	int opt;

	while ((opt = getopt(argc, argv, "hclaq:")) != -1)
	{
		switch (opt)
		{
		case 'h':
			fprintf(stderr, "%s", use);
			exit(0);
		case 'c':
			// options.output_mode=VERBOSE_MODE;
			break;
		case 'l':
			// options.output_mode=PIPE_MODE;
			break;
		case 'a':

			break;
		case 'q':

			break;
		default:
			exit(EXIT_FAILURE);
		}
	}
}
