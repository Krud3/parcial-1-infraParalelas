#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>  //openmp

// Definir el número de hilos como una variable global
int NUM_THREADS = 48;  // numero de hilos

// Funciones placeholder para la carga y guardado de imágenes
void cargarImagen(int *imagen, int width, int height, FILE *archivo);
void guardarImagen(int *imagen, int width, int height, FILE *archivo);

// Función para aplicar un filtro simple
void aplicarFiltro(int *imagen, int *imagenProcesada, int width, int height);

// Función para calcular la suma de los píxeles (como una estadística)
int calcularSumaPixeles(int *imagen, int width, int height);

char *filename;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <nombre_de_archivo>\n", argv[0]);
        exit(1);
    }

    filename = argv[1];
    int width, height;

    // Abrir el archivo binario para lectura
    FILE *archivo = fopen(filename, "rb");
    if (archivo == NULL) {
        perror("Error al abrir el archivo para cargar la imagen");
        exit(1);
    }

    // Leer ancho y alto
    fread(&width, sizeof(int), 1, archivo);
    fread(&height, sizeof(int), 1, archivo);
    
    // Asignar memoria basada en dimensiones dinámicas
    int *imagen = (int *)malloc(width * height * sizeof(int));
    int *imagenProcesada = (int *)malloc(width * height * sizeof(int));

    if (imagen == NULL || imagenProcesada == NULL) {
        perror("Error al asignar memoria para las imágenes");
        fclose(archivo);
        exit(1);
    }

    // Leer los datos de la imagen
    cargarImagen(imagen, width, height, archivo);
    fclose(archivo);

    // Configuración de los hilos
    omp_set_num_threads(NUM_THREADS);
    printf("Número de hilos: %d\n", NUM_THREADS);
    printf("Dimensiones de la imagen: %d x %d\n", width, height);

    // Aplicar filtro (paralelizable)
    aplicarFiltro(imagen, imagenProcesada, width, height);

    // Calcular suma de píxeles (parte paralelizable)
    int sumaPixeles = calcularSumaPixeles(imagenProcesada, width, height);

    printf("Suma de píxeles: %d\n", sumaPixeles);

    // Guardar la imagen procesada en un nuevo archivo binario
    char output_filename[512];
    snprintf(output_filename, sizeof(output_filename), "%s.new", filename);
    FILE *archivo_salida = fopen(output_filename, "wb");
    if (archivo_salida == NULL) {
        perror("Error al abrir el archivo para guardar la imagen");
        free(imagen);
        free(imagenProcesada);
        exit(1);
    }

    // Escribir ancho y alto en el archivo de salida
    fwrite(&width, sizeof(int), 1, archivo_salida);
    fwrite(&height, sizeof(int), 1, archivo_salida);

    // Escribir los datos de la imagen procesada
    guardarImagen(imagenProcesada, width, height, archivo_salida);
    fclose(archivo_salida);

    free(imagen);
    free(imagenProcesada);
    return 0;
}

// Carga una imagen desde un archivo binario
void cargarImagen(int *imagen, int width, int height, FILE *archivo) {
    size_t elementosLeidos = fread(imagen, sizeof(int), width * height, archivo);
    if (elementosLeidos != width * height) {
        perror("Error al leer la imagen desde el archivo");
        exit(1);
    }
}

// Guarda una imagen en un archivo binario
void guardarImagen(int *imagen, int width, int height, FILE *archivo) {
    size_t elementosEscritos = fwrite(imagen, sizeof(int), width * height, archivo);
    if (elementosEscritos != width * height) {
        perror("Error al escribir la imagen en el archivo");
        fclose(archivo);
        exit(1);
    }
}

void aplicarFiltro(int *imagen, int *imagenProcesada, int width, int height) {
    int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int Gy[3][3] = {
        {-1, -2, -1},
        {0,  0,  0},
        {1,  2,  1}
    };

    // Paralelizar el bucle externo que recorre las filas de la imagen usando OpenMP.
    #pragma omp parallel for shared(imagen, imagenProcesada, width, height, Gx, Gy)
    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            int sumX = 0;
            int sumY = 0;

            // Aplicar máscaras de Sobel (Gx y Gy)
            for (int ky = -1; ky <= 1; ky++) {
                for (int kx = -1; kx <= 1; kx++) {
                    sumX += imagen[(y + ky) * width + (x + kx)] * Gx[ky + 1][kx + 1];
                    sumY += imagen[(y + ky) * width + (x + kx)] * Gy[ky + 1][kx + 1];
                }
            }

            // Calcular magnitud del gradiente
            int magnitude = abs(sumX) + abs(sumY);
            imagenProcesada[y * width + x] = (magnitude > 255) ? 255 : magnitude;  // Normalizar a 8 bits
        }
    }
}

int calcularSumaPixeles(int *imagen, int width, int height) {
    int suma = 0;

    // Paralelizar el bucle con reducción
    #pragma omp parallel for reduction(+:suma) 
    for (int i = 0; i < width * height; i++) {
        suma += imagen[i];
    }

    return suma;
}
