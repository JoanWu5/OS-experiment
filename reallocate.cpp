#include <iostream>
#include <math.h>
#define PagetableLength 64
using namespace std;
int PageTable[PagetableLength] = {0};

int main(){
    int LogicalAddress = 0;
    int PageNum = 0;
    int w = 0;
    int i = 0;
    int num = 0;
    int f;
    int PageSize;
    char flag;
    cout << "������ҳ�ų���;" << endl;
    cin >> num;
    cout << "������ҳ���С��" << endl;
    cin >> PageSize;
    cout << "�����������ţ�" << endl;
    for(i = 0; i < pow(2,num); i++ ){
        cin >> PageTable[i];
    }
    cout << "ϵͳҳ�Ŷ�Ӧ������;\n";
    for (i = 0; i <pow(2,num); i++){
        cout<<i<<"-->"<< PageTable[i]<<endl;
    }
    while(f){
    	cout << endl << "�������߼���ַ;\n";
        cin >> LogicalAddress;
    	PageNum = LogicalAddress / PageSize;
    	w = LogicalAddress % PageSize;//ҳ��ƫ�Ƶ�ַ
 		if(PageNum >= PagetableLength){//�ж��Ƿ�Խ��
        	cout << "���η��ʵĵ�ַ�ѳ������̵ĵ�ַ�ռ䣬���󣡣�\n";
        	return -1;
    	}
    	cout << "��Ӧ�������ַΪ;" << endl << PageTable[PageNum] * PageSize + w << endl;
    	cout << "�㻹�����������������밴Y/y,��������" << endl;
        cin >> flag;
        if(flag=='Y'||flag=='y')
        	f=1;
        else
            break;
    }
    return 0;
}

