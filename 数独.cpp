#include <windows.h>
#include <stdio.h>
#include <time.h>
 
char sd[81];
bool isok = false;
 
//��ʾ����
void show()
{
 if (isok) puts("������");
 else puts("��ʼ�����");
 
 for (int i = 0; i < 81; i++)
 {
  putchar(sd[i] + '0');
  if ((i + 1) % 9 == 0) putchar('\n');
 }
 putchar('\n');
}
 
//��ȡ����
bool Init()
{
 FILE *fp = fopen("in.txt", "rb");
 if (fp == NULL) return false;
 fread(sd, 81, 1, fp);
 fclose(fp);
 for (int i = 0; i < 81; i++)
 {
  if (sd[i] >= '1' && sd[i] <= '9') sd[i] -= '0';
  else sd[i] = 0;
 }
 show();
 return true;
}
 
//�ݹ�������
void force(int k)
{
 if (isok) return;
 if (!sd[k])
 {
  for (int m = 1; m <= 9; m++)
  {
   bool mm = true;
   for (int n = 0; n < 9; n++)
   {
    if ((m == sd[k/27*27+(k%9/3)*3+n+n/3*6]) || (m == sd[9*n+k%9]) || (m == sd[k/9*9+n]))
    {
     mm = false;
     break;
    }
   }
   if (mm)
   {
    sd[k] = m;
    if (k == 80)
    {
     isok = true;
     show();
     return;
    }
    force(k + 1);
   }
  }
  sd[k] = 0;
 }
 else
 {
  if (k == 80)
  {
   isok = true;
   show();
   return;
  }
  force(k + 1);
 }
}
 
int main()
{
 system("CLS");
 if (Init())
 {
  double start = clock();
  force(0);
  printf("��ʱ%.0fms", clock() - start);
 }
 else puts("��ʼ������");
 getchar();
}
