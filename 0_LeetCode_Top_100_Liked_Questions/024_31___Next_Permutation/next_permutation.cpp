#include <iostream>
#include <vector>
#include <algorithm>


/*
	==============
	=== MEDIUM ===
	==============
	
	===========================
	31) Next Permutation
	===========================
	
	============
	Description:
	============

	A permutation of an array of integers is an arrangement of its members into
	a sequence or linear order.

	- For example: for arr = [1, 2, 3], the following are all the permutations
	of arr:
	[1, 2, 3]
	[1, 3, 2]
	[2, 1, 3]
	[2, 3, 1]
	[3, 1, 2]
	[3, 2, 1]

	The next permutation of an array of integers is the next lexicographically
	greater permutation of its integer. More formally, if all the permutations
	of the array are sorted in one container according to their lexicographical
	order, then hte next permutation of that array is the permutation that
	follows it in the sorted container. If such arrangement is not possible,
	the array must be rearranged as the lowest possible order (i.e. sorted
	in ascending order).

	- For example, the next permutation of arr = [1, 2, 3] is [1, 3, 2]
	- Similarly, the next permutation of arr = [2, 3, 1] is [3, 1, 2]
	- While the next permutation of arr = [3, 2, 1] is [1, 2, 3] because
	  [3, 2, 1] does not have a lexicographical larger rearrangement.

	Given an array of integers nums, find the next permutation of nums.

	The replacement must be in place and use only constant extra memory.
	
	=================================================
	FUNCTION: void nextPermutation(vector<int)& nums;
	=================================================
	
	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================
	
	--- Example 1 ---
	Input: nums = [1, 2, 3]
	Output: [1, 3, 2]
	
	--- Example 2 ---
	Input:  nums = [3, 2, 1]
	Output: [1, 2, 3]
	
	--- Example 3 ---
	Input:  nums = [1, 1, 5]
	Output: [1, 5, 1]
	
	*** Constraints ***
	1 <= nums.length <= 100
	0 <= nums[i] <= 100

*/


/*
	------------
	--- IDEA ---
	------------

	~~~ Base case ~~~
	First we observe that if array is in descending order:
	5 4 3 2 1

	There is no next permutation. That has also been said in the Description
	of a problem. In that case we should return the array in ascending order.
	That is we should completely reverse the current array.

	Note: We're not covering the base case separately. It's only that after the
	first while loop, 'i' is less than 0 and thus the whole vector will be
	reversed.


	~~~ Algorithm ~~~
	It's actually not intuitive to find the pattern, but there is one.

	Start 'i' from the second element from the back, so that it has only 1
	element to the right.

		while (i >= 0 && nums[i] >= nums[i + 1])
			i--

	Once we're on index 'i' where nums[i] < nums[i + 1] then assign 'j' to
	point to the very last element and then:

		while (nums[i] >= nums[j])
			j--

		swap(nums, i, j)

		// Inclusive [nums[i+1], nums[nums.size()-1]]
		reverse(nums, i + 1, n - 1)

	Here, try it out:

	// First 25 permutations of [1, 2, 3, 4, 5]
	1 2 3 4 5
	1 2 3 5 4
	1 2 4 3 5
	1 2 4 5 3
	1 2 5 3 4
	1 2 5 4 3
	1 3 2 4 5
	1 3 2 5 4
	1 3 4 2 5
	1 3 4 5 2
	1 3 5 2 4
	1 3 5 4 2
	1 4 2 3 5
	1 4 2 5 3
	1 4 3 2 5
	1 4 3 5 2
	1 4 5 2 3
	1 4 5 3 2
	1 5 2 3 4
	1 5 2 4 3
	1 5 3 2 4
	1 5 3 4 2
	1 5 4 2 3
	1 5 4 3 2
	2 1 3 4 5
	...
	
*/



/* Time  Beats: 100% */
/* Space Beats: 42.13% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution{
public:
	void nextPermutation(std::vector<int>& nums)
	{
		int i = nums.size() - 2;

		while (i >= 0 && nums[i] >= nums[i + 1])
			i--;

		if (i >= 0)
		{
			int j = nums.size() - 1;

			while (nums[i] >= nums[j])
				j--;

			std::swap(nums[i], nums[j]);
		}

		// Ranges are both inclusive. reverse [i+1, nums.size()-1]
        std::reverse(nums.begin() + i + 1, nums.end());
	}
};


void
print_vector(std::vector<int>& vec)
{
	bool first = true;
	for (const auto& x: vec)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n\n";
}


int
main()
{
	Solution sol;

	/* Example 1 */
	// std::vector<int> nums = {1, 4, 3, 5, 2};

	/* Example 2 */
	// std::vector<int> nums = {1, 4, 5, 3, 2};

	/* Example 3 */
	std::vector<int> nums = {1, 5, 4, 3, 2};

	/* Example 4 */
	// std::vector<int> nums = {2, 5, 4, 3, 1};

	/* Example 5 */
	// std::vector<int> nums = {5, 2, 3, 4, 1};

	/* Example 6 */
	// std::vector<int> nums = {5, 4, 1, 2, 3};

	/* Example 7 */
	// std::vector<int> nums = {1, 2, 3};

	/* Example 8 */
	// std::vector<int> nums = {3, 2, 1};

	/* Example 9 */
	// std::vector<int> nums = {2, 3, 1};

	std::cout << "\n\t========================";
	std::cout << "\n\t=== NEXT PERMUTATION ===";
	std::cout << "\n\t========================\n";


	/* Write Input */
	std::cout << "\n\tOriginal vector:  [";
	print_vector(nums);


	/* Solution */
	sol.nextPermutation(nums);


	/* Write Output */
	std::cout << "\tNext Permutation: [";
	print_vector(nums);

	return 0;
}
