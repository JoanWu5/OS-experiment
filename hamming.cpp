/*-------------------------------------------------------------------------
 * Name:   ���������Դ���롣
 * Date:   2018.11.21
 * Author: @��˼ͩ 
 * �� devc++ �²���ͨ��
 * ʵ�ֹ��̣��������ݣ�������Ҫ�ĺ�����λ������żУ�� 
 *------------------------------------------------------------------------*/
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
using namespace std;
int main ()
{
  	int a, b, c[30], d, r = 0, d1; //����λ����30
  	cout << " ��������λ���� ";
  	cin >> a;
	while (a + r + 1 > pow (2, r))
    {
      	r++;
    }
  	cout << "��Ҫ������λ�� " << r << " : �ܹ� :" << a +
    r << endl;
	cout << " һһ��������λ:" << endl;
	for (int i = 1; i <= a; ++i)
    	cin >> c[i];
	cout << endl << " ������������� : ";
	for (int i = 1; i <= a; ++i)
    	cout << c[i] << " ";
	cout << endl;
	int data[a + r];
  	d = 0;
  	d1 = 1;
	for (int i = 1; i <= a + r; ++i)
    {
      	if ((i) == pow (2, d))
 		{
   			data[i] = 0;
   			++d;
 		}
      	else
 		{
   			data[i] = c[d1];
   			++d1;
 		}
    }
	d1 = 0;
  	int min, max = 0, parity, s, j;
  	for (int i = 1; i <= a + r; i = pow (2, d1))
    {
      	++d1;
      	parity = 0;
      	j = i;
      	s = i;
      	min = 1;
      	max = i;
      	for (j; j <= a + r;)
 		{
   			for (s = j; max >= min && s <= a + r; ++min, ++s)
     		{
       			if (data[s] == 1)
  				parity++;
     		}
   			j = s + i;
   			min = 1;
 		}
      	if (parity % 2 == 0) // żУ��
 		{
   			data[i] = 0;
 		}
      	else
 		{
   			data[i] = 1; 
 		}
    }
	cout << endl << " ����żУ��ĺ������ֱ����� : ";
	for (int i = 1; i <= a + r; ++i)
    	cout << data[i] << " ";
	cout << endl << endl;
}
