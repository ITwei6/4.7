#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//霍尔最初方法--定义一个基准值key
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
		else//a[left]>a[mid]且a[right]>a[mid]
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
		else//a[left]<a[mid]且a[right]<a[mid]
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
//1.霍尔方法
void Quicksort1(int*a,int left,int right)//需要区间范围
{
	//递归结束条件
	if (left >= right)
		return;

	int keyi = left;
	int begin = left;
	int end = right;
	////随机选key
	//int randi = rand() % (right - left) + begin;
	//Swap(&a[keyi], &a[randi]);

	//三数取中，不是取数组中间的数，而是取三个数中中间的数--begin mid end
	int midi=Midi(a, begin, end);
	Swap(&a[keyi], &a[midi]);
	while (left < right)
	{
		//右找小
		while (left<right && a[right]>=a[keyi])
			right--;
		//左找大
		while (left < right && a[left] <= a[keyi])
			left++;
		//交换右边的小和左边的大
		Swap(&a[left], &a[right]);
	}
	//最后将key值与left和right相遇位置交换
	Swap(&a[keyi], &a[left]);
	keyi = left;
	//begin   keyi-1 key keyi+1   end
	Quicksort1(a, begin, keyi - 1);
	Quicksort1(a, keyi + 1, end);
}
//2.挖坑法
void Quicksort2(int* a, int left, int right)
{
	if (left >= right)
		return;
	//将key的值保留
	int key = a[left];
	int begin = left;
	int end = right;
	int hole = begin;
	//三数取中，不是取数组中间的数，而是取三个数中中间的数--begin mid end
	int midi = Midi(a, begin, end);
	Swap(&key, &a[midi]);
	while (left < right)
	{
		//右边找小
		while (left < right && a[right] >= key)
			--right;
		//找到之后将它甩到坑里，自己形成新的坑
		a[hole] = a[right];
		hole = right;
		while (left < right && a[left] <= key)
			++left;
		//找到之后将它甩到坑里，自己形成新的坑
		a[hole] = a[left];
		hole = left;
	}
	//最后left和right相遇，将key插入到坑里
	a[hole] = key;
	Quicksort2(a, begin, hole - 1);
	Quicksort2(a, hole + 1, end);

}
//3.前后指针方法
void Quicksort3(int* a, int left, int right)
{
	if (left >= right)
		return;
	//三数取中，不是取数组中间的数，而是取三个数中中间的数--begin mid end
	int midi = Midi(a, left, right);
	Swap(&a[left], &a[midi]);
	int keyi = left;
	int cur = left + 1;
	int prev = left;
	int begin = left;
	int end = right;
	//cur用来找小，当cur找到小时，prev++，prev的值与cur的值交换，cur继续往后走
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
//递归真正的问题--
// 1.效率。现阶段影响不大
// 2.深度太深，跑不过去--会栈溢出
// {relse版本可以优化，缩小栈帧的消耗}

//具备的能力：递归改成非递归
// 1.直接改成循环--斐波那契数列
// 2.使用 栈 辅助改循环
//递归是要消耗空间，递归一次需要建立一个栈帧，栈区域的内存不够

//递归 栈帧里面存放的是什么？关键---区间
//递归栈帧中本质变的是区间--所以栈里面也就要存区间、
//栈里面压入的是-- 递归的子区间入栈
//              --出栈的是子区间
//1.栈里面取一个区间，单趟排序
//单趟分割子区间入栈--分割完后将区间入栈
//子区间只有一个值或者不存在就不入

//快排--可以看成前序遍历
// 
//2.快排最后一个大坑--当有很多相同的数时，效率会很慢
//三路划分
//void QuickNone(int* a, int left, int right)
//{
//	ST st;
//	STinit(&st);
//	//将区间入栈
//	StackPush(&st, left);
//	StackPush(&st, right);
//	while (!STEmpty(&st))
//	{
//		int begin = Stackfront(&st);
//		StackPop(&st);
//
//		int end = Stackfront(&st);
//		StackPop(&st);
//		int keyi = PartSort(a, begin, end);//分割区间
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
//两个有序区间归并--
// 归并不是说个数问题而是有序问题才可以归并
// 2.依次比较，小的尾插到新空间

//归并- 可以看成后续遍历--左右子树有序--最后有序
// 0.递归到最后一层后有序才可以归并 只有确定有序后 才可以进行归并--也可以用小区间优化
// 1.一开始进行平分--不像快排--一开始左边比key小，右边比key大
// 向下分割，回来是归并
// 时间复杂度：logN*N

//需要一个临时数组tmp--必须赋值覆盖数据
//每次将数据归并完后，都要拷贝回去。能保证原数组最终是有序的

//【递归分治子问题】
// 
//快速排序通过单趟排序算出 两个子区间--特点：左小于key右大于key
//因为区间不一定从0开始，所以tmp数组开始下标不能为0 

//非递归-归并
//不能用栈？为什么，？后序？
//一一归，二二归，四四归……

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
//	StackInit(&st);//初始化栈
//	//首先将序列的左右区间入栈
//	StackPush(&st, right);
//	StackPush(&st, left);
//	//开始使用栈辅助修改循环
//	while (!StackEmpty(&st))
//	{
//		//当栈不为空时，将区间出栈--出两个元素
//		int begin = StackTop(&st);
//		int end = StackTop(&st);
//		//将区间出来后，就利用改区间对序列进行单趟排序
//	
//		int midi = Midi(a, left, right);
//		Swap(&a[left], &a[midi]);
//		int keyi = left;
//		int cur = left + 1;
//		int prev = left;
//		//cur用来找小，当cur找到小时，prev++，prev的值与cur的值交换，cur继续往后走
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
//	 //单趟排序完后选出key ，而key又将序列分成两个子序列，相当于两个区间，将这两个区间入栈，注意先将右区间入栈，再入左区间
//	//还有要注意的是，当子序列无法再分割时，无法产生区间时就不入栈
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
//	// 按照基准值key对a数组的 [left, right)区间中的元素进行划分
//	/*int keyi = partion(a, left, right);*/
//
//	// 划分成功后以key为边界形成了左右两部分 [left, keyi-1] 和 [keyi+1, right)
//	// 递归排[left, keyi-1]左子序列
//	QuickSort(a, left, keyi-1);
//
//	// 递归排[keyi+1+1, right)右子序列
//	QuickSort(keyi, keyi + 1, right);
//}