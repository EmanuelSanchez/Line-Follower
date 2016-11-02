##########################################
#
#   Program to clasifier the images to
#   the ANN
#
##########################################

import cv2
import numpy as np
import os
import shutil
import sys

# Variables to group the classications
readings = {'0':'None', '1':'Line', '2':'Curve', '3':'Bifurcatión', '4':'Pre-bifurcation:left', '5':'Pre-bifurcation:right', '6':'Pre-bifurcation:wrong'}

img_name = ""

def set_directory():
    print("\nFolders:")
    os.chdir('samples/')
    for base, dirs, files in os.walk('.'):
        print(base[2:])
    while(1):
        try:
            path = input("\nFolder path (path/example/): ")
            os.chdir(path)
            break
        except:
            print("\n\tWrong Path\n")

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

'''
0- Image Acondition
'''

def image_acondition(img):
    img = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    ret,img = cv2.threshold(img,160,255,cv2.THRESH_BINARY)
    return img

'''
1- Detect Bifurcations
    1.1- detect lines
    1.2- detect intersections between lines
'''

# Probabilistic Hough Transform to detect lines

def detect_lines(img):
    lines = cv2.HoughLinesP(img,1,np.pi/180,3,3,2)
    print(lines)
    for x1,y1,x2,y2 in lines[0]:
        cv2.line(img,(x1,y1),(x2,y2),(0,150,0),2)
    show_image(img)
    return img

# Finds the intersection of two lines, or returns false.
# The lines are defined by (o1, p1) and (o2, p2).

# proof this to all points in lines array (every combination)
'''
def intersection(int o1, int p1, int o2, int p2, int &r):
    int x = o2 - o1
    int d1 = p1 - o1
    int d2 = p2 - o2

    float cross = d1.x*d2.y - d1.y*d2.x;
    if (abs(cross) < /*EPS*/1e-8)
        return false;

    double t1 = (x.x * d2.y - x.y * d2.x)/cross;
    r = o1 + d1 * t1;
    return true;
'''

'''
2- Detect Pre-bifurcations
'''

#Left

#Right

'''
3- Detect Curves
'''

# no se si sea mejor encontrar lineas debido a la probabilidad y luego lo demás

def main():
    set_directory()
    imagelist = os.listdir('.')
    for image in imagelist:
        global img_name
        img_name = image
        img = cv2.imread(image)
        img_acond = image_acondition(img)
        try:
            show_image(img_acond)
            img_lines = detect_lines(img_acond)
        except:
            pass


if __name__ == "__main__":
    main()
