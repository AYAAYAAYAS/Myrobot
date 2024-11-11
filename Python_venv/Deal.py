import cv2
import numpy as np

class ImageDeal:

    def trace_laser(frame):
        color_list={'red':{'down_threshold':np.array([0 , 75, 30]),'up_threshold':np.array([7 ,255 ,255])},
                    'green':{'down_threshold':np.array([0 , 75, 30]),'up_threshold':np.array([0 , 75, 30])}
                    }
        GreenLaser = 'green'
        RedLaser = 'red'
        #frame = (frame * 0.8).clip(0, 255).astype(np.uint8)
        img_hsv= cv2.cvtColor(frame ,cv2.COLOR_BGR2HSV)
        h,s,v = cv2.split(img_hsv) 
        v = cv2.equalizeHist(v)
        img_hsv = cv2.merge([h,s,v])
        
        Green_hsv = cv2.inRange(img_hsv,color_list[GreenLaser]['down_threshold'],color_list[GreenLaser]['up_threshold'])
        Red_hsv = cv2.inRange(img_hsv,color_list[RedLaser]['down_threshold'],color_list[RedLaser]['up_threshold'])
        element = cv2.getStructuringElement(cv2.MORPH_RECT,(5,5))

        frame_R = cv2.morphologyEx(Red_hsv, cv2.MORPH_OPEN, element)
        frame_R = cv2.morphologyEx(Red_hsv, cv2.MORPH_CLOSE, element)

        frame_G = cv2.morphologyEx(Green_hsv, cv2.MORPH_OPEN, element)
        frame_G = cv2.morphologyEx(Green_hsv, cv2.MORPH_CLOSE, element)
        
        try:
            counter_r, _ = cv2.findContours(frame_R,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
            
            if counter_r :
                L_CR = max(counter_r,key = cv2.contourArea)
                M = cv2.moments(L_CR)
                if(M["m00"]!=0):
                    target_rx = int(M["m10"]/M["m00"])
                    target_ry = int(M["m01"]/M["m00"])
                    cv2.line(frame,(target_rx-5,target_ry),(target_rx+5,target_ry),(255,0,0),3)
                    cv2.line(frame,(target_rx,target_ry-5),(target_rx,target_ry+5),(255,0,0),3)
        except:
            print("1")
        
        try:
            counter_g, _ = cv2.findContours(frame_G,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
            if counter_g:
                L_CG = max(counter_r,key = cv2.contourArea)
                M = cv2.moments(L_CG)
                if(M["m00"]!=0):
                    target_gx = int(M["m10"]/M["m00"])
                    target_gy = int(M["m01"]/M["m00"])
                    cv2.line(frame,(target_gx-5,target_gy),(target_gx+5,target_gy),(0,0,255),3)
                    cv2.line(frame,(target_gx,target_gy-5),(target_gx,target_gy+5),(0,0,255),3)
        except:
            print("2")

        cv2.imshow("frame",frame)
        cv2.imshow("R",frame_R)
        #cv2.imshow("G",frame_G)
        # return target_rx,target_ry,target_gx,target_gy

    def trace_redlaser(frame):
        target_rx,target_ry,target_gx,target_gy =None,None,None,None
        frame = (frame * 0.8).clip(0, 255).astype(np.uint8)
        img_hsv= cv2.cvtColor(frame ,cv2.COLOR_BGR2HSV)
        h,s,v = cv2.split(img_hsv)
        v = cv2.equalizeHist(v)
        img_hsv = cv2.merge([h,s,v])
        
        red_down = np.array([0 , 75, 50])
        red_upper = np.array([7 ,255 ,255])

        Red_hsv = cv2.inRange(img_hsv,red_down,red_upper)
        element = cv2.getStructuringElement(cv2.MORPH_RECT,(7,7))

        frame_R = cv2.morphologyEx(Red_hsv, cv2.MORPH_OPEN, element)
        frame_R = cv2.morphologyEx(Red_hsv, cv2.MORPH_CLOSE, element)
        
        try:
            counter_r,_= cv2.findContours(frame_R,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
            if  counter_r:
                CR = max(counter_r,key = cv2.contourArea)
                M = cv2.moments(CR)
                target_rx = int(M["m10"]/M["m00"])
                target_ry = int(M["m01"]/M["m00"])
                cv2.line(frame,(target_rx-5,target_ry),(target_rx+5,target_ry),(0,0,255),3)
                cv2.line(frame,(target_rx,target_ry-5),(target_rx,target_ry+5),(0,0,255),3)
                rect = cv2.minAreaRect(CR)
                box = cv2.boxPoints(rect)
        except:
            print("1")
        cv2.imshow("R",frame) 
        cv2.imshow("frame_R",frame_R)   
        return target_rx,target_ry
    
    def ShapeDetection(img):

        img = cv2.medianBlur(img,7)
        img_hsv= cv2.cvtColor(img ,cv2.COLOR_BGR2HSV)
        h,s,v = cv2.split(img_hsv)
        v = cv2.equalizeHist(v)
        img_hsv = cv2.merge([h,s,v])
        img_gray = cv2.cvtColor(img_hsv,cv2.COLOR_HSV2RGB)
        img_gray = cv2.cvtColor(img_gray,cv2.COLOR_RGB2GRAY)
        img_blur = cv2.GaussianBlur(img_gray,(9,9),-1)
        img_blur = cv2.Canny(img_blur,66,70)
        cv2.imshow("img_blur",img_blur)
        contours,hierarchy = cv2.findContours(img_blur,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_NONE)
        if contours:
            for obj in contours:
                max_con = max(obj , key = cv2.contourArea)
                perimeter = cv2.arcLength(obj ,True)
                approx = cv2.approxPolyDP(obj ,0.02*perimeter,True)
                CornerNum = len(approx)   #轮廓角点的数量
                x, y, w, h = cv2.boundingRect(approx)  #获取坐标值和宽度、高度
                if CornerNum ==3: objType ="triangle"
                elif CornerNum == 4:               
                    for i in range(0,4):
                        print("矩形角坐标%d:"%(i+1),approx[i][0][0], approx[i][0][1])
                        cv2.circle(img, (approx[i][0][0], approx[i][0][1]), 5, (0,255,255), 3)
                box = cv2.boxPoints(cv2.minAreaRect(max_con))
                box = np.int32(box)
                cv2.drawContours(img,[box],0,(255,0,0),2) 
        # for obj in contours:
        #     area=cv2.contourArea(obj)    
        #     cv2.drawContours(img, obj , -1, (255, 0, 0), 4) 
        #     perimeter = cv2.arcLength(obj ,True) 
        #     approx = cv2.approxPolyDP(obj ,0.02*perimeter,True)  
        #     CornerNum = len(approx)   #轮廓角点的数量
        #     x, y, w, h = cv2.boundingRect(approx)  #获取坐标值和宽度、高度
        #     if CornerNum ==3: objType ="triangle"
        #     elif CornerNum == 4:               
        #         for i in range(0,4):
        #             print("矩形角坐标%d:"%(i+1),approx[i][0][0], approx[i][0][1])
        #             cv2.circle(img, (approx[i][0][0], approx[i][0][1]), 5, (0,255,255), 3)
        cv2.imshow("4",img)

    def process_frame(img):
        drawing = np.zeros(img.shape, np.uint8)
        frame = cv2.bilateralFilter(img, 5, 50, 100)  # 滤波
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        _, binary = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY_INV)
        contours, _ = cv2.findContours(binary, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        rectangles = []
        for contour in contours:
            # 近似轮廓为多边形
            epsilon = 0.02 * cv2.arcLength(contour, True)
            approx = cv2.approxPolyDP(contour, epsilon, True)
            area = cv2.contourArea(contour)
            # 检查多边形是否有4个顶点
            if len(approx) == 4 and area > 25000:
                rectangles.append(approx)
                # 绘制轮廓（可选，用于可视化）
                cv2.drawContours(drawing, [approx], -1, (0, 255, 0), 3)

                # 获取矩形的四个角点
                rect_points = approx.reshape(4, 2)
                for point in rect_points:
                    x, y = point.ravel()
                    cv2.circle(img, (int(x), int(y)), 8, (255, 0, 0), -1)
        cv2.imshow("2",img)
        return img, drawing, rectangles    
    def black_process(img):
        
        frame = cv2.bilateralFilter(img, 5, 50, 100)  # 滤波
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        _, binary = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY_INV)
        contours, _ = cv2.findContours(binary, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        if contours:
            max_con = max(contours , key = cv2.contourArea)

            box = cv2.boxPoints(cv2.minAreaRect(max_con))
            box = np.int32(box)
            cv2.drawContours(img,[box],0,(255,0,0),2) 
        cv2.imshow("fas",img)    


           

