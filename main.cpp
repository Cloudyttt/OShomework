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
		puts(" ||����Ŀ¼��                    ||");
		puts(" ++------------------------------++");
		puts(" || 1--ϵͳ�ļ�����              ||");
		puts(" || 2--ʱ��Ƭ��ת                ||");
		puts(" || 3--����ҵ����-����ռ         ||");
		puts(" || 4--����ҵ����-��ռ           ||");
		puts(" || 5--���м��㷨-��ȫ��         ||");
		puts(" || 6--���м��㷨-��Դ����       ||");
		puts(" || 7--�˳�ϵͳ                  ||");
		puts(" +================================+\n");
		puts("�������Ӧ���к���ѡ����Ӧ����...");
		scanf_s("%d", &choice);
		getchar();
		while (choice > 7 || choice < 1)
		{
			puts("����������������룺");
			scanf_s("%d", &choice);
			getchar();
		}
		switch (choice) {
		case 1:
			system("cls");
			puts("��ϵͳ�ļ��Ĳ�����");
			puts("");
			mainRun();
			break;
		case 2:
			system("cls");
			puts("��ʱ��Ƭ��ת���̵��ȡ�");
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
			puts("������ҵ����-����ռ��");
			puts("");
			if (isFileIncluded() == 'y')
				SJFRun_file();
			else
				SJFRun();
			break;
		case 4:
			system("cls");
			puts("������ҵ����-��ռ��");
			puts("");
			if (isFileIncluded() == 'y')
				SRTFRun_file();
			else
				SRTFRun();
			break;
		case 5:
			system("cls");
			puts("�����м��㷨-��ȫ�Լ�顿");
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
			puts("�����м��㷨-������Դ���䡿");
			puts("");
			if (isFileIncluded() == 'y')
				requestRun_file();
			else
				requestRun();
			break;

		case 7:
		default:
			system("cls");
			puts("�˳�ϵͳ��");
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
	puts("��ѡ���Ƿ�������ļ���(y/n)");
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
				printf("�����������������룺\n");
				scanf_s("%c", &ch);
				getchar();
			}
		}
	}
}










