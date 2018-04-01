#ifndef _SAFECHECK_H
#define _SAFECHECK_H
#include <stdio.h> 
#include<stdlib.h>
#include <string.h>
#define max_pro_num 100//最大进程数
#define max_sour_num 100//最大资源数

int pro_num, sour_num;//进程数和资源数
int sour_total[max_sour_num];//每个资源拥有的最多数目
int Finish[max_pro_num] = { 0 };//进程是否完成标志,0未完成，1完成

int MAX[max_pro_num][max_sour_num];//最大需求资源矩阵
int Allocation[max_pro_num][max_sour_num];//已经分配的资源矩阵
int Available[max_sour_num];//还剩的可利用的资源
int Need[max_pro_num][max_sour_num];//需求矩阵

void print();
void AVAILABLE();//可用资源
void NEED();//需要的资源
bool enough(int i);


void inputDta(){//初始化
	printf("请输入进程数：\n");
	scanf_s("%d", &pro_num);
	printf("请输入资源种类数量：：\n");
	scanf_s("%d", &sour_num);
	//输入sour_total
	printf("请输入每个资源拥有的数目：\n");
	for (int i = 0; i<sour_num; ++i){
		scanf_s("%d", &sour_total[i]);
	}
	//输入MAX
	printf("请输入各进程最大需求资源矩阵(MAX)：\n");
	for (int i = 0; i<pro_num; ++i){
		for (int j = 0; j<sour_num; ++j){
			scanf_s("%d", &MAX[i][j]);
		}
	}
	//输入Allocation
	printf("请输入各进程已经分配的资源矩阵（Allocation）：\n");
	for (int i = 0; i<pro_num; ++i){
		for (int j = 0; j<sour_num; ++j){
			scanf_s("%d", &Allocation[i][j]);
		}
	}
}

//初始化
void inputDta_file(){
	FILE *inFile;
	//char w[1000];
	err1 = fopen_s(&inFile, "banker.txt", "r");
	if (inFile == NULL) {
		puts("打开文件失败！");
		system("pause");
		return;
	}
	else
		puts("成功打开文件！\n");
	fscanf_s(inFile, "%d", &pro_num);
	fscanf_s(inFile,"%d", &sour_num);
	//输入sour_total
	for (int i = 0; i<sour_num; ++i){
		fscanf_s(inFile,"%d", &sour_total[i]);
	}
	//输入MAX
	for (int i = 0; i<pro_num; ++i){
		for (int j = 0; j<sour_num; ++j){
			fscanf_s(inFile, "%d", &MAX[i][j]);
		}
	}
	//输入Allocation
	for (int i = 0; i<pro_num; ++i){
		for (int j = 0; j<sour_num; ++j){
			fscanf_s(inFile, "%d", &Allocation[i][j]);
		}
	}
	fclose(inFile);
}

//计算Available数组
void AVAILABLE()
{
	for (int y = 0; y<sour_num; ++y)
	{
		int total = 0;
		for (int x = 0; x<pro_num; ++x)
		{
			total += Allocation[x][y];
		}
		Available[y] = sour_total[y] - total;
	}
}
//计算Need矩阵
void NEED(){
	for (int i = 0; i<pro_num; ++i)
	{
		for (int j = 0; j<sour_num; ++j)
		{
			Need[i][j] = MAX[i][j] - Allocation[i][j];
		}
	}
}


void print(){//打印
	AVAILABLE();
	NEED();
	//第一行
	printf("\t Allocation\t   Max\t\tAvailable\t  Need\n");

	//第二行
	for (int i = 0; i<4; ++i){
		printf("\t  ");
		for (int j = 0; j<sour_num; ++j){
			printf("%c ", (char)('A' + j));
		}
	}
	printf("\n");

	//剩下几行
	for (int i = 0; i<pro_num; ++i){
		//进程名
		printf("P%d:", i + 1);

		//Allocation
		printf("\t  ");
		for (int j = 0; j<sour_num; ++j){
			printf("%d ", Allocation[i][j]);
		}

		//Max
		printf("\t  ");
		for (int j = 0; j<sour_num; ++j){
			printf("%d ", MAX[i][j]);
		}

		//Available
		printf("\t  ");
		if (i == 0){
			for (int j = 0; j<sour_num; ++j){
				printf("%d ", Available[j]);
			}
		}
		else printf("\t     ");

		//Need
		printf("\t  ");
		for (int j = 0; j<sour_num; ++j){
			printf("%d ", Need[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

//检查是否Need<Available
bool enough(int i)
{
	bool flag = false;
	int count = 0;
	for (int j = 0; j<sour_num; ++j)
	{
		if (Need[i][j] <= Available[j])
			count++;
		else continue;
	}
	//cout<<"enough"<<count<<endl;
	if (count == sour_num)
		flag = true;
	return flag;
}
//work = work+allcocation
void work(int i)
{
	for (int j = 0; j<sour_num; ++j)
	{
		Available[j] += Allocation[i][j];
	}
}
//恢复
void re_work(int i){
	for (int j = 0; j<sour_num; ++j){
		Available[j] -= Allocation[i][j];
		//cout<<"*re*"<<Available[j];
	}
	//cout<<endl;
}


int pro_name[max_pro_num] = { 0 };
int answer = 0;
void banker1(int count){//银行家
	//进程全运行完之后
	if (count == pro_num){
		printf("安全序列%d:\t", ++answer);
		for (int x = 0; x<pro_num; ++x)
			printf("P%d  ", pro_name[x]+1);
		printf("\n");
	}
	else{//还未运行完
		for (int i = 0; i<pro_num; ++i){
			if (enough(i) && Finish[i] == 0){
				pro_name[count] = i;
				work(i);
				Finish[i] = 1;
				banker1(++count);//回调
				count--;//恢复
				Finish[i] = 0;
				re_work(i);
			}
			else continue;
		}
	}
}

void safeRun(){
	//初始化
	inputDta();
	printf("初始状态： \n");
	print();
	banker1(0);
	system("pause");
}

void safeRun_file(){
	//初始化
	inputDta_file();
	printf("初始状态： \n");
	print();
	banker1(0);
	system("pause");

}

#endif