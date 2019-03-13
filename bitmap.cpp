//用位示图管理磁盘存储空间
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#define COUNT 64

typedef struct DiskStruct{ //磁盘结构
    int cylindernum;//柱面号
    int tracknum;//磁道号 
    int recordnum;//物理记录号 
}Disk;
 
//位示图，由盘组共8个柱面，每个柱面有2个磁道，每个磁道分成4个物理记录，需要64位来表示位示图
struct Bitmap{ 
	int bitmap[COUNT];//0空，1占有 
    int fileid[COUNT];//请求的物理块属于第几个 
};
 
struct Bitmap *bitinfo = NULL; 
 
//打印位示图信息 
void showbitmap(){
    int i = 0; 
    printf("当前系统磁盘位示图（0表示块空闲）：\n");
      
    for(i=0;i<COUNT;i++){    
        if(i%8==0){
            printf("\n");   
        } 
        printf("%d\t",bitinfo->bitmap[i]);
    }
    system("pause");
}
int fileidcount=1; //物理块ID 
//分配物理块
void diskallocate(){
    //由用户输入需要的物理块数： 
    int neednum;
    int i;
    int occupy = 0;
      
    printf("输入需要分配的块数:\n");
    scanf("%d",&neednum);
      
    for(i=0;i<COUNT;i++){
        occupy=occupy+bitinfo->bitmap[i]; 
    }
    if(COUNT-occupy<neednum){
        printf("没有足够的空闲磁盘，分配失败！");
    }
    else{
        printf("开始分配...\n"); 
        for(i=0;i<COUNT;i++){
            if( bitinfo->bitmap[i]==0){
                printf("分配块物理地址为:第%d个柱面，\t第%d个磁道,\t第%d个扇区\n",i/8,i%8/4,(i%8)%4);
                bitinfo->bitmap[i] = 1;
                bitinfo->fileid[i]=fileidcount;
                neednum--;
            }
            if(neednum==0){
            	fileidcount++;
                break;
            }    
        }
        printf("分配成功！\n");   
    }
    system("pause");
}

//回收 
void diskrecycle(){ 
	int fileidtemp,bitmapid;
	Disk disk;
    int i;
    do{
    	printf("输入要回收的磁盘的柱面号(0-7)：");
    	scanf("%d",&disk.cylindernum);	
	}while(disk.cylindernum<0||disk.cylindernum>7);
	do{
		printf("输入要回收的磁盘的磁道号(0-1)：");
		scanf("%d",&disk.tracknum);	
	}while(disk.tracknum!=0&&disk.tracknum!=1);
	do{
		printf("输入要回收的磁盘的物理记录号(0-3)：");
		scanf("%d",&disk.recordnum);	
	}while(disk.recordnum<0||disk.recordnum>3);
	
	//根据归还的磁盘物理地址计算出归还块在位示图中的对应位
	bitmapid=disk.cylindernum*8+disk.tracknum*4+disk.recordnum; 
    fileidtemp=bitinfo->fileid[bitmapid];
    
    for( i=0;i<COUNT;i++){
        if(fileidtemp!=bitinfo->fileid[i]){
            continue;     
        }
        else{
            bitinfo->bitmap[i] = 0; 
            printf("回收位示图中第%d字节的第%d位的物理块\n",i/8,i%8);
        }
    }
    system("pause");
}
 
 
int main (){
    int j;
    //初始化
    bitinfo = (struct Bitmap*)malloc(sizeof(struct Bitmap));
    for(j=0;j<COUNT;j++){
        bitinfo->bitmap[j]=0;
        bitinfo->fileid[j]=0; 
    }
 
    //功能选择 
    int func = 0; 
    while(1){
        printf("\n1:查看磁盘位示图\n");
        printf("2:分配磁盘空间\n");
        printf("3:回收磁盘空间\n");
        printf("-1:退出程序\n");
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
