import sys
import serial
import time

ser=serial.Serial (“/dev/ttyACM1”)
ser.baudrate=9600
fp=open(‘/dev/hidraw0’,’rb’)

m=0
T=True
ser.open()

while True:
   m=0
while T:
buffer=fp.read(8)
for c in buffer:
          d=0
iford(c)>0:
              d=ord(c)-29
              m=m+d
if d==11:
            T=False
  Print m
ser.write(str(m))
  T=True
Time.sleep(5)
print “\n”
ser.close()

