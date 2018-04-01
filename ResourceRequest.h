#ifndef _REQUEST_H
#define _REQUEST_H

#include<stdio.h>  
#include<string.h>  

#define MAX_PROCESS 100  
#define MAX_RESOURCE 100  
int available[MAX_RESOURCE];                    //可用资源数组    
int max[MAX_PROCESS][MAX_RESOURCE];            //最大需求矩阵    
int allocation[MAX_PROCESS][MAX_RESOURCE];    //分配矩阵   
int need[MAX_PROCESS][MAX_RESOURCE];     //需求矩阵    
int request[MAX_PROCESS][MAX_RESOURCE];        //进程请求资源数   
int p[MAX_PROCESS]; //记录序列  
int n, m;   
int pro_name2[MAX_PROCESS] = { 0 };
int answer2 = 0;
int Finish2[MAX_PROCESS] = { 0 };//进程是否完成标志,0未完成，1完成//n个进程,m个资源    
void Init()                //初始化算法    
{
	int i, j;
	printf("请输入进程的数目:\n");
	scanf_s("%d", &n);
	printf("请输入资源的种类:\n");
	scanf_s("%d", &m);
	printf("请输入各个资源现有的数目:\n");
	for (i = 0; i<m; i++)
	{
		scanf_s("%d", &available[i]);
	}
	printf("请输入每个进程最多所需的各资源数,按照%dx%d矩阵从左到右、从上到下输入:\n", n, m);
	for (i = 0; i<n; i++)
	{
		for (j = 0; j<m; j++)
		{
			scanf_s("%d", &max[i][j]);
		}
	}
	printf("请输入每个进程已分配的各资源数,也按照%dx%d矩阵从左到右、从上到下输入:\n", n, m);
	for (i = 0; i<n; i++)
	{
		for (j = 0; j<m; j++)
		{
			scanf_s("%d", &allocation[i][j]);
			need[i][j] = max[i][j] - allocation[i][j];
			available[j] = available[j] - allocation[i][j];
			if (need[i][j]<0)
			{
				printf("您输入的第%d个进程所拥有的第%d个资源数错误,请重新输入:\n", i + 1, j + 1);
				j--;
				continue;
			}
		}
	}

	
}
void Init_file()
{
	FILE *inFile;
	//char w[1000];
	err1 = fopen_s(&inFile, "banker.txt", "r");
	if (inFile == NULL) {
		puts("打开banker.txt文件失败！");
		system("pause");
		return;
	}
	else
		puts("成功打开banker.txt文件！\n");
	fscanf_s(inFile, "%d", &n);
	fscanf_s(inFile, "%d", &m);
	//printf("请依次输入%d类资源的可用资源数目的最大值(中间以空格隔开)：\n", typenum);
	for (int i = 0; i<m; i++)
	{
		fscanf_s(inFile, "%d", &available[i]);
	}
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			fscanf_s(inFile, "%d", &max[i][j]);
		}
	}
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			fscanf_s(inFile, "%d", &allocation[i][j]);
			need[i][j] = max[i][j] - allocation[i][j];
			available[j] = available[j] - allocation[i][j];
			if (need[i][j]<0)
			{
				printf("您输入的第%d个进程所拥有的第%d个资源数错误,请修改数据:\n", i + 1, j + 1);
				j--;
				continue;
			}
		}
	}
	fclose(inFile);
}

bool enough2(int i)
{
	bool flag = false;
	int count = 0;
	for (int j = 0; j < m; ++j)
	{
		if (need[i][j] <= available[j])
			count++;
		else continue;
	}
	//printf("\n");
	if (count == m)
		flag = true;
	return flag;
}

//work = work+allcocation
void work2(int i){
	for (int j = 0; j < m; ++j){
		available[j] += allocation[i][j];
	}
}

//恢复
void re_work2(int i){
	for (int j = 0; j < m; ++j){
		available[j] -= allocation[i][j];
	}
}

//银行家
void banker2(int count)
{
	//进程全运行完之后
	if (count == n){
		printf("\n安全序列%d:", ++answer2);
		for (int x = 0; x < n; ++x)
		{
			printf("P%d ", pro_name2[x]);
		}
		//printf("\n");
	}
	else
	{
		//还未运行完
		for (int i = 0; i < n; ++i)
		{
			if (enough2(i) && Finish2[i] == 0)
			{
				pro_name2[count] = i;
				work2(i);
				Finish2[i] = 1;
				//printf("P%d", count);
				//printf("—%d", pro_name2);
				banker2(++count);//回调
				//恢复
				count--;
				Finish2[i] = 0;
				re_work2(i);
			}
			else continue;
		}
	}
}

bool Safe()    //安全性算法  
{
	answer2 = 0;
	banker2(0);
	if (answer2 > 0){
		return true;
	}
	else
		return false;
}
void Bank()                //银行家算法    
{
	int num;
	for (int i = 0; i < m; i++)
	{
		printf("%d  ", available[i]);
	}
	printf("\n");
	while (1)
	{
		printf("请输入要申请资源的进程号(注:第1个进程号为0,依次类推)\n");
		scanf_s("%d", &num);
		printf("\n请输入进程所请求的各资源的数量:\n");
		for (int i = 0; i<m; i++)
		{
			scanf_s("%d", &request[num][i]);
			if (request[num][i]>need[num][i])//如果用户选择的线程的第i个资源请求数＞该线程该资源所需的数量    
			{
				printf("您输入的请求数超过该进程对该资源的需求量!请重新输入!\n");
				i--;
				Bank();
				continue;
			}
			if (request[num][i]>available[i])//如果用户选择的线程的第i个资源请求数＞系统现有的第i个资源的数量    
			{
				printf("您输入的请求数超过系统拥有该资源的数目!请重新输入!\n");
				i--;
				Bank();
				continue;
			}
			//如果请求合理，接着执行  
			available[i] -= request[num][i];//系统可用资源减去申请了的    
			allocation[num][i] += request[num][i];//线程被分配的资源加上已申请了的    
			need[num][i] -= request[num][i];//线程还需要的资源减去已申请得到的    
		}
		if (Safe())//available  allocation  need变动之后，是否会导致不安全    
		{
			printf("\n同意分配请求,以上为分配后存在的全部安全序列!\n");
		}
		else
		{
			printf("您的请求被拒绝!\n");
			for (int i = 0; i<m; i++)
			{
				available[i] += request[num][i];
				allocation[num][i] -= request[num][i];
				need[num][i] += request[num][i];
			}
		}
	}
}
void requestRun()
{
	Init();
	Bank();
	system("pause");
}
void requestRun_file(){
	Init_file();
	Bank();
	system("pause");
}
#endif