//karatsuba algorithms: z = x * y

#include <stdio.h>
#include <stdlib.h>

int powTen(int m)
//return pow(10, m)
{
	if(m <= 0) 
		return 0;
	int ret = 1;
	while(m > 0){
		ret *= 10;
		m--;
	}
	return ret;
}
int max_len(int m)
{
	if(m < 10)
		return 1;
	int ret = 1;
	while( m / 10 != 0){
		ret ++;
		m /= 10;
	}
	return ret;
}

int karatsuba(int num1, int num2)
{
	if(num1 < 10 || num2 < 10)
		return num1 * num2;
	int m = max_len(num1 > num2 ? num1: num2);
	int m2 = m / 2;
	int pow10m2 = powTen(m2);
	
	int high1 = num1 / pow10m2;
	int low1 = num1 % pow10m2;
	int high2 = num2 / pow10m2;
	int low2 = num2 % pow10m2;

	int z0 = karatsuba(low1, low2);
	int z1 = karatsuba(low1 + high1, low2 + high2);
	int z2 = karatsuba(high1, high2);

	return z2 * powTen(2 * m2) + (z1 - z2 - z0) * powTen(m2) + z0;
}

int main()
{
	int x = 12345;
	int y = 56789;
	printf("%d * %d = %d\n%d\n", x, y, karatsuba(x, y), x * y);
	return 0;
}
