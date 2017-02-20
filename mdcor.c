#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>


/*++++++++++++++++++++++++++全局常量+++++++++++++++++++++++++++++++++++*/
#define MAXN 10000
int nside = 7;                  //模拟盒上每个方向上的晶格数量 
const double a0 = 3.1652;       //晶格常数 


/*++++++++++++++++++++++++++全局变量+++++++++++++++++++++++++++++++++++*/
int N;      //体系原子总数 
double cor[MAXN][3] = {0.0};            //体系坐标数组
double v[MAXN][3] = {0.0};              //体系速度数组 
double box[3] = {0.0};                  //模拟盒子尺寸 


/*++++++++++++++++++++++++++函数原型+++++++++++++++++++++++++++++++++++*/
void test(void);

/*------------------产生坐标-------------------*/
int BccCor(int side);           //产生一个bcc体系中的原子坐标 
void OutputCor(void);           //输出体系原子坐标到cor.txt文件

/*------------------输出参数-------------------*/
void OutputPara(void);

/*------------------产生速度-------------------*/
void InitialVelocity(void);     //产生初速度
double GaussRand(void);         //产生高斯随机数
void OutputVelocity(void);      //输出速度到v.txt文件 

/*++++++++++++++++++++++++++主函数+++++++++++++++++++++++++++++++++++*/
int main(void)
{
    test();
    
    return 0;
}


/*++++++++++++++++++++++++++函数实现+++++++++++++++++++++++++++++++++++*/

/*---------------------测试函数-----------------------------*/ 
void test(void)
{
    N = BccCor(nside);      //产生坐标，确定原子数 
    OutputCor();            //输出坐标到cor.txt
    
    OutputPara();           //输出体系参数 
    
    InitialVelocity();      //初始化速度 
    OutputVelocity();       //输出速度 
     
}

/*---------------------产生坐标的函数-----------------------*/
/*
产生一个bcc体系中的原子坐标 
int side, 为模拟盒子的每条边上的晶格数量 
*/
int BccCor(int side)
{
	
	int i, j, k;
	int cnt = 0;       //记录体系中原子个数 
	
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

	return cnt;        //返回体系原子总数 
}

/*输出体系原子坐标到cor.txt文件*/
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


/*---------------------输出体系参数---------------------------*/
void OutputPara(void)
{
	
	/*模拟盒子尺寸*/
	int i;
	for (i=0; i<3; i++)
	{
	    box[i] = a0 * nside;
    }
	/*输出参数*/
	
	FILE *fp = fopen("para.txt", "w");
	
	fprintf(fp, "原子总数N:\t%d\n", N);
	fprintf(fp, "晶格常数a0:\t%d\n", a0);
	fprintf(fp, "盒子每条边上晶格数为：\t%d\t%d\t%d\n", 
                nside, nside, nside);
	fprintf(fp, "盒子边长: \t%lf\t%lf\t%lf\n", 
                box[0], box[1], box[2]);
	
	fclose(fp);
}

/*---------------------产生初速度的函数-----------------------*/
void InitialVelocity(void)
{   
	int i, j;
	double vall[3] = {0.0};    //速度的和与平均数 
	
	//分配Gauss随机数
	for (i=0; i<N; i++)
    {
		for (j=0; j<3; j++)
        {
			v[i][j] = GaussRand();
			vall[j] +=  v[i][j];
		}
	}
	
	//动量守恒， 求各方向上平均速度 
	for (i=0; i<3; i++)		
		vall[i] /= N; 
	
	for (i=0; i<N; i++)
    {
		for (j=0; j<3; j++)
        {
			v[i][j] -= vall[j];
		}
	}
	//速度标定
    //0K下应该不使用温度标定 
    
}

//利用box-muller变换法，产生高斯随机数
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

//输出速度到v.txt文件 
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



