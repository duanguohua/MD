#include <stdio.h>




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




