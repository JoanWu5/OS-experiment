#include<iostream>
#include<iomanip>
 
using namespace std;
 
//�����������ʼ��
//���̵������
int N=10;
//��Դ�������
int M=50;
//��������Դ����
int Available[50] = {0};
int Available_A[50] = {0};
//���������
int Max[10][50] = {0};
//�ѷ�����Դ��
int Allocation[10][50] = {0};
int Allocation_A[10][50] = {0};
//������Դ��Ŀ
int Need[10][50] = {0};
int Need_N[10][50] = {0};
//������Դ����
int Request[100]={0};
//��������
int Work[50] = {0};
//��������
int Finish[50] = {0};
//��ȫ����
int Security[10] = {0};	
//�ж�ֵ
int Bool = 0;
//�ݴ����	
int Temp[50] = {0};	
//��Դ����
char Name[20] = {0};
 
//��ʼ����Դ��ĿM������ÿһ����Դ�����ƺ���Ŀ�Լ�������ĿN	
void input_1(){	
	int m,n;
	cout<<"��������Դ��������Ŀ��";
	cin>>m;
	if(m<=M){
		M=m;
		//����ÿһ����Դ�����ƺ���ĿAvailable
		for(int i=1;i<=M;i++){
			cout<<"�������"<<i<<"����Դ�����ƣ�";
			cin>>Name[i-1];
			cout<<"�������"<<i<<"����Դ����Ŀ��";
			cin>>Available[i-1];
		}
		cout<<endl;
	}
	else
		cout<<"��Դ��Ŀ̫�࣬���������롤����"<<endl;
	
	cout<<"��������̵���Ŀ��";
	cin>>n;
	if(n<=N){
		N=n;
		cout<<endl;
	}
	else
		cout<<"����̫�࣬���������롤����"<<endl;
	
}
 
//��������������ͷ������	
void input_2(){	
	int i,j; 
	//����������
	cout<<"����������̵������������ֵ("<<N<<"*"<<M<<"����)[Max]:"<<endl;
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			cin>>Max[i][j];
		}
	}
	
	//�������
	cout<<"����������̵ķ�������ֵ("<<N<<"*"<<M<<"����)[Allocation]:"<<endl;
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			cin>>Allocation[i][j];
		}
	}
	
}
 
//����ϵͳĿǰ������Դ���������
void input_4();
void input_3(){	
	int i,j;
	Bool=1;
	//�жϷ����Ƿ�������Ƿ��з�������������
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			if(Allocation[i][j]>Max[i][j]){
				cout<<"���������"<<endl;
				Bool=0;
				break;
			}
		}
	}	
	//����жϺ��� 
	if(Bool==1){
		//����ϵͳĿǰ������Դ
		for(j=0;j<M;j++){
			for(i=0;i<N;i++){
				Temp[j] += Allocation[i][j];
			}
			Available[j] -= Temp[j];
		}
	
		//�õ��������
		for(i=0;i<N;i++){
			for(j=0;j<M;j++){
				Need[i][j] = Max[i][j]-Allocation[i][j];
			}
		}
	}
	//����жϷ��䲻���� 
	else
		input_4();
}
 
//��������
void input_4(){	
	int i,j;	
	cout<<"��������������̵ķ�������ֵ("<<N<<"*"<<M<<"����)[Allocation]:"<<endl;
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			cin>>Allocation[i][j];
		}
	}
	//�����ж� 
	input_3();
}
 
//��ʾ��Ϣ
void show(){	
	cout<<"*************************************************************"<<endl;
	cout<<"ϵͳĿǰ�ɷ�����Դ��Ŀ[Available]:"<<endl;	
	for(int i=0;i<M;i++){
		cout<<setw(3)<<Name[i];
	}
	cout<<endl;
	for(int i=0;i<M;i++){
		cout<<setw(3)<<Available[i];
	}
	cout<<endl;
	
	cout<<"ϵͳ��ǰ����Դ����������£�"<<endl;
	cout<<"           Max          Allocation         Need"<<endl;
	cout<<"������ ";
	for(int j=0;j<3;j++){
		for(int i=0;i<M;i++)
			cout<<setw(3)<<Name[i];
		cout<<"      ";
	}
	cout<<endl;
	//��ӡ����
	for(int i=0;i<N;i++){
		cout<<"  P"<<i<<"   ";
		for(int j=0;j<M;j++)
			cout<<setw(3)<<Max[i][j];
		cout<<"      ";
		for(int j=0;j<M;j++)
			cout<<setw(3)<<Allocation[i][j];
		cout<<"      ";
		for(int j=0;j<M;j++)
			cout<<setw(3)<<Need[i][j];
		cout<<endl;
	}
}
 
