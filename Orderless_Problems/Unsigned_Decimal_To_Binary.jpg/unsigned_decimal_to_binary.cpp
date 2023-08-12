#include <iostream>
#include <limits.h>
// #include <climits>

#define SIZE 128

int  solution(int A, int B);
int  _solution(unsigned long long A, unsigned long long B); // wrapper
int  bits_in_binary_representation(unsigned long long n);
void decimal_to_binary(int n);

int
main()
{
	// 10000000000000000 -> the product of MAX_1 * MAX_2

	// int number_1 = 3;
	// int number_2 = 7;
	
	int number_1 = 100000000;
	int number_2 = 100000000;

	unsigned long long product = number_1 * number_2;
	// printf("\n\t Product = %llu\n\n", product);
	int sol = solution(number_1, number_2);

	std::cout << "\n\tBits for Number (" << number_1 << " * " << number_2 << ") = " << product << " is: " << sol << "\n\n";

	// printf("\n\tBits for Number (%d * %d) = %llu is : %llu\n\n", number_1, number_2, product, sol);
	// printf("\n\tULLONG_MAX = %llu\n\n", ULLONG_MAX);

	return 0;
}


int solution(int A, int B)
{
	unsigned long long cur_A = (unsigned long long) A;
	unsigned long long cur_B = (unsigned long long) B;
	return _solution(cur_A, cur_B);
}


int
_solution(unsigned long long A, unsigned long long B)
{
	int sol = bits_in_binary_representation(A*B);
	return sol;
}


int
bits_in_binary_representation(unsigned long long n)
{
	int ret_count = 0;

	while (n > 0)
	{
		if (n % 2 == 1)
			ret_count++;

		n = n / 2;
	}

	return ret_count;
}


void
decimal_to_binary(int n)
{
	int binary[SIZE];
	int number = n;
	int i = 0;
	int ret_count = 0;

	while (n > 0)
	{
		binary[i] = n % 2;
		n = n / 2;
		i++;
	}

	std::cout << "Number: " << number << " in binary is: ";
	for (int x = i - 1; x >= 0; x--)
		std::cout << binary[x];

	std::cout << "\n\n";
}
