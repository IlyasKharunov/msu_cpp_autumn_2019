#include"Bigint.h"
#include<limits.h>
#include<cassert>
using namespace std;

int main() {
	BigInt* numbers = new BigInt[500];
	numbers[0] = 0;
	int i = 1;

	for (BigInt n = 1; n < 500; n = n + 1) {
		numbers[i] = numbers[i-1] + numbers[i-1] + 1;
		i++;
	}
	cout <<' '<< numbers[499] << endl;

	BigInt* neg_numbers = new BigInt[500];
	neg_numbers[0] = 0;
	i = 1;

	for (BigInt n = 1; n < 500; n = n + 1) {
		neg_numbers[i] = neg_numbers[i - 1] + neg_numbers[i - 1] - 1;
		i++;
	}
	cout << neg_numbers[499] << endl;

	BigInt* numbers2 = new BigInt[500];
	numbers2[0] = 0;
	i = 1;
	for (BigInt n = 1; n < 500; n = n + 1) {
		numbers2[i] = numbers2[i-1] + numbers2[i-1] + 1;
		i++;
	}

	for (int j = 0; j < 500; j++) 
		assert(numbers[j] == numbers2[j]);
	for (int j = 2; j < 500; j++) 
		assert(numbers[j] > numbers[j - 1]);
	for (int j = 0; j < 500; j++)
		assert(numbers[0] == -neg_numbers[0]);
	for (int j = 0; j < 500; j++) 
		assert(numbers[j]+neg_numbers[j] == 0);
	for (int j = 0; j < 500; j++) 
		assert(neg_numbers[j] + numbers[j] == 0);
	for (int j = 1; j < 500; j++) 
		assert(numbers[j-1] > neg_numbers[j]);
	for (int j = 0; j < 500; j++) 
		assert(neg_numbers[j] - neg_numbers[j] == 0);
	for (int j = 0; j < 500; j++) 
		assert(numbers[j] - numbers[j] == 0);
	for (int j = 0; j < 500; j++) 
		assert(BigInt(j)+neg_numbers[j] + numbers[j]- BigInt(j) == 0);

	BigInt* numbers_moved = new BigInt[500];
	copy(numbers, numbers + 500, numbers_moved);

	for (int j = 0; j < 500; j++) 
		numbers_moved[j] = move(numbers[j]);

	for (int j = 0; j < 500; j++) 
		assert(numbers_moved[j] == -neg_numbers[j]);
	for (int j = 0; j < 500; j++) 
		assert(numbers[j]+5 == 5);

	BigInt a = 0, b, c(0), d = 1;

	assert(a == b and b == c and c != d and c < d);
	assert(c == d - d and d == d + a and d == b + d);

	BigInt t = 1000000000;
	for (int i = 0; i < 100000-1; i++) t = t + 1000000000;

	cout << ' '<<t - 1 << endl;
	cout << 1 - t << endl;
	cout << 1 - t - (t - 1) << endl;

	assert(BigInt(123456789) - BigInt(123456666) == 123);
	assert(BigInt(123456666) - BigInt(123456789) == -123);
	return 0;
}