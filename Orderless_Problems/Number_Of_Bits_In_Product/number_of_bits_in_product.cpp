#include <iostream>

class Solution{
public:
	int solution(int A, int B)
	{
		int product = A * B;

		int count = 0;
		while (product > 0)
		{
			count += 0x1 & product;

			product >>= 1;
		}

		return count;
	}
};

int main()
{
	Solution sol;

	/* Example 1 */
	int A = 3;
	int B = 7;

	/* Example 2 */
	// int A = 1;
	// int B = 1;

	/* Example 3 */
	// int A = 1;
	// int B = 2;

	/* Example 4 */
	// int A = 0;
	// int B = 7;

	/* Example 5 */
	// int A = 3;
	// int B = 0;

	std::cout << "\n\t===============================";
	std::cout << "\n\t== NUMBER OF BITS IN PRODUCT ==";
	std::cout << "\n\t===============================\n";


	/* Write Input */
	std::cout << "\n\tA: " << A << ", B: " << B << "\n";

	/* Solution */
	int count = sol.solution(A, B);

	/* Write Output */
	std::cout << "\n\tProduct: " << A * B;
	std::cout << "\n\tBits in Product: " << count << "\n\n";

	return 0;
}
