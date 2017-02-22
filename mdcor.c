#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>


/*++++++++++++++++++++++++++ȫ�ֳ���+++++++++++++++++++++++++++++++++++*/
#define MAXN 10000
int nside = 7;                  //ģ�����ÿ�������ϵľ������� 
const double a0 = 3.1652;       //������ 


/*++++++++++++++++++++++++++ȫ�ֱ���+++++++++++++++++++++++++++++++++++*/
/* ȫ�ֱ���������ʱ�������Զ���ʼ��Ϊ0 */ 
int N;      //��ϵԭ������ 
double cor[MAXN][3];            //��ϵ��������
double v[MAXN][3];              //��ϵ�ٶ����� 
double box[3];                  //ģ����ӳߴ� 


//Ԫ����verlet���ڱ�Ľ���
double rm = 5.2;                //verlet���ڱ�İ뾶 
int cellside[3];                //���������ϵ�Ԫ���� 
int Nc;                         //Ԫ������
double cellbox[3];              //Ԫ���ı߳�



/*++++++++++++++++++++++++++����ԭ��+++++++++++++++++++++++++++++++++++*/
void test(void);

/*------------------��������-------------------*/
int BccCor(int side);           //����һ��bcc��ϵ�е�ԭ������ 
void OutputCor(void);           //�����ϵԭ�����굽cor.txt�ļ�

/*------------------����Ԫ��------------------*/
void CalcuSubcell(void);        //ÿ�������ϵ�Ԫ�������ͱ߳�����Ԫ������


/*------------------�������-------------------*/
void OutputPara(void);

/*------------------�����ٶ�-------------------*/
void InitialVelocity(void);     //�������ٶ�
double GaussRand(void);         //������˹�����
void OutputVelocity(void);      //����ٶȵ�v.txt�ļ� 

/*++++++++++++++++++++++++++������+++++++++++++++++++++++++++++++++++*/
int main(void)
{
    test();
    
    return 0;
}


/*++++++++++++++++++++++++++����ʵ��+++++++++++++++++++++++++++++++++++*/

/*---------------------���Ժ���-----------------------------*/ 
void test(void)
{
    N = BccCor(nside);      //�������꣬ȷ��ԭ���� 
    OutputCor();            //������굽cor.txt
    
    OutputPara();           //�����ϵ���� 
    
    InitialVelocity();      //��ʼ���ٶ� 
    OutputVelocity();       //����ٶ� 
     
}

/*---------------------��������ĺ���-----------------------*/
/*
����һ��bcc��ϵ�е�ԭ������ 
int side, Ϊģ����ӵ�ÿ�����ϵľ������� 
*/
int BccCor(int side)
{
	
	int i, j, k;
	int cnt = 0;       //��¼��ϵ��ԭ�Ӹ��� 
	
	for (i = 0; i < side; i++)
	{
		for (j = 0; j < side; j++)
		{
			for (k = 0; k < side; k++)
			{
				cor[cnt][0] = i * a0;
				cor[cnt][1] = j * a0;
				cor[cnt][2] = k * a0;
				cnt++;
				cor[cnt][0] = (i + 0.5) * a0;
				cor[cnt][1] = (j + 0.5) * a0;
				cor[cnt][2] = (k + 0.5) * a0;
				cnt++;
			}
		}
	}

	return cnt;        //������ϵԭ������ 
}

/*�����ϵԭ�����굽cor.txt�ļ�*/
void OutputCor(void)    
{
	int i;
	FILE *fp = fopen("cor.txt", "w");
	for (i=0; i<N; i++)
    {
		fprintf(fp, "%d\t%lf\t%lf\t%lf\n", i, cor[i][0], cor[i][1], cor[i][2]);		
	}	
	fclose(fp);	
}


/*---------------------�����ϵ����---------------------------*/
void OutputPara(void)
{
	
	/*ģ����ӳߴ�*/
	int i;
	for (i=0; i<3; i++)
	{
	    box[i] = a0 * nside;
    }
    /*����Ԫ����Ϣ��ÿ�������ϵ�Ԫ���������߳�����ϵ�ܵ�Ԫ����*/
    CalcuSubcell();
    
	/*�������*/
	
	FILE *fp = fopen("para.txt", "w");
	
	fprintf(fp, "ԭ������N:\t%d\n", N);
	fprintf(fp, "������a0:\t%d\n", a0);
	fprintf(fp, "����ÿ�����Ͼ�����Ϊnside��\t%d\t%d\t%d\n", 
                nside, nside, nside);
	fprintf(fp, "���ӱ߳�box[3]: \t%lf\t%lf\t%lf\n\n", 
                box[0], box[1], box[2]);
	
	fprintf(fp, "Ԫ������Nc:\t%d\n", Nc);
	fprintf(fp, "ÿ������Ԫ����Ϊcellside[3]��\t%d\t%d\t%d\n", 
                cellside[0], cellside[1], cellside[2]);
    fprintf(fp, "Ԫ���ı߳�cellbox[3]: \t%lf\t%lf\t%lf\n", 
                cellbox[0], cellbox[1], cellbox[2]);
	
	fclose(fp);
}

//ÿ�������ϵ�Ԫ�������ͱ߳�����Ԫ������
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
//    printf("%d\n", Nc);
}




/*---------------------�������ٶȵĺ���-----------------------*/
void InitialVelocity(void)
{   
	int i, j;
	double vall[3] = {0.0};    //�ٶȵĺ���ƽ���� 
	
	//����Gauss�����
	for (i=0; i<N; i++)
    {
		for (j=0; j<3; j++)
        {
			v[i][j] = GaussRand();
			vall[j] +=  v[i][j];
		}
	}
	
	//�����غ㣬 ���������ƽ���ٶ� 
	for (i=0; i<3; i++)		
		vall[i] /= N; 
	
	for (i=0; i<N; i++)
    {
		for (j=0; j<3; j++)
        {
			v[i][j] -= vall[j];
		}
	}
	//�ٶȱ궨
    //0K��Ӧ�ò�ʹ���¶ȱ궨 
    
}

//����box-muller�任����������˹�����
double GaussRand(void)
{
	static bool available = false;
	static double gset;
	double fac, rsq, v1, v2;
	
	if (! available)
    {
		do 
        {
			v1 = 2.0 * rand() / RAND_MAX - 1.0;
			v2 = 2.0 * rand() / RAND_MAX - 1.0;
			rsq = v1 * v1 + v2 * v2;
		} while (rsq >= 1.0 || rsq == 0.0);
		
		fac = sqrt(-2.0 * log(rsq)/rsq);
		gset = v1 * fac;
		available = true;
		return(v2 * fac);
	}
	else
    {
		available = false;
		return gset;
	}
}

//����ٶȵ�v.txt�ļ� 
void OutputVelocity(void)
{
    FILE *fp = fopen("v.txt", "w");
    int i;
    for (i=0; i<N; i++)
    {
        fprintf(fp, "%d\t%lf\t%lf\t%lf\n", i, v[i][0], v[i][1], v[i][2]);
    }
    fclose(fp);
}



