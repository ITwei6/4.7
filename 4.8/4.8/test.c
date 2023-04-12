#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//�����������--����һ����׼ֵkey
void Swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
int Midi(int* a, int left, int right)
{
	int mid = (left + right) / 2;
	if (a[left] > a[mid])
	{
		if (a[mid] > a[right])
		{
			return mid;
		}
		else//a[left]>a[mid]��a[right]>a[mid]
		{
			if (a[left] > a[right])
			{
				return right;
			}
			else
			{
				return left;
			}
		}
	}
	else//a[left]<a[mid]
	{
		if (a[mid] < a[right])
		{
			return mid;
		}
		else//a[left]<a[mid]��a[right]<a[mid]
		{
			if (a[left] > a[right])
			{
				return left;
			}
			else
			{
				return right;
			}
		}
	}
}
//1.��������
void Quicksort1(int*a,int left,int right)//��Ҫ���䷶Χ
{
	//�ݹ��������
	if (left >= right)
		return;

	int keyi = left;
	int begin = left;
	int end = right;
	////���ѡkey
	//int randi = rand() % (right - left) + begin;
	//Swap(&a[keyi], &a[randi]);

	//����ȡ�У�����ȡ�����м����������ȡ���������м����--begin mid end
	int midi=Midi(a, begin, end);
	Swap(&a[keyi], &a[midi]);
	while (left < right)
	{
		//����С
		while (left<right && a[right]>=a[keyi])
			right--;
		//���Ҵ�
		while (left < right && a[left] <= a[keyi])
			left++;
		//�����ұߵ�С����ߵĴ�
		Swap(&a[left], &a[right]);
	}
	//���keyֵ��left��right����λ�ý���
	Swap(&a[keyi], &a[left]);
	keyi = left;
	//begin   keyi-1 key keyi+1   end
	Quicksort1(a, begin, keyi - 1);
	Quicksort1(a, keyi + 1, end);
}
//2.�ڿӷ�
void Quicksort2(int* a, int left, int right)
{
	if (left >= right)
		return;
	//��key��ֵ����
	int key = a[left];
	int begin = left;
	int end = right;
	int hole = begin;
	//����ȡ�У�����ȡ�����м����������ȡ���������м����--begin mid end
	int midi = Midi(a, begin, end);
	Swap(&key, &a[midi]);
	while (left < right)
	{
		//�ұ���С
		while (left < right && a[right] >= key)
			--right;
		//�ҵ�֮����˦������Լ��γ��µĿ�
		a[hole] = a[right];
		hole = right;
		while (left < right && a[left] <= key)
			++left;
		//�ҵ�֮����˦������Լ��γ��µĿ�
		a[hole] = a[left];
		hole = left;
	}
	//���left��right��������key���뵽����
	a[hole] = key;
	Quicksort2(a, begin, hole - 1);
	Quicksort2(a, hole + 1, end);

}
//3.ǰ��ָ�뷽��
void Quicksort3(int* a, int left, int right)
{
	if (left >= right)
		return;
	//����ȡ�У�����ȡ�����м����������ȡ���������м����--begin mid end
	int midi = Midi(a, left, right);
	Swap(&a[left], &a[midi]);
	int keyi = left;
	int cur = left + 1;
	int prev = left;
	int begin = left;
	int end = right;
	//cur������С����cur�ҵ�Сʱ��prev++��prev��ֵ��cur��ֵ������cur����������
	while (cur <= right)
	{
		if (a[cur] <= a[keyi] && a[++prev] != a[cur])
		{
			Swap(&a[cur], &a[prev]);
		}
		++cur;
	}
	Swap(&a[prev], &a[keyi]);
	 keyi = prev;
	Quicksort3(a, begin, keyi - 1);
	Quicksort3(a, keyi + 1,end);
}
//�ݹ�����������--
// 1.Ч�ʡ��ֽ׶�Ӱ�첻��
// 2.���̫��ܲ���ȥ--��ջ���
// {relse�汾�����Ż�����Сջ֡������}

//�߱����������ݹ�ĳɷǵݹ�
// 1.ֱ�Ӹĳ�ѭ��--쳲���������
// 2.ʹ�� ջ ������ѭ��
//�ݹ���Ҫ���Ŀռ䣬�ݹ�һ����Ҫ����һ��ջ֡��ջ������ڴ治��

//�ݹ� ջ֡�����ŵ���ʲô���ؼ�---����
//�ݹ�ջ֡�б��ʱ��������--����ջ����Ҳ��Ҫ�����䡢
//ջ����ѹ�����-- �ݹ����������ջ
//              --��ջ����������
//1.ջ����ȡһ�����䣬��������
//���˷ָ���������ջ--�ָ����������ջ
//������ֻ��һ��ֵ���߲����ھͲ���

