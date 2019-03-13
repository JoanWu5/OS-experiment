/*-------------------------------------------------------------------------
 * Name:   ����������Դ���롣
 * Date:   2018.11.21
 * Author: @��˼ͩ 
 * �� devc++ �²���ͨ��
 * ʵ�ֹ��̣�����ͨ�� HuffmanTree() �����������������Ȼ���������� main()��
 *           �Ե����Ͽ�ʼ(Ҳ���Ǵ��������Ϊ��Ľ�㿪ʼ)���ϲ���жϣ�����
 *           �������࣬������Ϊ 0,�����Ҳ�,������Ϊ 1�����������ɵı��롣
 *------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

#define MAXBIT      100
#define MAXVALUE  10000
#define MAXLEAF     30
#define MAXNODE    MAXLEAF*2 -1

typedef struct 
{
    int bit[MAXBIT];
    int start;
} HCodeType;        /* ����ṹ�� */
typedef struct
{
    int weight;
    int parent;
    int lchild;
    int rchild;
} HNodeType;        /* ���ṹ�� */

/* ����һ�Ź������� */
void HuffmanTree (HNodeType HuffNode[MAXNODE],  int n)
{ 
    /* i��j�� ѭ��������m1��m2���������������ͬ������������СȨֵ����Ȩֵ��
        x1��x2���������������ͬ������������СȨֵ����������е���š�*/
    int i, j, m1, m2, x1, x2;
    /* ��ʼ����Ź����������� HuffNode[] �еĽ�� */
    for (i=0; i<2*n-1; i++)
    {
        HuffNode[i].weight = 0;
        HuffNode[i].parent =-1;
        HuffNode[i].lchild =-1;
        HuffNode[i].lchild =-1;
    } 

    /* ���� n ��Ҷ�ӽ���Ȩֵ */
    for (i=0; i<n; i++)
    {
        printf ("Please input weight of leaf node %d:", i);
        scanf ("%d", &HuffNode[i].weight);
    } 

    /* ѭ������ Huffman �� */
    for (i=0; i<n-1; i++)
    {
        m1=m2=MAXVALUE;     /* m1��m2�д�������޸�����ҽ��Ȩֵ��С��������� */
        x1=x2=0;
        /* �ҳ����н����Ȩֵ��С���޸�����������㣬���ϲ�֮Ϊһ�Ŷ����� */
        for (j=0; j<n+i; j++)
        {
            if (HuffNode[j].weight < m1 && HuffNode[j].parent==-1)
            {
                m2=m1; 
                x2=x1; 
                m1=HuffNode[j].weight;
                x1=j;
            }
            else if (HuffNode[j].weight < m2 && HuffNode[j].parent==-1)
            {
                m2=HuffNode[j].weight;
                x2=j;
            }
        }
            /* �����ҵ��������ӽ�� x1��x2 �ĸ������Ϣ */
        HuffNode[x1].parent  = n+i;
        HuffNode[x2].parent  = n+i;
        HuffNode[n+i].weight = HuffNode[x1].weight + HuffNode[x2].weight;
        HuffNode[n+i].lchild = x1;
        HuffNode[n+i].rchild = x2;

        printf ("x1.weight and x2.weight in round %d: %d, %d\n", i+1, HuffNode[x1].weight, HuffNode[x2].weight);  /* ���ڲ��� */
        printf ("\n");
    } 
} 

int main(void)
{
    HNodeType HuffNode[MAXNODE];            /* ����һ�����ṹ������ */
    HCodeType HuffCode[MAXLEAF],  cd;       /* ����һ������ṹ�����飬 ͬʱ����һ����ʱ���������������ʱ����Ϣ */
    int i, j, c, p, n;
    printf ("Please input n:");
    scanf ("%d", &n);
    HuffmanTree (HuffNode, n);
    
    for (i=0; i < n; i++)
    {
        cd.start = n-1;
        c = i;
        p = HuffNode[c].parent;
        while (p != -1)   /* �������� */
        {
            if (HuffNode[p].lchild == c)
                cd.bit[cd.start] = 0;
            else
                cd.bit[cd.start] = 1;
            cd.start--;        /* �����ĵ�һλ */
            c=p;                    
            p=HuffNode[c].parent;    /* ������һѭ������ */
        } 
        
        /* ���������ÿ��Ҷ���Ĺ���������ͱ������ʼλ */
        for (j=cd.start+1; j<n; j++)
        { HuffCode[i].bit[j] = cd.bit[j];}
        HuffCode[i].start = cd.start;
    } 
    
    /* ����ѱ���õ����д��ڱ���Ĺ��������� */
    for (i=0; i<n; i++)
    {
        printf ("%d 's Huffman code is: ", i);
        for (j=HuffCode[i].start+1; j < n; j++)
        {
            printf ("%d", HuffCode[i].bit[j]);
        }
        printf ("\n");
    }
    getchar();
    return 0;
}
