mdcor.c
用于产生体系的初始坐标和速度

md.c
用于进行分子动力学（MD）计算

cellneighbor.c
用于生成每个元胞的26个近邻元胞标量序号，并放在ncell.txt中以备MD主程序
来调用和读入。各元胞的近邻元胞序号，只要每条边上元胞个数确定，那么
每一个元胞的邻近元胞标量序号便确定，不变。在后序的程序调用中读入即可。
也因此，cellneighbor.c中的函数不用再并入到MD主程序中去，这样可以使主程序更加精简。