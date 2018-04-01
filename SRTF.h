#ifndef _SRTF_H
#define _SRTF_H
#define N 100//进程个数，可以任意修改，这里设置为3个进程

#include<stdio.h>

int times = 0;//时间轴
int totaltimes = 0;
void init2();
void orderByReachtimes2();
int search_Shortest_Remain_Jobs();
void update2(int);
int finishOrNot2();
void run2();
void showData();
int num;
//定义结构体
struct JobsStructs
{
	int reachtimes;//到达时间   
	int remaintimes;//剩余时间
	int overtime; // 完成时间
	int wait_time;
	int needtimes;//需要运行的总时间
	int No;//进程号
	int flag;//标志位，1标示已做完该作业，0标示未做完，初始化为0
}Jobs[N];

//输入结构体数组Jobs[]数据
void init2()
{
	printf("请输入进程数目：");
	scanf_s("%d", &num);
	printf("\n请依次输入各进程到达时间：\n");
	for (int i = 0; i < num; i++)
	{
		scanf_s("%d", &Jobs[i].reachtimes);
	}
	printf("\n请输入进程服务时间：\n");
	for (int i = 0; i < num; i++)
	{
		scanf_s("%d", &Jobs[i].needtimes);
		Jobs[i].remaintimes = Jobs[i].needtimes;//刚开始时剩余时间=所需时间
		Jobs[i].flag = 0;
		totaltimes += Jobs[i].needtimes;
	}
}
//从文件读取数据
void init2_file()
{
	FILE *inFile;
	err1 = fopen_s(&inFile, "SRTF.txt", "r");
	if (inFile == NULL) 
	{
		puts("打开SRTF.txt文件失败！");
		system("pause");
		return;
	}
	else
	{
		puts("成功打开SRTF.txt文件！\n");
	}
	fscanf_s(inFile, "%d", &num);
	for (int i = 0; i < num; i++)
	{
		fscanf_s(inFile, "%d", &Jobs[i].reachtimes);
	}
	for (int i = 0; i < num; i++)
	{
		fscanf_s(inFile, "%d", &Jobs[i].needtimes);
		Jobs[i].remaintimes = Jobs[i].needtimes;//刚开始时剩余时间=所需时间
		Jobs[i].flag = 0;
		totaltimes += Jobs[i].needtimes;
	}
	fclose(inFile);
}
//按到达时间先后排序数组
void orderByReachtimes2()
{
	for (int i = 0; i < num; i++)
	for (int j = i + 1; j<num; j++)
	{
		if (Jobs[i].reachtimes > Jobs[j].reachtimes)//按到达时间升序排序
		{
			struct JobsStructs temp = Jobs[i];
			Jobs[i] = Jobs[j];
			Jobs[j] = temp;
		}
	}
}
//寻找最短剩余时间的作业的下标并返回下标
int search_Shortest_Remain_Jobs()
{
	int index = -1;
	int remain = 32767;
	for (int i = 0; i<num; i++)
	{
		if (Jobs[i].flag == 0)
		{
			if (times >= Jobs[i].reachtimes)//该作业已到达，可以对其进行判断
			{
				if (Jobs[i].remaintimes<remain)//该作业未做完
				{
					remain = Jobs[i].remaintimes;
					index = i;

				}
			}
		}
	}
	return index;//返回最短剩余时间的作业的下标+1
}
//被调度的作业剩余时间减1，时间轴加1,参数index为被调度的作业的下标
void update2(int index)
{
	if (index == -1)
	{
		printf("%d	\n", index+1);
		times++;
	}
	else
	{
		
		printf("P%d\t\n", index+1);
		Jobs[index].remaintimes--;
		if (Jobs[index].remaintimes == 0)//如果作业剩余时间为0，说明作业已做完，置标志位为1
		{
			Jobs[index].flag = 1;
			Jobs[index].overtime  = times;
		}
		times++;
	}
}
//判断数组中是否还有没完成的作业，有则返回1，否则返回0
int finishOrNot2()
{
	for (int i = 0; i < num; i++)
	{
		if (Jobs[i].flag == 0)
		{
			return 1;//说明此时还有作业未做完
		}
	}
	return 0;
}
//最短剩余时间优先算法 Shortest Remaining times First
void SRTFRun()
{
	int timer = 0;
	init2();
	//showData();
	printf("进程号从1开始\n");
	printf("运行结果:\n");
		printf("====================\n");
	printf("时间片\t执行进程\t\n");
	while (finishOrNot2() && timer < totaltimes)
	{
		//返回最少剩余时间的作业的下标
		int index = search_Shortest_Remain_Jobs();
		printf("%d\t",timer++);
		update2(index);
	}
	printf("====================\n");
	printf("进程号\t完成时间\t\n");
	for(int t = 0; t < num; t++)
	{
		printf("P%d:\t%d\n", t + 1, Jobs[t].overtime);
	}
	printf("====================\n");
	system("pause");
}
void SRTFRun_file()
{
	int timer = 0;
	init2_file();
	printf("进程号从1开始\n");
	printf("运行结果:\n");
	printf("====================\n");
	printf("时间片\t执行进程\t\n");
	while (finishOrNot2() && timer <= totaltimes)
	{
		int index = search_Shortest_Remain_Jobs();//返回最少剩余时间的作业的下标
		printf("%d\t", timer++);
		update2(index);
	}
	printf("====================\n");
	printf("进程号\t完成时间\t\n");
	for(int t = 0; t < num; t++)
	{
		printf("P%d:\t%d\n", t + 1, Jobs[t].overtime);
	}
	printf("====================\n");
	system("pause");
}
void showData()
{
	
	printf("times	");
	//输出时间轴，每个单位为一个时间片，时间轴的长度可以自己设置的长一
	for (int i = 0; i<totaltimes; i++)
	//点，每个时间片对应的是主存中正在运行的一个进程号
	{
		printf("%d	", i);
	}
	printf("\n");
}

#endif