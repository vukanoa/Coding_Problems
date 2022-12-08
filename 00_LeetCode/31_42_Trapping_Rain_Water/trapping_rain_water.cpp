#include <iostream>
#include <vector>
#include <stack>
#include <climits>


/*
	============
	=== HARD ===
	============

	===========================
	42) Trapping Rain Water
	===========================

	============
	Description:
	============

	Given "n" non-negative integers representing an elevation map where the
	width of each bar is 1, compute how much water it can trap after raining.

	=============================================
	FUNCTION: int trap(std::vector<int>& height);
	=============================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  height = [0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]
	Output: 6

	--- Example 2 ---
	Input:  height = [4, 2, 0, 3, 2, 5]
	Output: 9

	*** Constraints ***
	n == height.length
	1 <= n <= 2 * 10^4
	0 <= height[i] <= 10^5

*/


/*
	------------
	--- IDEA ---
	------------

	==============
	=== O(n^2) ===
	==============
	(Brute Force)

	total_amount_of_water = 0;

	Iterating through an entire array and for each element find:
	1. Its left max  (including itself)
		left_max = std::max(left_max, height[i])
	2. Its right max (including itself)
		right_max = std::max(right_max, height[i])


	min_max = std::min(left_max, right_max);

	if (min_max - height[i] > 0)
		total_amount_of_water += min_max;

	The key takeaway from here is that every iteration we are just calculating
	the number of "squares" of water juct above the current block. Even if
	that means that "it cannot be like that". We will see in subsequent
	iterations that the range will "close", therefore the rain will be trapped.


	============
	=== O(n) ===
	============
	(Dynamic Programming)

	Since we are iterating to find left_max & right_max for each height[i], we
	can notice that such this is optimizable.

	We could use two additional arrays where we would memotize left_max for
	each index in the vector "height".

	And then at the very end iterate through an entire array and:
		total += std::min(dp_left_max[i], dp_right_max[i] - height[i]);



	============
	=== O(n) ===
	============
	(Using Stacks)

	Instead of storing the largest bar up to an index as in Dynamic Progrmaming
	approach, we can use stack to keep track of the bars that are bounded by
	longer bars and hence - may store water.

	We keep a stack and iterate over the array.
	We add the index of the bar to the stack if bar is smaller than or equal to
	the bar at the top of the stack, which means that the current bar is
	bounded by the previous bar in the stack.
	If we found a bar longer than that at the top, we are sure that the bar at
	the top of the stack is bounded by the current bar and a previous bar in
	the stack, hence, we can pop and add resulting trapped water to "total".


*/


/* Time  Complexity: O(n^2) */
/* Space Complexity: O(1) */
class Solution_brute{
public:
	int trap(std::vector<int>& height)
	{
		// Since the very left "margin" (coordinate system) cannot hold water
		if (height.size() < 3)
			return 0;

		int left_max  = INT_MIN;
		int right_max = INT_MIN;

		int total = 0;

		for (int i = 0; i < height.size(); i++)
		{
			left_max = height[i];
			for (int j = i; j >= 0; j--)
			{
				if (height[j] > left_max)
					left_max = height[j];
			}

			right_max = height[i];
			for (int j = i; j < height.size(); j++)
			{
				if (height[j] > right_max)
					right_max = height[j];
			}

			int min_max = std::min(left_max, right_max);

			if (min_max - height[i] > 0)
				total += min_max - height[i];
		}

		return total;
	}
};



/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_dp{
public:
	int trap(std::vector<int>& height)
	{
		// Since the very left "margin" (coordinate system) cannot hold water
		if (height.size() < 3)
			return 0;

		int n = height.size();
		std::vector<int> dp_left_max (n, 0);
		std::vector<int> dp_right_max(n, 0);

		int total = 0;

		dp_left_max[0] = height[0];
		for (int i = 1; i < n; i++)
			dp_left_max[i] = std::max(dp_left_max[i - 1], height[i]);

		dp_right_max[n - 1] = height[n - 1];
		for (int i = n - 2; i >= 0; i--)
			dp_right_max[i] = std::max(height[i], dp_right_max[i + 1]);

		for (int i = 1; i < n - 1; i++)
			total += std::min(dp_left_max[i], dp_right_max[i]) - height[i];

		return total;
	}
};



/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_stack{
public:
	int trap(std::vector<int>& height)
	{
		// Since the very left "margin" (coordinate system) cannot hold water
		if (height.size() < 3)
			return 0;

		int n = height.size();
		int curr_index = 0;
		int total = 0;

		std::stack<int> stack;

		while (curr_index < n)
		{
			while (!stack.empty() && height[stack.top()] < height[curr_index])
			{
				int prev_top = stack.top();
				stack.pop();

				if (stack.empty())
					break;

				int distance = curr_index - stack.top() - 1;
				int bounded = std::min(height[curr_index], height[stack.top()]) - height[prev_top];

				total += distance * bounded;
			}

			stack.push(curr_index++);
		}

		return total;
	}
};



int
main()
{
	// Solution_brute sol_brute;
	// Solution_dp sol_dp;
	Solution_stack sol_stack;

	/* Example 1 */
	std::vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};

	/* Example 2 */
	// std::vector<int> height = {4, 2, 0, 3, 2, 5};

	std::cout << "\n\t===========================";
	std::cout << "\n\t=== TRAPPING RAIN WATER ===";
	std::cout << "\n\t===========================\n\n";

	bool first = true;
	std::cout << "\n\tHeights: [";
	for (auto x: height)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n";

	// int total = sol_brute.trap(height);
	// int total = sol_dp.trap(height);
	int total = sol_stack.trap(height);

	std::cout << "\n\tTotal: " << total << "\n\n";


	return 0;
}
