#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

char buffer[512];
ssize_t nbytes, bufsiz;
struct stat sb;

void copy(int fdo, int fdd)
{
	ssize_t bytes_read;

	printf("Comienzo de COPIA de fichero regular\n");
	/* Bucle de lectura/escritura */
	while ((bytes_read = read(fdo, &buffer, sizeof(char))) > 0)
	{
		write(fdd, &buffer, bytes_read);
	}
}

void copy_regular(char *orig, char *dest)
{
}

void copy_link(char *orig, char *dest)
{
	char *bufOrigen;
	bufsiz = sb.st_size + 1;
	bufOrigen = malloc(bufsiz);
	nbytes = readlink(orig, bufOrigen, bufsiz);

	if (nbytes == -1)
	{
		perror("XXX -> ERROR readlink");
		exit(EXIT_FAILURE);
	}
	bufOrigen = strcat(bufOrigen, "\0");

	printf("'%s' points to '%.*s'\n", orig, (int)nbytes, bufOrigen);

	// Symlink function
	int sl = symlink(bufOrigen, dest);

	if (sl == -1)
	{
		printf("Error al crear el symlink  \n");
	}

	free(bufOrigen);
}

int main(int argc, char *argv[])
{

	/* Variables */
	int fd1, fd2;

	/* Comprobamos que se pasan dos argumentos */
	if (argc < 3)
	{
		printf("Uso: %s <origen> <destino>\n", argv[0]);
		exit(1);
	}

	/* Abrimos los dos archivos */
	if ((fd1 = open(argv[1], O_RDONLY | O_CREAT)) == -1)
	{
		perror("No se puede abrir el archivo de origen\n");
		exit(1);
	}

	if ((fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC)) == -1)
	{
		perror("No se puede abrir el archivo de destino\n");
		exit(1);
	}

	if (lstat(argv[1], &sb) == -1)
	{
		perror("lstat");
		exit(EXIT_FAILURE);
	}

	printf("---> File type: ");

	switch (sb.st_mode & S_IFMT)
	{
	case S_IFLNK:
		printf("symlink\n");
		copy_link(argv[1], argv[3]);
		break;
	case S_IFREG:
		printf("regular file\n");
		copy(fd1, fd2);
		break;
	default:
		printf("Error\n");
		break;
	}

	/* Cierre de archivos */
	close(fd1);
	close(fd2);

	return 0;
}
