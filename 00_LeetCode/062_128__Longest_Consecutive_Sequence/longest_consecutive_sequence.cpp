#include <iostream>
#include <vector>
#include <unordered_set>

/*
	==============
	=== MEDIUM === (Previously was under HARD)
	==============

	=================================
	128) Longest Consecutive Sequence
	=================================

	============
	Description:
	============

	Given an unsorted array of integers "nums", return the length of the
	longest consecutive elements sequence.

	=====
	Node: You must write an algorithm that runs in O(n) time.
	=====

	=========================================================
	FUNCTION: int longestConsecutive(std::vector<int>& nums);
	=========================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  nums = [100, 4, 200, 1, 3, 2]
	Output: 4

	--- Example 2 ---
	Input:  nums = [0, 3, 7, 2, 5, 8, 4, 6, 0, 1]
	Output: 9

	*** Constraints ***
	0 <= nums.length <= 10^5
	-10^9 <= nums[i] <= 10^9

*/


/*
	------------
	--- IDEA ---
	------------

	Let's start with a brute force solution:

	class Solution{
	private:
		// O(n)
		bool number_exists(std::vector<int>& nums, int num)
		{
			for (int i = 0; i < nums.size(); i++)
			{
				if (nums[i] == num)
					return true;
			}

			return false;
		}

	public:
		int longestConsecutive(std::vector<int>& nums)
		{
			int max = 0;

			// O(n)
			for (int i = 0; i < nums.size(); i++)
			{
				int current_num = nums[i];
				int current_sequence_length = 1;

				// O(n) * (number_exists -> O(n)) => O(n^2)
				while (number_exists(nums, current_num + 1))
				{
					current_num++;
					current_sequence_length++;
				}

				max = std::max(max, current_sequence_length);
			}

			return max;
		}
	};


	We can immediately see that if we use a Set instead of iterating through
	the entire array each time in function "number_exists" we can reduce the
	time complexity from O(n^3) to O(n^2).

	Here is a O(n^2) Solution:
	// O(n^2)

	class Solution{
	public:
		int longestConsecutive(std::vector<int>& nums)
		{
			std::unordered_set<int> uset;

			for (int num: nums)
				uset.insert(num);

			int max = 0;

			// O(n)
			for (int i = 0; i < nums.size(); i++)
			{
				int current_num = nums[i];
				int current_sequence_length = 1;

				// O(n)
				// uset.find -> O(1)
				while (uset.find(current_num + 1) != uset.end())
				{
					current_num++;
					current_sequence_length++;
				}

				max = std::max(max, current_sequence_length);
			}

			return max;
		}
	};

	Let's consider the first Example:
	Input:  nums = [100, 4, 200, 1, 3, 2]

	We can immediately see that we don't have to start "counting" the length
	of the longest sequence if we are at elements: 4, 3 or 2 since they do not
	represent the start of the longest sequence.

	Thus, we can see that we only have to "track" the longest sequence if the
	element indeed represents the start of a sequence.

	So how can we know if an element is a starting element if, in this example,
	we see '1' AFTER we see 4, and we have to do it in O(n)?

	The answer is - Starting element is the smallest in the sequence.
	Starting element minus 1 does NOT exist in the array, or rather, in Set.

	When we get to element '4' we can try to find a '3' if it does exist then
	that indicates that '4' is NOT a starting element, thus we can just move
	forward.

	99  does NOT    exist so 100 is INDEED a starting element
	3   does INDEED exist so 4   is NOT    a starting element
	199 does NOT    exist so 200 is INDEED a starting element
	0   does NOT    exist so 1   is INDEED a starting element
	2   does INDEED exist so 3   is NOT    a starting element
	1   does INDEED exist so 2   is NOT    a starting element

	We only loop the while loop for starting elements, which in this example,
	are:
		100, 200 and 1.

	Thus we keep Time Complexity to O(n).


	1 2 3 4       100     200

	You can clearly observe that to know that a single element is a starting
	one, it must NOT have a left neighbor.

	  1 doesn't have left neighbor, i.e. 0
	100 doesn't have left neighbor i.e. 99
	200 doesn't have left neighbor i.e. 199

	So each element will be processed twice. Once when creating a set at the
	beginning. And once when iterating through sequence from each starting
	element, thus this makes it O(n).

*/

/* Time  Beats: 32.64% */
/* Space Beats: 57.57% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution{
public:
	int longestConsecutive(std::vector<int>& nums)
	{
		std::unordered_set<int> uset;

		for (int num: nums)
			uset.insert(num);

		int max = 0;

		// O(n)
		for (int i = 0; i < nums.size(); i++)
		{
			int current_num = nums[i];
			int current_sequence_length = 1;

			if (uset.find(current_num - 1) == uset.end())
			{
				while (uset.find(current_num + 1) != uset.end())
				{
					current_num++;
					current_sequence_length++;
				}
			}

			max = std::max(max, current_sequence_length);
		}

		return max;
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	std::vector<int> nums = {100, 4, 200, 1, 3, 2};

	/* Example 2 */
	// std::vector<int> nums = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};

	/* Example 3 */
	// std::vector<int> nums = {8, 304, 7, 3, 4, 305, 303, 6, 308, 307, 306};

	/* Example 4 */
	// std::vector<int> nums = {};

	/* Example 5 */
	// std::vector<int> nums = {3};

	std::cout << "\n\t====================================";
	std::cout << "\n\t=== LONGEST CONSECUTIVE SEQUENCE ===";
	std::cout << "\n\t====================================\n";


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
	int max = sol.longestConsecutive(nums);


	/* Write Output */
	std::cout << "\n\tLongest Consecutive Sequence: " << max << "\n\n";


	return 0;
}
