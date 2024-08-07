import cv2
import mediapipe as mp
import math
import serial
import time
from threading import Thread, Lock
from queue import Queue
import struct
import asyncio
import websockets

str__ = 0
password=[0]
flag =0
uart2=None
RES=None
lock=Lock()

async def echo(websocket, path):
    async for message in websocket:
        await websocket.send(message)
        uart2.write(message.encode())
        print(message)

def vector_2d_angle(v1,v2):
    '''
        求解二维向量的角度
    '''
    v1_x=v1[0]
    v1_y=v1[1]
    v2_x=v2[0]
    v2_y=v2[1]
    try:
        angle_= math.degrees(math.acos((v1_x*v2_x+v1_y*v2_y)/(((v1_x**2+v1_y**2)**0.5)*((v2_x**2+v2_y**2)**0.5))))
    except:
        angle_ =65535.
    if angle_ > 180.:
        angle_ = 65535.
    return angle_
def hand_angle(hand_):
    '''
        获取对应手相关向量的二维角度,根据角度确定手势
    '''
    angle_list = []
    #---------------------------- thumb 大拇指角度
    angle_ = vector_2d_angle(
        ((int(hand_[0][0])- int(hand_[2][0])),(int(hand_[0][1])-int(hand_[2][1]))),
        ((int(hand_[3][0])- int(hand_[4][0])),(int(hand_[3][1])- int(hand_[4][1])))
        )
    angle_list.append(angle_)
    #---------------------------- index 食指角度
    angle_ = vector_2d_angle(
        ((int(hand_[0][0])-int(hand_[6][0])),(int(hand_[0][1])- int(hand_[6][1]))),
        ((int(hand_[7][0])- int(hand_[8][0])),(int(hand_[7][1])- int(hand_[8][1])))
        )
    angle_list.append(angle_)
    #---------------------------- middle 中指角度
    angle_ = vector_2d_angle(
        ((int(hand_[0][0])- int(hand_[10][0])),(int(hand_[0][1])- int(hand_[10][1]))),
        ((int(hand_[11][0])- int(hand_[12][0])),(int(hand_[11][1])- int(hand_[12][1])))
        )
    angle_list.append(angle_)
    #---------------------------- ring 无名指角度
    angle_ = vector_2d_angle(
        ((int(hand_[0][0])- int(hand_[14][0])),(int(hand_[0][1])- int(hand_[14][1]))),
        ((int(hand_[15][0])- int(hand_[16][0])),(int(hand_[15][1])- int(hand_[16][1])))
        )
    angle_list.append(angle_)
    #---------------------------- pink 小拇指角度
    angle_ = vector_2d_angle(
        ((int(hand_[0][0])- int(hand_[18][0])),(int(hand_[0][1])- int(hand_[18][1]))),
        ((int(hand_[19][0])- int(hand_[20][0])),(int(hand_[19][1])- int(hand_[20][1])))
        )
    angle_list.append(angle_)
    return angle_list

def h_gesture(angle_list,isStraight_list):
    '''
        # 二维约束的方法定义手势
        # fist five gun love one six three thumbup yeah
    '''
    thr_angle = 67.
    thr_angle_thumb = 54.
    thr_angle_s = 49.
    gesture_str = None
    if 65535. not in angle_list:
        if (angle_list[0]>thr_angle_thumb) and (angle_list[1]>thr_angle) and (angle_list[2]>thr_angle) and (angle_list[3]>thr_angle) and (angle_list[4]>thr_angle):
            gesture_str = "0"
        elif (angle_list[0]<thr_angle_s) and (angle_list[1]<thr_angle_s) and (angle_list[2]<thr_angle_s) and (angle_list[3]<thr_angle_s) and (angle_list[4]<thr_angle_s):
            gesture_str = "5"
        elif (angle_list[0]<thr_angle_s-3)  and (angle_list[1]<thr_angle_s) and (angle_list[2]>thr_angle) and (angle_list[3]>thr_angle) and (angle_list[4]>thr_angle):
            gesture_str = "8"
        elif (angle_list[0]<thr_angle_s)  and (angle_list[1]<thr_angle_s) and (angle_list[2]<thr_angle_s) and (angle_list[3]>thr_angle) and (angle_list[4]>thr_angle):
            gesture_str = "7"
        elif (angle_list[0]>5)  and (angle_list[1]<thr_angle_s) and (angle_list[2]>thr_angle) and (angle_list[3]>thr_angle) and (angle_list[4]>thr_angle):
            gesture_str = "1"
        elif (angle_list[0]<thr_angle_s)  and (angle_list[1]>thr_angle) and (angle_list[2]>thr_angle) and (angle_list[3]>thr_angle) and (angle_list[4]<thr_angle_s):
            gesture_str = "6"
        elif (angle_list[0]>thr_angle_thumb)  and (angle_list[1]<thr_angle_s) and (angle_list[2]<thr_angle_s) and (angle_list[3]<thr_angle_s) and (angle_list[4]>thr_angle):
            gesture_str = "3"
        elif (angle_list[0]>thr_angle_thumb) and (angle_list[1]<thr_angle_s) and (angle_list[2]<thr_angle_s) and (angle_list[3]<thr_angle_s) and (angle_list[4]<thr_angle):
            gesture_str="4"
        elif (angle_list[0]<thr_angle_s)  and (angle_list[1]>thr_angle) and (angle_list[2]>thr_angle) and (angle_list[3]>thr_angle) and (angle_list[4]>thr_angle):
            pass
        elif (angle_list[0]>thr_angle_thumb)  and (angle_list[1]<thr_angle_s) and (angle_list[2]<thr_angle_s) and (angle_list[3]>thr_angle) and (angle_list[4]>thr_angle):
            gesture_str = "2"
        elif (angle_list[0] < 20) and (angle_list[1] >thr_angle) and (angle_list[2]>thr_angle) and ( angle_list[3]>thr_angle) and (angle_list[4] >thr_angle):
            gesture_str = "9"
    return gesture_str
  
