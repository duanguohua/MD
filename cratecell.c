/* ֻ��Ҫ�������ݾ��ܵõ�ÿ�������ϵ�Ԫ�������ͱ߳�����Ԫ������ 
    1��ģ����ӱ߳�box[3] 
    2��verlet���ڱ�İ뾶 
*/


#include <stdio.h>


double box[3] = {22.156400, 22.156400, 22.156400};      //ģ����ӳߴ� 
double rm = 5.2;            //verlet���ڱ�İ뾶 

int cellside[3];            //���������ϵ�Ԫ���� 
int Nc;
double cellbox[3];          //Ԫ���ı߳�
 
void CalcuSubcell(void);    //�õ�Ԫ����


int main(void)
{

    CalcuSubcell();
    return 0;
}



//�õ�Ԫ������Ԫ���߳�
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
        //�õ�һ�������ϵĵ�Ԫ������Ԫ���߳� 
        cellside[i]--;
        cellbox[i] = box[i]/cellside[i];
        Nc *= cellside[i];
    }
    printf("%d\n", Nc);
}


//Ϊÿһ�����ӷ���Ԫ���ţ�������Ԫ���б�
 
