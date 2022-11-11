#include <iostream>
#include <vector>
#include <map>

/*
	============
	=== EASY ===
	============

	==========
	1) Two Sum
	==========

	Given an array of integers nums and an integer target, return indices of
	the two numbers such that they add up to target.

	You may assume that each input would have exactly one solution, and you may
	not use the same element twice.

	You can return the answer in any order.
	
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

	*** Constraint ***
	2 <= nums.length <= 10^4
	-10^9 <= nums[i] <= 10^9
	-10^9 <= target  <= 10^9
	Only one valid answer exists
*/


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
	/* Example 1 */
	std::vector<int> nums = {2, 7, 11, 15};
	int target = 9;

	/* Example 2 */
	// std::vector<int> nums = {3, 2, 4};
	// int target = 6;

	/* Example 3 */
	// std::vector<int> nums = {3, 3};
	// int target = 6;

	Solution sol;
	std::vector<int> solution_vect = sol.twoSum(nums, target);

	bool first = true;
	std::cout << "\n\tSolution is: [";
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
