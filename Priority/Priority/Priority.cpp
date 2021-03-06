//按优先数调度算法实现处理器调度的程序
#include "pch.h"
#include<iostream>
#include<cstdlib>
using namespace std;

typedef struct PCB {
	struct PCB *next;//定义指向下一个节点的指针
	char name[10];//定义进程名
	int Required_time;//定义需求运行时间
	int Prio;//定义优先级
	char state;//定义进程状态Ready/End
}*Proc;

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
		cout << "进程名，优先数，要求运行时间:";
		cin >> p->name >> p->Prio >> p->Required_time;
		p->state = 'R';
		p->next = NULL;
	}
	p->next = H->next;
}

//输入运行中的进程信息
void Displnfo(Proc H) {
	Proc p = H->next;
	do {
		cout << "进程名:" << p->name << "\t优先数:" << p->Prio << "\t要求运行时间:" << p->Required_time << "\t状态:" << p->state << endl;
		p = p->next;
	} while (p != H->next);  //整个进程链条始终完整，只是状态位有差异
}

Proc Max_Priority(Proc H) {//确定最大优先级进程子程序
	Proc p = H->next;
	int max = -100;//max为最大优先数，初始化为-100
	Proc key=NULL;

	do {
		if (p->state == 'W')//W为辅助状态标志，表示正在运行
			return NULL;//返回null
		else
			if (max < p->Prio&&p->state == 'R') {//从就绪进程中选取优先数最大的进程
				max = p->Prio;//max存放每次循环中的最大优先数
				key = p;//将优先级最高进程赋给key
			}
		p = p->next;
	} while (p != H->next);
	if (key->state == 'E')//具有最大优先数的进程若已运行完毕
		return NULL;//则返回null
	else
		return key;//将key作为返回值返回
}

void Priority(Proc &H) {
	cout << endl << "----------------START-----------------\n";
	int flag = ProcNum;//记录剩余进程数
	int round = 0;//记录轮转数
	int All_time = 0;
	Proc key;
	Proc p = H->next;
	do {
		All_time += p->Required_time;
		p = p->next;
	} while (p != H->next);
	p = H->next;
	for (round = 0; round < All_time; round++) {
		cout << "Round" << round + 1;
		key = Max_Priority(H);
		if (key != NULL) {
			key->state = 'W';
		}
		if (key->state == 'W') {
			cout << "\t正在运行--" << key->name << endl;
			key->Required_time--;
			key->Prio--;
			if (key->Required_time == 0) {
				key->state = 'E';
				flag--;
			}
			else {
				key->state = 'R';
			}
		}
		else
			key->state = 'R';
		key = key->next;
		while (flag&&key->Required_time == 0)
			key = key->next;
		Displnfo(H);
	}
	cout << endl << "-----------------END-----------------\n";
}

int main() {
	Proc H;
	lnitPCB(H);  //数据初始化
	Displnfo(H); //输出此刻的进程状态
	Priority(H);//优先调度法
	system("pause");
}


