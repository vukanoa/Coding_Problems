#include <iostream>
#include <vector>

/*
	============
	=== EASY ===
	============

	===========================
	283) Move Zeroes
	===========================

	============
	Description:
	============

	Given an integer array "nums", move all 0's to the end of it while
	maintaining the relative order of the non-zero elements.

	=====
	Node: that you must do this in-place without making a copy of the array.
	=====

	Follow up: Could you minimize the total number of operations done?

	=============================================
	FUNCTION: void moveZeroes(vector<int>& nums);
	=============================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  nums = [0, 1, 0, 3, 12]
	Output: [1, 3, 12, 0, 0]

	--- Example 2 ---
	Input:  nums = [0]
	Output: [0]

	*** Constraints ***
	1 <= nums.length <= 10^4
	-2^31 <= nums[i] <= 2^31 -1

*/


// Sort of like Bubble sort, but optimized
/* Time  Complexity: O(n^2) */
/* Space Complexity: O(1) */
class Solution_inefficient {
public:
    void moveZeroes(std::vector<int>& nums)
    {
        int n = nums.size();

        for (int i = n - 2; i >= 0; i--)
        {
            if (nums[i] == 0)
            {
                int x = i;
                int prev = x + 1;

                while (prev < n && nums[prev] != 0)
                {
                    std::swap(nums[x], nums[prev]);
                    x++;
                    prev = x + 1;
                }
            }
        }
    }
};


int
main()
{
	Solution_inefficient sol_ineff;

	/* Example 1 */
	// std::vector<int> nums = {0, 1, 0, 3, 12};

	/* Example 2 */
	// std::vector<int> nums = {0};

	/* Example 3 */
	// std::vector<int> nums = {0, 1};

	/* Example 4 */
	std::vector<int> nums = {13, 0, 0, 5, 1, 0, 3, 12, 0, 7, 0};


	std::cout << "\n\t===================";
	std::cout << "\n\t=== MOVE ZEROES ===";
	std::cout << "\n\t===================\n\n";


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
	std::cout << "]\n\n";

	/* Solution */
	sol_ineff.moveZeroes(nums);

	std::cout << "\t\t*** MOVE ZEROES ***\n";

	/* Write Output */
	first = true;
	std::cout << "\n\tNums: [";
	for (auto x: nums)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n\n";

	return 0;
}
