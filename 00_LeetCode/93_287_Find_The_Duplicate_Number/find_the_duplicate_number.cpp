#include <iostream>
#include <vector>

/*
	==============
	=== MEDIUM ===
	==============

	==============================
	287) Find the Duplicate Number
	==============================

	============
	Description:
	============

	Given an array of integers "nums" containing n + 1 integers where each
	integer is in the range [1, n] inclusive.

	There is only one repeated number in "nums", return this repeated number.

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		My Note(This isn't a part of LeetCode Description)

		(This means that one number can repeat multiple times, not that the
		repeating number can repeat once, i.e. repeating number has frequency
		of 2 while other have frequence of 1.

		This is possible: [2, 2, 2, 2, 2])
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	You must solve the problem WITHOUT modifying the array "nums" and uses
	only constant extra space.

	Follow up:
		- How can we prove that at least one duplicate number must exist in
		  "nums"?

		- Can you solve the problem in linear runtime complexity?

	===============================================
	FUNCTION: int findDuplicate(vector<int>& nums);
	===============================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  nums = [1, 3, 4, 2, 2]
	Output: 2

	--- Example 2 ---
	Input:  nums = [3, 1, 3, 4, 2]
	Output: 3

	--- Example 3 ---
	Input:  nums = [2, 2, 2, 2, 2]
	Output: 2

	*** Constraints ***
	1 <= n <= 10^5
	nums.length == n + 1
	1 <= nums[i] <= n
	All the integers in "nums" appear only *once* except for *precisely one
	integer* which appears two or more times.

*/


/*
	------------
	--- IDEA ---
	------------

	Approach 7: Floyd's Tortoise and Hare (Cycle Detection)

	Intuition
	The idea is to reduce the problem to Problem: 142 Linked List Cycle II
	"Given a linked list, return the node where the cycle begins."

	First of all, where does the cycle come from? Let's use the function
	f(x) = nums[x] to construct the sequence:
		x, nums[x], nums[nums[x]], nums[nums[nums[x]]], ...

	Each new element in the sequence is an element in nums at the index of the
	previous element.

	If one starts from x = nums[0], such a sequence will produce a linked list
	with a cycle.

	"The cycle appears because "nums" contains duplicates. The duplicate node
	is a cycle entrance"

	Here is how it works:

	----------   --------
	|        v   v       |
	|    0 1 2 3 4 5 6   |
	|    2 6 4 1 3 1 5   |
	|    |   |           |
	------   -------------

	(etc. you get the point. Every VALUE is used as a POINTER. And instead
	of having addresses as pointer values which you dereference, we use
	indices instead.
	And dereferencing is the same:
		nums[4] <==> *(nums + 4)


	                  6
	                  ^
	                 /  \
	                /    \
	2 -> 4 -> 3 -> 1      v
	               ^----- 5

	The example above is simple because the loop is small. Here is a more
	interesting example.

	index 0 1 2 3 4 5 6 7 8 9
	nums  2 5 9 6 9 3 8 9 7 1

	       1 -> 5
	       ^     \
	      /       v
	2 -> 9        3
	     ^        |
	     |        v
	     |        6
	     |       /
	     \      v
	      7 <- 8

	Now the problem is to find the entrance of the cycle, i.e. the loop node.

	Algorithm
	Floyd's Algorithm consists of two phases and uses two pointers, usually
	called "tortoise" and "hare".

	In phase 1:
		hare = nums[nums[hare]] is twice as tortoise = nums[tortoise]
	
	// In linked lists it's:
	// hare = hare->next->next; tortoise = tortoise->next;

	Since the hare goes fast, it would be the first to enter the cycle and run
	around the cycle. At some point, the tortoise enters the cycle as well, and
	since it's moving slower the hare catches up to the tortoise at some
	intersection point. Now phase 1 is over, and the tortoise has lost.

	Note that the intersection point is not the cycle entrance in the general
	case.


	index 0 1 2 3 4 5 6 7 8 9
	nums  2 5 9 6 9 3 8 9 7 1

cycle entrance (9)
        |
	    |  1 -> 5
	    |  ^     \
	    v /       v
	2 -> 9        3
	     ^        |
	     |        v
	     |        6
	     |       /
	     \      v
	      7 <- 8
	      ^
	      |
first intersection


	           a
	         ----> o
	   f    /       \
	o ---> o         |
	       ^         |
	        \  c-a   |
		     \------/

	To compute the intersection point, let's note that the hare has traversed
	twice as many nodes as the tortoise, i.e. 2d(tortoise) = d(hare), implying:

	2(F + a) = F + nC + a, where nC is some integer.

	Hence the coordinate of the intersection point is F + a = nC

	In phase 2, we give the tortoise a second chance by slowing down the hare,
	so that it now moves at the speed of tortoise:
		tortoise = nums[tortoise]; hare = nums[hare]

	The tortoise is back at the starting position, and the hare starts from the
	intersection point.



               a        hare
             ----> o   ------>
       f    /       \
    o ---> o         |
---->      ^         |
tortoise    \  c-a   |
    	     \------/


*/

/* Time  Beats: 76.77% */
/* Space Beats: 57.56% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution{
public:
	int findDuplicate(std::vector<int>& nums)
	{
		// Find the intersection point of the two runners
		int tortoise = nums[0];
		int hare     = nums[0];

		do
		{
			tortoise = nums[tortoise];
			hare     = nums[nums[hare]];
		} while (tortoise != hare);

		// Find the "entrance" to the cycle.
		tortoise = nums[0];
		while (tortoise != hare)
		{
			tortoise = nums[tortoise];
			hare     = nums[hare];
		}

		return hare;
	}
};


int
main()
{
	Solution sol;


	/* Example 1 */
	std::vector<int> nums = {1, 3, 4, 2, 2};

	/* Example 2 */
	// std::vector<int> nums = {3, 1, 3, 4, 2};

	/* Example 3 */
	// std::vector<int> nums = {2, 2, 2, 2, 2};

	std::cout << "\n\t=================================";
	std::cout << "\n\t=== FIND THE DUPLICATE NUMBER ===";
	std::cout << "\n\t=================================\n";


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
	int output = sol.findDuplicate(nums);


	/* Write Output */
	std::cout << "\n\tDuplicate: " << output << "\n\n";


	return 0;
}
