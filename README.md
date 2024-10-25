# Datos de la máquina
Procesador: AMD Ryzen 9 5900X 12-Core Proceessor (24 CPUs),~3.7GHz

Memoria RAM: 32768MB

GPU: NVIDIA GeForce RTX 3070

# Datos recopilados

|N                           | Tiempo Secuencial (s) | Tiempo Paralelo 24 hilos (s) | Tiempo Paralelo 48 hilos (s) |
|----------------------------|-----------------------|------------------------------|------------------------------|
|1                           | 10.86                 | 09.72 🔴                     | 09.70 🔴                    |
|2                           | 10.58                 | 10.06                        | 10.10                        |
|3                           | 10.34                 | 10.31  🔴                    | 11.42 🔴                    |
|4                           | 11.43 🔴              | 10.23                        | 09.91                        |
|5                           | 10.42 🔴              | 09.72                        | 09.65                        |
|Promedio (eliminando peores)| 10.59                 | 10.00                        | 9.89                         |


# Speedup

|Speedup 24 hilos|Speedup 48 hilos|
|----------------|----------------|
|1.06            |1.07            |

# Discución

Los speedup obtenidos para 24 hilos y 48 hilos, fueron 106% y 107% respectivamente, no fueron considerablemente mejores, pero sí hubo diferencia.

Esto quiere decir o según lo que logro analizar: El algoritmo probablemente no se beneficia de una mayor cantidad de hilos. Según lo que entendí sobre **Numba** este tipo de operaciones se ven mejor reflejadas si son realizadas por la **GPU**, en nuestro caso estamos utilizando la **CPU** para ello. Además sería bueno revizar el algoritmo para encontrar en donde está haciendo operaciones de sincronización ya que esto podría desbalancear la carga de éste.