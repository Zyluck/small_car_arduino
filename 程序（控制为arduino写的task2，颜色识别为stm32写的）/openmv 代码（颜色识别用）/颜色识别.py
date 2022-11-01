import sensor, image, time
from pyb import UART
global zuo,zhong,you
zuo=0
zhong=0
you=0

red_threshold =(21, 64, 35, 83, 11, 104)#红色颜色阈值
green_threshold = (23, 66, -54, -16, -128, 127)#绿色颜色阈值
blue_threshold=(42, 0, 3, 53, -120, -30)#蓝色颜色阈值


red_color_code = 1 # code = 2^0 = 1
green_color_code = 2 # code = 2^1 = 2
blue_color_code=4 #code=2^2=4
black_color_code=8 #code=2^3=8

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA) #160*120
sensor.skip_frames(10)
sensor.set_auto_whitebal(False)
clock = time.clock()
uart = UART(3,9600)
uart.init(9600, bits=8, parity=None, stop=1)
#lcd.init()

global color
flag_color=1       #颜色检测标志位
while(flag_color==1):
    clock.tick()
    img = sensor.snapshot()
    img.draw_rectangle((12,18,86,159),color=(0x00,0x00,0x00))
    img.draw_rectangle((121,22,82,164),color=(0x00,0x00,0x00))
    img.draw_rectangle((230,11,82,159),color=(0x00,0x00,0x00))  #三个识别区的位置（根据储物位置和摄像头位置调整 ）

    blob_zuo = img.find_blobs([red_threshold,green_threshold,blue_threshold],area_threshold=200,merge=True,roi=(12,18,86,159))
    blob_zhong = img.find_blobs([red_threshold,green_threshold,blue_threshold],area_threshold=200,merge=True,roi=(121,22,82,164))
    blob_you = img.find_blobs([red_threshold,green_threshold,blue_threshold],area_threshold=200,merge=True,roi=(230,11,82,159))
    zuo=0
    you=0
    zhong=0
    ##########判断左边物块颜色
    if blob_zuo:
        for blob in blob_zuo:
            x = blob[0]
            y = blob[1]
            width = blob[2]
            height = blob[3]
            center_x = blob[5]
            center_y = blob[6]
            color_code = blob[8]
        # 添加颜色说明
            if color_code == red_color_code:
                img.draw_string(x, y - 10, "red", color = (0xFF, 0x00, 0x00))
                zuo = 1
            elif color_code == green_color_code:
                img.draw_string(x, y - 10, "green", color = (0x00, 0xFF, 0x00))
                zuo = 2
            elif color_code == blue_color_code:
                img.draw_string(x, y - 10, "blue", color = (0x00, 0x00, 0xFF))
                zuo = 3
            color=color_code
            img.draw_rectangle([x, y, width, height])
            img.draw_cross(center_x, center_y)
            #print("%d" % zuo)
            #uart.write("%d" % zuo)#串口通信传输
###################  中间颜色检测
    if blob_zhong:
        for blob in blob_zhong:
            x = blob[0]
            y = blob[1]
            width = blob[2]
            height = blob[3]
            center_x = blob[5]
            center_y = blob[6]
            color_code = blob[8]
            if color_code == red_color_code:
                img.draw_string(x, y - 10, "red", color = (0xFF, 0x00, 0x00))
                zhong = 1
            elif color_code == green_color_code:
                img.draw_string(x, y - 10, "green", color = (0x00, 0xFF, 0x00))
                zhong = 2
            elif color_code == blue_color_code:
                img.draw_string(x, y - 10, "blue", color = (0x00, 0x00, 0xFF))
                zhong = 3
            color=color_code
            img.draw_rectangle([x, y, width, height])
            img.draw_cross(center_x, center_y)
            #print("%d" % zhong)
            #uart.write("%d" % zhong)#串口通信
######################  右侧物块颜色检测
    if blob_you:
        for blob in blob_you:
            x = blob[0]
            y = blob[1]
            width = blob[2]
            height = blob[3]
            center_x = blob[5]
            center_y = blob[6]
            color_code = blob[8]
# 添加颜色说明
            if color_code == red_color_code:
                img.draw_string(x, y - 10, "red", color = (0xFF, 0x00, 0x00))
                you = 1
            elif color_code == green_color_code:
                img.draw_string(x, y - 10, "green", color = (0x00, 0xFF, 0x00))
                you = 2
            elif color_code == blue_color_code:
                img.draw_string(x, y - 10, "blue", color = (0x00, 0x00, 0xFF))
                you = 3
            color=color_code
            img.draw_rectangle([x, y, width, height])
            img.draw_cross(center_x, center_y)
            #print("%d" % you)
            #uart.write("%d" % you)#串口通信
            #time.sleep(10)
            ##########################      将检测到的颜色发送  ##############

            #elif(color_code==4):
               # print("blue")
               # command="b"
               # uart.write(command)
               # time.sleep(10)
    #print("%d" % zuo)
    #print("%d" % zhong)
    #print("%d" % you)
        if zuo != 0 and you != 0 and zhong!= 0 and zuo!=you and zuo!=zhong and you!=zhong :
            print("%d%d%d" % (zuo,zhong,you))
            uart.write ("%d%d%d" % (zuo,zhong,you))
        #if uart.any():
            #tmp_data = uart.readline()
            #if tmp_data==7:                 #检测物块颜色是否被接受
            break                       #已被接受，此函数结束
###############################################          颜色检测与串口      ####################
