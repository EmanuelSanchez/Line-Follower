#######################################################################
#
#   Script to rename in order the samples
#
#######################################################################


import os

def set_directory():
    print("\nFolders:")
    os.chdir('samples/')
    for base, dirs, files in os.walk('.'):
        print(base[2:])
    while(1):
        path = input("Folder path (path/example/): ")
        if (os.path.isdir(path)):
            break
        else:
            print("\tWRONG PATH")
    return  path

def main():
    global path
    path = set_directory()
    filelist = os.listdir(path)
    for fichier in filelist[:]: # filelist[:] makes a copy of filelist.
        if not(fichier.endswith(".png")):
            filelist.remove(fichier)
    list = []
    i = 0
    for file in filelist:
        list.append(filelist[i][:-4])
        i+=1
    list.sort(key=int)
    min = input("Enum From: ")
    i = int(min)
    for image in list:
        try:
            os.rename(path+"/"+image+".png", path+"/"+str(i)+".png")
            i+=1
        except:
            print("Salto en imagen: "+image+".png")
if __name__ == "__main__" :
    main()
