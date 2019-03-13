/*-------------------------------------------------------------------------
 * Name:   汉明码编码源代码。
 * Date:   2018.11.21
 * Author: @李思桐 
 * 在 devc++ 下测试通过
 * 实现过程：输入数据，计算需要的汉明码位数，用偶校检 
 *------------------------------------------------------------------------*/
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
using namespace std;
int main ()
{
  	int a, b, c[30], d, r = 0, d1; //最大比位数：30
  	cout << " 输入数据位数： ";
  	cin >> a;
	while (a + r + 1 > pow (2, r))
    {
      	r++;
    }
  	cout << "需要汉明码位数 " << r << " : 总共 :" << a +
    r << endl;
	cout << " 一一输入数据位:" << endl;
	for (int i = 1; i <= a; ++i)
    	cin >> c[i];
	cout << endl << " 你输入的数据是 : ";
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
      	if (parity % 2 == 0) // 偶校验
 		{
   			data[i] = 0;
 		}
      	else
 		{
   			data[i] = 1; 
 		}
    }
	cout << endl << " 用于偶校验的汉明码字比特是 : ";
	for (int i = 1; i <= a + r; ++i)
    	cout << data[i] << " ";
	cout << endl << endl;
}
