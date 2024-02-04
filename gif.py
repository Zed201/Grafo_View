import imageio.v2 as imageio
import os
# varre todos os png da pasta de imagens para criar o gif

output = "out.gif"

caminhos = []
for root, dirs, files in os.walk("./images"):
    for file in files:
        caminhos.append(os.path.join(root, file))

#print(sorted(caminhos))
with imageio.get_writer(output, fps=0.7) as file:
    for caminho in sorted(caminhos):
        file.append_data(imageio.imread(caminho))
        

