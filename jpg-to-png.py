import os
from PIL import Image

input_dir = "images"  #change to your directory
output_dir = "converted_png"  

if not os.path.exists(output_dir):
    os.makedirs(output_dir)

for filename in os.listdir(input_dir):
    if filename.endswith(".jpg") or filename.endswith(".jpeg"):
       
        img_path = os.path.join(input_dir, filename)
        img = Image.open(img_path)

        png_filename = os.path.splitext(filename)[0] + ".png"
        output_path = os.path.join(output_dir, png_filename)

        img.save(output_path)
