#ifndef _REQUEST_H
#define _REQUEST_H

#include<stdio.h>  
#include<string.h>  

#define MAX_PROCESS 100  
#define MAX_RESOURCE 100  
int available[MAX_RESOURCE];                    //������Դ����    
int max[MAX_PROCESS][MAX_RESOURCE];            //����������    
int allocation[MAX_PROCESS][MAX_RESOURCE];    //�������   
int need[MAX_PROCESS][MAX_RESOURCE];     //�������    
int request[MAX_PROCESS][MAX_RESOURCE];        //����������Դ��   
int p[MAX_PROCESS]; //��¼����  
int n, m;   
int pro_name2[MAX_PROCESS] = { 0 };
int answer2 = 0;
int Finish2[MAX_PROCESS] = { 0 };//�����Ƿ���ɱ�־,0δ��ɣ�1���//n������,m����Դ    
void Init()                //��ʼ���㷨    
{
	int i, j;
	printf("��������̵���Ŀ:\n");
	scanf_s("%d", &n);
	printf("��������Դ������:\n");
	scanf_s("%d", &m);
	printf("�����������Դ���е���Ŀ:\n");
	for (i = 0; i<m; i++)
	{
		scanf_s("%d", &available[i]);
	}
	printf("������ÿ�������������ĸ���Դ��,����%dx%d��������ҡ����ϵ�������:\n", n, m);
	for (i = 0; i<n; i++)
	{
		for (j = 0; j<m; j++)
		{
			scanf_s("%d", &max[i][j]);
		}
	}
	printf("������ÿ�������ѷ���ĸ���Դ��,Ҳ����%dx%d��������ҡ����ϵ�������:\n", n, m);
	for (i = 0; i<n; i++)
	{
		for (j = 0; j<m; j++)
		{
			scanf_s("%d", &allocation[i][j]);
			need[i][j] = max[i][j] - allocation[i][j];
			available[j] = available[j] - allocation[i][j];
			if (need[i][j]<0)
			{
				printf("������ĵ�%d��������ӵ�еĵ�%d����Դ������,����������:\n", i + 1, j + 1);
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
		puts("��banker.txt�ļ�ʧ�ܣ�");
		system("pause");
		return;
	}
	else
		puts("�ɹ���banker.txt�ļ���\n");
	fscanf_s(inFile, "%d", &n);
	fscanf_s(inFile, "%d", &m);
	//printf("����������%d����Դ�Ŀ�����Դ��Ŀ�����ֵ(�м��Կո����)��\n", typenum);
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
				printf("������ĵ�%d��������ӵ�еĵ�%d����Դ������,���޸�����:\n", i + 1, j + 1);
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

//�ָ�
void re_work2(int i){
	for (int j = 0; j < m; ++j){
		available[j] -= allocation[i][j];
	}
}

//���м�
void banker2(int count)
{
	//����ȫ������֮��
	if (count == n){
		printf("\n��ȫ����%d:", ++answer2);
		for (int x = 0; x < n; ++x)
		{
			printf("P%d ", pro_name2[x]);
		}
		//printf("\n");
	}
	else
	{
		//��δ������
		for (int i = 0; i < n; ++i)
		{
			if (enough2(i) && Finish2[i] == 0)
			{
				pro_name2[count] = i;
				work2(i);
				Finish2[i] = 1;
				//printf("P%d", count);
				//printf("��%d", pro_name2);
				banker2(++count);//�ص�
				//�ָ�
				count--;
				Finish2[i] = 0;
				re_work2(i);
			}
			else continue;
		}
	}
}

bool Safe()    //��ȫ���㷨  
{
	answer2 = 0;
	banker2(0);
	if (answer2 > 0){
		return true;
	}
	else
		return false;
}
void Bank()                //���м��㷨    
{
	int num;
	for (int i = 0; i < m; i++)
	{
		printf("%d  ", available[i]);
	}
	printf("\n");
	while (1)
	{
		printf("������Ҫ������Դ�Ľ��̺�(ע:��1�����̺�Ϊ0,��������)\n");
		scanf_s("%d", &num);
		printf("\n���������������ĸ���Դ������:\n");
		for (int i = 0; i<m; i++)
		{
			scanf_s("%d", &request[num][i]);
			if (request[num][i]>need[num][i])//����û�ѡ����̵߳ĵ�i����Դ�����������̸߳���Դ���������    
			{
				printf("������������������ý��̶Ը���Դ��������!����������!\n");
				i--;
				Bank();
				continue;
			}
			if (request[num][i]>available[i])//����û�ѡ����̵߳ĵ�i����Դ��������ϵͳ���еĵ�i����Դ������    
			{
				printf("�����������������ϵͳӵ�и���Դ����Ŀ!����������!\n");
				i--;
				Bank();
				continue;
			}
			//��������������ִ��  
			available[i] -= request[num][i];//ϵͳ������Դ��ȥ�����˵�    
			allocation[num][i] += request[num][i];//�̱߳��������Դ�����������˵�    
			need[num][i] -= request[num][i];//�̻߳���Ҫ����Դ��ȥ������õ���    
		}
		if (Safe())//available  allocation  need�䶯֮���Ƿ�ᵼ�²���ȫ    
		{
			printf("\nͬ���������,����Ϊ�������ڵ�ȫ����ȫ����!\n");
		}
		else
		{
			printf("�������󱻾ܾ�!\n");
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