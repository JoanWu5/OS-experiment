//按时间轮转调度算法实现处理器调度的程序
#include "pch.h"
#include<iostream>
#include<cstdlib>
using namespace std;

typedef struct PCB {
	struct PCB *next;//定义指向下一个节点的指针
	char name[10];//定义进程名，并分配空间
	int All_time;//定义总运行时间
	int Runned_time;//定义已运行时间
	char state;//定义进程状态Ready/End
}*Proc;//指向该PCB的指针

int ProcNum = 5;//总进程数

//初始化就绪队列
void lnitPCB(Proc &H) {
	int Num = ProcNum;
	H = (Proc)malloc(sizeof(PCB));   //建立头结点
	H->next = NULL;
	Proc p = H;            //定义一个指针
	cout << "总进程个数为" << ProcNum << "个，请依次输入相应信息" << endl;
	cout << endl;
	while (Num--) {
		p = p->next = (Proc)malloc(sizeof(PCB));
		cout << "进程名，总运行时间，已运行时间:";
		cin >> p->name >> p->All_time >> p->Runned_time;
		p->state = 'R';
		p->next = NULL;
	}
	p->next = H->next;
}

//输入运行中的进程信息
void Displnfo(Proc H) {
	Proc p = H->next;
	do {
		cout << "进程名:" << p->name << "\t总运行时间:" << p->All_time << "\t已运行时间" << p->Runned_time << "\t状态:" << p->state << endl;
		p = p->next;
	} while (p != H->next);  //整个进程链条始终完整，只是状态位有差异
}

//时间片轮转法
void SJP_Simulator(Proc &H) {
	cout << endl << "-------------START-----------------\n";
	int flag = ProcNum;     //记录剩余进程数
	int round = 0;          //记录轮转数
	Proc p = H->next;
	while (p->All_time > p->Runned_time)
	{
		round++;
		cout << endl << "Round" << round << "--正在运行" << p->name << "进程" << endl;
		p->Runned_time++;//更改正在运行的进程的已运行的时间
		if (p->All_time == p->Runned_time) {
			//判断该进程是否结束
			p->state = 'E';
			flag--;
		}
		p = p->next;
		while (flag && p->All_time == p->Runned_time)
			p = p->next; //跳过先前已结束的进程
		Displnfo(H);//输出此时为就绪状态的进程 的信息
	}
	cout << endl << "---------------END-----------------\n";
}

int main() {
	Proc H;
	lnitPCB(H);  //数据初始化
	Displnfo(H); //输出此刻的进程状态
	SJP_Simulator(H);//时间片轮转法
	system("pause");
}

