#include <iostream>
#include <vector>
#include <stack>

/*
	============
	=== HARD ===
	============

	==================================
	84) Largest Rectangle in Histogram
	==================================

	============
	Description:
	============

	Given an array of integers "heights" representing the histogram's bar
	height where the width of each bar is 1, return the area of the largest
	rectangle in the histogram.

	=========================================================
	FUNCTION: int largestRectangleArea(vector<int>& heights);
	=========================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  heights = [2, 1, 5, 6, 2, 3]
	Output: 10

	--- Example 2 ---
	Input:  heights = [2, 4]
	Output: 4

	*** Constraints ***
	1 <= heights.length <= 10^5
	0 <= heights[i] <= 10^4

*/


/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution{
public:
	int largestRectangleArea(std::vector<int>& heights)
	{
		int n = heights.size();
		std::vector<int> left(n);
		std::vector<int> right(n);

		std::stack<int> stack;

		// Fill left
		for (int i = 0; i < n; i++)
		{
			if (stack.empty())
			{
				left[i] = 0;
				stack.push(i);
			}
			else
			{
				while (!stack.empty() && heights[stack.top()] >= heights[i])
					stack.pop();

				left[i] = stack.empty() ? 0 : stack.top() + 1;
				stack.push(i);
			}
		}

		// Clear stack
		while (!stack.empty())
			stack.pop();

		// Fill right
		for (int i = n - 1; i >= 0; i--)
		{
			if (stack.empty())
			{
				right[i] = n - 1;
				stack.push(i);
			}
			else
			{
				while (!stack.empty() && heights[stack.top()] >= heights[i])
					stack.pop();

				right[i] = stack.empty() ? n - 1 : stack.top() - 1;
				stack.push(i);
			}
		}

		int max_area = 0;
		for (int i = 0; i < n; i++)
		{
			int width = right[i] - left[i] + 1;
			max_area = std::max(max_area, heights[i] * width);
		}

		return max_area;
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	std::vector<int> heights = {2, 1, 5, 6, 2, 3};

	/* Example 2 */
	// std::vector<int> heights = {2, 4};

	/* Example 3 */
	// std::vector<int> heights = {5, 2, 4, 7, 9, 3, 2, 6};

	/* Example 4 */
	// std::vector<int> heights = {1, 1, 1, 1, 1, 1};

	/* Example 5 */
	// std::vector<int> heights = {3, 5, 5, 4, 0, 1, 7};

	std::cout << "\n\t======================================";
	std::cout << "\n\t=== LARGEST RECTANGLE IN HISTOGRAM ===";
	std::cout << "\n\t======================================\n";

	bool first = true;
	std::cout << "\n\tHeights: [";
	for (auto x: heights)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n";

	/* Solution */
	int max_area = sol.largestRectangleArea(heights);

	std::cout << "\n\tMax Area: " << max_area << "\n\n";

	return 0;
}
