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


/*
	------------
	--- IDEA ---
	------------

	Brute force solution would be to find first left bar that the current one
	and first right bar less that the current one, for each bar(each number
	in the array).

	Since that would take O(n^2) we have to optimize it somehow.

	We can use stack.
	So how can a stack help us optimize this solution?
	We have two vectors: "left" and "right". Those represent the left most bar
	(inclusive) up to which the current bar is the lowest and the right most
	bar(inclusive) up to which the current bar is the lowest.
	Size of both left and right is the same as the size of the array - we will
	have the left and the right bound for each and every bar.

	After we have that it's easy to calculate max_area for each bar. After that
	all we have to do is just return the maximum value of all of those
	max_areas.

	But how does the stack help us?
	Consider this example:
		[2, 1, 5, 6, 2, 3]

	If the stack is empty, that means the left most bar that has to be included
	in calculating the max area of the current bar is the bar at index 0, that
	is why we say:
		left[i] = 0;

	and we push current index's in the stack.
	Why?

	If the stack isn't empty then while the stack is not empty and while
	the bar under the index at the top of the stack is greater than or equals
	to current bar's height, pop from the stack.

	After the while loop ended see if stack is empty, if it is then:
		left[i] = 0

	and if it is not then:
		left[i] = stack.top() + 1;

	Why stack.top() + 1?
	Because we have found the bar whose height is less than the height of the
	current one, thus we have to exclude that, so we add + 1 since stack.top()
	returns the index of the bar not the height of the bar.


	Let's go Iteration by iteration:
	=== 1st Iteration ===

	left    = [-1, -1, -1, -1, -1, -1]
	heights = [ 2,  1,  5,  6,  2,  3]
	            ^
	Stack
	----------------
	|
	----------------


	=== 2nd Iteration ===

	left    = [ 0, -1, -1, -1, -1, -1]
	heights = [ 2,  1,  5,  6,  2,  3]
	                ^
	Stack
	----------------
	| 0 |
	----------------
	pop()
	push(1)


	=== 3rd Iteration ===

	left    = [ 0,  0, -1, -1, -1, -1]
	heights = [ 2,  1,  5,  6,  2,  3]
	                    ^
	Stack
	----------------
	| 1 |
	----------------
	push(2)


	=== 4th Iteration ===

	left    = [ 0,  0,  2, -1, -1, -1]
	heights = [ 2,  1,  5,  6,  2,  3]
	                        ^
	Stack
	----------------
	| 1 | 2 |
	----------------
	push(3)


	=== 5th Iteration ===

	left    = [ 0,  0,  2,  3, -1, -1]
	heights = [ 2,  1,  5,  6,  2,  3]
	                            ^
	Stack
	----------------
	| 1 | 2 | 3 |
	----------------
	pop
	pop
	push(4)


	=== 6th Iteration ===

	left    = [ 0,  0,  2,  3,  2, -1]
	heights = [ 2,  1,  5,  6,  2,  3]
	                                ^
	Stack
	----------------
	| 1 | 4 |
	----------------
	push(5)


	After the for loop:

	left   =  [ 0,  0,  2,  3,  2,  5]
	heights = [ 2,  1,  5,  6,  2,  3]
	                                   ^
	Stack
	----------------
	| 1 | 4 | 5 |
	----------------


	After this, we have to do a similar thing for "right" vector, therefore we
	first have to clear the stack.

	The rest of the algorithm was explained at the beginning of this
	explanation.

*/


/* Time  Beats: 66.90% */
/* Space Beats: 60.71% */

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



/*
	------------
	--- IDEA ---
	------------

	TODO: Detailed Explanation
	
*/



/* Time  Beats: 89.17% */
/* Space Beats: 63.46% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Neat{
public:
	int largestRectangleArea(std::vector<int>& heights)
	{
		int max_area = 0;
		std::stack<std::pair<int , int>> stack; // pair: (index, height)

			for (int i = 0; i < heights.size(); i++)
			{
				int start = i;

				while (!stack.empty() && stack.top().second > heights[i])
				{
					std::pair<int, int> top = stack.top();
					stack.pop();

					max_area = std::max(max_area, top.second * (i - top.first));
					start = top.first;
				}

				stack.push({start, heights[i]});
			}

			while (!stack.empty())
			{
				std::pair<int, int> top = stack.top();
				stack.pop();

				max_area = std::max(max_area, top.second * (int)(heights.size() - top.first));
			}

		return max_area;
	}
};


int
main()
{
	Solution sol;
	Solution_Neat sol_neat;

	/* Example 1 */
	// std::vector<int> heights = {2, 1, 5, 6, 2, 3};

	/* Example 2 */
	// std::vector<int> heights = {2, 4};

	/* Example 3 */
	// std::vector<int> heights = {5, 2, 4, 7, 9, 3, 2, 6};

	/* Example 4 */
	// std::vector<int> heights = {5, 2, 8, 7, 9, 3, 2, 9};

	/* Example 5 */
	// std::vector<int> heights = {1, 1, 1, 1, 1, 1};

	/* Example 6 */
	// std::vector<int> heights = {1, 2, 9, 8, 1, 1};

	/* Example 7 */
	std::vector<int> heights = {3, 5, 5, 4, 0, 1, 7};

	std::cout << "\n\t======================================";
	std::cout << "\n\t=== LARGEST RECTANGLE IN HISTOGRAM ===";
	std::cout << "\n\t======================================\n";


	/* Write Input */
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
	// int max_area = sol.largestRectangleArea(heights);
	int max_area = sol_neat.largestRectangleArea(heights);

	
	/* Write Output */
	std::cout << "\n\tMax Area: " << max_area << "\n\n";


	return 0;
}
