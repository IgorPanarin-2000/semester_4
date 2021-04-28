import numpy as np
from numpy import array
from PIL import Image
from sys import argv

if len(argv) < 2:
    print("Error! Not enough parameters")
    exit(-1)

try:
    image = Image.open(argv[1])
except:
    print("No such image!")
    exit(-1)
image_arr = array(image)

mbri = 0

for i in range(image_arr.shape[0]):
    for j in range(image_arr.shape[1]):
        mbri = max(mbri,int(image_arr[i][j][0])+image_arr[i][j][1]+image_arr[i][j][2])

koef = 255 * 3 / mbri

for i in range(image_arr.shape[0]):
    for j in range(image_arr.shape[1]):
        image_arr[i][j][0] = min(255,image_arr[i][j][0]*koef)
        image_arr[i][j][1] = min(255,image_arr[i][j][1]*koef)
        image_arr[i][j][2] = min(255,image_arr[i][j][2]*koef)
            
        

new_im = Image.fromarray(image_arr)
new_im.save(argv[2])