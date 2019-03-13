//��λʾͼ������̴洢�ռ�
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#define COUNT 64

typedef struct DiskStruct{ //���̽ṹ
    int cylindernum;//�����
    int tracknum;//�ŵ��� 
    int recordnum;//�����¼�� 
}Disk;
 
//λʾͼ�������鹲8�����棬ÿ��������2���ŵ���ÿ���ŵ��ֳ�4�������¼����Ҫ64λ����ʾλʾͼ
struct Bitmap{ 
	int bitmap[COUNT];//0�գ�1ռ�� 
    int fileid[COUNT];//�������������ڵڼ��� 
};
 
struct Bitmap *bitinfo = NULL; 
 
//��ӡλʾͼ��Ϣ 
void showbitmap(){
    int i = 0; 
    printf("��ǰϵͳ����λʾͼ��0��ʾ����У���\n");
      
    for(i=0;i<COUNT;i++){    
        if(i%8==0){
            printf("\n");   
        } 
        printf("%d\t",bitinfo->bitmap[i]);
    }
    system("pause");
}
int fileidcount=1; //�����ID 
//���������
void diskallocate(){
    //���û�������Ҫ����������� 
    int neednum;
    int i;
    int occupy = 0;
      
    printf("������Ҫ����Ŀ���:\n");
    scanf("%d",&neednum);
      
    for(i=0;i<COUNT;i++){
        occupy=occupy+bitinfo->bitmap[i]; 
    }
    if(COUNT-occupy<neednum){
        printf("û���㹻�Ŀ��д��̣�����ʧ�ܣ�");
    }
    else{
        printf("��ʼ����...\n"); 
        for(i=0;i<COUNT;i++){
            if( bitinfo->bitmap[i]==0){
                printf("����������ַΪ:��%d�����棬\t��%d���ŵ�,\t��%d������\n",i/8,i%8/4,(i%8)%4);
                bitinfo->bitmap[i] = 1;
                bitinfo->fileid[i]=fileidcount;
                neednum--;
            }
            if(neednum==0){
            	fileidcount++;
                break;
            }    
        }
        printf("����ɹ���\n");   
    }
    system("pause");
}

//���� 
void diskrecycle(){ 
	int fileidtemp,bitmapid;
	Disk disk;
    int i;
    do{
    	printf("����Ҫ���յĴ��̵������(0-7)��");
    	scanf("%d",&disk.cylindernum);	
	}while(disk.cylindernum<0||disk.cylindernum>7);
	do{
		printf("����Ҫ���յĴ��̵Ĵŵ���(0-1)��");
		scanf("%d",&disk.tracknum);	
	}while(disk.tracknum!=0&&disk.tracknum!=1);
	do{
		printf("����Ҫ���յĴ��̵������¼��(0-3)��");
		scanf("%d",&disk.recordnum);	
	}while(disk.recordnum<0||disk.recordnum>3);
	
	//���ݹ黹�Ĵ��������ַ������黹����λʾͼ�еĶ�Ӧλ
	bitmapid=disk.cylindernum*8+disk.tracknum*4+disk.recordnum; 
    fileidtemp=bitinfo->fileid[bitmapid];
    
    for( i=0;i<COUNT;i++){
        if(fileidtemp!=bitinfo->fileid[i]){
            continue;     
        }
        else{
            bitinfo->bitmap[i] = 0; 
            printf("����λʾͼ�е�%d�ֽڵĵ�%dλ�������\n",i/8,i%8);
        }
    }
    system("pause");
}
 
 
int main (){
    int j;
    //��ʼ��
    bitinfo = (struct Bitmap*)malloc(sizeof(struct Bitmap));
    for(j=0;j<COUNT;j++){
        bitinfo->bitmap[j]=0;
        bitinfo->fileid[j]=0; 
    }
 
    //����ѡ�� 
    int func = 0; 
    while(1){
        printf("\n1:�鿴����λʾͼ\n");
        printf("2:������̿ռ�\n");
        printf("3:���մ��̿ռ�\n");
        printf("-1:�˳�����\n");
        printf("*****************************************************\n");
        scanf("%d",&func);
        switch(func){
            case 1 :showbitmap();break;
            case 2 :diskallocate();break;
            case 3 :diskrecycle();break; 
            case -1 :return 0;
        }
    }   
}
