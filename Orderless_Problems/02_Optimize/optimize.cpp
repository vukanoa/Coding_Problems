#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

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


int original(vector<int>& A)
{
	int N = A.size();
	int result = 0;

	for (int i = 0; i < N; i++)
		for (int j = i; j < N; j++)
			if (A[i] != A[j])
				result = max(result, j - i);
	
	return result;
}

int solution(std::vector<int>& A)
{
	if (A.size() == 1)
		return 0;
	
	int n = A.size();

	if (A[0] != A[n - 1])
		return n - 1;

	int result = 0;

	std::unordered_map<int, int> umap_first_occured;

	// O(n)
	for (int i = 0; i < n; i++)
	{
		// If it doesn't exist, insert it
		if (umap_first_occured.find(A[i]) == umap_first_occured.end())
			umap_first_occured.insert({A[i], i});
	}

	// O(n)
	for (auto& entry : umap_first_occured)
	{
		if (entry.first != A[n-1]) // Or A[0] since they are the same
		{
			result = std::max(result,  0  + entry.second);
			result = std::max(result, n-1 - entry.second);
		}
	}

	// O(n)
	int first_diff_from_left = n-1;
	for (int i = 0; i < n; i++)
	{
		if (A[0] != A[i])
		{
			first_diff_from_left = i;
			break;
		}
	}

	// O(n)
	int first_diff_from_right = 0;
	for (int i = n-1; i >= 0; i--)
	{
		if (A[0] != A[i])
		{
			first_diff_from_right = i;
			break;
		}
	}

	result = std::max(result, 0   + first_diff_from_right);
	result = std::max(result, n-1 - first_diff_from_left);

	return result;
}


int
main()
{
	// Example 1
	// vector<int> A = {4, 6, 2, 2, 6, 6, 4};

	// Example 2
	// vector<int> A = {4, 6, 2, 2, 6, 6, 4, 4, 4, 4};

	// Example 3
	// std::vector<int> A = {1, 2, 3, 4, 5, 6, 1};

	// Example 4
	// std::vector<int> A = {4, 4, 4, 4, 4, 4, 7, 4, 4};

	// Example 5
	// std::vector<int> A = {5, 5};

	// Example 6
	// vector<int> A;
	// for (int i = 0; i <= 75000; i++)
	// 	A.push_back(i);

	// Example 7
	vector<int> A;
	for (int i = 0; i <= 500000; i++)
		A.push_back(i);


	// int sol1 = original(A); // Unoptimized solution
	int sol2 = solution(A);    // OPTIMIZED solution
	// std::cout << "\n\tSolution_1 is: " << sol1 << "\n\n";
	std::cout << "\n\tSolution_2 is: " << sol2 << "\n\n";

	return 0;
}
