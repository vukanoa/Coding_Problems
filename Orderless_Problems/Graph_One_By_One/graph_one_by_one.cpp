/*

	Example 1
	int N = 4;

	A [1, 2, 4, 4, 5]
	B [2, 3, 1, 3, 1]

	
	return true -> (1,2) (2,3) (4,3)


	Example 2
	int N = 4;

	A [1, 2, 1, 3]
	B [2, 4, 3, 4]

	return false -> There is no direct connection from vertex 2 to 3


	Example 3
	int N = 6;

	A [2, 4, 5, 3]
	B [3, 5, 6, 4]

	return false -> There is no direct connection from vertex 1 to 2


	Example 4
	int N = 3;

	A [1, 3]
	B [2, 2]

	return true -> (1,2) (3,2)

	N [2..100000]
	M [0..100000]

	A & B are integers within the range [1..N]
	There are no self-loops (edges A[k] = B[k]) in the graph;
	There are no multiple edges between the same vertices

*/

#include <iostream>
#include <vector>
#include <climits>

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
int solution(int N, std::vector<int>& A, std::vector<int>& B)
{
	int M = A.size();

	// To have a straight path(such as 1 - 2 - 3), you need minimum N-1 edges
	if (M < N-1)
		return false;
	
	// N+1 so that I don't have to worry about indexing
	std::vector<int> map(N+1, INT_MAX);

	for (int i = 0; i < M; i++)
	{
		if (B[i] > A[i] && B[i] < map[A[i]])
			map[A[i]] = B[i];

		if (A[i] > B[i] && A[i] < map[B[i]])
			map[B[i]] = A[i];
	}

/*
	A = [1, 2, 4, 4, 3]
	B = [2, 3, 1, 3, 1]

	1 : 2
	2 : 3
	3 : 4
	4 : INT_MAX
*/

	/* Starting from the index: 1 for the ease of indexing explained above */
	/*
	   Going up until N, even though we index from 1 since we don't have to
	   check if the Nth number(4 in this case) is connected further
	*/
	for (int i = 1; i < N; i++)
	{
		// If not connected at all
		if (map[i] == INT_MAX)
			return false;

		// If not connected to subsequent node
		if (map[i] != i + 1)
			return false;
	}

	return true;
}


int
main()
{
	/* Example 1 */
	int N = 4;
	std::vector<int> A = {1, 2, 4, 4, 3};
	std::vector<int> B = {2, 3, 1, 3, 1};

	/* Example 2 */
	// int N = 4;
	// std::vector<int> A = {1, 2, 1, 3};
	// std::vector<int> B = {2, 4, 3, 4};

	/* Example 3 */
	// int N = 6;
	// std::vector<int> A = {2, 4, 5, 3};
	// std::vector<int> B = {3, 5, 6, 4};

	/* Example 4 */
	// int N = 3;
	// std::vector<int> A = {1, 3};
	// std::vector<int> B = {2, 2};

	std::cout << "\n\t========================";
	std::cout << "\n\t=== GRAPH ONE BY ONE ===";
	std::cout << "\n\t========================\n";


	/* Write Input */
	std::cout << "\n\tInput";
	std::cout << "\n\t\tN: " << N;
	bool first = true;
	std::cout << "\n\t\tA: [";
	for (auto x: A)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]";

	first = true;
	std::cout << "\n\t\tB: [";
	for (auto x: B)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n\n";



	/* Solution */
	bool sol = solution(N, A, B);


	/* Write Output */
	std::cout << "\n\tSolution: ";
	if (sol)
		std::cout << "\n\t\tThe path from 1 to " << N << " does INDEED exist!\n\n";
	else
		std::cout << "\n\t\tThe path from 1 to " << N << " does NOT exist!\n\n";

	return 0;
}
