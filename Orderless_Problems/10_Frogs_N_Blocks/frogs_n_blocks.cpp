#include <iostream>
#include <climits>

/*
	J <= K
	Distance = K - J + 1

	[2, 6, 8, 5]
	ret 3 // blocks[0] & blocks[2] // Start blocks[0]

	[1, 5, 5, 2, 6]
	ret 4 // blocks[1] & blocks[4] // Start blocks[3]

	[1, 1]
	ret 2 // blocks[0] & blocks[1] // Start blocks[1]

	N [2..200 000]
	each element in the blocks is from [0...1 000 000 000]
*/

int solution(int blocks[], int N);

int
main()
{
	std::cout << "\n\t===========\n";
	std::cout << "\t== FROGS ==\n";
	std::cout << "\t===========\n";

	int N = 4;
	int blocks[N] = {2, 6, 8, 2};

	// int N = 5;
	// int blocks[N] = {1, 5, 5, 2, 6};

	// int N = 2;
	// int blocks[N] = {1, 1};

	// int N = 8;
	// int blocks[N] = {4, 2, 1, 8, 9, 2, 5, 5};

	int sol = solution(blocks, N);

	std::cout << "\n\tSolution is: " << sol << "\n\n";

	return 0;
}


int
solution(int blocks[], int N)
{
	int max = INT_MIN;
	int distance;

	for (int i = 0; i < N; i++)
	{
		if (i == 0)
		{
			distance = 1; // Starting distance is 1
			for (int j = 0; j < N-1; j++)
			{
				if (blocks[j] <= blocks[j+1])
					distance++;
			}
		}
		else if (i == N - 1)
		{
			distance = 1; // Starting distance is 1
			for (int j = N-1; j > 1; j--)
			{
				if (blocks[j] <= blocks[j-1])
					distance++;
			}
		}
		else
		{
			int e; // East
			for (e = i; e < N-1; e++)
			{
				if (blocks[e] > blocks[e+1])
					break;
			}

			int w; // West
			for (w = i; w > 1; w--)
			{
				if (blocks[w] > blocks[w-1])
					break;
			}
			
			distance = e - w + 1;
		}

		if (distance > max)
			max = distance;
	}

	return max;
}
