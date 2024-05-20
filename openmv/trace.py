import sensor, image, time, math, ustruct
from pyb import UART

uart = UART(3,115200)#初始化串口3，波特率为115200
uart.init(115200 ,bits = 8 ,parity = None ,stop = 1)#停止位8位，优先级无，停止位1
# 追踪黑线。使用 [(128, 255)] 追踪白线.
GRAYSCALE_THRESHOLD = [(0, 64)]
# 下面是一个 roi【区域】元组列表。每个 roi 用 (x, y, w, h)表示的矩形。
# 本例程的采样图像为 160*120，列表把 roi 把图像分成 3 个矩形，越靠近的摄像头
#视野（通常为图像下方）的矩形权重越大。
ROIS = [
 (0, 100, 160, 20, 0.7), # 可以根据不同机器人情况进行调整。
 (0, 50, 160, 20, 0.3),
 (0, 0, 160, 20, 0.1)
 ]
# 计算以上 3 个矩形的权值【weight】的和，和不需要一定为 1.
weight_sum = 0
for r in ROIS: weight_sum += r[4] # r[4] 为矩形权重值.
# 摄像头配置
sensor.reset() # 初始化.
sensor.set_pixformat(sensor.GRAYSCALE) # 使用灰度图像.
sensor.set_framesize(sensor.QQVGA) # 使用 QQVGA 分辨率（160*120）.
sensor.skip_frames(time = 1000) # 等待摄像头稳定.
sensor.set_auto_gain(False) # 必须关闭自动增益
sensor.set_auto_whitebal(False) # 必须关闭白平衡
clock = time.clock() # Tracks FPS.

def Sending_data(buffer_1 ,buffer_2):
    global uart
    global data
    data=ustruct.pack("<bbiib",
                      0x2C,
                      0x12,
                      int(buffer_1),
                      int(buffer_2),
                      0x5B)
    uart.write(data)


while(True):
    clock.tick() # Track elapsed milliseconds between snapshots().
    img = sensor.snapshot() # 实时拍照.
    centroid_sum = 0
    for r in ROIS:
        blobs = img.find_blobs(GRAYSCALE_THRESHOLD, roi=r[0:4],merge=True) # r[0:4] 是上面定义的 roi 元组.
        if blobs:
 # Find the blob with the most pixels.
            largest_blob = max(blobs, key=lambda b: b.pixels())
 # Draw a rect around the blob.
            img.draw_rectangle(largest_blob.rect())
            img.draw_cross(largest_blob.cx(), largest_blob.cy())

    centroid_sum += largest_blob.cx() * r[4]
    center_pos = (centroid_sum / weight_sum) # 确定直线的中心.
 # 将直线中心位置转换成角度，便于机器人处理.
    deflection_volue = 0
 # 使用反正切函数计算直线中心偏离角度。可以自行画图理解
#权重 X 坐标落在图像左半部分记作正偏，落在右边部分记为负偏，
#所以计算结果加负号。
    deflection_volue = -math.atan((center_pos-80)/60)
 # 将偏离值转换成偏离角度.
    deflection_angle = math.degrees(deflection_volue)

#    OUT_DATA =bytearray([0x2C,0x12,buffer_1, buffer_2,  buffer_3, 0x5B ])#发送数据包
#    uart.write(OUT_DATA)
    time.sleep_ms(1000)
    Sending_data((int)(center_pos*100),(int)(deflection_angle*10))

 # 计算偏离角度后可以控制机器人进行调整.
    print(data)
    print(center_pos)
    print("Turn Angle: %f" % deflection_angle)

    print(clock.fps())
