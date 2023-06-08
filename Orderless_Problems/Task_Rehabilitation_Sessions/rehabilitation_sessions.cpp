#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

int
solution(vector<int> &A, int X, int Y)
{
	if (X < 2 || X > 200000 || A.size() < 2 || A.size() > 200000 )
		return -1; // Invalid argumnets

	if(Y < 1 || Y >= 200000)
		return -1; // Invlaid arguments

	for (auto x : A)
	{
		if (x > 1000)
			return -1; // Each element of array A is an integer within the range [1..1000]
	}

	/*
	   We can immediately see that the very first session has to start
	   (X-1)*Y - 1 position from the very end of an array.

	   So we don't have to iterate through an entire array. The first session
	   can only begin from 0 to (end() - ( (X-1)*Y + 1)  )

	   So that's an optimization
	 */

	unsigned last = A.size();
	last -= ((X - 1)*Y + 1);

	int min = INT_MAX;
	int sum = 0;

	for (unsigned i = 0; i <= last; i++)
	{
		int tmp_i = i;
		int tmp_x = X;

		while (tmp_x--)
		{
			sum += A[tmp_i];
			tmp_i += Y;
		}

		if (sum < min)
			min = sum;

		sum = 0;
	}

	return min;
}


int
main()
{
	// int X = 2;
	// int Y = 2;
	// vector<int> A = {4, 2, 3, 7};

	// int X = 2;
	// int Y = 3;
	// vector<int> A = {10, 3, 4, 7};

	// int X = 3;
	// int Y = 2;
	// vector<int> A = {4, 2, 5, 4, 3, 5, 1, 4, 2, 7};

	int X = 3;
	int Y = 4;
	vector<int> A = {9, 3, 4, 8, 7, 2, 3, 1, 2, 7}; // 12

	// int X = 5;
	// int Y = 2;
	// vector<int> A = {}; 


	std::cout << "\n\tSolution is: " << solution(A, X, Y) << "\n\n";

	return 0;
}
