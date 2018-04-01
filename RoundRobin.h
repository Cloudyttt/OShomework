#ifndef _RR_H
#define _RR_H

#include<stdio.h>  
#include <string.h>
#define MAX 10  
struct task_struct
{
	int number;					//进程编号
	double come_time;			//到达时间
	double run_begin_time;		//开始运行时间
	double run_time;			//运行时间
	double run_end_time;		//运行结束时间
	int priority;				//优先级
	int run_flag;				//调度标志
	int start_flag;				//是否为第一次开始调度  
} tasks[MAX];

struct task_struct  copy_task[MAX];//备份  
int counter; /*实际进程个数*/
int time_counter = 0;
void pinput();
void pinput_file();
void poutput(); /*调度结果输出*/
void time();
int charge();//判断是否所有的进程都被执行过  

void RRRun()
{
	pinput();
	printf("【时间片轮转算法。】\n\n");
	time();
	poutput();
	system("pause");
}
void RRRun_file()
{
	pinput_file();
	printf("【时间片轮转算法】\n\n");
	time();
	poutput();
	system("pause");
}
void time()
{
	double time_temp = 0;
	int i;
	int j = 0;
	int k = 0;

	for (i = 0; i < counter; i++)
	{
		copy_task[i].number = tasks[i].number;
		copy_task[i].come_time = tasks[i].come_time;
		copy_task[i].run_time = tasks[i].run_time;
	}

	time_temp = tasks[0].come_time;
	while (charge())
	{
		for (i = 0; i < counter; i++)
		{
			if (tasks[i].come_time > time_temp)
			{
				time_temp = tasks[i].come_time;
			}
			if (tasks[i].run_flag == 0)//该进程还未结束  
			{
				if (tasks[i].start_flag == 0)  //该条件成立则说明，该进程是第一次执行，记录开始执行时间  
				{
					tasks[i].run_begin_time = time_temp;
					tasks[i].start_flag = 1;
				}
				if (tasks[i].run_time / time_counter > 1)//至少有两倍的时间片未执行  
				{
					tasks[i].run_time = tasks[i].run_time - time_counter;
					time_temp = time_temp + time_counter;
				}
				else if (tasks[i].run_time - time_counter == 0)
				{
					time_temp = time_temp + time_counter;
					tasks[i].run_end_time = time_temp;
					tasks[i].run_flag = 1;
					tasks[i].run_time = copy_task[i].run_time;
				}
				else//仅剩下不足一倍的时间片  
				{
					time_temp = time_temp + tasks[i].run_time;
					tasks[i].run_end_time = time_temp;
					tasks[i].run_flag = 1;
					tasks[i].run_time = copy_task[i].run_time;
				}
			}
		}
	}
}

int charge()//判断是否全部进程都执行完毕  
{
	int k;
	int super_flag = 0;//判断是否全部的进程都执行完毕  
	for (k = 0; k < counter; k++)
	{
		if (tasks[k].run_flag == 0)
		{
			super_flag = 1;
			return super_flag;
			break;
		}
		else
		{
			super_flag = 0;
		}
	}
	return super_flag;
}

void pinput() /*进程参数输入*/
{
	printf("请输入进程数目:\n");
	scanf_s("%d", &counter);
	printf("请输入时间片时间：\n");
	scanf_s("%d", &time_counter);
	printf("请输入到达时间:\n");
	for (int i = 0; i < counter; ++i)
	{
		tasks[i].number = i + 1;
		scanf_s("%lf", &tasks[i].come_time);
	}
	printf("请输入进程区间:\n");
	for (int i = 0; i < counter; ++i)
	{
		scanf_s("%lf", &tasks[i].run_time);
	}
	printf("请输入优先级:\n");
	for (int i = 0; i < counter; ++i)
	{
		scanf_s("%d", &tasks[i].priority);
		tasks[i].run_begin_time = 0;
		tasks[i].run_end_time = 0;
		tasks[i].run_flag = 0;		//运行是否结束  
		tasks[i].start_flag = 0;	//是否首次被执行  
	}

}
void pinput_file() //进程参数输入
{
	FILE *inFile;
	err1 = fopen_s(&inFile, "RoundRobin.txt", "r");
	if (inFile == NULL) {
		puts("打开RoundRobin.txt文件失败！");
		system("pause");
		return;
	}
	else
	{
		puts("成功打开RoundRobin.txt文件！\n");
	}
	fscanf_s(inFile, "%d", &counter);
	fscanf_s(inFile,"%d", &time_counter);
	for (int i = 0; i < counter; ++i)
	{
		tasks[i].number = i + 1;
		fscanf_s(inFile,"%lf", &tasks[i].come_time);
	}
	for (int i = 0; i < counter; ++i)
	{
		fscanf_s(inFile,"%lf", &tasks[i].run_time);
	}
	for (int i = 0; i < counter; ++i)
	{
		fscanf_s(inFile,"%d", &tasks[i].priority);
		tasks[i].run_begin_time = 0;
		tasks[i].run_end_time = 0;
		tasks[i].run_flag = 0;		//运行是否结束  
		tasks[i].start_flag = 0;	//是否首次被执行  
	}
	fclose(inFile);

}
void poutput() /*调度结果输出*/
{
	int i;
	double turn_round_time = 0, f1, w = 0;
	printf("进程号 到达时间 执行时间 开始时间 结束时间 优先级 周转时间\n");
	for (i = 0; i<counter; i++)
	{
		f1 = tasks[i].run_end_time - copy_task[i].come_time;
		turn_round_time += f1;
		printf("%d\t%.2lf\t%.2lf\t%.2lf\t  %.2lf\t    %d\t   %.2lf\n", 
			copy_task[i].number, copy_task[i].come_time, copy_task[i].run_time, 
			tasks[i].run_begin_time, tasks[i].run_end_time, tasks[i].priority, f1);
	}
	printf("平均轮转调度时间 = %.2lf\n\n", turn_round_time / counter);
}
#endif