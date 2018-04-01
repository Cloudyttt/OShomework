#ifndef _RR_H
#define _RR_H

#include<stdio.h>  
#include <string.h>
#define MAX 10  
struct task_struct
{
	int number;					//���̱��
	double come_time;			//����ʱ��
	double run_begin_time;		//��ʼ����ʱ��
	double run_time;			//����ʱ��
	double run_end_time;		//���н���ʱ��
	int priority;				//���ȼ�
	int run_flag;				//���ȱ�־
	int start_flag;				//�Ƿ�Ϊ��һ�ο�ʼ����  
} tasks[MAX];

struct task_struct  copy_task[MAX];//����  
int counter; /*ʵ�ʽ��̸���*/
int time_counter = 0;
void pinput();
void pinput_file();
void poutput(); /*���Ƚ�����*/
void time();
int charge();//�ж��Ƿ����еĽ��̶���ִ�й�  

void RRRun()
{
	pinput();
	printf("��ʱ��Ƭ��ת�㷨����\n\n");
	time();
	poutput();
	system("pause");
}
void RRRun_file()
{
	pinput_file();
	printf("��ʱ��Ƭ��ת�㷨��\n\n");
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
			if (tasks[i].run_flag == 0)//�ý��̻�δ����  
			{
				if (tasks[i].start_flag == 0)  //������������˵�����ý����ǵ�һ��ִ�У���¼��ʼִ��ʱ��  
				{
					tasks[i].run_begin_time = time_temp;
					tasks[i].start_flag = 1;
				}
				if (tasks[i].run_time / time_counter > 1)//������������ʱ��Ƭδִ��  
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
				else//��ʣ�²���һ����ʱ��Ƭ  
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

int charge()//�ж��Ƿ�ȫ�����̶�ִ�����  
{
	int k;
	int super_flag = 0;//�ж��Ƿ�ȫ���Ľ��̶�ִ�����  
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

void pinput() /*���̲�������*/
{
	printf("�����������Ŀ:\n");
	scanf_s("%d", &counter);
	printf("������ʱ��Ƭʱ�䣺\n");
	scanf_s("%d", &time_counter);
	printf("�����뵽��ʱ��:\n");
	for (int i = 0; i < counter; ++i)
	{
		tasks[i].number = i + 1;
		scanf_s("%lf", &tasks[i].come_time);
	}
	printf("�������������:\n");
	for (int i = 0; i < counter; ++i)
	{
		scanf_s("%lf", &tasks[i].run_time);
	}
	printf("���������ȼ�:\n");
	for (int i = 0; i < counter; ++i)
	{
		scanf_s("%d", &tasks[i].priority);
		tasks[i].run_begin_time = 0;
		tasks[i].run_end_time = 0;
		tasks[i].run_flag = 0;		//�����Ƿ����  
		tasks[i].start_flag = 0;	//�Ƿ��״α�ִ��  
	}

}
void pinput_file() //���̲�������
{
	FILE *inFile;
	err1 = fopen_s(&inFile, "RoundRobin.txt", "r");
	if (inFile == NULL) {
		puts("��RoundRobin.txt�ļ�ʧ�ܣ�");
		system("pause");
		return;
	}
	else
	{
		puts("�ɹ���RoundRobin.txt�ļ���\n");
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
		tasks[i].run_flag = 0;		//�����Ƿ����  
		tasks[i].start_flag = 0;	//�Ƿ��״α�ִ��  
	}
	fclose(inFile);

}
void poutput() /*���Ƚ�����*/
{
	int i;
	double turn_round_time = 0, f1, w = 0;
	printf("���̺� ����ʱ�� ִ��ʱ�� ��ʼʱ�� ����ʱ�� ���ȼ� ��תʱ��\n");
	for (i = 0; i<counter; i++)
	{
		f1 = tasks[i].run_end_time - copy_task[i].come_time;
		turn_round_time += f1;
		printf("%d\t%.2lf\t%.2lf\t%.2lf\t  %.2lf\t    %d\t   %.2lf\n", 
			copy_task[i].number, copy_task[i].come_time, copy_task[i].run_time, 
			tasks[i].run_begin_time, tasks[i].run_end_time, tasks[i].priority, f1);
	}
	printf("ƽ����ת����ʱ�� = %.2lf\n\n", turn_round_time / counter);
}
#endif