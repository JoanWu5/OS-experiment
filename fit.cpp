//�ɱ��������ʽ�²����״���Ӧ�㷨
//@author:�鵤÷
 
#include<stdio.h>
#include<stdlib.h>
 
#define MAXSIZE 50
typedef struct spare{
	int start;//ʼַ
	int length;//����
	int state;//״̬
	struct spare *next;
}SPARESPACE;

int memory;//�ڴ��С
int count;//��¼��������
SPARESPACE *unallocated = NULL, *assigned = NULL;//δ�����unallocated���ѷ����assigned
 
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
	printf("\n�ѷ�����������£�\n");
	printf("ʼַ\t����\t��־\n");
	while (p){
		temp = p;
		printf("%dKB\t%3dKB\t", p->start, p->length);
		if (p->state){
			printf("����%d\n",p->state);
		}
		p = p->next;
	}
		
	p = unallocated;
	printf("\n���з��������£�\n");
	printf("ʼַ\t����\t��־\n");
	while (p){
		printf("%dKB\t%3dKB\t", p->start, p->length);
		if(temp==NULL&&p->state==0)
			printf("δ����\n");
		else if (p->state == 0 )
			if(temp->start>p->start)
				printf("�ձ�Ŀ\n");
			else
				printf("δ����\n");
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
		printf("�ڴ���û�иý��̣�\n");
	}
	else{
		printf("���ڴ����ҵ�Ҫ���յĽ���%d\n",p->state);
		if (p == assigned)
			assigned = p->next;
		else
			pre->next = p->next;
			
		SPARESPACE *temp = unallocated;
		int flag = 0;
		if (p->start + p->length == temp->start){//�͵�һ��������
			flag = 1;
			temp->start = p->start;
			temp->length += p->length;
		}
		else{
			while (temp->next){
				if (temp->start + temp->length == p->start){//������
					flag = 1;
					if (p->start + p->length == temp->next->start){//������
						temp->length = temp->length + p->length + temp->next->length;
						SPARESPACE *tp = temp->next;
						temp->next = temp->next->next;
						free(tp);
					}
					else{//��������
						temp->length = temp->length + p->length;
					}
					break;
				}
				if (p->start + p->length == temp->next->start){//��������
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
		printf("��ѡ������ҵ��1  ������ҵ��2  ������-1����");
		scanf("%d",&select);
		if (select == 1){
			printf("����������ҵ�ĳ���:");
			do{
				scanf("%d", &request);
				if(request<=0){
					printf("����������һ��>0��ֵ��\n");
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
				printf("�뽫��ҵ������С��\n");
				count--; 
				continue;
			}
			spare = (SPARESPACE *)malloc(sizeof(SPARESPACE));
			spare->start = p->start;
			spare->length = request;
			spare->state = count;
			spare->next = NULL;
			insertIntoAssigned(spare);
			//��������Ŀհ׷���
			p->start = p->start + request;
			p->length = p->length - request;
			deleteNullShare();
		}
		else if (select == 2){
			printf("������Ҫ������ҵ�Ľ��̺ţ�");
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
	printf("�������ڴ�������");
	scanf("%d",&memory);
	init();
	firstFit();
	return 0;
}
