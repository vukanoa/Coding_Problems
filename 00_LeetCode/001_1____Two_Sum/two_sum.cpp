#include <iostream>
#include <vector>
#include <map>


/*
	============
	=== EASY ===
	============

	===========================
	1) Two Sum
	===========================

	============
	Description:
	============

	Given an array of integers nums and an integer target, return indices of
	the two numbers such that they add up to target.

	You may assume that each input would have exactly one solution, and you may
	not use the same element twice.

	=====
	Node: You can return the answer in any order.
	=====

	======================================================================
	FUNCTION: std::vector<int> twoSum(std::vector<int>& nums, int target);
	======================================================================


	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input : nums = [2, 7, 11, 15], target = 9
	Output: [0, 1]
	Explanation: Because nums[0] + nums[1] == 9, we return [0, 1]

	--- Example 2 ---
	Input : nums = [3, 2, 4], target = 6
	Output: [1, 2]

	--- Example 3 ---
	Input : nums = [3, 3], target = 6
	Output: [0, 1]

	*** Constraints ***
	2 <= nums.length <= 10^4
	-10^9 <= nums[i] <= 10^9
	-10^9 <= target  <= 10^9
	Only one valid answer exists

*/

/*
	------------
	--- IDEA ---
	------------

	Make a Hash Map:
	KEY     VALUE
	value   index

	At the beginning Insert:
	KEY     VALUE
	nums[0] 0

	Iterate from 1 onwards.

	Subtract nums[i] from target and check if that number exists in the
	Hash Map.

	If it DOES exist, then return the index of that number(taking it from the
	Hash map) and the current index 'i'.

	If not, add it to the Hash Map with its corresponding index and continue
	iterating.
*/

/* Time  Beats: 99.81% */
/* Space Beats: 13.85% */
/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target)
	{
		std::map<int, int> map;
		map.insert({nums[0], 0});

		for (int i = 1; i < nums.size(); i++)
		{
			int difference = target - nums[i];

			if (map.find(difference) != map.end()) // difference is in the map
				return {map[difference], i};
			else
			    map.insert({nums[i], i});
		}

		return {}; // This means - return a default constructed instance
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	std::vector<int> nums = {2, 7, 11, 15};
	int target = 9;

	/* Example 2 */
	// std::vector<int> nums = {3, 2, 4};
	// int target = 6;

	/* Example 3 */
	// std::vector<int> nums = {3, 3};
	// int target = 6;

	std::cout << "\n\t===============";
	std::cout << "\n\t=== TWO SUM ===";
	std::cout << "\n\t===============\n";

	/* Write Input */
	bool first = true;
	std::cout << "\n\tNumbers: [";
	for (auto x: nums)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n";

	/* Solution */
	std::vector<int> solution_vect = sol.twoSum(nums, target);

	/* Write Output */
	first = true;
	std::cout << "\n\tSolution: [";
	for (auto x: solution_vect)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n\n";

	return 0;
}
