import numpy as np
from PIL import Image
from tifffile import *
import os

Input_File_Name = 'temp.tif'

# 建立输出文件夹
os.mkdir('D:\桌面\大创项目\PRO_图像分割\图像分割结果\\'+Input_File_Name)
os.mkdir('D:\桌面\大创项目\PRO_图像分割\图像分割结果\\'+Input_File_Name+"\\initial data")
os.mkdir('D:\桌面\大创项目\PRO_图像分割\图像分割结果\\'+Input_File_Name+"\\data")

program_path = 'D:\桌面\大创项目\PRO_图像分割\Python实现\\'
input_path = 'D:\桌面\大创项目\PRO_图像分割\Python实现\\'
out_path = 'D:\桌面\大创项目\PRO_图像分割\图像分割结果\\'+Input_File_Name+"\\initial data"
out_file_path = 'D:\桌面\大创项目\PRO_图像分割\图像分割结果\\'+Input_File_Name+"\\data"


FirstImArray = imread(Input_File_Name,key = 1)  # 图片存放路径
width = FirstImArray.shape[0]
CutNum = 4

a = int(width/CutNum)
# 小正方体的边长

# 将每一帧图片切割并保存
def Cut():
    for i in range(CutNum):
        for j in range(CutNum):
            im_mini = im[i*a:a+i*a ,j*a:a+j*a]
            if slice in range(0,width,a):
                # 建立存放每个小块数据的文件夹
                os.makedirs(out_path+'\\im_'+str(q)+"_"+str(i)+'_'+str(j))
            os.chdir(out_path+'\\im_'+str(q)+"_"+str(i)+'_'+str(j))
            Image.fromarray(im_mini).save('im_'+str(i)+"_"+str(j)+'_'+str(slice)+'.jpg')
            #图片格式：im_横向编号(x方向)_纵向编号(y方向)_来源于的帧数(z方向)

# 遍历每一帧图片
for q in range(CutNum):
    for slice in range(q*a,q*a+a):
        im = imread(input_path+'temp.tif',key = slice)  # tiff文件存放的路径
        Cut()
        os.chdir(program_path) # 程序所在的路径

# 将单张JPG图片合并为tiff格式图片
def JPG_TIFF():
    # 遍历每个小文件夹
    for s in os.listdir(out_path):
        # ['im_0_0_0', 'im_0_0_1', 'im_0_0_10', 'im_0_0_11',

        # 打开小文件夹，获取其中的图片
        ls = os.listdir(out_path + "\\" + s)

        # 将小文件夹中的图片按顺序排列
        ls_1 = []
        for i in ls:
            ls_1.append(int(i[7:-4]))
        d = dict(zip(ls,ls_1))
        # print(d)
        ls = (sorted(d, key=d.__getitem__))

        #构建图片集
        pic_all = []
        for i in ls:
            pic_1 = np.array(Image.open(out_path+"\\"+s+'\\'+i))
            pic_all.append(pic_1)

        # 将图片集转化为三维数组
        pic_all = np.array(pic_all)

        # 将三维数组转化为tiff图像
        os.chdir(out_file_path)
        imwrite(ls[0][:7]+str(int(ls[0][7:-4])//a)+".tif", pic_all, photometric='minisblack')

JPG_TIFF()
