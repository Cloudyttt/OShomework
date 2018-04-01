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
		puts("打开input.txt文件失败！");
		system("pause");
		return;
	}
	else
	{
		puts("成功打开input.txt文件！");
	}
	fscanf_s(inFile, "%s", &w, 100);
	err2 = fopen_s(&outFile, "output.txt", "w");
	fprintf(outFile, "%s", w);
	fclose(inFile);
	fclose(outFile);
	printf("output.txt文本内容已替换！");
	puts("");
	system("pause");
}
void replace()
{
	FILE *inFile, *outFile;
	char w[100];
	err1 = fopen_s(&inFile, "input.txt", "r");
	if (inFile == NULL) {
		puts("打开文件失败！");
		system("pause");
		return;
	}
	else
	{
		puts("成功打开input.txt文件！");
	}
	fscanf_s(inFile, "%s", &w, 100);
	err2 = fopen_s(&outFile, "output.txt", "w");
	fprintf(outFile, "%s", w);
	fclose(inFile);
	fclose(outFile);
	printf("output文本内容已替换!\n");
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
		puts("打开input.txt文件失败！");
		system("pause");
		return;
	}
	else
		puts("成功打开input.txt文件！");
	fscanf_s(inFile, "%s", &w, 1000);
	err2 = fopen_s(&outFile, "output.txt", "a+");
	fprintf(outFile, "%s", w);
	fclose(inFile);
	fclose(outFile);
	printf("input.txt中文本内容已添加到output.txt文本内容后！\n");
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
		puts("打开input.txt文件失败！");
		system("pause");
		return;
	}
	else
	{
		puts("成功打开input.txt文件！");
	}
	fscanf_s(inFile, "%s", &w, 1000);
	err2 = fopen_s(&outFile, "output.txt", "a+");
	fprintf(outFile, "%s", w);
	fclose(inFile);
	fclose(outFile);
	printf("input.txt中文本内容已添加到output.txt文本内容后！\n");
	puts("");
	remove("input.txt");
	system("pause");
}
char isDeleteFile() 
{
	char ch;
	puts("是否删除原input.txt文件？(y/n)");
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
void mainRun()
{
	int choice;
	do 
	{
		system("cls");
		puts(" 【文件操作目录】");
		puts("+-----------------+");
		puts(" 1. 文本附加");
		puts(" 2. 文本替换");
		puts(" 3. 返回根目录");
		puts("+-----------------+");
		scanf_s("%d", &choice); getchar();
		switch (choice) 
		{
			case 1:
				//system("cls");
				puts("【文本附加】\n"); 
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
				puts("【文本替换】\n"); 
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