#######################################################################
#
#   Script to show the images
#
#######################################################################

import cv2
import os
import sys

def main():
    print("\nFolders:")
    os.chdir('samples/')
    for base, dirs, files in os.walk('.'):
        print(base[2:])
    path = input("Folder path (path/example/): ")
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
    for file in list:
        image = str(file)+'.png'
        img = cv2.imread(path+image)
        while(True):
            cv2.namedWindow(image, cv2.WINDOW_NORMAL)
            cv2.resizeWindow(image, 300, 300)
            cv2.imshow(image,img)
            if cv2.waitKey(1) & 0xFF == ord('q'):
                break
            elif cv2.waitKey(1) & 0xFF == ord('e'):
                sys.exit(0)
        cv2.destroyAllWindows()

if __name__ == "__main__":
 	main()