//�жϴ�ʱϵͳ�Ƿ��ǰ�ȫ��
int safetycheck(){	
	int i,j;
	for(j=0;j<M;j++){
		Work[j]=Available[j];
	}	
	int s=0;
	//����ѭ����֤����N���Ų飬ʹ��ǰ�����Ų�����в�������Ľ����ܼ����ж� 
	for(int a=0;a<N;a++){
		//i=0;
		//����ѭ�����ƴ�0~N-1�����̵��ж� 
		for(i=0;i<N;i++){
			//�жϽ�����Դ����״̬�Ƿ�Ϊδ���	
			if(Finish[i]==0){
				//�ж�ÿһ����Դ�������Ƿ�С�ڿ��� 
				j=0;
				while(j<M){
					if(Need[i][j]<=Work[j]){
						//����������ʱ��˵�����Ϸ�����򣬽����Է��� 
						if(j==M-1){
							//������Դ
							for(int b=0;b<M;b++){
								Work[b] += Allocation[i][b];
							}
							//�޸�״̬ 
							Finish[i]=1;
							//��¼��ȫ˳�� 
							Security[s]=i;
							s++;
						}
						j++;
					}
					//ֻҪ��һ�������ܱ����㣬������ 
					else
						break;
				}
			}	
		}
	}
	
	Bool=1;
	//�ж��Ƿ���û�еõ�����Ľ���
	//����У�ʹBool��ֵ��Ϊ 0 
	for(j=0;j<N;j++){
		if(Finish[j]==0){
			Bool=0;
			break;
		}
	}
	//Bool=1��ʾ���н��̵�Finish������ 1 ����ϵͳ�ǰ�ȫ�� 
	if(Bool==1){
		cout<<"ϵͳ�ǰ�ȫ�ģ�"<<endl;
			cout<<"����һ����ȫ�����ǣ�";
			//�����ȫ����
			for(int j=0;j<N;j++){
				cout<<"P"<<Security[j];
				if(j<N-1)
					cout<<"-->";
			}
			cout<<endl;
			return Bool;
	}
	//Bool��=1��˵����û�еõ���Դ�Ľ��̣�ϵͳ����ȫ 
	else{
		cout<<"ϵͳ���ǰ�ȫ�ģ�"<<endl;
		return Bool;
	} 
}
 
//������Դ
int allocate(int p){	
	int j=0;
	Bool=1;
	int flag=1;
	//�ж�����ĺϷ��� 
	for(j=0;j<M;j++){
		//�ж������Ƿ�������� 
		if(Request[j]>Need[p][j]){
			Bool=0;
			//����ʱ�� 0 ֵ���ظ��������� 
			return Bool;
			break;
		}
		//�ж������Ƿ���ڿ�����Դ 
		else if(Available[j]<Request[j]){
			Bool=-1;
			//����ʱ�� -1 ֵ���ظ��������� 
			return Bool;
			break;
		}
	}
	//��Boolֵ���� 1 ��˵���������������� 
	if(Bool==1){
		for(j=0;j<M;j++){
			Allocation[p][j] += Request[j];
			Need[p][j] -= Request[j];
			Available[j] -= Request[j];
		}
		//�жϽ����Ƿ���ɣ������ɣ����ս��̣����¿�����Դ 
		for(j=0;j<M;j++){
			if(Need[p][j]!=0)
				flag=0;
				break;
		} 
		if(flag==1){
			for(j=0;j<M;j++){
				Available[j]+=Allocation[p][j];	
			}
		}
		return Bool; 
	}
}
 
//������Դ�������󲢼�������ĺ�����
void bank(){	
	int i,j,p;	
	//���ݱ���
	for(i=0;i<N;i++){
		Available_A[i]=Available[i];
		for(j=0;j<M;j++){
			Allocation_A[i][j]=Allocation[i][j];
			Need_N[i][j]=Need[i][j];
		}
	}
	
	//��������
	cout<<"������������Դ�Ľ�����:��0--"<<N-1<<"��"<<endl;
	cin>>p;
	cout<<"������������Դ�������:��1*"<<M<<"�ľ���"<<endl;
	for(j=0;j<M;j++){
		cin>>Request[j];
	}
	
	//���÷����㷨
	int value_1=allocate(p);
	//������󲻺Ϸ� 
	if(value_1==0){
		cout<<"�Ƿ�����"<<endl;
		//�˳��ú��� 
		return; 
	}
	if(value_1==-1){
		cout<<"ϵͳ��Դ����"<<endl;
		//�˳��ú��� 
		return;
	}
	//���������Ϲ淶 
	if(value_1==1){		
		//ִ�а�ȫ���㷨
		int value_2=safetycheck();
		//���ϰ�ȫ���㷨 
		if(value_2==1){
			cout<<"��Դ�ѷ���"<<endl;
			show();
		}
		//�����ϰ�ȫ���㷨 
		else{
			cout<<"��������ϵͳ����ȫ�������з��䡣"<<endl;
			//���ݻ�ԭ  
			for(i=0;i<N;i++){
				Available[i]=Available_A[i];
				for(j=0;j<M;j++){
					Allocation[i][j]=Allocation_A[i][j];
					Need[i][j]=Need_N[i][j];
				}
			}
			show(); 
		}	
	}
}
 
//������
int main(){	
	char choice;
	int a=1; 	
	//���� 
	input_1();
	input_2();
	input_3();
	//��ʾ 
	show();
	//�ж������״̬�Ƿ�ȫ 
	safetycheck();
	//����ѡ�� 
	while(a==1){
		cout<<"\t-------------------���м��㷨��ʾ------------------"<<endl;
		cout<<"                     R:�������   "<<endl;	
		cout<<"                     E:�˳�       "<<endl;
		cout<<"\t---------------------------------------------------"<<endl;
		cout<<"��ѡ��";
		cin>>choice;
		switch(choice){
			case 'R':
				bank();
				break;
			case 'E':
				a=0;
				break;
			default: cout<<"����ȷѡ��!"<<endl;
			break;
		}
	}		
	return 0;
}
/*ʾ����
4
A
3
B
12
C
14
D
14

5
max��
0 0 4 4
2 7 5 0
0 9 8 4
0 6 6 10
3 6 10 10

allocate:
0 0 3 2
1 0 0 0
0 0 3 2
0 0 1 4
1 3 5 4
*/ 
