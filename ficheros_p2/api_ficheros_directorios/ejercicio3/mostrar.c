#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{

	/* Variables */
	int fd1, opt;
	struct stat sb;

	/* Comprobamos que se pasan dos argumentos */
	if (argc < 3)
	{
		printf("Uso: %s <flag : -n ó -e> <fichero> <N> \n", argv[0]);
		exit(1);
	}

	int pos;

	if (argv[3] == NULL)
		pos = 0;
	else
		pos = atoi(argv[3]);

	/* Abrimos el archivo */
	if ((fd1 = open(argv[2], O_RDONLY)) == -1)
	{
		perror("No se puede abrir el archivo de origen\n");
		exit(1);
	}

	if (stat(argv[2], &sb) == -1)
	{
		perror("stat");
		exit(EXIT_FAILURE);
	}

	printf("Total file size: %lu bytes\n", sb.st_size);
	int size = sb.st_size;
	char buffer[size];

	// Leemos file
	read(fd1, buffer, size);

	while ((opt = getopt(argc, argv, "ne:")) != -1)
	{
		switch (opt)
		{
		case 'n':
			write(1, buffer, pos);
			break;
		case 'e':
			lseek(fd1, pos, SEEK_SET);
			read(fd1, buffer, size - pos);
			write(1, buffer, size);
			break;
		default: /* '?' */
			fprintf(stderr, "Uso: %s <flag : -n ó -e> <fichero> <N> \n", argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	// printf("> %s \n", buffer);

	return 0;
}
