#coding:utf-8
'''
https://gist.github.com/sing1ee/6137554
老鼠毒药分析
原题:有11瓶酒，只有一瓶有毒。喝酒之后，三天会死，只有三天时间。
	请问至少需要多少只老鼠，可以找出9瓶没有毒的酒。
分析:
题目描述很简单，可我们仍要抓住要点：

11瓶，1瓶有毒
喝酒之后，三天会死；只有三天时间->即使某一个老鼠没有被毒死，也不会有时间重复利用了
要使用最少个数的老鼠，要找到9瓶没有毒的,10瓶无毒的，为何要找到9瓶呢？
老鼠开始喝酒，第一只要喝哪些，第二只要喝哪些呢？现在有什么依据么？
显然酒瓶和老鼠都是一样的，不可区分的。那么怎么来选择哪些老鼠喝哪瓶酒，进而进行判断呢？
这是这个题目的关键点、核心点。
11个酒瓶，我们对其编号1-11，如下为二进制的表示，看完二进制的表示，也许很多同学，
就明白了该如何选择。

编号	二进制
1	0001
2	0010
3	0011
4	0100
5	0101
6	0110
7	0111
8	1000
9	1001
10	1010
11	1011
观察每一位的0和1的分布情况，从右向左，第一位是1的，有6个情况；是0的，有5个情况。这样，我们可以让一只老鼠喝掉都是1的，
然后又两种情况：
老鼠死了，说明有毒的那个瓶子的二进制位从右到左第一位是1.
老鼠没死，说明有毒的那个瓶子的二进制位从右到左第一位是0.
同样的，同时，另外两只老鼠测试第二位为1的瓶子以及第三位为1的瓶子，分别因为死或者没死，得到0、1的情况。
三只老鼠，所有可能的情况如下:
01情况	解释
000	三个老鼠都没死，只可能是1000号瓶子有毒，剩下10个都没毒
001	可能有毒的是0001、1001，去掉这两个，还有9个无毒
010	0101有毒，10个无毒
011	0011,1011可能有毒，9个确保无毒
100	0100有毒，10个无毒
101	0101有毒，10个无毒
110	0110有毒，10个无毒
111	0111有毒，10个无毒
根据上面的表格，得到，至少需要三个老鼠。
此类的题目分析的思路，就是这样的，要找到突破口：表示为二进制的形式。
例如，1w瓶酒，只有一瓶有毒，只有三天时间，老鼠喝了之后，三天才会发作，至少需要多少只老鼠，才能找到有毒的酒？
一样的思路，就是二进制位数多了一些。

【分析完毕】
'''
