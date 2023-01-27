#include <iostream>
#include <vector>

/*
	============
	=== EASY ===
	============

	===========================
	169) Majority Element
	===========================

	============
	Description:
	============

	Given an array "nums" of size "n", return the majority element.

	The majority element is the element that appears more than [n / 2] times.
	You may assume that the majority element always exists in the array.

	=================================================
	FUNCTION: int majorityElement(vector<int>& nums);
	=================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  nums = [3, 2, 3]
	Output: 3

	--- Example 2 ---
	Input:  nums = [2, 2, 1, 1, 1, 2, 2]
	Output: 2

	*** Constraints ***
	n == nums.length
	1 <= n <= 5 * 10^4
	-10^9 <= nums[i] <= 10^9

	Follow-up: Could you solve the problem in linear time and in O(1) space?

*/


/*
	------------
	--- IDEA ---
	------------

	Approach: Bit Manipulation

	Intuition

	If an element "majority_element" occurs more than std::floor(n/2) times,
	then there are at least std::floor(n/2) elements of identical values with
	"num" at each bit. That is, we can reconstruct the exact value of "num" by
	combining the most frequent value (0 or 1) at each bit.


	Algorithm

	Starting from the least significant bit, we enumerate each bit to determine
	which value is the majority at this bit, 0 or 1, and put this value to the
	corresponding bit of the result. Finally, we end up with the most least
	significant bit of all elements and reutnr the result.


	Implementation

	Because all numbers are in the range [-10^9, 10^9], which can be
	represented in 32-bit, we only need to enumerate 32 bits.

*/


/*
	Time  Complexity: O(n * logC)
	C is the max absolute value in "nums", i.e., 10^5 in this problem. We
	enumerate all logC bits for each number in "nums".
*/
/* Space Complexity: O(1) */
class Solution{
public:
	int majorityElement(std::vector<int>& nums)
	{
		int n = nums.size();
		int majority_element = 0;

		for (int i = 0; i < 32; i++)
		{
			int bit = 1 << i;

			// Count how many numbers have this bit set
			int bit_count = 0;
			for (int num : nums)
			{
				if ((num & bit) != 0)
					bit_count++;
			}

			// If this bit is present in more than n / 2 elements
			// then it must be set in the majority element
			if (bit_count > n / 2)
				majority_element |= bit;
		}

		return majority_element;
	}
};


int
main()
{
	Solution sol;

	/* Example 1 */
	std::vector<int> nums = {3, 2, 3};

	/* Example 2 */
	// std::vector<int> nums = {2, 2, 1, 1, 1, 2, 2};

	/* Example 3 */
	// std::vector<int> nums = {7, 7, 5, 7, 5, 1, 5, 7, 5, 5, 7, 7, 7, 7, 7, 7};

	std::cout << "\n\t========================";
	std::cout << "\n\t=== MAJORITY ELEMENT ===";
	std::cout << "\n\t========================\n";


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
	int majority_element = sol.majorityElement(nums);

	std::cout << "\n\tMajority Element: " << majority_element << "\n\n";

	return 0;
}
