import cv2
import numpy as np
from Deal import ImageDeal as ImaD
import serial
# import ustruct
import binascii
if __name__ == "__main__":
    cap = cv2.VideoCapture(0)
    # cap.set(3,640)
    # cap.set(4,640)
    # uart2 = serial.Serial(port="/dev/ttyAMA1",baudrate=115200)
    # xc1, yc1, xc2, yc2 = 427, 432, 427, 432
    # send_data = [0xA4,xc1,yc1,xc2,yc2,0xD2]                    
    #send_data=ustruct.pack("<bbhhhhb",send_data)   
    # a=uart2.read()
    
    while True:
        ret,frame = cap.read()
        # frame = frame[200:640,320:760]
        # print(send_data)
        
        # xc1b, yc1b, xc2b, yc2b = xc1, yc1, xc2, yc2

        xc1, yc1 = ImaD.trace_redlaser(frame)
        # ImaD.trace_laser(frame)
        # uart2.write(send_data)
        # ImaD.process_frame(frame)
        # ImaD.black_process(frame)
        ImaD.ShapeDetection(frame)

        # if xc2 == None:
        #     xc1, yc1, xc2, yc2 = xc1b, yc1b, xc2b, yc2b
        # xc2, yc2 = xc2 + wStart, yc2 + hStart
        # print('红色激光点坐标:', xc2, yc2)
        # I_D.ShapeDetection(frame)
        # cv2.imshow('sd',frame)
        print(xc1, yc1)
        if cv2.waitKey(100) & 0xff == ord('q'):
            break
    cap.release()
    cv2.destroyAllWindows()

