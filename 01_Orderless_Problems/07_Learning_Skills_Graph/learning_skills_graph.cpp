#include<iostream>
#include <vector>

int solution(std::vector<int> &T, std::vector<int>&A);

int
main()
{
	/* First Example */
	// std::vector<int> T {0, 0, 1, 1};
	// std::vector<int> A {2};

	/* Second Example */
	// std::vector<int> T {0, 0, 1, 2};
	// std::vector<int> A {1, 2};

	/* Third Example */
	// std::vector<int> T {0, 0, 0, 0, 2, 3, 3};
	// std::vector<int> A {2, 5, 6};

	/* Fourth Example */
	std::vector<int> T {0, 3, 0, 0, 5, 0, 5};
	std::vector<int> A {4, 2, 6, 1, 0};

	std::cout << "\n\tT: ";

	/* Print out T & A */
	for(auto x : T)
		std::cout << x << " ";
	std::cout << "\n";

	std::cout << "\tA: ";
	for(auto x : A)
		std::cout << x << " ";

	/* Solution */
	int sol = solution(T, A);
	std::cout << "\n\n\tSolution is: " << sol << "\n\n";

	return 0;
}

/*
	Examples:
	
	1. T = [0, 0, 1, 1],              A = [2],               return 3

	2. T = [0, 0, 0, 0, 2, 3, 3],     A = [2, 5, 6],         return 5

	3. T = [0, 0, 1, 2],              A = [1, 2],            return 3

	4. T = [0, 3, 0, 0, 5, 0, 5],     A = [4, 2, 6, 1, 0],   return 7

	N is an integer within the range [1..100000]
	M is an integer within the range [1..N]
	each element of arrays T and A is an integer within...

	1)
		T     [0, 0, 1, 1]
		flags [1, 1, 1, 0]            A[2]
	
	2)
		T     [0, 0, 0, 0, 2, 3, 3]
		flags [1, 0, 1, 1, 0, 1, 1]   A[2, 5, 6]

	3)
		T     [0, 0, 1, 2]
		flags [1, 1, 1, 0]            A[1, 2]
		
	4)
		T     [0, 3, 0, 0, 5, 0, 5]
		flags [1, 1, 1, 1, 0, 1, 1]   A[4, 2, 6, 1, 0]

*/


int
solution(std::vector<int> &T, std::vector<int>&A)
{
	int ret_count = 0;
	int* flags = (int*) calloc(T.size(), sizeof(int));

	int tmp_a = 0;

	for (tmp_a = 0; tmp_a < A.size(); tmp_a++)
	{
		if (flags[A[tmp_a]] == 1)
			continue;
		else
		{
			int index = A[tmp_a];
			while(index != 0)
			{
				if (flags[index] == 0)
				{
					flags[index]++;
					ret_count++;
					index = T[index];
				}
				else
					break;
			}

			if (index == 0 && flags[index] == 0)
			{
				flags[index]++;
				ret_count++;
			}
		}
	}
	
	return ret_count;
}
