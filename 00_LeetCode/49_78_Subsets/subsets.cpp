#include <iostream>
#include <vector>


/*
	==============
	=== MEDIUM ===
	==============

	===========================
	78) Subsets
	===========================

	============
	Description:
	============

	Given an integer array "nums" of unique elements, return all possible
	subsets(the power set).

	The solution set MUST NOT contain duplicate subsets. Return the solution in
	any order.

	=========================================================
	FUNCTION: vector<vector<int>> subsets(vector<int>& nums);
	=========================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  nums = [1, 2, 3]
	Output: [[], [1], [2], [3], [1, 2], [3], [1, 3], [2, 3], [1, 2, 3]]

	--- Example 2 ---
	Input:  nums = [0]
	Output: [[], [0]]

	*** Constraints ***
	1 <= nums.length <= 10
	-10 <= nums[i] <= 10
	All the numbers of "nums" are UNIQUE

*/


/*
	------------
	--- IDEA ---
	------------

	(Beats 100%)

	Let's start from empty subest in output list. At each step one takes new
	integer into consideration and generates new subsets from the existing
	ones.

	nums: 1 2 3

	1. Start from empty subset:
		{}

	2. Take "1" into consideration and add new subsets by updating existing
	   ones:
		{}, {1}

	3. Take 2 into consideration and add new subsets by updating existing ones:
		{}, {1}, {2}, {1, 2}

	4. Take 3 into consideration and add new subsets by updating existing ones:
		{}, {1}, {2}, {1, 2}, {3}, {1, 3}, {2, 3}, {1, 2, 3}

*/


class Solution{
public:
	std::vector<std::vector<int>> subsets(std::vector<int>& nums)
	{
		int n = nums.size();

		std::vector<std::vector<int>> results;
		results.push_back({});

		if (n == 0)
			return results;

		int results_size = 0;

		for (int num : nums)
		{
			results_size = results.size();

			for (int i = 0; i < results_size; i++)
			{
				std::vector<int> tmp;
                for (int j = 0; j < results[i].size(); j++)
				    tmp.push_back(results[i][j]);

				tmp.push_back(num);

				results.push_back(tmp);
			}
		}

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
	// std::vector<int> nums = {0};

	/* Example 3 */
	// std::vector<int> nums = {1, 2};

	/* Example 4 */
	// std::vector<int> nums = {1, 2, 3, 4};


	std::cout << "\n\t===============";
	std::cout << "\n\t=== SUBSETS ===";
	std::cout << "\n\t===============\n";

	/* Write Input */
	bool first = true;
	std::cout << "\n\tNums: [";
	for (auto x: nums)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n";

	/* Solution */
	std::vector<std::vector<int>> results = sol.subsets(nums);

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
