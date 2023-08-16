#include <iostream>
#include <vector>

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




/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution{
public:
	int solution(std::vector<int>& blocks, int N)
	{
		std::vector<int> dp_left (N, 0);
		std::vector<int> dp_right(N, 0);

		// Jumping to the right
		for (int i = N-2 ; i >= 0; i--)
		{
			if (blocks[i] <= blocks[i + 1])
				dp_right[i] = 1 + dp_right[i + 1];
		}

		// Jumping to the left
		for (int i = 1; i < N; i++)
		{
			if (blocks[i - 1] >= blocks[i])
				dp_left[i] = 1 + dp_left[i - 1];
		}

		int largest_distance = 0;
		for (int i = 0; i < N; i++)
		{
			// int current_distance = (i + dp_right[i]) - (i - dp_left[i]) + 1;
			int current_distance = dp_right[i] + dp_left[i] + 1;

			largest_distance = std::max(largest_distance, current_distance);
		}

		return largest_distance;
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	// int N = 4;
	// std::vector<int> blocks = {2, 6, 8, 2};

	/* Example 2 */
	int N = 5;
	std::vector<int> blocks = {1, 5, 5, 2, 6};

	/* Example 3 */
	// int N = 2;
	// std::vector<int> blocks = {1, 1};

	/* Example 4 */
	// int N = 8;
	// std::vector<int> blocks = {4, 2, 1, 8, 9, 2, 5, 5};

	std::cout << "\n\t===========";
	std::cout << "\n\t== FROGS ==";
	std::cout << "\n\t===========\n";


	/* Write Input */
	bool first = true;
	std::cout << "\n\tBlocks: [";
	for (auto x: blocks)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n";


	/* Solution */
	int largest_distance = sol.solution(blocks, N);


	/* Write Output */
	std::cout << "\n\tLargest Distance: " << largest_distance << "\n\n";

	return 0;
}
