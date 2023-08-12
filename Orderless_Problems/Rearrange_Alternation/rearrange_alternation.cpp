/*
	Rearrange alternation such that no two odd or even numbers are next to each
	other.

	But you must do it in O(n) Time Complexity and in O(1) Space Complexity.
*/

#include <iostream>
#include <vector>

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
void solution(std::vector<int>& A)
{
	int n = A.size();

	if (n <= 2)
		return;
	

	if (n % 2 != 0) // Even number of elements
	{
		int even = 0;
		int odd  = 0;

		// O(n)
		// Count Even & Odd numbers
		for (const int& num : A)
			num & 1 ? odd++ : even++;

		if (odd > even && A[0] % 2 == 0)
		{
			// O(n)
			for (int i = 1; i < n; i++)
			{
				if (A[i] % 2 != 0)
				{
					std::swap(A[0], A[i]);
					break;
				}
			}
		}
		else if (even > odd && A[0] % 2 != 0)
		{
			// O(n)
			for (int i = 1; i < n; i++)
			{
				if (A[i] % 2 == 0)
				{
					std::swap(A[0], A[i]);
					break;
				}
			}
		}
	}

	int left  = 1;
	int right = 1;

	// O(n)
	while (right < n)
	{
		// Same parity
		if (A[left - 1] % 2 == A[left] % 2)
		{
			while (right < n)
			{
				if (A[left] % 2 != A[right] % 2)
				{
					std::swap(A[left], A[right]);
					left++;
					right = left;
					break;
				}

				right++;
			}

			if (right == n)
				return;
		}
		else
		{
			left++;
			right++;
		}
	}
}

#include<iostream>

int
main()
{
	// std::vector<int> A = {6, 7, 3, 5, 4, 2, 8};
	// std::vector<int> A = {7, 6, 3, 5, 4, 2, 8};
	// std::vector<int> A = {2, 5, 8, 1, 4, 6, 3};
	// std::vector<int> A = {2, 5, 8, 1, 4, 7, 6, 3, 9};
	// std::vector<int> A = {6, 1, 8, 7, 2, 5, 4, 3};
	// std::vector<int> A = {6, 1, 8, 7, 2, 5, 4, 3, 9};
	// std::vector<int> A = {4, 1, 6, 5, 2, 3};
	// std::vector<int> A = {4, 1, 6, 5, 2, 3, 7};
	// std::vector<int> A = {8, 6, 2, 4, 7, 1, 5, 3};
	// std::vector<int> A = {8, 5, 2, 7, 4, 1, 6, 3, 9};
	// std::vector<int> A = {1, 1, 1, 1, 4, 4, 4, 4};
	// std::vector<int> A = {1, 1, 1, 1, 4, 4, 4, 4, 4};
	std::vector<int> A = {1, 1, 1, 1, 1, 4, 4, 4, 4};

	/* Write Input */
	std::cout << "\n\tBefore:";
	bool first = true;
	std::cout << "\n\tA: [";
	for (auto x: A)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n\n";


	/* Solution */
	solution(A);

	/* Write Output */
	std::cout << "\n\tAfter:";
	first = true;
	std::cout << "\n\tA: [";
	for (auto x: A)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n\n";

	return 0;
}
