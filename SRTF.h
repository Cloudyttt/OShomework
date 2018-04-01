#ifndef _SRTF_H
#define _SRTF_H
#define N 100//���̸��������������޸ģ���������Ϊ3������

#include<stdio.h>

int times = 0;//ʱ����
int totaltimes = 0;
void init2();
void orderByReachtimes2();
int search_Shortest_Remain_Jobs();
void update2(int);
int finishOrNot2();
void run2();
void showData();
int num;
//����ṹ��
struct JobsStructs
{
	int reachtimes;//����ʱ��   
	int remaintimes;//ʣ��ʱ��
	int overtime; // ���ʱ��
	int wait_time;
	int needtimes;//��Ҫ���е���ʱ��
	int No;//���̺�
	int flag;//��־λ��1��ʾ���������ҵ��0��ʾδ���꣬��ʼ��Ϊ0
}Jobs[N];

//����ṹ������Jobs[]����
void init2()
{
	printf("�����������Ŀ��");
	scanf_s("%d", &num);
	printf("\n��������������̵���ʱ�䣺\n");
	for (int i = 0; i < num; i++)
	{
		scanf_s("%d", &Jobs[i].reachtimes);
	}
	printf("\n��������̷���ʱ�䣺\n");
	for (int i = 0; i < num; i++)
	{
		scanf_s("%d", &Jobs[i].needtimes);
		Jobs[i].remaintimes = Jobs[i].needtimes;//�տ�ʼʱʣ��ʱ��=����ʱ��
		Jobs[i].flag = 0;
		totaltimes += Jobs[i].needtimes;
	}
}
//���ļ���ȡ����
void init2_file()
{
	FILE *inFile;
	err1 = fopen_s(&inFile, "SRTF.txt", "r");
	if (inFile == NULL) 
	{
		puts("��SRTF.txt�ļ�ʧ�ܣ�");
		system("pause");
		return;
	}
	else
	{
		puts("�ɹ���SRTF.txt�ļ���\n");
	}
	fscanf_s(inFile, "%d", &num);
	for (int i = 0; i < num; i++)
	{
		fscanf_s(inFile, "%d", &Jobs[i].reachtimes);
	}
	for (int i = 0; i < num; i++)
	{
		fscanf_s(inFile, "%d", &Jobs[i].needtimes);
		Jobs[i].remaintimes = Jobs[i].needtimes;//�տ�ʼʱʣ��ʱ��=����ʱ��
		Jobs[i].flag = 0;
		totaltimes += Jobs[i].needtimes;
	}
	fclose(inFile);
}
//������ʱ���Ⱥ���������
void orderByReachtimes2()
{
	for (int i = 0; i < num; i++)
	for (int j = i + 1; j<num; j++)
	{
		if (Jobs[i].reachtimes > Jobs[j].reachtimes)//������ʱ����������
		{
			struct JobsStructs temp = Jobs[i];
			Jobs[i] = Jobs[j];
			Jobs[j] = temp;
		}
	}
}
//Ѱ�����ʣ��ʱ�����ҵ���±겢�����±�
int search_Shortest_Remain_Jobs()
{
	int index = -1;
	int remain = 32767;
	for (int i = 0; i<num; i++)
	{
		if (Jobs[i].flag == 0)
		{
			if (times >= Jobs[i].reachtimes)//����ҵ�ѵ�����Զ�������ж�
			{
				if (Jobs[i].remaintimes<remain)//����ҵδ����
				{
					remain = Jobs[i].remaintimes;
					index = i;

				}
			}
		}
	}
	return index;//�������ʣ��ʱ�����ҵ���±�+1
}
//�����ȵ���ҵʣ��ʱ���1��ʱ�����1,����indexΪ�����ȵ���ҵ���±�
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
		if (Jobs[index].remaintimes == 0)//�����ҵʣ��ʱ��Ϊ0��˵����ҵ�����꣬�ñ�־λΪ1
		{
			Jobs[index].flag = 1;
			Jobs[index].overtime  = times;
		}
		times++;
	}
}
//�ж��������Ƿ���û��ɵ���ҵ�����򷵻�1�����򷵻�0
int finishOrNot2()
{
	for (int i = 0; i < num; i++)
	{
		if (Jobs[i].flag == 0)
		{
			return 1;//˵����ʱ������ҵδ����
		}
	}
	return 0;
}
//���ʣ��ʱ�������㷨 Shortest Remaining times First
void SRTFRun()
{
	int timer = 0;
	init2();
	//showData();
	printf("���̺Ŵ�1��ʼ\n");
	printf("���н��:\n");
		printf("====================\n");
	printf("ʱ��Ƭ\tִ�н���\t\n");
	while (finishOrNot2() && timer < totaltimes)
	{
		//��������ʣ��ʱ�����ҵ���±�
		int index = search_Shortest_Remain_Jobs();
		printf("%d\t",timer++);
		update2(index);
	}
	printf("====================\n");
	printf("���̺�\t���ʱ��\t\n");
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
	printf("���̺Ŵ�1��ʼ\n");
	printf("���н��:\n");
	printf("====================\n");
	printf("ʱ��Ƭ\tִ�н���\t\n");
	while (finishOrNot2() && timer <= totaltimes)
	{
		int index = search_Shortest_Remain_Jobs();//��������ʣ��ʱ�����ҵ���±�
		printf("%d\t", timer++);
		update2(index);
	}
	printf("====================\n");
	printf("���̺�\t���ʱ��\t\n");
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
	//���ʱ���ᣬÿ����λΪһ��ʱ��Ƭ��ʱ����ĳ��ȿ����Լ����õĳ�һ
	for (int i = 0; i<totaltimes; i++)
	//�㣬ÿ��ʱ��Ƭ��Ӧ�����������������е�һ�����̺�
	{
		printf("%d	", i);
	}
	printf("\n");
}

#endif