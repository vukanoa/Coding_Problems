#include <iostream>
#include <vector>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	75) Sort Colors
	===========================

	============
	Description:
	============

	Given an array "nums" with 'n' objects colored red, white or blue, sort
	them in-place so that objects of the same color are adjacent, with the
	colors in the order red, white and blue.

	We will use the integers 0, 1 and 2 to represent the color red, white and
	blue, respectively.

	You must solve this problem without using the library's sort function.

	=============================================
	FUNCTION: void sortColors(vector<int>& nums);
	=============================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  nums = [2, 0, 2, 1, 1, 0]
	Output: nums = [0, 0, 1, 1, 2, 2]

	--- Example 2 ---
	Input:  nums = [2, 0, 1]
	Output: [0, 1, 2]

	--- Example 3 ---
	Input:  nums = [2, 0, 1, 2, 0, 2, 2, 1, 2, 1, 1, 2, 0]
	Output: [0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2]

	*** Constraints ***
	n == nums.length
	1 <= n <= 300
	nums[i] is either 0, 1 or 2.

*/

/*
	Beats 100%

	Legend:
		^ -> i
		# -> j
		@ -> one

	[2, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 0]
	 ^                                      #

	[0, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 2]
	 ^                                   #

	[0, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 2]
	 ^                                   #

	[0, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 2]
	    ^                                #

	[0, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 2]
	       ^                             #

	[0, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 2]
	       ^                             #

	[0, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 2]
	       ^                          #

	[0, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 2] one = 11
	       ^                          #
		                              @

	[0, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 2]
	       ^                       #  @

	[0, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 2]
	       ^                    #     @

	[0, 0, 2, 2, 0, 2, 2, 1, 0, 1, 1, 1, 2, 2]
	       ^                 #        @

	[0, 0, 1, 2, 0, 2, 2, 1, 0, 1, 1, 2, 2, 2]
	       ^                 #     @

	[0, 0, 0, 2, 0, 2, 2, 1, 1, 1, 1, 2, 2, 2]
	       ^              #        @

	[0, 0, 0, 2, 0, 2, 2, 1, 1, 1, 1, 2, 2, 2]
	          ^           #        @

	[0, 0, 0, 1, 0, 2, 2, 1, 1, 1, 2, 2, 2, 2]
	          ^           #     @

	[0, 0, 0, 1, 0, 2, 2, 1, 1, 1, 2, 2, 2, 2]
	          ^        #        @

	[0, 0, 0, 2, 0, 2, 1, 1, 1, 1, 2, 2, 2, 2]
	          ^     #           @

	[0, 0, 0, 1, 0, 2, 1, 1, 1, 2, 2, 2, 2, 2]
	          ^     #        @

	[0, 0, 0, 2, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2]
	          ^  #           @

	[0, 0, 0, 1, 0, 1, 1, 1, 2, 2, 2, 2, 2, 2]
	          ^  #        @

	[0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2]
	          ^           @
              #

	[0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2]
	          #  ^        @
*/



/*
	------------
	--- IDEA ---
	------------

	The above example should illustrate how the algorithm works.

	We have two pointers(three to be exact):
		'i' and 'j'. (and "one")

	Whenever 'i' == 0, just increment 'i' since that is the position '0'(color
	red) should be at.

	At the beginning, pointer "one" is -1("unititialized" yet).
	Why?

	The idea is that we need to find the very first value 1 from the right
	border. Once we find it, we will use that position to swap with a value 2
    at position 'i'.

	There is one special case:
		'i' == 1 and 'j' == 1

	What do we do then?
	Just decrement 'j'
	& if "one" if it's still -1(Initialize it with
	a position of our first value of 1(color white) from the right border)

	If 'i' == 2 and 'j' == 2
		decrement j

	if 'i' == 2 and we have found a value of(color white) from the right then
	swap value of 2 with the most right value of 1(color white) and decrement
	the position of "one" to point at the current right most value of 1.

*/


class Solution{
public:
	void sortColors(std::vector<int>& nums)
	{
		int n = nums.size();

		if (n == 1)
			return;

		int one = -1; // Not found yet
		int i = 0;
		int j = n - 1;

		while (i <= j)
		{
			if (nums[i] == 2)
			{
				if (one > 0)
				{
					std::swap(nums[i], nums[one]);
					one--;
				}
				else
				{
					if (nums[j] < 2)
						std::swap(nums[i], nums[j]);

					if (nums[j] == 1)
						one = j;

					j--;
				}
			}
			else if (nums[i] == 1)
			{
				if (nums[j] == 0 || (nums[j] == 2 && one > 0))
					std::swap(nums[i], nums[j]);

				if (nums[j] == 1 && one < 0)
					one = j;

				j--;
			}
			else
				i++;
		}
	}
};


void
print_array(std::vector<int>& nums, std::string str)
{
	bool first = true;
	std::cout << "\n\t" << str << ": [";
	for (auto x: nums)
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

	std::cout << "\n\t===================";
	std::cout << "\n\t=== SORT COLORS ===";
	std::cout << "\n\t===================\n\n";

	/* Example 1 */
	// std::vector<int> nums = {2, 0, 2, 1, 1, 0};

	/* Example 2 */
	// std::vector<int> nums = {2, 0, 1};

	/* Example 3 */
	// std::vector<int> nums = {2, 0, 1, 2, 0, 2, 2, 1, 2, 1, 1, 2, 0};

	/* Example 4 */
	// std::vector<int> nums = {1, 2, 0};

	/* Example 5 */
	std::vector<int> nums = {2, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 0};

	print_array(nums, "Array");

	/* Solution */
	sol.sortColors(nums);

	print_array(nums, "Sorted");
	return 0;
}
