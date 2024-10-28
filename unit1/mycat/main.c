#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 1024

void error_handler(const char *sms)
{
    fprintf(stderr, "Error en %s: %s\n", sms, strerror(errno));
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    char buffer[BUFFER_SIZE];
    ssize_t bytes_leidos;

    // Caso cuando no se proporcionan argumentos, leer desde stdin
    if (argc == 1)
    {
        while ((bytes_leidos = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0)
        {
            if (write(STDOUT_FILENO, buffer, bytes_leidos) == -1)
            {
                error_handler("escritura en stdout");
            }
        }
        if (bytes_leidos == -1)
        {
            error_handler("lectura de stdin");
        }
    }
    // Caso cuando se proporciona un nombre de archivo como argumento
    else if (argc == 2)
    {
        int fd = open(argv[1], O_RDONLY);
        if (fd == -1)
        {
            error_handler("apertura del archivo");
        }
        while ((bytes_leidos = read(fd, buffer, BUFFER_SIZE)) > 0)
        {
            if (write(STDOUT_FILENO, buffer, bytes_leidos) == -1)
            {
                error_handler("escritura en stdout");
            }
        }
        if (bytes_leidos == -1)
        {
            error_handler("lectura del archivo");
        }
        close(fd);
    }
    // Demasiados argumentos proporcionados
    else
    {
        fprintf(stderr, "Uso: %s [nombre de archivo]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    return 0;
}
