#include <iostream>
#include <vector>
#include <queue>
#include <climits>

/* Time  Complexity: O(Y * (N * logX)) */
/* Space Complexity: O(N) */
class Solution{
public:
	int solution(std::vector<int>& A, int X, int Y)
	{
		if (A.size() == 1)
			return A[0];

		int N = A.size();
		int min_cost = INT_MAX;

		for (int i = 0; i < Y && i + Y < N; i++)
		{
			std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;

			for (int j = i; j < N; j+=Y)
				min_heap.push(A[j]);

			int cost = 0;
			for (int k = 0; k < X; k++)
			{
				cost += min_heap.top();
				min_heap.pop();
			}

			min_cost = std::min(min_cost, cost);
		}

		return min_cost;
	}
};

int
main()
{
	Solution sol;

	/* Example 1 */
	// std::vector<int> A = {4, 2, 3, 7};
	// int X = 2;
	// int Y = 2;

	/* Example 2 */
	// std::vector<int> A = {10, 3, 4, 7};
	// int X = 2;
	// int Y = 3;

	/* Example 3 */
	// std::vector<int> A = {4, 2, 5, 4, 3, 5, 1, 4, 2, 7};
	// int X = 3;
	// int Y = 2;

	/* Example 4 */
	// std::vector<int> A = {4, 2, 5, 4, 3, 5, 1, 4, 2, 7, 1};
	// int X = 3;
	// int Y = 2;

	/* Example 5 */
	std::vector<int> A = {3, 2, 7, 8, 3, 5, 9, 4, 2, 5, 4, 3, 5, 1, 4, 2, 1, 7};
	int X = 4;
	int Y = 3;

	std::cout << "\n\t===============================";
	std::cout << "\n\t=== REHABILITATION SESSIONS ===";
	std::cout << "\n\t===============================\n\n";


	/* Write Input */
	std::cout << "\n\tX: " << X;
	std::cout << "\n\tY: " << Y;
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
	int cost = sol.solution(A, X, Y);


	/* Write Output */
	std::cout << "\n\tSolution: " << cost << "\n\n";

	return 0;
}
