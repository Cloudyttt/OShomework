#ifndef _FILE_H
#define _FILE_H

#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>
errno_t err1, err2, err3;
void replace_file()
{
	FILE *inFile, *outFile;
	char w[100];
	err1 = fopen_s(&inFile, "input.txt", "r");
	if (inFile == NULL) 
	{
		puts("��input.txt�ļ�ʧ�ܣ�");
		system("pause");
		return;
	}
	else
	{
		puts("�ɹ���input.txt�ļ���");
	}
	fscanf_s(inFile, "%s", &w, 100);
	err2 = fopen_s(&outFile, "output.txt", "w");
	fprintf(outFile, "%s", w);
	fclose(inFile);
	fclose(outFile);
	printf("output.txt�ı��������滻��");
	puts("");
	system("pause");
}
void replace()
{
	FILE *inFile, *outFile;
	char w[100];
	err1 = fopen_s(&inFile, "input.txt", "r");
	if (inFile == NULL) {
		puts("���ļ�ʧ�ܣ�");
		system("pause");
		return;
	}
	else
	{
		puts("�ɹ���input.txt�ļ���");
	}
	fscanf_s(inFile, "%s", &w, 100);
	err2 = fopen_s(&outFile, "output.txt", "w");
	fprintf(outFile, "%s", w);
	fclose(inFile);
	fclose(outFile);
	printf("output�ı��������滻!\n");
	puts("");
	remove("input.txt");
	system("pause");
}
void append_file()
{
	FILE *inFile, *outFile;
	char w[1000];
	//char r[1000];
	err1 = fopen_s(&inFile, "input.txt", "r");
	if (inFile == NULL) {
		puts("��input.txt�ļ�ʧ�ܣ�");
		system("pause");
		return;
	}
	else
		puts("�ɹ���input.txt�ļ���");
	fscanf_s(inFile, "%s", &w, 1000);
	err2 = fopen_s(&outFile, "output.txt", "a+");
	fprintf(outFile, "%s", w);
	fclose(inFile);
	fclose(outFile);
	printf("input.txt���ı���������ӵ�output.txt�ı����ݺ�\n");
	puts("");
	system("pause");
}
void append()
{
	FILE *inFile, *outFile;
	char w[1000];
	err1 = fopen_s(&inFile, "input.txt", "r");
	if (inFile == NULL) 
	{
		puts("��input.txt�ļ�ʧ�ܣ�");
		system("pause");
		return;
	}
	else
	{
		puts("�ɹ���input.txt�ļ���");
	}
	fscanf_s(inFile, "%s", &w, 1000);
	err2 = fopen_s(&outFile, "output.txt", "a+");
	fprintf(outFile, "%s", w);
	fclose(inFile);
	fclose(outFile);
	printf("input.txt���ı���������ӵ�output.txt�ı����ݺ�\n");
	puts("");
	remove("input.txt");
	system("pause");
}
char isDeleteFile() 
{
	char ch;
	puts("�Ƿ�ɾ��ԭinput.txt�ļ���(y/n)");
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
void mainRun()
{
	int choice;
	do 
	{
		system("cls");
		puts(" ���ļ�����Ŀ¼��");
		puts("+-----------------+");
		puts(" 1. �ı�����");
		puts(" 2. �ı��滻");
		puts(" 3. ���ظ�Ŀ¼");
		puts("+-----------------+");
		scanf_s("%d", &choice); getchar();
		switch (choice) 
		{
			case 1:
				//system("cls");
				puts("���ı����ӡ�\n"); 
				if (isDeleteFile() == 'n')
				{
					append_file();
				}
				else
				{
					append();
				}
				break;
			case 2:
				//system("cls");
				puts("���ı��滻��\n"); 
				if (isDeleteFile() == 'n')
				{
					replace_file();
				}
				else
				{
					replace();
				}
				break;
			case 3:
			default:
				break;
		}
	} while (choice != 3);
}
#endif