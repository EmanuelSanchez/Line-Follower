#######################################################################
#
#   Script to show the images and classifier them
#
#######################################################################

import cv2
import numpy as np
import shutil
import os
import sys

# Variables to group the classications
readings = {'0':'None', '1':'Line', '2':'Curve', '3':'Bifurcatión', '4':'Pre-bifurcation:left', '5':'Pre-bifurcation:right', '6':'Pre-bifurcation:wrong'}
path = ""
img_name = ""

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

def images_list():
    filelist = os.listdir(path)
    list = []
    i = 0
    for file in filelist:
        list.append(filelist[i][:-4])
        i+=1
    list.sort(key=int)
    return list

def show_menu():
    print("\nOptions:")
    for i in range(0,7):        #Show the options
        print("\t"+str(i)+" - "+readings[str(i)])
    print("\n\t n  - No clasify")
    print("\t e  - Exit\n")

def show_image(img):
    while(True):
        cv2.namedWindow(img_name, cv2.WINDOW_NORMAL)
        cv2.resizeWindow(img_name, 300, 300)
        cv2.imshow(img_name,img)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
        elif cv2.waitKey(1) & 0xFF == ord('e'):
            sys.exit(0)
    cv2.destroyAllWindows()

def write_classification(option, file):
    file.write(option)
    file.write(",")

def classify(img, file):
    while(True):
            cv2.namedWindow(img_name, cv2.WINDOW_NORMAL)
            cv2.resizeWindow(img_name, 300, 300)
            cv2.imshow(img_name,img)
            if cv2.waitKey(0) & 0xFF == ord('q'):
                break
            elif cv2.waitKey(0) & 0xFF == ord('e'):
                file.close()
                sys.exit(0)
            '''
            if cv2.waitKey(1) & 0xFF == ord("0"):
                option = 0
                print(readings[str(option)])
                write_classification()
                break
            elif cv2.waitKey(1) & 0xFF == ord("1"):
                option = 1
                print(readings[str(option)])
                write_classification()
                break
            elif cv2.waitKey(1) & 0xFF == ord("2"):
                option = 2
                print(readings[str(option)])
                write_classification()
                break
            elif cv2.waitKey(1) & 0xFF == ord('e'):
                sys.exit(0)
            elif cv2.waitKey(1) & 0xFF == ord('n'):
                pass
            '''
    while(1):
        option = input("Option: ")
        cv2.destroyAllWindows()
        if(option == "n"):
            print("No classify\n")
            break
        elif(option == "x"):
            if(not(os.path.isdir("backup"+file.name[:-4]))):
                os.mkdir("backup"+file.name[:-4])
            shutil.move(path+"/"+img_name, "backup"+file.name[:-4]+"/")
            break
        elif(option == "0"):
            print(readings[str(option)])
            print("\n")
            write_classification(option, file)
            break
        elif(option == "1"):
            print(readings[str(option)])
            print("\n")
            write_classification(option, file)
            break
        elif(option == "2"):
            print(readings[str(option)])
            print("\n")
            write_classification(option, file)
            break
        elif(option == "3"):
            print(readings[str(option)])
            print("\n")
            write_classification(option, file)
            break
        elif(option == "4"):
            print(readings[str(option)])
            print("\n")
            write_classification(option, file)
            break
        elif(option == "5"):
            print(readings[str(option)])
            print("\n")
            write_classification(option, file)
            break
        elif(option == "6"):
            print(readings[str(option)])
            print("\n")
            write_classification(option, file)
            break
        else:
            print("Wrong Option:")


def main():
    global path
    path = set_directory()
    list = images_list()
    show_menu()
    file = open("classification_"+path+".txt", 'a')
    for i in list:
        global img_name
        img_name = str(i)+'.png'
        img = cv2.imread(path+"/"+str(i)+'.png')
        classify(img, file)
    file.close()

if __name__ == "__main__":
 	main()
