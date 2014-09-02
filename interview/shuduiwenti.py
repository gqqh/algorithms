#coding:utf-8
'''
题目：给定两个数组X和Y，元素都是正数。请找出满足如下条件的数对的数目：
1、x ^ y > y ^ x, 即x的y次方大于y的x次方
2、x来自X数组，y来自Y数组
'''
'''
#try1 蛮力方案，O(m*n)
x = [2, 19, 20, 3, 4, 100, 50, 39, 23, 54]
y = [4, 8, 3, 18, 40, 288, 42, 12, 45]
ret = []

for i in x:
	for j in y:
		if i ** j > j ** i:
			ret.append((i, j))
print ret
'''
#try2
'''
x、y都是正数，所以：x^y > y^x <==> ylog(x)>xlog(y) <==> log(x)/x > log(y)/y
然后，对数组X和Y分别计算log(x)/x,log(y)/y
然后对Y进行排序O(nlogn)
遍历X数组，对于每一个x，在Y中，进行二分查找，即可。
总的时间复杂度为O(nlogn + mlogn).
'''

import math
x = [2, 19, 20, 3, 4, 100, 50, 39, 23, 54]
y = [4, 8, 3, 18, 40, 288, 42, 12, 45]
ret = []
y.sort()
for i in x:
	mid = len(y)/2
	low = 0
	high = len(y) - 1
	dx = math.log(i)/i
	while low <= high:
		if dx <= math.log(y[mid])/y[mid]:
			low = mid + 1
			mid = (low + high) / 2
		else:
			high = high - 1
			mid = (low + high) / 2
	for j in y[mid:]:
		if i ** j > j ** i:
			ret.append((i, j))
print ret
