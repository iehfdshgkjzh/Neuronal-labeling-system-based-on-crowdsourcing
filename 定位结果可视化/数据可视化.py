def Data_Visual(file1,file2):
    import matplotlib
    import numpy as np
    import matplotlib.pyplot as plt
    from mpl_toolkits.mplot3d import Axes3D
    import Excel读写 as excel

    data_1 = excel.read_excel(file1)
    data_2 = excel.read_excel(file2)

    x_1, y_1, z_1 = [], [], []
    for i in data_1:
        x_1.append(i[0])
        y_1.append(i[1])
        z_1.append(i[2])
    x, y, z = np.array(x_1), np.array(y_1), np.array(z_1)
    ax = plt.subplot(111, projection='3d')  # 创建一个三维的绘图工程
    ax.scatter(x, y, z, c='y')  # 绘制数据点

    x_2, y_2, z_2 = [], [], []
    for i in data_2:
        x_2.append(i[0])
        y_2.append(i[1])
        z_2.append(i[2])
    x, y, z = np.array(x_2), np.array(y_2), np.array(z_2)
    ax = plt.subplot(111, projection='3d')  # 创建一个三维的绘图工程
    ax.scatter(x, y, z, c='b')  # 绘制数据点

    ax.set_zlabel('Z')  # 坐标轴
    ax.set_ylabel('Y')
    ax.set_xlabel('X')

    plt.show()
