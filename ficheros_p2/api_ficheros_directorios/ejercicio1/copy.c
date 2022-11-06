#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

char buffer[512];

void copy(int fdo, int fdd)
{

	ssize_t bytes_read;


	printf("Comienzo de COPIA\n");
	/* Bucle de lectura/escritura */
	while ((bytes_read = read(fdo, &buffer, sizeof(char))) > 0)
	{
		write(fdd, &buffer, bytes_read);
	}


}

int main(int argc, char *argv[])
{

	/* Variables */
	int fd1, fd2;

	/* Comprobamos que se pasan dos argumentos */
	if (argc != 3)
	{
		printf("Uso: %s <origen> <destino>\n", argv[0]);
		exit(1);
	}

	/* Abrimos los dos archivos */
	if ((fd1 = open( argv[1], O_RDONLY | O_CREAT )) == -1)
	{
		perror("No se puede abrir el archivo de origen\n");
		exit(1);
	}

	if ((fd2 = open( argv[2], O_WRONLY | O_CREAT | O_TRUNC)) == -1)
	{
		perror("No se puede abrir el archivo de destino\n");
		exit(1);
	}

	copy(fd1,fd2);

	/* Cierre de archivos */
	close(fd1);
	close(fd2);

	return 0;
}
