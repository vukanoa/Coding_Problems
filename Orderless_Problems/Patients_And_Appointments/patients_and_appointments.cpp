#include <iostream>
#include <vector>
#include <unordered_set>

class Solution{
public:
	int solution(std::vector<int>& A, std::vector<int>& B, int S)
	{
		std::unordered_set<int> taken;

		return dfs_backtracking(A, B, taken, 0);
	}

private:
	bool dfs_backtracking(std::vector<int>& A, std::vector<int>& B, std::unordered_set<int>& taken, int i)
	{
		if (i == A.size())
			return true;

		if (taken.find(A[i]) == taken.end()) // Not taken
		{
			taken.insert(A[i]);

			if (dfs_backtracking(A, B, taken, i + 1))
				return true;

			taken.erase(A[i]);
		}

		if (taken.find(B[i]) == taken.end()) // Not taken
		{
			taken.insert(B[i]);

			if (dfs_backtracking(A, B, taken, i + 1))
				return true;

			taken.erase(B[i]);
		}

		return false;
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	// std::vector<int> A = {1, 1, 3};
	// std::vector<int> B = {2, 2, 1};
	// int S = 3;

	/* Example 2 */
	// std::vector<int> A = {3, 2, 3, 1};
	// std::vector<int> B = {1, 3, 1, 2};
	// int S = 3;

	/* Example 3 */
	// std::vector<int> A = {2, 5, 6, 5};
	// std::vector<int> B = {5, 4, 2, 2};
	// int S = 8;

	/* Example 4 */
	std::vector<int> A = {1, 2, 1, 6, 8, 7, 8};
	std::vector<int> B = {2, 3, 4, 7, 7, 8, 7};
	int S = 10;

	/* Example 5 */
	// std::vector<int> A = {1, 2, 1, 6, 8, 7, 5};
	// std::vector<int> B = {2, 3, 4, 7, 7, 8, 7};
	// int S = 10;

	/* Example 6 */
	// std::vector<int> A = {7};
	// std::vector<int> B = {3};
	// int S = 8;

	/* Example 7 */
	// std::vector<int> A = {7, 3};
	// std::vector<int> B = {3, 7};
	// int S = 7;

	/* Example 8 */
	// std::vector<int> A = {7, 3, 7};
	// std::vector<int> B = {3, 7, 3};
	// int S = 7;

	/* Example 9 */
	// std::vector<int> A = {7, 3, 7};
	// std::vector<int> B = {3, 7, 3};
	// int S = 7;

	std::cout << "\n\t===================================";
	std::cout << "\n\t===== PATIENTS & APPOINTMENTS =====";
	std::cout << "\n\t===================================\n";


	/* Write Input */
	std::cout << "\n\tS: " << S;
	bool first = true;
	std::cout << "\n\tA: [";
	for (auto x: A)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]";

	first = true;
	std::cout << "\n\tB: [";
	for (auto x: B)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n\n";


	/* Solution */
	bool possible = sol.solution(A, B, S);


	/* Write Output */
	if (possible)
		std::cout << "\n\tOut: It's Possible!\n\n";
	else
		std::cout << "\n\tOut: It's NOT Possible!\n\n";

	return 0;
}
