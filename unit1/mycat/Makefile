# Nombre del compilador
CC = gcc

# Opciones del compilador
CFLAGS = -Wall -g

# El nombre del archivo ejecutable
TARGET = main

# Instrucciones para compilar el programa
all: $(TARGET)

$(TARGET): main.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o

# Regla para generar el archivo objeto main.o
main.o: main.c
	$(CC) $(CFLAGS) -c main.c

# Limpiar archivos compilados
clean:
	rm -f $(TARGET) *.o
