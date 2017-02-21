/*
����nc[3]�����ݣ����õ�ncell[Nc][26]������
Ҳ���ǣ���ģ�����ÿ�������ϵ�Ԫ�������õ�ÿ��Ԫ���Ľ���Ԫ���������
��ncell[Nc][26]������һ�����������ᷢ���ı䡣 
*/ 

#include <stdio.h>



#define Nc 27               //Nc = nc[0] * nc[1] * nc[2];
int nc[3] = {3, 3, 3};     //����ģ������У�ÿ���ϵ�Ԫ���� 

/*ÿ��Ԫ����26������Ԫ��������ţ�
������������Ϊ�±꼴������ */
int ncell[Nc][26];          //������ֻΪ����ncell[Nc][26]�е����� 


void CellNeighbor(void);                                    //ÿ��Ԫ����26������Ԫ���������
int CellVecto2Scale(int cx, int cy, int cz);                //��Ԫ��������ŵõ��������� 
void CellNeighborScale(int cell, int cx, int cy, int cz);   //��Ԫ��������ŵõ������н���Ԫ���ı������
void CellPeriod(int *a, int period);                        //��Ԫ����ÿ��������ִ������������  

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

/*ÿ��Ԫ����26������Ԫ���������*/
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
                //��ǰԪ���ı������
                cell = CellVecto2Scale(i, j, k);      
                CellNeighborScale(cell, i, j, k);
            }
        }
    }
}

//��Ԫ��������ŵõ��������� 
int CellVecto2Scale(int cx, int cy, int cz)
{
    return nc[0] * nc[1] * cx + nc[2] * cy + cz;
}

//��Ԫ��������ŵõ������н���Ԫ���ı������
/*
int cell, ��ǰԪ���ı������ 
int cx, int cy, int cz, ��ǰԪ����������� 
*/
void CellNeighborScale(int cell, int cx, int cy, int cz)
{
    int i, j, k;
    int celltmp, tmpcx, tmpcy, tmpcz;   //��ʱԪ��������������� 
    int cnt = 0;                        //������ 
    
    /*
    ��Ӧע�⵽Ԫ���������Ա߽����� 
    �����Ա߽�Ӧʩ����Ԫ������������ϣ�
    ���Ǳ������ 
    */
    for (i = -1; i < 2; i++)
    {
        tmpcx = cx + i;
        CellPeriod(&tmpcx, nc[0]);          //ʩ�������Ա߽����� 
        for (j = -1; j < 2; j++)
        {
            tmpcy = cy + j;
            CellPeriod(&tmpcy, nc[1]);      //ʩ�������Ա߽�����
            for (k = -1; k < 2; k++)
            {
                tmpcz = cz + k;
                CellPeriod(&tmpcz, nc[2]);  //ʩ�������Ա߽�����
                
                if (!i && !j && !k)         //�����㵱ǰԪ�������� 
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

//��Ԫ����ÿ��������ִ������������ 
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


