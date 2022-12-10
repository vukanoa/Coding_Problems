#include <iostream>
#include <vector>
#include <algorithm>


/*
	==============
	=== MEDIUM ===
	==============

	===========================
	46) Permutations
	===========================

	============
	Description:
	============

	Given an array "nums" of distinct integers, return all the possible
	permutations.

	=====
	Node: You can return the answer in any order.
	=====

	========================================================================
	FUNCTION: std::vector<std::vector<int>> permute(std::vector<int>& nums);
	========================================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  nums = [1, 2, 3]
	Output: [[1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 2, 1]]

	--- Example 2 ---
	Input:  nums = [0, 1]
	Output: [[0, 1], [1, 0]]

	--- Example 3 ---
	Input:  nums = [1]
	Ouput:  [[1]]

	*** Constraints ***
	1 <= nums.length <= 6
	-10 <= nums[i] <= 10
	All the integers of "nums" are unique

*/


/*
	------------
	--- IDEA ---
	------------

	- First we sort our initial "nums" array since that won't
	  change the runtime complexity and we need our array values in
	  sorted order

	- We begin from permutation:
	  A = {A[0] A[1] ... A[n - 1]}

	- Find biggest "left" (0 <= left < n - 1)
	  so that A[left] < A[left + 1]

	- Find biggest "right" (right > left && right <= n - 1)
	  so that A[right] > A[left]

	- Swap A[right] and A[left]

	- Reverse the order of elements
	  A[left + 1] A[left + 2] ... A[n - 1]

	left  = ^
	right = #

	1 2 3 4 5 --> 1 2 3 5 | 4 --> 1 2 3 5 4
	      ^ #

	1 2 3 5 4 --> 1 2 4 | 5 3 --> 1 2 4 3 5
	    ^   #

	1 2 4 3 5 --> 1 2 4 5 | 3 --> 1 2 4 5 3
	      ^ #

	1 2 4 5 3 --> 1 2 5 | 4 3 --> 1 2 5 3 4
	    ^ #

	1 2 5 3 4 --> 1 2 5 4 | 3 --> 1 2 5 4 3
	      ^ #

	1 2 5 4 3 --> 1 3 | 5 4 2 --> 1 3 2 4 5
	  ^     #

	1 3 2 4 5 --> 1 3 2 5 | 4 --> 1 3 2 5 4
	      ^ #
*/



/* Time  Complexity: O(n!) */
/* Space Complexity: O(1) */
class Solution{
public:
	int next_permutation(std::vector<int>& nums)
	{
		int n = nums.size();

		int* first = &nums[0];
		int* last  = &nums[n - 1];

		int* left  = last - 1;
		int* right = last;

		// Find the largest "left" so that nums[left] < nums[left + 1]
		while (left > first)
		{
			if (*(left) < *(left + 1))
				break;

			left--;
		}

		/*
		   If no nums[left] < nums[left + 1], "nums" is the last permutation
		   in lexicographic order
		 */
		if (*(left) > *(left + 1))
			return 0;

		// Find largest "right" so that nums[left] < nums[right]
		while (right > left)
		{
			if (*(right) > *(left))
				break;

			right--;
		}

		// Swap nums[right] and nums[left]
		int tmp = *left;
		*left = *right;
		*right = tmp;

		// Reverse the remaining nums[left + 1] ... nums[n - 1]
		first = left + 1;

		while (first < last)
		{
			tmp = *first;
			*first = *last;
			*last = tmp;

			first++;
			last--;
		}

		return 1;
	}

	std::vector<std::vector<int>> permute(std::vector<int>& nums)
	{
		std::vector<std::vector<int>> results;
		if (nums.size() == 1)
		{
			results.push_back(nums);

			return results;
		}

		std::sort(nums.begin(), nums.end());
		do
		{
			std::vector<int> vec_tmp;
			for (int i = 0; i < nums.size(); i++)
				vec_tmp.push_back(nums[i]);

			results.push_back(vec_tmp);
		} while (next_permutation(nums));

		return results;
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	std::vector<int> nums = {1, 2, 3};

	/* Example 2 */
	// std::vector<int> nums = {0, 1};

	/* Example 3 */
	// std::vector<int> nums = {1};

	/* Example 4 */
	// std::vector<int> nums = {0, 7, -2, -5};

	std::cout << "\n\t====================";
	std::cout << "\n\t=== PERMUTATIONS ===";
	std::cout << "\n\t====================\n";

	/* Write Input */
	bool first = true;
	std::cout << "\n\tArray: [";
	for (auto x: nums)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n";


	/* Solution */
	std::vector<std::vector<int>> results = sol.permute(nums);


	/* Write Output */
	first = true;
	std::cout << "\n\tResults: [";
	for (auto x: results)
	{
		if (!first)
			std::cout << ", ";

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


	return 0;
}
