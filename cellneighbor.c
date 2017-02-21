/*
利用nc[3]的数据，来得到ncell[Nc][26]的数据
也就是，由模拟盒子每个方向上的元胞数来得到每个元胞的近邻元胞标量序号
此ncell[Nc][26]中数据一产生，即不会发生改变。 
*/ 

#include <stdio.h>



#define Nc 27               //Nc = nc[0] * nc[1] * nc[2];
int nc[3] = {3, 3, 3};     //假设模拟盒子中，每边上的元胞数 

/*每个元胞其26个近邻元胞标量序号，
不含其自身，因为下标即其自身 */
int ncell[Nc][26];          //本程序只为产生ncell[Nc][26]中的数据 


void CellNeighbor(void);                                    //每个元胞其26个近邻元胞标量序号
int CellVecto2Scale(int cx, int cy, int cz);                //由元胞向量序号得到其标量序号 
void CellNeighborScale(int cell, int cx, int cy, int cz);   //由元胞向量序号得到其所有近邻元胞的标题序号
void CellPeriod(int *a, int period);                        //对元胞在每个方向上执行周期性条件  

void test(void);
int main(void)
{
    test();
    
    return 0;
}

void test(void) 
{
/*    int i, tmp;
    for (i = -1; i < 4; i++)
    {
        tmp = i;
        CellPeriod(&tmp, 3);
        printf("%d ", tmp);
    }*/
    CellNeighbor();
    
    int i, j;
    for (i = 0; i < Nc; i++)
    {
        printf("%d ", i);
        for (j = 0; j < 26; j++)
        {
            printf("%d ", ncell[i][j]);
        }
        putchar('\n');
    }
}

/*每个元胞其26个近邻元胞标量序号*/
void CellNeighbor(void)
{
    int i, j, k, cell;
    i = j = k = cell = 0;
    
    for (i = 0; i < nc[0]; i++)
    {
        for (j = 0; j < nc[1]; j++)
        {
            for (k = 0; k < nc[2]; k++)
            {
                //当前元胞的标量序号
                cell = CellVecto2Scale(i, j, k);      
                CellNeighborScale(cell, i, j, k);
            }
        }
    }
}

//由元胞向量序号得到其标量序号 
int CellVecto2Scale(int cx, int cy, int cz)
{
    return nc[0] * nc[1] * cx + nc[2] * cy + cz;
}

//由元胞向量序号得到其所有近邻元胞的标题序号
/*
int cell, 当前元胞的标量序号 
int cx, int cy, int cz, 当前元胞的向量序号 
*/
void CellNeighborScale(int cell, int cx, int cy, int cz)
{
    int i, j, k;
    int celltmp, tmpcx, tmpcy, tmpcz;   //临时元胞标量和向量序号 
    int cnt = 0;                        //计数器 
    
    /*
    还应注意到元胞的周期性边界条件 
    周期性边界应施加在元胞的向量序号上，
    而非标量序号 
    */
    for (i = -1; i < 2; i++)
    {
        tmpcx = cx + i;
        CellPeriod(&tmpcx, nc[0]);          //施加周期性边界条件 
        for (j = -1; j < 2; j++)
        {
            tmpcy = cy + j;
            CellPeriod(&tmpcy, nc[1]);      //施加周期性边界条件
            for (k = -1; k < 2; k++)
            {
                tmpcz = cz + k;
                CellPeriod(&tmpcz, nc[2]);  //施加周期性边界条件
                
                if (!i && !j && !k)         //不计算当前元胞标量号 
                {
                    continue;
                }
                
                celltmp = CellVecto2Scale(tmpcx, tmpcy, tmpcz);
                ncell[cell][cnt] = celltmp;
                cnt++;
            }
        }
    }
}

//对元胞在每个方向上执行周期性条件 
void CellPeriod(int *a, int period)
{
    if (*a < 0)
    {
        *a += period;
    }
    else if (*a >= period)
    {
        *a -= period;
    }
    else
    {
        return;
    }
}