def get_angleError(point_4,point_3,point_2,point_1):
    try:
        point_4_cx, point_4_cy = int(point_4.x * w), int(point_4.y * h)
        point_3_cx, point_3_cy = int(point_3.x * w), int(point_3.y * h)
        point_2_cx, point_2_cy = int(point_2.x * w), int(point_2.y * h)
        point_1_cx, point_1_cy = int(point_1.x * w), int(point_1.y * h)

        angle_1 = math.degrees(math.atan((point_3_cx - point_4_cx) / (point_3_cy - point_4_cy)))
        angle_2 = math.degrees(math.atan((point_1_cx - point_2_cx) / (point_1_cy - point_2_cy)))
        angle_error = abs(angle_1 - angle_2)
        if angle_error<12:
            isStraight = 1
        else:
            isStraight = 0
    except:
        angle_error = 1000
        isStraight = 0

    return angle_error, isStraight


"""
匹配手势
"""
def match_num(value):
    print("--------------------------------")
    match value:
        case "0":
            uart2.write(value.encode())
        case "1":
            uart2.write(value.encode())
        case "2":
            uart2.write(value.encode())
        case "3":
            uart2.write(value.encode())
        case "4":
            uart2.write(value.encode())
        case "5":
            uart2.write(value.encode())
        case "6":
            uart2.write(value.encode())
        case "7":
            uart2.write(value.encode())
        case "8":
            uart2.write(value.encode())
        case "9":
            uart2.write(value.encode())

def send_password():
    start_flag = 0x2c
    separator_flag = 0x2a
    end_flag = 0x5b
    uart2.write(bytearray([start_flag]))
    uart2.write(bytearray([separator_flag]))
    print("start_flag", hex(start_flag), "separator_flag", hex(separator_flag))
    for p in password:      
        uart2.write(bytearray([int(p)]))
    uart2.write(bytearray([end_flag]))
    print("end_flag", hex(end_flag))

def detect(queue):
    global str__
    global flag
    global uart2
    global RES
    global password  # 声明 password 为全局变量
    mp_drawing = mp.solutions.drawing_utils
    mp_hands = mp.solutions.hands
    hands = mp_hands.Hands(
        static_image_mode=False,
        max_num_hands=1,
        min_detection_confidence=0.75,
        min_tracking_confidence=0.75
    )
    cap = cv2.VideoCapture(0)
    uart2.timeout = 0.1
    password = []

    while True:
        ret, frame = cap.read()
        frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        frame = cv2.flip(frame, 1)
        results = hands.process(frame)
        frame = cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)
        size = uart2.inWaiting()
        if size != 0:
            flag = uart2.read(size=1)
            hex_flag = flag.hex()
            uart2.flushInput()
            RES = int(hex_flag, 16)
            print("start", RES, type(RES))

        if results.multi_hand_landmarks:
            for hand_landmarks in results.multi_hand_landmarks:
                mp_drawing.draw_landmarks(frame, hand_landmarks, mp_hands.HAND_CONNECTIONS)
                hand_local = []
                for i in range(21):
                    x = hand_landmarks.landmark[i].x * frame.shape[1]
                    y = hand_landmarks.landmark[i].y * frame.shape[0]
                    hand_local.append((x, y))
                if hand_local:
                    angle_list = hand_angle(hand_local)
                    isStraight_list = []

                    for i in range(1, 5):
                        angle_error, isStraight = get_angleError(hand_local[i], hand_local[i + 4], hand_local[i + 8], hand_local[i + 12])
                        isStraight_list.append(isStraight)
                    gesture_str = h_gesture(angle_list, isStraight_list)

                    if gesture_str:
                        if RES == 28:
                            with lock:
                                thread_1 = Thread(target=Serial_thread, args=(queue, frame, gesture_str))
                                thread_1.start()
                                thread_1.join(timeout=0.3)
                                while not queue.empty():
                                    queue.get()

                                if len(password)== 4:  
                                    print("Sending password...")
                                    send_password()
                                    password.clear()
                                    RES = 0  # Reset RES to avoid multiple sends

                        thread_1 = Thread(target=Serial_thread, args=(queue, frame, gesture_str))
                        thread_1.start()
                        thread_1.join(timeout=0.2)
                        while not queue.empty():
                            queue.get()
                    else:
                        str__ = None
                    cv2.putText(frame, gesture_str, (0, 100), 0, 1.3, (0, 0, 255), 3)
       
            
            # password = [gesture_str] * 8  # 更新 password
           

        cv2.imshow('MediaPipe Hands', frame)
        if cv2.waitKey(1) & 0xFF == 27:
            break
    cap.release()
    cv2.destroyAllWindows()

def Serial_thread(queue,frame,gesture_str):
    global str__
    global RES
    cv2.putText(frame,"wait",(200,100),0,1.3,(0,0,255),3)

    if gesture_str == str__:
            queue.put("done")
    else :
        match_num(gesture_str)       
        str__ = gesture_str
        queue.put("done") 
        if RES == 28:
            password.append(str__)

        
def main():
    global uart2
    #asyncio.get_event_loop().run_until_complete(websockets.serve(echo, '0.0.0.0', 9988))
    #asyncio.get_event_loop().run_forever()
    uart2 = serial.Serial(port="/dev/ttyAMA1",baudrate=115200)
    queue = Queue()
    separator_thread = Thread(target=detect, args=(queue,))
    separator_thread.start()
    separator_thread.join()
    
if __name__ == '__main__':

    #detect()
    main()
