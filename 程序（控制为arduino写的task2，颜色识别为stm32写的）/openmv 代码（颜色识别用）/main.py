import sensor, image, time
from pyb import UART
from pyb import LED
from pyb import Pin
pin0 = Pin('P0', Pin.IN, Pin.PULL_UP)
global zuo,zhong,you
zuo=0
zhong=0
you=0
led1 = LED(1)
led2 = LED(2)
led3 = LED(3)


red1_threshold =(23, 37, 45, 66, 18, 85)#红色颜色阈值
red2_threshold = (35, 51, 57, 81, 15, 60)
red3_threshold = (29, 49, 55, 74, 24, 61)
green1_threshold = (23, 40, -67, -22, -128, 127)#绿色颜色阈值
green2_threshold = (34, 51, -59, -14, 5, 42)
green3_threshold = (31, 52, -56, -14, -128, 127)
blue1_threshold=(9, 32, -12, 20, -49, -18)#蓝色颜色阈值
blue2_threshold=(2, 36, -19, 28, -72, -11)
blue3_threshold=(10, 34, -10, 23, -51, -19)


red1_color_code = 1 # code = 2^0 = 1
red2_color_code = 2 # code = 2^1 = 2
red3_color_code=4 #code=2^2=4
green1_color_code=8 #code=2^3=8
green2_color_code=16
green3_color_code=32
blue1_color_code=64
blue2_color_code=128
blue3_color_code=256

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA) #160*120
sensor.skip_frames(10)
sensor.set_auto_whitebal(False)
clock = time.clock()
uart = UART(3,9600)
uart.init(9600, bits=8, parity=None, stop=1)

global color
flag_color=1       #颜色检测标志位
def get_Colour():
    while(flag_color==1):
        clock.tick()
        img = sensor.snapshot()
        img.draw_rectangle((23,71,48,70),color=(0x00,0x00,0x00))
        img.draw_rectangle((127,70,58,78),color=(0x00,0x00,0x00))
        img.draw_rectangle((235,70,58,77),color=(0x00,0x00,0x00))  #三个识别区的位置（根据储物位置和摄像头位置调整 ）

        blob_zuo = img.find_blobs([red1_threshold,red2_threshold,red3_threshold,green1_threshold,green2_threshold,green3_threshold,blue1_threshold,blue2_threshold,blue3_threshold],area_threshold=200,merge=True,roi=(23,71,48,70))
        blob_zhong = img.find_blobs([red1_threshold,red2_threshold,red3_threshold,green1_threshold,green2_threshold,green3_threshold,blue1_threshold,blue2_threshold,blue3_threshold],area_threshold=200,merge=True,roi=(127,70,58,78))
        blob_you = img.find_blobs([red1_threshold,red2_threshold,red3_threshold,green1_threshold,green2_threshold,green3_threshold,blue1_threshold,blue2_threshold,blue3_threshold],area_threshold=200,merge=True,roi=(235,70,58,77))
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
                if color_code == 1 or color_code == 2 or color_code == 4 :
                    img.draw_string(x, y - 10, "red", color = (0xFF, 0x00, 0x00))
                    zuo = 1
                elif color_code == 8 or color_code == 16 or color_code == 32 :
                    img.draw_string(x, y - 10, "green", color = (0x00, 0xFF, 0x00))
                    zuo = 2
                elif color_code == 64 or color_code == 128 or color_code == 256 :
                    img.draw_string(x, y - 10, "blue", color = (0x00, 0x00, 0xFF))
                    zuo = 3
                color=color_code
                img.draw_rectangle([x, y, width, height])
                img.draw_cross(center_x, center_y)
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
                if color_code == 1 or color_code == 2 or color_code == 4 :
                    img.draw_string(x, y - 10, "red", color = (0xFF, 0x00, 0x00))
                    zhong = 1
                elif color_code == 8 or color_code == 16 or color_code == 32 :
                    img.draw_string(x, y - 10, "green", color = (0x00, 0xFF, 0x00))
                    zhong = 2
                elif color_code == 64 or color_code == 128 or color_code == 256 :
                    img.draw_string(x, y - 10, "blue", color = (0x00, 0x00, 0xFF))
                    zhong = 3
                color=color_code
                img.draw_rectangle([x, y, width, height])
                img.draw_cross(center_x, center_y)
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
                if color_code == 1 or color_code == 2 or color_code == 4 :
                    img.draw_string(x, y - 10, "red", color = (0xFF, 0x00, 0x00))
                    you = 1
                elif color_code == 8 or color_code == 16 or color_code == 32 :
                    img.draw_string(x, y - 10, "green", color = (0x00, 0xFF, 0x00))
                    you = 2
                elif color_code == 64 or color_code == 128 or color_code == 256 :
                    img.draw_string(x, y - 10, "blue", color = (0x00, 0x00, 0xFF))
                    you = 3
                color=color_code
                img.draw_rectangle([x, y, width, height])
                img.draw_cross(center_x, center_y)

            if zuo != 0 and you != 0 and zhong!= 0 and zuo!=you and zuo!=zhong and you!=zhong :
                uart.write ("%d%d%d" % (zuo,zhong,you))
                uart.write ("%d%d%d" % (zuo,zhong,you))
                uart.write ("%d%d%d" % (zuo,zhong,you))
                uart.write ("%d%d%d" % (zuo,zhong,you))
                uart.write ("%d%d%d" % (zuo,zhong,you))
                break                    #已被接受，此函数结束
    ###############################################          颜色检测与串口      ####################
#time.sleep(500)
#while(pin0.value() != 0):
    led1.off()
led1.on()
led2.on()
led3.on()
get_Colour()

