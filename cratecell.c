/* 只需要两个数据就能得到每个方向上的元胞数量和边长，及元胞总数 
    1、模拟盒子边长box[3] 
    2、verlet近邻表的半径 
*/


#include <stdio.h>


double box[3] = {22.156400, 22.156400, 22.156400};      //模拟盒子尺寸 
double rm = 5.2;            //verlet近邻表的半径 

int cellside[3];            //三个方向上的元胞数 
int Nc;
double cellbox[3];          //元胞的边长
 
void CalcuSubcell(void);    //得到元胞数


int main(void)
{

    CalcuSubcell();
    return 0;
}



//得到元胞数和元胞边长
void CalcuSubcell(void)
{
    int i;
    Nc = 1;
    for (i = 0 ; i < 3; i++)
    {
        cellside[i] = 1;
        cellbox[i] = box[i];
        for (; cellbox[i] > rm; cellside[i]++)
        {
            cellbox[i] = box[i]/cellside[i];
        }
        //得到一个方向上的的元胞数和元胞边长 
        cellside[i]--;
        cellbox[i] = box[i]/cellside[i];
        Nc *= cellside[i];
    }
    printf("%d\n", Nc);
}


//为每一个粒子分配元胞号，并建立元胞列表
 
