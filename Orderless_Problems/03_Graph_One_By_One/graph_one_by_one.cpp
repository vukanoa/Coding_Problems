#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

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


/* Naive, not efficient solution */
/*
bool
solution(int N, std::vector<int> &A, std::vector<int> &B)
{
	int cur = 1;
	int i = 0;
	while (i < A.size())
	{
		if (A[i] == cur && B[i] == cur+1)
		{
			if (cur+1 == N)
				return true;
			else
			{
				cur++;
				i = 0;
				continue;
			}
		}
		else if (B[i] == cur && A[i] == cur+1)
		{

			if (cur+1 == N)
				return true;
			else
			{
				cur++;
				i = 0;
				continue;
			}
		}
		i++;
	}

	return false;
}
*/


bool
solution(int N, std::vector<int> &A, std::vector<int> &B)
{
	int cur = 1;
	int i = 0;
	while (i < A.size())
	{
		if (A[i] == cur && B[i] == cur+1)
		{
			if (cur+1 == N)
				return true;
			else
				cur++;
		}
		else if (B[i] == cur && A[i] == cur+1)
		{

			if (cur+1 == N)
				return true;
			else
				cur++;
		}
		i++;
	}

	return false;
}

int
main()
{
	/* Example 1 */
	int N = 4;
	std::vector<int> A = {1, 2, 4, 4, 5};
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


	/* Before sorting */
	std::cout << "\n\tBefore: \n";
	std::cout << "\t\tN: " << N << "\n";

	std::cout << "\n\t\tA: ";
	for(auto x: A)
		std::cout << x << " ";
	std::cout << "\n";

	std::cout << "\n\t\tB: ";
	for(auto x: B)
		std::cout << x << " ";
	std::cout << "\n";


	/* Sort */
	std::vector< std::pair <int,int> > vect;

    for (int i = 0; i < A.size(); i++)
        vect.push_back( std::make_pair(A[i], B[i]));

	std::sort(vect.begin(), vect.end());

	for ( int i = 0; i < 5; ++i )
	{
		A[i] = vect[i].first;
		B[i] = vect[i].second;
	}


	/* After sorting */
	std::cout << "\n\tAfter: \n";
	std::cout << "\t\tN: " << N << "\n";

	std::cout << "\n\t\tA: ";
	for(auto x: A)
		std::cout << x << " ";
	std::cout << "\n";

	std::cout << "\n\t\tB: ";
	for(auto x: B)
		std::cout << x << " ";
	std::cout << "\n";


	/* Solve the problem */
	std::cout << "\n\t=========\n";
	std::cout << "\tSolution:\n";
	std::cout << "\t=========\n";
	if (solution(N, A, B))
		std::cout << "\n\t\tThe path from 1 to " << N << " does INDEED exist!\n\n";
	else
		std::cout << "\n\t\tThe path from 1 to " << N << " does NOT exist!\n\n";

	return 0;
}
