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
    cout << "请输入页号长度;" << endl;
    cin >> num;
    cout << "请输入页面大小：" << endl;
    cin >> PageSize;
    cout << "请依次输入块号；" << endl;
    for(i = 0; i < pow(2,num); i++ ){
        cin >> PageTable[i];
    }
    cout << "系统页号对应块号情况;\n";
    for (i = 0; i <pow(2,num); i++){
        cout<<i<<"-->"<< PageTable[i]<<endl;
    }
    while(f){
    	cout << endl << "请输入逻辑地址;\n";
        cin >> LogicalAddress;
    	PageNum = LogicalAddress / PageSize;
    	w = LogicalAddress % PageSize;//页内偏移地址
 		if(PageNum >= PagetableLength){//判断是否越界
        	cout << "本次访问的地址已超出进程的地址空间，错误！；\n";
        	return -1;
    	}
    	cout << "对应的物理地址为;" << endl << PageTable[PageNum] * PageSize + w << endl;
    	cout << "你还想继续请求分配吗？是请按Y/y,否按其他键" << endl;
        cin >> flag;
        if(flag=='Y'||flag=='y')
        	f=1;
        else
            break;
    }
    return 0;
}

