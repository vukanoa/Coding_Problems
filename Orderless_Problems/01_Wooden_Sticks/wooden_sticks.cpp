#include <iostream>

int solution(int A, int B)
{
	if (A+B <= 3)
		return 0;

	// Make sure A is always longer so that we don't have to "duplicate" code
	if(A < B)
		std::swap(A, B);

	if (A/4 > B)
		return A/4;
	else if (A/3 >= B)
		return B;
	else if (A/3 < B)
		return std::max(A/3, B/2);

	return 0;
}

int
main()
{
	/* Example 1 */
	// int a = 10;
	// int b = 21;

	/* Example 2 */
	// int a = 21;
	// int b = 10;

	/* Example 3 */
	// int a = 5;
	// int b = 21;

	/* Example 4 */
	// int a = 4;
	// int b = 21;

	/* Example 5 */
	// int a = 2;
	// int b = 1;

	/* Example 6 */
	// int a = 1;
	// int b = 8;

	/* Example 7 */
	// int a = 15;
	// int b = 18;

	/* Example 8 */
	// int a = 13;
	// int b = 31;

	/* Example 9 */
	int a = 13;
	int b = 13;

	std::cout << "\n\t=====================";
	std::cout << "\n\t=== WOODEN STICKS ===";
	std::cout << "\n\t=====================\n";

	/* Write Input */
	std::cout << "\n\tInput: A = " << a << ", B = " << b << "\n";

	/* Solution */
	int result = solution(a, b);

	/* Write Onput */
	std::cout << "\n\tSolution is: " << result << std::endl << std::endl;

	return 0;
}
