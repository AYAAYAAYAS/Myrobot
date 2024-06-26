import cv2
import numpy as np
import onnxruntime as ort
import time


# 标签字典
dic_labels ={
    0: '1',
    1: 'num2'}

def plot_one_box(x, img, color=None, label=None, line_thickness=None):
    """
    绘制一个边界框到图像上
    """
    tl = (
            line_thickness or round(0.002 * (img.shape[0] + img.shape[1]) / 2) + 1
    )  # 线宽/字体厚度
    color = color or [np.random.randint(0, 255) for _ in range(3)]
    c1, c2 = (x[0], x[1]), (x[2], x[3])
    cv2.rectangle(img, c1, c2, color, thickness=tl, lineType=cv2.LINE_AA)
    if label:
        tf = max(tl - 1, 1)  # 字体厚度
        t_size = cv2.getTextSize(label, 0, fontScale=tl / 3, thickness=tf)[0]
        c2 = c1[0] + t_size[0], c1[1] - t_size[1] - 3
        cv2.rectangle(img, c1, c2, color, -1, cv2.LINE_AA)  # 填充矩形
        cv2.putText(
            img,
            label,
            (c1[0], c1[1] - 2),
            0,
            tl / 3,
            [225, 255, 255],
            thickness=tf,
            lineType=cv2.LINE_AA,
        )


# 图像预处理
def preprocess_image(image, input_size):
    img = cv2.resize(image, (input_size, input_size))
    img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    ret,img = cv2.threshold(img,40,200,cv2.THRESH_TOZERO)

    kernel = np.ones((3, 3), np.uint8)

    img = cv2.morphologyEx(img, cv2.MORPH_OPEN, kernel)
    cv2.namedWindow("1",cv2.WINDOW_KEEPRATIO)
    cv2.resizeWindow("1",320,320)
    cv2.imshow("1", img)

    img = cv2.cvtColor(img, cv2.COLOR_GRAY2RGB)

    # img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    img = img.astype(np.float32) / 255.0
    img = np.transpose(img, (2, 0, 1))  # 调整为模型输入格式
    img = np.expand_dims(img, axis=0)  # 添加批量维度


    return img


def infer_image(image, model):
    input_size = 640  # 输入模型的图像大小，这里固定为640*640
    input_data = preprocess_image(image, input_size)

    # 模型期望的输入名称为 'images'
    outputs = model.run(None, {'images': input_data})[0]

    # 直接绘制检测结果
    detected_labels = []
    for detection in outputs:
        # 提取坐标和置信度信息
        x1, y1, x2, y2 = int(detection[0]), int(detection[1]), int(detection[2]), int(detection[3])
        confidence = float(detection[4])
        class_id = int(detection[5])
        if confidence>0.3:
            label = f"{dic_labels[class_id]}: {confidence:.2f}"
            detected_labels.append(label)

            # 绘制边界框
            plot_one_box([x1, y1, x2, y2], image, label=label)
        if int(detection[5]) == 0:
            print(detection[5])

        print(f"Detected labels: {detected_labels}")  # 打印检测到的标签列表

    return image

# 主程序
if __name__ == "__main__":
    # 模型加载
    model_pb_path = "best.onnx"
    so = ort.SessionOptions()
    net = ort.InferenceSession(model_pb_path, so)

    # 打开视频流或摄像头
    video = 1  # 如果是视频文件，请替换为视频文件路径
    cap = cv2.VideoCapture(video)

    cv2.namedWindow("Video",cv2.WINDOW_KEEPRATIO)
    cv2.resizeWindow("Video",640,640)
    t1 = time.time()  # 初始化时间戳

    while True:
        success, img0 = cap.read()
        if not success:
            break

        # 进行目标检测和绘制
        img_with_detections = infer_image(img0, net)

        # 显示FPS
        cv2.putText(img_with_detections, "FPS: {:.2f}".format(1.0 / (time.time() - t1)), (50, 50), cv2.FONT_HERSHEY_COMPLEX, 1,
                    (0, 255, 0), 3)

        # 显示图像
        cv2.imshow("Video", img_with_detections)


        # 更新时间戳
        t1 = time.time()

        # 退出键设置
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    # 释放资源
    cap.release()
    cv2.destroyAllWindows()
