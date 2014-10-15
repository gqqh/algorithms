#coding:utf-8
'''
题目：给定两个数组X和Y，元素都是正数。请找出满足如下条件的数对的数目：
1、x ^ y > y ^ x, 即x的y次方大于y的x次方
2、x来自X数组，y来自Y数组
'''
'''
#try1 蛮力方案，O(m*n)
x = [2, 1, 19, 20, 3, 4, 100, 50, 39, 23, 54]
y = [4, 2, 8, 3, 18, 40, 288, 42, 12, 45]
ret = []

for i in x:
	for j in y:
		if i ** j > j ** i:
			ret.append((i, j))
print len(ret)
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
x = [2, 1, 19, 20, 3, 4, 100, 50, 39, 23, 54]
y = [4, 2, 8, 3, 18, 40, 288, 42, 12, 45]
ret = 0
# 对y进行排序
y.sort()
# 统计y[0...4]出现的个数
no_y = [0, 0, 0, 0, 0]
for i in y:
	if i < 5:
		no_y[i] += 1

# 遍历X数组，对于每一个x，统计其出现个数
for i in x:
	if i == 0:
		continue
	if i == 1:
		ret += no_y[0]
		continue
	mid = len(y)/2
	low = 0
	high = len(y) - 1
	while low <= high:
		if i >= y[ mid ]:
			low = mid + 1
			mid = (low + high) / 2
		else:
			high = mid - 1
			mid = (low + high) / 2
	ret += len( y[mid + 1:] )
	if i == 2:
		ret -= no_y[3] + no_y[4]
		continue
	if i == 3:
		ret += no_y[2]
		continue
print ret
