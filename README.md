# PainterScript
PainterScript
这个软件是用于生成图片的，你可以通过一些指令来生成你想要的图片。


在这个版本中调用PainterScript的API类似调用c语言的函数
注释是 ####
API后的各个参数之间用空格隔开，字符串直接写可以有空格，用#结尾
完整API列表（int 表示整数,bool 用1和0表示true和false，##表示字符串, []表示可选）：
0. resize int int == 设置宽度和高度：width， height    [0, +∞] 如何没有这条语句默认为640*480 
0. ouput  path == 输出图片
0. clear == 清空，用背景色填充

 1. foregroundcolor int int int  ==设置前景色：r g b   [0, 255]           
 1. backgroundcolor int int int  ==设置背景色：r g b   [0, 255]     
  
 2. line int int int int ==画线：起点的x，起点的y，终点的x，终点的y   [0, +∞]      
 
 3. rectangle int int int int   ==  画长方形：x, y, width, height        [0, +∞]  
 3. fillrectangle int int int int == 填充长方形：x, y, width, height      [0, +∞]  

 4. ellipse int int int int int == 画椭圆：x, y, width, height   [0, +∞] 
 4. fillellipse int int int int == 用前景色填充椭圆：x, y, width, height [0, +∞] 

 5. arc int int int int int int == 画圆弧：x, y, width, height, 起点的角度[0, 360], 终点的角度[0, 360]
 5. fillarc int int int int int int == 填充圆弧为扇形：x, y, width, height, 起点的角度[0, 360], 终点的角度[0, 360]

 6. string int int ## [int] [int] [##] [int] [int] [int] [bool] [bool] [bool] 
== 输出字符串：x, y, 文字内容
    ，字符的高度， 字符的宽度， 字体， 整体的转动角度0.1度为一个单位[0,3600], 单个字的转动角度0.1度为一个单位[0,3600]
    ,字体的粗细[0, 900], 是否为斜体， 是否有下划线， 是否有删除线

 7. image x y path [width|0] [height|0] [0|1] [maskpath] [maskwidth|0] [maskheight|0]
    == 位置x[0, width], ，y[0, height], 路径， 拉伸， [0:原图黑色边缘|1：原图白色边缘]使用这一位表示原图带了掩码， 掩码图路径，掩码图拉
    伸

8. polygon x0 y0 x1 y1 x2 y2 [...]   画多边形, 最少3个点最多20个点
8. polygon x0 y0 x1 y1 x2 y2 [...]   填充多边形


如：

resize 800 100

foregroundcolor 255 0 0
backgroundcolor 0 0 0

string 150 0 你好,世界# 100 0 asd# 0 0 500 0 0 0 

output D:/test.jpg#
