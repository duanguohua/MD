#include <stdio.h>



/*++++++++++++++++++++++++++全局常量+++++++++++++++++++++++++++++++++++*/
#define N 686                   //体系原子总数 
const double a0 = 3.1652;       //晶格常数
const int nside = 7;            //模拟盒上每个方向上的晶格数量 


/*++++++++++++++++++++++++++全局变量+++++++++++++++++++++++++++++++++++*/
double cor[N][3] = {0.0};            //体系坐标数组
double v[N][3] = {0.0};              //体系速度数组 
double box[3] = {0.0};               //模拟盒子尺寸 


/*++++++++++++++++++++++++++函数原型+++++++++++++++++++++++++++++++++++*/
void test(void);

/*------------输入坐标和速度-------------*/
void InputCor(void);            //输入原子坐标 
void InputVelocity(void);       //输入原子初速度 



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
    InputCor();
    InputVelocity();
    
}

/*---------------------输入坐标和速度-----------------------*/
//输入原子坐标 
void InputCor(void)
{
    FILE *fp = fopen("cor.txt", "r");
    int i;
    
    for (i = 0; i < N; i++)
    {
        fscanf(fp, "%*d %lf %lf %lf", &cor[i][0], &cor[i][1], &cor[i][2]);
//        printf("%d %lf %lf %lf\n", i, cor[i][0], cor[i][1], cor[i][2]);
    }
    fclose(fp);
}

//输入原子初速度 
void InputVelocity(void)
{
    FILE *fp = fopen("v.txt", "r");
    int i;
    
    for (i = 0; i < N; i++)
    {
        fscanf(fp, "%*d %lf %lf %lf", &v[i][0], &v[i][1], &v[i][2]);
//        printf("%d %lf %lf %lf\n", i, v[i][0], v[i][1], v[i][2]);
    }
    fclose(fp);
}


