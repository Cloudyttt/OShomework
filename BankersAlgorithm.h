#ifndef _SAFECHECK_H
#define _SAFECHECK_H
#include <stdio.h> 
#include<stdlib.h>
#include <string.h>
#define max_pro_num 100//��������
#define max_sour_num 100//�����Դ��

int pro_num, sour_num;//����������Դ��
int sour_total[max_sour_num];//ÿ����Դӵ�е������Ŀ
int Finish[max_pro_num] = { 0 };//�����Ƿ���ɱ�־,0δ��ɣ�1���

int MAX[max_pro_num][max_sour_num];//���������Դ����
int Allocation[max_pro_num][max_sour_num];//�Ѿ��������Դ����
int Available[max_sour_num];//��ʣ�Ŀ����õ���Դ
int Need[max_pro_num][max_sour_num];//�������

void print();
void AVAILABLE();//������Դ
void NEED();//��Ҫ����Դ
bool enough(int i);


void inputDta(){//��ʼ��
	printf("�������������\n");
	scanf_s("%d", &pro_num);
	printf("��������Դ������������\n");
	scanf_s("%d", &sour_num);
	//����sour_total
	printf("������ÿ����Դӵ�е���Ŀ��\n");
	for (int i = 0; i<sour_num; ++i){
		scanf_s("%d", &sour_total[i]);
	}
	//����MAX
	printf("��������������������Դ����(MAX)��\n");
	for (int i = 0; i<pro_num; ++i){
		for (int j = 0; j<sour_num; ++j){
			scanf_s("%d", &MAX[i][j]);
		}
	}
	//����Allocation
	printf("������������Ѿ��������Դ����Allocation����\n");
	for (int i = 0; i<pro_num; ++i){
		for (int j = 0; j<sour_num; ++j){
			scanf_s("%d", &Allocation[i][j]);
		}
	}
}

//��ʼ��
void inputDta_file(){
	FILE *inFile;
	//char w[1000];
	err1 = fopen_s(&inFile, "banker.txt", "r");
	if (inFile == NULL) {
		puts("���ļ�ʧ�ܣ�");
		system("pause");
		return;
	}
	else
		puts("�ɹ����ļ���\n");
	fscanf_s(inFile, "%d", &pro_num);
	fscanf_s(inFile,"%d", &sour_num);
	//����sour_total
	for (int i = 0; i<sour_num; ++i){
		fscanf_s(inFile,"%d", &sour_total[i]);
	}
	//����MAX
	for (int i = 0; i<pro_num; ++i){
		for (int j = 0; j<sour_num; ++j){
			fscanf_s(inFile, "%d", &MAX[i][j]);
		}
	}
	//����Allocation
	for (int i = 0; i<pro_num; ++i){
		for (int j = 0; j<sour_num; ++j){
			fscanf_s(inFile, "%d", &Allocation[i][j]);
		}
	}
	fclose(inFile);
}

//����Available����
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
//����Need����
void NEED(){
	for (int i = 0; i<pro_num; ++i)
	{
		for (int j = 0; j<sour_num; ++j)
		{
			Need[i][j] = MAX[i][j] - Allocation[i][j];
		}
	}
}


void print(){//��ӡ
	AVAILABLE();
	NEED();
	//��һ��
	printf("\t Allocation\t   Max\t\tAvailable\t  Need\n");

	//�ڶ���
	for (int i = 0; i<4; ++i){
		printf("\t  ");
		for (int j = 0; j<sour_num; ++j){
			printf("%c ", (char)('A' + j));
		}
	}
	printf("\n");

	//ʣ�¼���
	for (int i = 0; i<pro_num; ++i){
		//������
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

//����Ƿ�Need<Available
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
//�ָ�
void re_work(int i){
	for (int j = 0; j<sour_num; ++j){
		Available[j] -= Allocation[i][j];
		//cout<<"*re*"<<Available[j];
	}
	//cout<<endl;
}


int pro_name[max_pro_num] = { 0 };
int answer = 0;
void banker1(int count){//���м�
	//����ȫ������֮��
	if (count == pro_num){
		printf("��ȫ����%d:\t", ++answer);
		for (int x = 0; x<pro_num; ++x)
			printf("P%d  ", pro_name[x]+1);
		printf("\n");
	}
	else{//��δ������
		for (int i = 0; i<pro_num; ++i){
			if (enough(i) && Finish[i] == 0){
				pro_name[count] = i;
				work(i);
				Finish[i] = 1;
				banker1(++count);//�ص�
				count--;//�ָ�
				Finish[i] = 0;
				re_work(i);
			}
			else continue;
		}
	}
}

void safeRun(){
	//��ʼ��
	inputDta();
	printf("��ʼ״̬�� \n");
	print();
	banker1(0);
	system("pause");
}

void safeRun_file(){
	//��ʼ��
	inputDta_file();
	printf("��ʼ״̬�� \n");
	print();
	banker1(0);
	system("pause");

}

#endif