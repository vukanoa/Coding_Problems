#include <iostream>
#include <vector>

/*
	==============
	=== MEDIUM ===
	==============
	
	=============================
	11) Container With Most Water
	=============================
	
	============
	Description:
	============

	You are given an integer array height of length n. There are n vertical
	lines drawn such that the two endpoints of the i-th line are (i, 0) and
	(i, height[i]).

	Find two lines that together with the x-axis form a container, such that
	the container contains the most water.

	Return the maximum amount of water a container can store.
	
	=====
	Node: Notice that you may not slant the container.
	=====
	
	===========================================
	FUNCTION: int maxArea(vector<int>& height);
	===========================================
	
	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================
	
	--- Example 1 ---
	Input: height = [1, 8, 6, 2, 5, 4, 8, 3, 7]
	Output: 49
	Explanation: The above vertical lines are represented by array:
	[1, 8, 6, 2, 4, 3, 8, 3, 7]
	
	--- Example 2 ---
	Input: height = [1, 1]
	Output: 1
	
	*** Constraints ***
	n == height.length
	2 <= n <= 10^5
	0 <= height[i] <= 10^4
*/

using namespace std;

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
	int maxArea(vector<int>&height)
	{
		int max_area = 0;
		int left = 0;
		int right = height.size() - 1;

		while (left < right)
		{
			int width = right - left;
			int shorter = std::min(height[left], height[right]);

			max_area = std::max(max_area, shorter * width);

			if (height[left] <= height[right])
				left++;
			else
				right--;
		}

		return max_area;
	}
};


int
main()
{
	Solution sol;
	/* Example 1 */
	vector<int> height = {1, 8, 6, 2, 4, 3, 8, 3, 7};

	/* Example 2 */
	// vector<int> height = {1, 1};

	/* Example 3 */
	// vector<int> height = {3, 2, 1, 2, 8, 3, 9, 3, 5};

	/* Example 4 */
	// vector<int> height = {3, 2, 1, 2, 8, 3, 9, 1, 1};

	/* Example 5 */
	// vector<int> height = {1, 1, 1, 1, 1, 9, 2, 1, 9};

	/* Example 6 */
	// vector<int> height = {1, 2};


	std::cout << "\n\t================";
	std::cout << "\n\t=== MAX AREA ===";
	std::cout << "\n\t================\n";

	bool first = true;
	std::cout << "\n\tHeights: [";
	for (const auto& x: height)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n\n";

	int max_area = sol.maxArea(height);
	std::cout << "\n\tMax area is: " << max_area << "\n\n";

	return 0;
}
