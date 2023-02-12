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



/*
	------------
	--- IDEA ---
	------------

	Sort of like Bubble Sort, but a bit optimized. Not very much though.
	We start from the second element form the back since if we start
	from the last element and:
		if it is not 0
			continue
		else
			it's in the right spot, hence - Do nothing

	So we don't have to start from the very last element, but a 2nd from the
	back.

	Each time we find a zero we swap with the previous. We do that until the
	very next, right, element of our current moving zero is 0 or until our
	zero is less than n - 1st position.

	We do that for every zero. If we were to go from the very left, we would've
	had much more operations. So that's a tiny otpimization, though this is
	still very inefficient. It's just an interesting approach.

	It passes all the tests, though it beats only 5%.
*/

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


/*
	------------
	--- IDEA ---
	------------

	This question comes under a broad category of "Array Transformation". This
	category is the meat of tech interviews. Mostly because arrays are such a
	simple and easy to use data structure. Traversal or representation doesn't
	require any boilerplate code and most of your code will look like the
	Pseudocode itself.

	The 2 requirements of the question are:
		1. Move all the 0's to the end of array.
		2. All the non-zero elelments must retian their original order.

	It's good to realize here that both the requirements are mutually exclusive
	i.e you can solve the individual sub-problems and then combine them for the
	final solution.

	If asked in an interview, this approach would be a good start. You can
	explain the interviewer(not code) the above and build your base for the
	next Optimal Solution.
*/


/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Space_Inefficient{
public:
	void moveZeroes(std::vector<int>& nums)
	{
		int n = nums.size();

		// Count the zeroes
		int num_zeroes = 0;
		for (int i = 0; i < n; i++)
			num_zeroes += (nums[i] == 0);

		// Make all the non-zero elelments retain their original order.
		std::vector<int> help_vec;
		for (int i = 0; i < n; i++)
		{
			if (nums[i] != 0)
				help_vec.push_back(nums[i]);
		}

		// Move all zeroes to the end
		while (num_zeroes--)
			help_vec.push_back(0);

		// Overwrite original vector "nums"
		for (int i = 0; i < n; i++)
			nums[i] = help_vec[i];
	}
};


/*
	------------
	--- IDEA ---
	------------

	The idea is that we go through the array and gather all zeros on our road.

	Let's take our example:
	The first step - we meet 0.
	Okay, just remember that now the size of our snowball is 1. Go further.
	('#' will denote snowball. Number of characters is the size of snowball)

	[0, 1, 0, 3, 12]
	 # // Size 1

	Next step - We encounter 1. Swap the most left 0 of our snowball with
	element 1.

	-----
	|   |
	|   v
	[0, 1, 0, 3, 12]
	 #  |
	 ^  |
	 |---


	Next step - We encounter 0 again! (Our ball gets bigger, now its size = 2)
	[1, 0, 0, 3, 12]
	    #  #

	Next Step - 3. Swap again with the most left zero.

		-------
		|     |
	    |     v
	[1, 0, 0, 3, 12]
	    #  #  |
		^     |
	    |------

	Looks like our zeros roll all the time

	[1, 3, 0, 0, 12]
	       #  #

	Next Step - 12. Swap again.

		   --------
		   |      |
	       |      v
	[1, 3, 0, 0, 12]
	       #  #   |
	       ^      |
	       |-------


	We reach the end:

	[1, 3, 12, 0, 0]

*/

class Solution{
public:
	void moveZeroes(std::vector<int>& nums)
	{
		int snowball_size = 0;

		for (int i = 0; i < nums.size(); i++)
		{
			if (nums[i] == 0)
				snowball_size++;
			else if (snowball_size > 0)
			{
				int tmp = nums[i];
				nums[i] = 0;
				nums[i - snowball_size] = tmp;
			}
		}
	}
};


int
main()
{
	Solution_inefficient sol_ineff;
	Solution sol;
	Solution_Space_Inefficient sol_space;

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
	// sol_ineff.moveZeroes(nums);
	// sol.moveZeroes(nums);
	sol_space.moveZeroes(nums);

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
