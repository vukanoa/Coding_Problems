#include <iostream>
#include <vector>

/*
	============
	=== EASY ===
	============

	===========================
	163) Missing Ranges
	===========================

	============
	Description:
	============

	You are given an inclusive range [lower, upper] and a sorted unique
	integer array nums, where all elements are in the inclusive range.

	A number x is considered missing if x is in the range [lower, upper]
	and x is not in nums.

	Return the smallest sorted list of ranges that cover every missing
	number exactly. That is, no element of nums is in any of the ranges
	and each missing number is in one of the ranges.

	Each range [a, b] in the list should be output as:
		- "a->b" if a != b
		- "a" if a == b

	====================================================================================
	FUNCTION: vector<string> findMissingRanges(vector<int>& nums, int lower, int upper);
	====================================================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: nums = [0, 1, 3, 50, 75], lower = 0, upper = 90
	Output: ["2", "4->49", "51->74", "76->99"]

	--- Example 2 ---
	Input:  nums = [], lower = 1, upper = 1
	Output: ["1"]

	--- Example 3 ---
	Input:  nums = [], lower = -3, upper = -1
	Output: ["-3->-1"]

	*** Constraints ***
	Don't know

*/


/*
	------------
	--- IDEA ---
	------------

	It's self-explanatory.

	Check "lower" with the first element.
	Check middle elements with their previous elements.
	Check "upper" with the last element.
	
*/

/* Time  Complexity: O(n) */
/*
	Space Complexity: O(1)
	If the result we're returning is not counter since that is necessary, then
	it is O(1).
*/
class Solution{
public:
	std::vector<std::string> findMissingRanges(std::vector<int>& nums, int lower, int upper)
	{
		if (nums.empty())
			return {range(lower, upper)};

		int n = nums.size();
		std::vector<std::string> results;

		// First
		if (nums.front() > lower)
			results.push_back(range(lower, nums.front() - 1));

		// Middle
		for (int i = 1; i < n; i++)
		{
			if (nums[i] > nums[i - 1] + 1)
				results.push_back(range(nums[i - 1] + 1, nums[i] - 1));
		}

		// Last
		if (nums.back() < upper)
			results.push_back(range(nums.back() + 1, upper));


		return results;
	}

private:
	std::string range(int low, int high)
	{
		if (low == high)
			return std::to_string(low);

		return std::to_string(low) + "->" + std::to_string(high);
	}
};


int
main()
{
	Solution      sol;


	/* Example 1 */
	std::vector<int> nums = {0, 1, 3, 50, 75};
	int lower = 0;
	int upper = 90;

	/* Example 2 */
	// std::vector<int> nums = {};
	// int lower = 1;
	// int upper = 1;

	/* Example 3 */
	// std::vector<int> nums = {};
	// int lower = -3;
	// int upper = -1;


	std::cout << "\n\t======================";
	std::cout << "\n\t=== MISSING RANGES ===";
	std::cout << "\n\t======================\n";


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
	std::cout << "]";
	std::cout << "\n\tLower: " << lower;
	std::cout << "\n\tUpper: " << upper << "\n";


	/* Solution */
	std::vector<std::string> results = sol.findMissingRanges(nums, lower, upper);


	/* Write Output */
	first = true;
	std::cout << "\n\tResults: [";
	for (auto x: results)
	{
		if (!first)
			std::cout << ", ";

		std::cout << "\"" << x << "\"";
		first = false;
	}
	std::cout << "]\n\n";


	return 0;
}

