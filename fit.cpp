//可变分区管理方式下采用首次适应算法
//@author:伍丹梅
 
#include<stdio.h>
#include<stdlib.h>
 
#define MAXSIZE 50
typedef struct spare{
	int start;//始址
	int length;//长度
	int state;//状态
	struct spare *next;
}SPARESPACE;

int memory;//内存大小
int count;//记录任务序列
SPARESPACE *unallocated = NULL, *assigned = NULL;//未分配表unallocated，已分配表assigned
 
void insertIntoSpare(SPARESPACE *spare){
	SPARESPACE *p = NULL,*pre = NULL;
	p = pre = unallocated;
	if (unallocated == NULL){
		unallocated = spare;
	}
	else if (p->start > spare->start){
		spare->next = p;
		unallocated = spare;
	}
	else{
		p = p->next;
		while (p){
			if (p->start > spare->start){
				break;
			}
			pre = p;
			p = p->next;
		}
		spare->next = p;
		pre->next = spare;
	}
}

void insertIntoAssigned(SPARESPACE *spare){
	SPARESPACE *p;
	p = assigned;
	if (assigned == NULL){
		assigned = spare;
	}
	else{
		while (p->next){
			p = p->next;
		}
		p->next = spare;
	}
}

int init(){
    SPARESPACE *spare;
	spare = (SPARESPACE*)malloc(sizeof(SPARESPACE));
	spare->start = 0;
	spare->length =memory;
	spare->state = 0;
	spare->next = NULL;
	insertIntoSpare(spare);
	count=0;	
	return 0;
}

void deleteNullShare()
{
	SPARESPACE *pre, *p;
	p = pre = unallocated;
	if (p->length == 0){
		unallocated = p->next;
		free(p);
	}
	else{
		while (p){
			if (p->length == 0)
				break;
			pre = p;
			p = p->next;
		}
		if (p){
			pre->next = p->next;
			free(p);
		}
	}
}

void showMemState(){
	SPARESPACE *p = NULL;
	SPARESPACE *temp = NULL; 
	p = assigned;
	printf("\n已分配分区表如下：\n");
	printf("始址\t长度\t标志\n");
	while (p){
		temp = p;
		printf("%dKB\t%3dKB\t", p->start, p->length);
		if (p->state){
			printf("进程%d\n",p->state);
		}
		p = p->next;
	}
		
	p = unallocated;
	printf("\n空闲分区表如下：\n");
	printf("始址\t长度\t标志\n");
	while (p){
		printf("%dKB\t%3dKB\t", p->start, p->length);
		if(temp==NULL&&p->state==0)
			printf("未分配\n");
		else if (p->state == 0 )
			if(temp->start>p->start)
				printf("空表目\n");
			else
				printf("未分配\n");
		p = p->next;
	}
}

void recoverMem(int ID){
	SPARESPACE *p = NULL,*pre=NULL;
	p = pre =  assigned;
	while (p){
		if (p->state == ID){
			break;
		}
		pre = p;
		p = p->next;
	}
	if (p == NULL){
		printf("内存中没有该进程！\n");
	}
	else{
		printf("在内存中找到要回收的进程%d\n",p->state);
		if (p == assigned)
			assigned = p->next;
		else
			pre->next = p->next;
			
		SPARESPACE *temp = unallocated;
		int flag = 0;
		if (p->start + p->length == temp->start){//和第一个下相邻
			flag = 1;
			temp->start = p->start;
			temp->length += p->length;
		}
		else{
			while (temp->next){
				if (temp->start + temp->length == p->start){//上相邻
					flag = 1;
					if (p->start + p->length == temp->next->start){//下相邻
						temp->length = temp->length + p->length + temp->next->length;
						SPARESPACE *tp = temp->next;
						temp->next = temp->next->next;
						free(tp);
					}
					else{//仅上相邻
						temp->length = temp->length + p->length;
					}
					break;
				}
				if (p->start + p->length == temp->next->start){//仅下相邻
					flag = 1;
					temp->next->start = p->start;
					temp->next->length += p->length;
					break;
				}
				temp = temp->next;
			}
			if (flag == 0){
				if (temp->start + temp->length == p->start){
					temp->length += p->length;
				}
				else{
					SPARESPACE *spare = (SPARESPACE *)malloc(sizeof(SPARESPACE));
					spare->start = p->start;
					spare->length = p->length;
					spare->state = 0;
					spare->next = NULL;
					insertIntoSpare(spare);
				}
			}
		}
	}
	free(p);
}

int firstFit(){
	int request;
	int select;
	int recover;
	SPARESPACE *p;
	SPARESPACE *spare = NULL;
	while(1){
		showMemState();
		printf("请选择（新作业：1  回收作业：2  结束：-1）：");
		scanf("%d",&select);
		if (select == 1){
			printf("请输入新作业的长度:");
			do{
				scanf("%d", &request);
				if(request<=0){
					printf("请重新输入一个>0的值：\n");
				}	
			}while(request<=0);
			count++;
			
			p = unallocated;
			while (p){
				if (p->length >= request){
					break;
				}
				p = p->next;
			}
			if (p == NULL){
				printf("请将作业容量定小点\n");
				count--; 
				continue;
			}
			spare = (SPARESPACE *)malloc(sizeof(SPARESPACE));
			spare->start = p->start;
			spare->length = request;
			spare->state = count;
			spare->next = NULL;
			insertIntoAssigned(spare);
			//处理分配后的空白分区
			p->start = p->start + request;
			p->length = p->length - request;
			deleteNullShare();
		}
		else if (select == 2){
			printf("请输入要回收作业的进程号：");
			scanf("%d",&recover);
			recoverMem(recover);
		}
		else if (select == -1){
			break;
		}
	}
	return 0;
}

int main(){
	printf("请输入内存容量：");
	scanf("%d",&memory);
	init();
	firstFit();
	return 0;
}
