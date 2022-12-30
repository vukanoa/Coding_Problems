#include <iostream>
#include <algorithm>
#include <vector>

/*

// Example 1
A[0] = 4
A[1] = 6
A[2] = 2
A[3] = 2
A[4] = 6
A[5] = 6
A[6] = 4
Return 5


// Example 2
A[0] = 0
A[1] = 1
...
A[74999] = 74999
A[75000] = 75000
return 75000


int solution(vector<int> &A)
{
	int N = A.size();
	int result = 0;

	for (int i = 0; i < N; i++)
		for (int j = i; j < N; j++)
			if (A[i] != A[j])
				result = max(result, j - i);
	
	return result;
}
*/

using namespace std;


int original(vector<int> &A)
{
	int N = A.size();
	int result = 0;

	for (int i = 0; i < N; i++)
		for (int j = i; j < N; j++)
			if (A[i] != A[j])
				result = max(result, j - i);
	
	return result;
}

int
solution(vector<int> &A)
{
	int N = A.size();
	int result = 0;
	int end = 0;

	for (int i = 0; i < N; i++)
	{
		for (int j = N - 1; j > 1; j--)
		{
			if (result >= j - i)
				end = 1; // We certainly cannot find larger distance onwards

			if (A[i] != A[j])
			{
				result = max(result, j - i);
				break;

				if (result == A.size())
					end = 1; // It's already maximum possible distance
			}
		}

		if (end == 1)
			break;
	}
	
	return result;
}

int
main()
{
	// Example 1
	// vector<int> A = {4, 6, 2, 2, 6, 6, 4};

	// Example 2
	vector<int> A;
	for (int i = 0; i <= 75000; i++)
		A.push_back(i);

	// Example 3
	// vector<int> A;
	// for (int i = 0; i <= 500000; i++)
	// 	A.push_back(i);


	// int sol = original(A); // Unoptimized solution
	int sol = solution(A);    // OPTIMIZED solution
	std::cout << "\n\tSolution is: " << sol << "\n\n";

	return 0;
}
