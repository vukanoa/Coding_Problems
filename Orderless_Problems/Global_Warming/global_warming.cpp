#include <iostream>
#include <vector>

/* Time  Complexity: O(M * N * K^2) */
/* Space Complexity: O(1) */
class Solution{
public:
	int solution(std::vector<std::vector<int>>& A, int K)
	{
		int M = A.size();
		int N = A[0].size();

		if (M == 1 && N == 1)
			return A[0][0] ? 0 : 1;

		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (A[i][j] == 1)
				{
					int row = i - K + 1;
					int col = j - K + 1;

					int R = i + K;
					int C = j + K;

					for (int x = row; x < R; x++)
					{
						for (int y = col; y < C; y++)
						{
							if (x < 0 || y < 0)
								continue;
							
							if (A[x][y] == 1)
								continue;
							else
								A[x][y] = 2;
						}
					}

					if (i - K >= 0) A[i - K][  j  ] = 2; // Up
					if (i + K <  M) A[i + K][  j  ] = 2; // Down
					if (j - K >= 0) A[  i  ][j - K] = 2; // Left
					if (j + K <  N) A[  i  ][j + K] = 2; // Right
				}
			}
		}

		int turbines = 0;
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (A[i][j] == 0)
					turbines++;
			}
		}

		return turbines;
	}
};

#include<iostream>

int
main()
{
	Solution sol;

	/* Example 1 */
	// int K = 1;
	// std::vector<std::vector<int>> A = {{1, 0, 0},
	//                                    {0, 0, 0},
	//                                    {0, 0, 1},
	//                                    {0, 1, 0}};


	/* Example 2 */
	// int K = 2;
	// std::vector<std::vector<int>> A = {{0, 0, 0, 0},
	//                                    {0, 0, 0, 0},
	//                                    {0, 0, 0, 0}};


	/* Example 3 */
	int K = 2;
	std::vector<std::vector<int>> A = {{0, 0, 0, 0, 0, 0, 0, 0},
	                                   {0, 0, 0, 0, 0, 0, 0, 0},
	                                   {0, 0, 1, 0, 0, 0, 0, 0},
	                                   {0, 0, 0, 0, 0, 0, 0, 0},
	                                   {0, 0, 0, 0, 0, 0, 0, 0},
	                                   {0, 0, 0, 0, 0, 0, 0, 0},
	                                   {0, 0, 0, 0, 0, 0, 1, 0},
	                                   {0, 0, 0, 0, 0, 0, 0, 0}};


	std::cout << "\n\t======================";
	std::cout << "\n\t=== GLOBAL WARMING ===";
	std::cout << "\n\t======================\n";



	/* Write Input */
	bool first = true;
	std::cout << "\n\tA: \n\t\t[";
	for (auto x: A)
	{
		if (!first)
			std::cout << ",\n\t\t ";

		bool first_first = true;
		std::cout << "[";
		for (const auto& xx : x)
		{
			if (!first_first)
				std::cout << ", ";

			std::cout << xx;
			first_first = false;
		}
		std::cout << "]";

		first = false;
	}
	std::cout << "]\n\n";

	/* Solution */
	int turbines = sol.solution(A, K);


	/* Write Output */
	std::cout << "\n\tTurbines: " << turbines << "\n\n";

	return 0;
}
