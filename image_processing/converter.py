#######################################################################
#
#
#
#######################################################################

import os

def show_files():
    print("\nFiles:")
    os.chdir('samples/')
    filelist = os.listdir('.')
    for fichier in filelist[:]: # filelist[:] makes a copy of filelist.
        if not(fichier.endswith(".txt")):
            filelist.remove(fichier)
    print(filelist)
    print("\n")
    return filelist

def main():
    file_name = show_files()
    #file_name = input("File Name: ")
    file = open(file_name[0], "r")
    classifications_array = file.readline().split(',')[:-1]
    print(classifications_array[396])
    img_num = len(classifications_array)
    print(img_num)
    file.close()

if __name__ == "__main__":
    main()
