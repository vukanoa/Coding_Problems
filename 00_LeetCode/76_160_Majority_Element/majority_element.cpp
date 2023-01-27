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
class Solution_Bit_Manipulation{
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


/*
	------------
	--- IDEA ---
	------------

	************************************
	*** Boyer-Moore Voting Algorithm ***
	************************************

	Intuition
	If we had some way of counting instances of the majority element as +1 and
	instances of any other as -1, summing them would make it obvious that the
	majority element is indeed the majority lement.

	Algorithm
	Essentially, what Boyer-Moore does is look for a suffix "suf" of "nums"
	where suf[0] is the majority element in that suffix. To do this, we
	maintain a count, which is incremented whenever we see an instance of our
	current candidate for majority element and decremented whenever we see
	anything else. Whenever "count" equals 0, we effectively forget about
	everything in "nums" up to the current index and consider the current
	number as the candidate for majority element. It is not immediately
	obvious why we can get away with forgetting prefixes of "nums" - consider
	the following examples (pipes are inserted to separate runs of nonzero
	"count").

	[7, 7, 5, 7, 5, 1 | 5, 7, | 5, 5, 7, 7 | 7, 7, 7, 7]

	Here, the 7 at index 0 is selected to be the first candidate for majority
	element. "count" will eventually reach 0 after index 5 is processed, so the
	5 at index 6 will be the next candidate. In this case, 7 is the true
	majority element, so by disregarding this prefix, we are ignoring an equal
	number of majority and minority elements - therefore, 7 will still be the
	majority element in the suffix formed by throwing away the first prefix.

	[7, 7, 5, 7, 5, 1 | 5, 7 | 5, 5, 7, 7 | 5, 5, 5, 5]

	Now, the majority element is 5 (we changed the last run of the array from
	7s to 5s), but our first candidate is still 7. In this case, our candidate
	is not the true majority element, but we still cannot discard more majority
	elements than minority elements (this would imply that "count" could reach
	-1 before we reassign "candidate", which is obivously false).

	Therefore, given that it is impossible (in both cases) to discard more
	majority elements than minority elements, we are safe in discarding the
	prefix and attempting to recursively solve the majority element problem for
	the suffix. Eventually, a suffix will be found for which "count" does not
	hit 0, and the majority element of that suffix will necessarily be the same
	as the majority element of the overall array.

*/


/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution{
public:
	int majorityElement(std::vector<int>& nums)
	{
		int count = 0;
		int candidate = 0;

		for (int i = 0; i < nums.size(); i++)
		{
			if (count == 0)
				candidate = nums[i];

			count += (nums[i] == candidate) ? 1 : -1;
		}

		return candidate;
	}
};


int
main()
{
	Solution_Bit_Manipulation sol_bin_manipulation;
	Solution sol;

	/* Example 1 */
	// std::vector<int> nums = {3, 2, 3};

	/* Example 2 */
	// std::vector<int> nums = {2, 2, 1, 1, 1, 2, 2};

	/* Example 3 */
	// std::vector<int> nums = {7, 7, 5, 7, 5, 1, 5, 7, 5, 5, 7, 7, 7, 7, 7, 7};

	/* Example 4 */
	std::vector<int> nums = {7, 7, 5, 7, 5, 1, 5, 7, 5, 5, 7, 7, 5, 5, 5, 5};

	std::cout << "\n\t========================";
	std::cout << "\n\t=== MAJORITY ELEMENT ===";
	std::cout << "\n\t========================\n";


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
	// int majority_element = sol_bit_manipulation.majorityElement(nums);
	int majority_element = sol.majorityElement(nums);

	/* Write Output */
	std::cout << "\n\tMajority Element: " << majority_element << "\n\n";

	return 0;
}
