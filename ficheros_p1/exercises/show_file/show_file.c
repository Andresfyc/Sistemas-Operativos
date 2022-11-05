#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#define NUM_ALPHA  5

int main(int argc, char* argv[]) {
	FILE* file; FILE*file2;

    char buffer[5];
    char buffer2[5];


	if (argc!=3) {
        fprintf(stderr,"Usage: %s <file_name> <file_name_2> \n",argv[0]);
		exit(1);
	}

	/* Open file*/
	if ((file = fopen(argv[1], "r")) == NULL)
		err(2,"The input file %s could not be opened",argv[1]);

    if ((file2 = fopen(argv[2], "w+")) == NULL)
        err(2,"The input file %s could not be opened",argv[2]);

    int c = fread(&buffer, sizeof( char ), 5, file );
    printf( "Number of characters read = %i\n", c );
    printf("File 1 -> %s",buffer);

    fclose(file);
    fwrite(&buffer, sizeof(char), 5 , file2);

    fseek(file2, 0 , SEEK_SET);
    int c2 = fread(&buffer2, sizeof(char), 5, file2 );
    printf( "Number of characters read 2= %i\n", c2 );
    printf("File 2 -> %s",buffer2);



    fclose(file2);

    return 0;
}
