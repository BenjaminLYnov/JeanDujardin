import os

# Create build folder
nom_dossier = "build"
if not os.path.exists(nom_dossier):
    os.makedirs(nom_dossier)

# do cmake ..
os.system("cd " + os.getcwd() + "/build/" + " && cmake ..")