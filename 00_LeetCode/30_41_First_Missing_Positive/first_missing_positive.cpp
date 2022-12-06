#include <iostream>
#include <vector>


/*
	============
	=== HARD ===
	============
	
	===========================
	41) First Missing Positive
	===========================
	
	============
	Description:
	============

	Given an unsorted integer array "nums", return the smallest missing
	positive integer.

	You must implement an algorithm in O(n) time and uses constant extra space.
	
	======================================================
	FUNCTION: int firstMissingPositive(vector<int>& nums);
	======================================================
	
	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================
	
	--- Example 1 ---
	Input:  nums = [1, 2, 0]
	Output: 3
	
	--- Example 2 ---
	Input:  nums = [3, 4, -1, 1]
	Output: 2
	
	--- Example 3 ---
	Input:  nums = [7, 8, 9, 11, 12]
	Output: 1
	
	*** Constraints ***
	1 <= nums.length <= 10^5
	-2^31 <= nums[i] <= 2^31 - 1

*/

/*
	------------
	--- IDEA ---
	------------

	Put each number in its right place.
	
	Example:
	We find number 4 in our array "nums" and we should swap it with nums[3]

	Once we have "sorted" the array, the first place where its number is not
	right, return position + 1;

	Complexity explained:
	Consider nums[i] = i + 1 as a CORRECT_SLOT

		i) CORRECT_SLOT will never be changed; for CORRECT_SLOT,
		nums[nums[i] - 1] always equals to nums[i].

		ii) For each std::swap, the number of CORRECT_SLOT increases by
		at least 1.
		Position: nums[nums[i] - 1] = nums[i] becomes CORRECT_SLOT after
		std::swap, and according to i) this MUST be a new CORRECT_SLOT

		iii) The maximum of CORRECT_SLOT <= n
	
	Therefore, Time complexity is O(n)


	In other words:
	We visit each number once, and each number will be put in its right place
	at most once. So it is O(n) + O(n).
	

	We iterate through an entire array and check if the number is greater
	than 0 and less or equals to n, since we only consider positive integers.
	And if we have all the positive integers from 1 to n in our array, then
	return n + 1.

	If the number is between 1 and n then if that number(nums[i]) is not in
	the right place, that is:
		nums[nums[i] - 1] != nums[i]
	
	then swap it to a place where its supposed to be. Then again, within the
	while loop do this again - Place the current number under nums[i] to its
	right place in the array. That is:
		nums[nums[i] - 1] = nums[i]
	
	If we are doing multiple swaps for a single value of 'i', and we are
	iterating through an entire array, how is is possible that a complexity is
	still O(n);

	We will have multiple swaps for i == 0(in our example), but as we iterate
	we will have less and less swap. Sometimes 1, and most of the times 0.

	In the end the total amount of swaps in an entire for loop is <= N.

	Our example:
	[7, 1, 4, 9, 2, 8, 3, 5]

	1st iteration (i == 0)
		[3, 1, 4, 9, 2, 8, 7, 5]
		[4, 1, 3, 9, 2, 8, 3, 5]
		[9, 1, 3, 4, 2, 8, 7, 5]
	
	2nd iteration (i == 1)
		[1, 9, 3, 4, 2, 8, 7, 5]
	
	3rd iteration (i == 2)
		// Nothing has changed

	4th iteration (i == 3)
		// Nothing has changed

	5th iteration (i == 4)
		[1, 2, 3, 4, 9, 8, 7, 5]

	6th iteration (i == 5)
		[1, 2, 3, 4, 9, 5, 7, 8]
		[1, 2, 3, 4, 5, 9, 7, 8]

	7th iteration (i == 6)
		// Nothing has changed

	8th iteration (i == 7)
		// Nothing has changed


	1st iteration
		3 swaps
	
	2nd iteration
		1 swap
	
	3rd iteration
		0 swaps (nums[2] == 3) // It's a CORRECT_SLOT
	
	4th iteration
		0 swaps (nums[3] == 4) // It's a CORRECT_SLOT

	5th iteration
		2 swaps
	
	6th iteration
		1 swap
		
	7th iteration
		0 swaps (nums[6] == 7) // It's a CORRECT_SLOT
	
	8th iteration
		0 swaps (nums[7] == 8) // It's a CORRECT_SLOT

		
	Total number of swaps = 3 + 1 + 2 + 1 = 7 <= n
	
	Therefore - Time Complexity is O(n)
	
*/

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution{
public:
	int
	firstMissingPositive(std::vector<int>& nums)
	{
		int n = nums.size();

		for (int i = 0; i < n; i++)
		{
			while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i])
				std::swap(nums[i], nums[nums[i] - 1]);
		}

		for (int i = 0; i < n; i++)
		{
			if (nums[i] != i + 1)
				return i + 1;
		}

		return n + 1;
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	// std::vector<int> nums = {1, 2, 0};

	/* Example 2 */
	// std::vector<int> nums = {3, 4, -1, 1};

	/* Example 3 */
	// std::vector<int> nums = {7, 8, 9, 11, 12};

	/* Example 4 */
	std::vector<int> nums = {7, 1, 9, 2, 6, 3, 5};

	std::cout << "\n\t==============================";
	std::cout << "\n\t=== FIRST MISSING POSITIVE ===";
	std::cout << "\n\t==============================\n\n";

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
	int first_positive = sol.firstMissingPositive(nums);

	std::cout << "\n\tOutput: " << first_positive << "\n\n";

	return 0;
}
