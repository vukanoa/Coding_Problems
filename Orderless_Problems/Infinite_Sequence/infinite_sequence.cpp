#include <iostream>
#include <vector>
#include <unordered_map>

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution{
public:
	int solution(int N)
	{
		int dp_2 = 0;
		int dp_1 = 1;

		for (int i = 2; i < N; i++)
		{
			int num = dp_2 + dp_1;

			// If it's greater than 9, we have to sum the digits
			if (num > 9)
				num = sum_digits(num);

			dp_2 = dp_1;
			dp_1 = num;
		}

		return dp_2 + dp_1;
	}

private:
	int sum_digits(int n)
	{
		int sum = 0;

		while (n > 0)
		{
			sum += n % 10;
			n /= 10;
		}

		return sum;
	}
};


// class Solution{
// public:
// 	int solution(int N)
// 	{
// 		std::unordered_map<int, int> dp;
// 		dp.insert({0, 0});
// 		dp.insert({1, 1});
// 
// 		return fib(N - 2, dp) + fib(N - 1, dp);
// 	}
// 
// private:
// 	int fib(int N, std::unordered_map<int, int>& dp)
// 	{
// 		if (dp.find(N) != dp.end())
// 			return dp[N];
// 
// 		int num = fib(N - 2, dp) + fib(N - 1, dp);
// 
// 		if (num < 10)
// 			dp.insert({N, num});
// 		else
// 			dp.insert({N, sum_digits(num)});
// 
// 		return dp[N];
// 	}
// 
// 	int sum_digits(int n)
// 	{
// 		int sum = 0;
// 
// 		while (n > 0)
// 		{
// 			sum += n % 10;
// 			n /= 10;
// 		}
// 
// 		return sum;
// 	}
// };


int
main()
{
	Solution sol;

	/* Example 1 */
	// int N = 2;

	/* Example 2 */
	// int N = 6;

	/* Example 3 */
	// int N = 10;

	/* Example 3 */
	// int N = 11;

	/* Example 3 */
	// int N = 12;

	/* Example 3 */
	// int N = 100;

	/* Example 3 */
	// int N = 1000;

	/* Example 3 */
	// int N = 10000;

	/* Example 3 */
	// int N = 1000000;

	/* Example 3 */
	// int N = 10000000;

	/* Example 3 */
	// int N = 100000000;

	/* Example 3 */
	int N = 1000000000;

	std::cout << "\n\t=========================";
	std::cout << "\n\t=== INFINITE SEQUENCE ===";
	std::cout << "\n\t=========================\n\n";

	/* Write Input */
	std::cout << "\n\tN : " << N << "\n";

	/* Solution */
	int number = sol.solution(N);

	/* Write Output */
	std::cout << "\n\tOut: " << number << "\n\n";

	return 0;
}

