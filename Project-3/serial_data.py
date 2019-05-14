from graphics import *
import serial
from serial import Serial
import struct

win = GraphWin(width = 200, height = 200)
win.setCoords(0, 0, 10, 10) # set the coordinates of the window; bottom left is (0, 0) and top right is (10, 10)
mySquare = Rectangle(Point(1, 1), Point(9, 9)) # create a rectangle from (1, 1) to (9, 9)
mySquare.draw(win)


count=0
index=0
num=0
num_of_bars=10
array=[]
float_array=[]
ser=serial.Serial('COM3',115200,timeout=1)
i=0

RectArray=[]
while(index<10):
    RectArray.append(Rectangle(Point(1,index+1),Point(9,index+2)));
    index+=1
while(num<num_of_bars):
        RectArray[num].draw(win);
        num+=1

while True:
    j=0
    while count<5:
        array.append(ser.readline().decode('utf-8'))
        count+=1
    count=0
    while(j<len(array)-1):
        i=0
        while(i<(int(array[j])/10000)):
            count+=1
            RectArray[i].setFill("green")
            print(count)
            time.sleep(0.05)
            i+=1
        i=0
        while(i<num_of_bars):
            RectArray[i].setFill("black")
            i+=1
        j+=1
        del array[:]


