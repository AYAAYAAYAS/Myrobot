from pyb import UART
import sensor, image, time ,ustruct

         # Note: OpenMV Cam runs about half as fast when connected

uart=UART(3,115200)#初始化串口
uart.init(115200 ,bits = 8 ,parity=None ,stop=1)#波特率115200 8位 优先级无 停止位1

red_threshold  = (2, 12, -56, 2, -75, 14)#测试所用，白色，懒得该名称
sensor.reset()     # 初始化摄像头
sensor.set_pixformat(sensor.GRAYSCALE)#GRAYSCAL：灰度图像，每像素 8 位（1 字节），处理速度快；
                                      #RGB565:每像素为16位（2字节）5位用于红色 6位用于绿色 5位用于蓝色处理速度比灰度图像要慢
                                      #BAYER:占空间小，仅捕捉图像用，不可做图像处理。
sensor.set_framesize(sensor.QVGA)   # 设置像素
sensor.skip_frames(time = 1000)     # 跳过帧数
sensor.set_auto_whitebal(False)

clock = time.clock()                # Create a clock object to track the FPS、

def find_max(blobs):
    max_size=0
    for blob in blobs:
        if blob[2]*blob[3] > max_size:
            max_blob=blob
            max_size = blob[2]*blob[3]
    return max_blob

def Sending_data(cx,cy,cw,ch):
    global uart;
    data=ustruct.pack("<bbhhhhb",
                0x2c,
                0x12,
                int(cx),
                int(cy),
                int(cw),
                int(ch),
                0x5B)
     uart.write(data);

while(True):
    clock.tick()                    # Update the FPS clock.
    img = sensor.snapshot()         # Take a picture and return the image.
    blobs = img.find_blobs([red_threshold])
    if blobs:
        max_blob = find_max(blobs)
        img.draw_rectangle(max_blob.rect()) # rect
        img.draw_cross(max_blob.cx(), max_blob.cy()) # cx, cy
        cx=max_blob[5]
        cy=max_blob[6]
        cw=max_blob[2]
        ch=max_blob[3]
        OUT_DATA =bytearray([0x2C,0x12,cx,cy,cw,ch,0x5B])
        uart.write(OUT_DATA)
        print(OUT_DATA)






