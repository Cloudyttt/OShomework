#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"file.h"
#include"BankersAlgorithm.h"
#include"ResourceRequest.h"
#include"RoundRobin.h"
#include"SJF.h"
#include"SRTF.h"
char isFileIncluded();
int main()
{
	int choice;
	do 
	{
		system("cls");
		puts(" +================================+");
		puts(" ||【根目录】                    ||");
		puts(" ++------------------------------++");
		puts(" || 1--系统文件操作              ||");
		puts(" || 2--时间片轮转                ||");
		puts(" || 3--短作业优先-非抢占         ||");
		puts(" || 4--短作业优先-抢占           ||");
		puts(" || 5--银行家算法-安全性         ||");
		puts(" || 6--银行家算法-资源分配       ||");
		puts(" || 7--退出系统                  ||");
		puts(" +================================+\n");
		puts("请输入对应序列号来选择相应功能...");
		scanf_s("%d", &choice);
		getchar();
		while (choice > 7 || choice < 1)
		{
			puts("输入错误请重新输入：");
			scanf_s("%d", &choice);
			getchar();
		}
		switch (choice) {
		case 1:
			system("cls");
			puts("【系统文件的操作】");
			puts("");
			mainRun();
			break;
		case 2:
			system("cls");
			puts("【时间片轮转进程调度】");
			puts("");
			if (isFileIncluded() == 'y')
			{
				RRRun_file();
			}
			else
			{
				RRRun();
			}
			break;
		case 3:
			system("cls");
			puts("【短作业优先-非抢占】");
			puts("");
			if (isFileIncluded() == 'y')
				SJFRun_file();
			else
				SJFRun();
			break;
		case 4:
			system("cls");
			puts("【短作业优先-抢占】");
			puts("");
			if (isFileIncluded() == 'y')
				SRTFRun_file();
			else
				SRTFRun();
			break;
		case 5:
			system("cls");
			puts("【银行家算法-安全性检查】");
			puts("");
			if (isFileIncluded() == 'y')
			{
				safeRun_file();
			}
			else
			{
				safeRun();
			}
			break;
		case 6:
			system("cls");
			puts("【银行家算法-共享资源分配】");
			puts("");
			if (isFileIncluded() == 'y')
				requestRun_file();
			else
				requestRun();
			break;

		case 7:
		default:
			system("cls");
			puts("退出系统！");
			puts("");
			break;
		}
	} while (choice != 7);
	system("pause");
	return 0;
}
char isFileIncluded() 
{
	char ch;
	puts("请选择是否添加入文件？(y/n)");
	scanf_s("%c", &ch);
	getchar();
	while (1)
	{
		if (ch == 'y')
		{
			return ch;
		}
		else 
		{
			if (ch == 'n')
			{
				return ch;
			}
			else
			{
				printf("输入有误，请重新输入：\n");
				scanf_s("%c", &ch);
				getchar();
			}
		}
	}
}










