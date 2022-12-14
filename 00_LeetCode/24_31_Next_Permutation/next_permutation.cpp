#include <iostream>
#include <vector>


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

	First we observe that if array is in descending order:
	5 4 3 2 1

	there is no next permutation. That has also been said in the Description
	of a problem. In that case we should return the array in ascending order.
	That is we should completely reverse the current array.

	If the array is not in a descending order, in that case, all we have to do
	is we have to do is to find the first element that is greater than its
	very left element.

	nums[i + 1] > nums[i]

	once we find that, then swap element nums[i] with nums[nums.legnth - 1]

	and then reverse element starting from nums[i + 1](including itself)
	onwards.

	1 4 3 5 2
	    i
	
1)	1 4 2 5 3 // Swapped nums[i] and nums[nums.length - 1]
2)  1 4 2 3 5 // Reversed elements from i + 1 to nums.length - 1, inclusive
	
*/


class Solution{
public:
	void nextPermutation(std::vector<int>& nums)
	{
		int i = nums.size() - 2;

		while (i >= 0 && nums[i + 1] <= nums[i])
			i--;

		if (i >= 0)
		{
			int j = nums.size() - 1;

			while (nums[j] <= nums[i])
				j--;

			swap(nums, i, j);
		}

		reverse(nums, i + 1);
	}

	void reverse(std::vector<int>& nums, int begin)
	{
		int i = begin;
		int j = nums.size() - 1;
		while (i < j)
		{
			swap(nums, i, j);

			i++;
			j--;
		}
	}

	void swap(std::vector<int>& nums, int begin, int end)
	{
		int tmp = nums[begin];
		nums[begin] = nums[end];
		nums[end] = tmp;
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
	std::vector<int> nums = {1, 4, 3, 5, 2};

	/* Example 2 */
	// std::vector<int> nums = {1, 4, 5, 3, 2};

	/* Example 3 */
	// std::vector<int> nums = {1, 5, 4, 3, 2};

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
	std::cout << "\n\t========================\n\n";


	std::cout << "\n\tOriginal vector:  [";
	print_vector(nums);

	sol.nextPermutation(nums);

	std::cout << "\n\tNext Permutation: [";
	print_vector(nums);

	return 0;
}
