# Datos de la máquina
Procesador: AMD Ryzen 9 5900X 12-Core Proceessor (24 CPUs),~3.7GHz

Memoria RAM: 32768MB

GPU: NVIDIA GeForce RTX 3070

# Datos recopilados

|N                           | Tiempo Secuencial (s) | Tiempo Paralelo 24 hilos (s) | Tiempo Paralelo 48 hilos (s) |
|----------------------------|-----------------------|------------------------------|------------------------------|
|1                           | 1.20                  | 1.17                         | **1.39** 🔴                    |
|2                           | 1.07                  | **1.73** 🔴                   | 1.58                         |
|3                           | **1.02** 🔴           | 1.43                         | **2.35** 🔴                   |
|4                           | **1.27** 🔴             | **0.98** 🔴                   | 1.84                         |
|5                           | 1.19                  | 1.56                         | 1.48                         |
|Promedio (eliminando peores)| 1.15                  | 1.39                         | 1.63                         |


# Speedup

|Speedup 24 hilos|Speedup 48 hilos|
|----------------|----------------|
|0.83            |0.71            |

# Discución

Los speedup obtenidos para 24 hilos y 48 hilos, fueron menores a 1. Esto indica que no hubo mejora de rendimiento al paralelizar (en mi caso) el bucle que controlaba el aplicar el filtro.

Esto quiere decir o según lo que logro analizar: El algoritmo no se beneficia de una mayor cantidad de hilos. Según lo que entendí sobre **Numba** este tipo de operaciones se ven mejor reflejadas si son realizadas por la **GPU**, en nuestro caso estamos utilizando la **CPU** para ello. Además sería bueno revizar el algoritmo para encontrar en donde está haciendo operaciones de sincronización ya que esto podría desbalancear la carga de éste.