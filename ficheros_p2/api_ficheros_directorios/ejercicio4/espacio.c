#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

DIR *folder;
struct dirent *entry;
long int contador = 0;
struct stat sb;

/* Forward declaration */
int get_size_dir(char *fname, size_t *blocks);

/* Obtiene en el búfer de bloques el tamaño del archivo fname usando lstat.
   Si fname es un directorio, se llama a get_size_dir para agregar el tamaño de su contenido.
*/

int get_size(char *fname, size_t *blocks)
{
}

/* Obtiene el número total de bloques ocupados por todos los archivos en un directorio.
   Si un archivo contenido es un directorio una llamada recursiva a get_size_dir es
   realizado. entradas y .. son convenientemente ignorados.
*/

int get_size_dir(char *dname, size_t *blocks)
{

	
	
	int files = 0;

	folder = opendir(dname);
	if (folder == NULL)
	{
		perror("Unable to read directory");
		return (1);
	}

	while ((entry = readdir(folder)))
	{
		if (strcmp (entry->d_name, ".") != 0 && strcmp (entry->d_name, "..") != 0)
		{
			files++;
			
			stat(entry->d_name, &sb);
			contador += (long long)sb.st_size;
			printf("File %3d: %s %lld\n", files, entry->d_name, (long long)sb.st_size / 1000);
		}
	}

	printf("Tamaño del archivo: %ld K\n", contador/1000);
	closedir(folder);
}

/* Procesa todos los archivos en la línea de comando llamando a get_size en ellos para
   obtiene el número de bloques de 512 B que ocupan e imprime el tamaño total en
   kilobytes en la salida estándar
*/
int main(int argc, char *argv[])
{

	

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (stat(argv[1], &sb) == -1) {
        perror("estadística");
        exit(EXIT_FAILURE);
    }
	

	printf("File type:                ");

	switch (sb.st_mode & S_IFMT)
	{
	case S_IFDIR:
		printf("directory\n");
		get_size_dir(argv[1], (size_t *)sb.st_blocks );
		break;
	case S_IFREG:
		printf("regular file\n");
		break;
	default:
		printf("unknown?\n");
		break;
	}

	

	
	printf("Tamaño de bloque de E/S preferido: %ld bytes\n",
		   (long)sb.st_blksize/100);
	printf("Tamaño del archivo: %lld bytes\n",
		   (long long)sb.st_size);
	printf("Bloques asignados: %lld\n",
		   (long long)sb.st_blocks);
	

	return 0;
}