//����--���Կ���ǰ�����
// 
//2.�������һ�����--���кܶ���ͬ����ʱ��Ч�ʻ����
//��·����
//void QuickNone(int* a, int left, int right)
//{
//	ST st;
//	STinit(&st);
//	//��������ջ
//	StackPush(&st, left);
//	StackPush(&st, right);
//	while (!STEmpty(&st))
//	{
//		int begin = Stackfront(&st);
//		StackPop(&st);
//
//		int end = Stackfront(&st);
//		StackPop(&st);
//		int keyi = PartSort(a, begin, end);//�ָ�����
//		// begin   keyi-1 key keyi+1  end
//		if (keyi + 1 < end)
//		{
//			StackPush(&st, end);
//			StackPush(&st, keyi + 1);
//		}
//		if (begin < keyi - 1)
//		{
//			StackPush(&st, keyi - 1);
//			StackPush(&st, begin);
//		}
//	}
//	
//}
//������������鲢--
// �鲢����˵�������������������ſ��Թ鲢
// 2.���αȽϣ�С��β�嵽�¿ռ�

//�鲢- ���Կ��ɺ�������--������������--�������
// 0.�ݹ鵽���һ�������ſ��Թ鲢 ֻ��ȷ������� �ſ��Խ��й鲢--Ҳ������С�����Ż�
// 1.һ��ʼ����ƽ��--�������--һ��ʼ��߱�keyС���ұ߱�key��
// ���·ָ�����ǹ鲢
// ʱ�临�Ӷȣ�logN*N

//��Ҫһ����ʱ����tmp--���븳ֵ��������
//ÿ�ν����ݹ鲢��󣬶�Ҫ������ȥ���ܱ�֤ԭ���������������

//���ݹ���������⡿
// 
//��������ͨ������������� ����������--�ص㣺��С��key�Ҵ���key
//��Ϊ���䲻һ����0��ʼ������tmp���鿪ʼ�±겻��Ϊ0 

//�ǵݹ�-�鲢
//������ջ��Ϊʲô��������
//һһ�飬�����飬���Ĺ顭��

void QuickTest()
{
	srand(time(0));
	const int N = 100000;
	int* a2 = (int*)malloc(sizeof(int) * N);
	for (int i = 0; i < N; ++i)
	{
		a2[i] = rand();
	}
	int begin1 = clock();
	Quicksort1(a2, 0, N - 1);
	int end1 = clock();
	printf("Quicksort:%d\n", end1 - begin1);
	free(a2);
}
int main()
{
	/*int a[] = { 6,1,2,7,9,3,4,5,10,8 };
	int n = sizeof(a) / sizeof(a[0]);
	Quicksort3(a,0,n-1);
	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}*/
	QuickTest();
	return 0;

}
//void QuickSortNoN(int* a, int left, int right)
//{
//	Stack st;
//	StackInit(&st);//��ʼ��ջ
//	//���Ƚ����е�����������ջ
//	StackPush(&st, right);
//	StackPush(&st, left);
//	//��ʼʹ��ջ�����޸�ѭ��
//	while (!StackEmpty(&st))
//	{
//		//��ջ��Ϊ��ʱ���������ջ--������Ԫ��
//		int begin = StackTop(&st);
//		int end = StackTop(&st);
//		//����������󣬾����ø���������н��е�������
//	
//		int midi = Midi(a, left, right);
//		Swap(&a[left], &a[midi]);
//		int keyi = left;
//		int cur = left + 1;
//		int prev = left;
//		//cur������С����cur�ҵ�Сʱ��prev++��prev��ֵ��cur��ֵ������cur����������
//		while (cur <= right)
//		{
//			if (a[cur] <= a[keyi] && a[++prev] != a[cur])
//			{
//				Swap(&a[cur], &a[prev]);
//			}
//			++cur;
//		}
//		Swap(&a[prev], &a[keyi]);
//		keyi = prev;
//		//[left   keyi-1]  [keyi+1  right] 
//	 //�����������ѡ��key ����key�ֽ����зֳ����������У��൱���������䣬��������������ջ��ע���Ƚ���������ջ������������
//	//����Ҫע����ǣ����������޷��ٷָ�ʱ���޷���������ʱ�Ͳ���ջ
//
//		if (left < keyi - 1)
//		{
//			StackPush(&st, right);
//			STackPush(&st, keyi + 1);
//		}
//		if (keyi + 1 < right)
//		{
//			StackPush(&st, keyi - 1);
//			StackPush(&st, left);
//		}
//	}
//	
//}
//void QuickSort(int *a, int left, int right)
//{
//	if (left>=right)
//		return;
//
//	// ���ջ�׼ֵkey��a����� [left, right)�����е�Ԫ�ؽ��л���
//	/*int keyi = partion(a, left, right);*/
//
//	// ���ֳɹ�����keyΪ�߽��γ������������� [left, keyi-1] �� [keyi+1, right)
//	// �ݹ���[left, keyi-1]��������
//	QuickSort(a, left, keyi-1);
//
//	// �ݹ���[keyi+1+1, right)��������
//	QuickSort(keyi, keyi + 1, right);
//}