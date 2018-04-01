#ifndef _SJF_H
#define _SJF_H
#include<stdio.h>
#define N 100
int Arival[N]= {0};
int Go[N]= {0};
int Start[N]= {0};
int End[N]= {0};
int Timer[N]= {0};
float DTimer[N]= {0};
int Check[N]= {0};

int Select(int a[],int n,int local)
{
    int i=0;
    for(int k=0; k<n; k++)
    {
        if(Check[k]==0)
        {
            i=k;
            break;
        }
    }
    for(int j=0; j<n; j++)
    {
        if(a[i]>a[j]&&Check[j]==0&&Arival[j]<=local)
        {
            i=j;
        }
    }
    Check[i]=1;
    return i;
}
void SJFRun()
{               // 主函数
    int n,k=0,l=0,Atimer=0,timer=0,localtime=0, waited_time = 0;
    printf("输入进程的个数:\n");
    scanf_s("%d",&n);
    printf("依次输入各个进程的到达时间，共%d个:\n", n);
    for(int i=0; i<n; i++)
    {
        scanf_s("%d", Arival + i);
    }
    printf("依次输入各个进程的运行时间，共%d个:\n",n);
    for(int j = 0; j < n; j++)
    {
        scanf_s("%d",Go + j );
    }
    Start[k]=Arival[k];
    End[k]=Start[k]+Go[k];
    Timer[k]=End[k]-Arival[k];
    DTimer[k]=(float)Timer[k]/Go[k];
    localtime=End[k];
    Check[k]=1;
	int wait = 0;
	double total_wait = 0;
    printf("进程  提交时间  运行时间  开始时间  结束时间  周转时间  带权周转时间\n");
    for(int m = 0; m < n; m++)
    {
        l=k;
        k=Select(Go,n,localtime);
        Start[k]=End[l];
        End[k]=Start[k]+Go[k];
        Timer[k]=End[k]-Arival[k];
        DTimer[k]=(float)Timer[k]/Go[k];
        localtime=End[k];
        Atimer=Timer[l]+Atimer;
        timer=timer+DTimer[l];
        printf(" %d     %2d        %2d         %2d        %2d        %2d         %.2f\n",l + 1,Arival[l],Go[l],Start[l],End[l],Timer[l],DTimer[l]);
    }
    printf("平均周转时间:%.2f\n",(float)Atimer/n);
	printf("平均等待时间:%.2f\n",(float)total_wait/n);
    printf("平均带权周转时间:%.2f\n",(float)timer/n);
	system("pause");
}

void SJFRun_file()
{
	errno_t err1, err2, err3;
	int n,k=0,l=0,Atimer=0,timer=0,localtime=0;
	FILE *inFile;
	err1 = fopen_s(&inFile, "SJF.txt", "r");
	if (inFile == NULL) 
	{
		puts("打开SRTF.txt文件失败！");
		system("pause");
		return;
	}
	else
	{
		puts("成功打开SRTF.txt文件！\n");
	}
	fscanf_s(inFile, "%d", &n);
	printf("读取到的进程数：\n%d\n", n);
	printf("读取到的各进程到达时间：\n");
	for(int j = 0; j < n; j ++ )
	{
		printf("P%d\t",j+1);
	}
	printf("\n");
	for(int i = 0; i < n; i++)
	{
		fscanf_s(inFile, "%d", &Arival[i]);
		printf("%d\t", Arival[i]);
	}
	printf("\n");
	printf("读取到的各进程运行时间：\n");
	for(int j = 0; j < n; j ++ )
	{
		printf("P%d\t",j+1);
	}
	printf("\n");
	for(int i = 0; i < n; i++)
	{
		fscanf_s(inFile, "%d", &Go[i]);
		printf("%d\t", Go[i]);
	}
	printf("\n");
    Start[k]=Arival[k];
    End[k]=Start[k]+Go[k];
    Timer[k]=End[k]-Arival[k];
    DTimer[k]=(float)Timer[k]/Go[k];
    localtime=End[k];
    Check[k]=1;
	printf("\n");
	printf("运行结果：\n");
	int wait = 0;
	double total_wait = 0;
    printf("进程  提交时间  运行时间  开始时间  结束时间  周转时间  带权周转时间\n");
    for(int m = 0; m < n; m++)
    {
        l=k;
        k=Select(Go,n,localtime);
        Start[k]=End[l];
        End[k]=Start[k]+Go[k];
        Timer[k]=End[k]-Arival[k];
        DTimer[k]=(float)Timer[k]/Go[k];
        localtime=End[k];
        Atimer=Timer[l]+Atimer;
		
        timer=timer+DTimer[l];
		wait = Timer[l] - Go[l];
		total_wait = total_wait + wait;
        printf(" %d     %2d        %2d         %2d        %2d        %2d         %.2f\n",l + 1,Arival[l],Go[l],Start[l],End[l],Timer[l],DTimer[l]);
    }
    printf("平均周转时间:%.2f\n",(float)Atimer/n);
	printf("平均等待时间:%.2f\n",(float)total_wait/n);
    printf("平均带权周转时间:%.2f\n",(float)timer/n);
	system("pause");
}
#endif