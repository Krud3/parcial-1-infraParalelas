from PIL import Image
import numpy as np
import sys
import os

if len(sys.argv) != 2:
  print("Proveer el nombre de un archivo PNG")
  sys.exit(1)

IMAGE_FILE = sys.argv[1]
FILENAME = os.path.splitext(os.path.basename(IMAGE_FILE))[0]
OUTPUT_FILE = f"{FILENAME}.bin"

# Cargar la imagen y convertirla a escala de grises
imagen = Image.open(IMAGE_FILE).convert('L')  # 'L' convierte a escala de grises
# se agrega el dinamismo en el tamanio tanto para ancho como para largo
width, height = imagen.size  # Obtener dimensiones dinámicas

# Convertir la imagen a un array de NumPy
array_imagen = np.array(imagen)

# Guardar ancho y alto como int32 al inicio del archivo binario
with open(OUTPUT_FILE, 'wb') as f:
    np.int32(width).tofile(f)
    np.int32(height).tofile(f)
    array_imagen.astype('int32').tofile(f)
