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


/* Time  Beats: 100% */
/* Space Beats: 31.29% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
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




/*
	------------
	--- IDEA ---
	------------

	This idea has worse Time Complexity than the previous, above, Solution.
	However, it's much much more readable and much more easier to grasp in my
	opinion.

	We wouldn't be able to solve this problem if it wasn't said that: 0, 1, & 2
	are the ONLY colors we're able to find in vector "nums".

	If it was possible to have 'm' different colors inside of vector "nums",
	then we would be able to solve this problem using almost the same approach
	but in O(m * n) time instead of O(n).

	We would have 'm' for loops. But for this problem we always have only 2 and
	since that is a constant, the Time Complexity is O(2 * n) => O(n).

	Anyway, let's break this Solution down:

	It's super easy and intuitive.

	Bases cases:
		If there is only 1 color inside the vector "nums", return immediately
		since we're sure that it is already sorted.

		If there are only 2 colors inside the vector "nums" and if the first
		one is greater than the second one - Swap and return.

	We will have 2 for loops.
	First we're trying to sort all the 0's at the beginning.
	After we're trying to sort 1's and 2's.

	First we want to place 0's at the beginning.
	To do that, we will have an additional, helper vector, named:
		index_buffer
	
	It will store contiugous indexes of non-zero elements(colors) in vector
	"nums".
	
	Once we stumble upon non-zero color:
		push_back in vector "index_buffer".

	Once we stumble upon zero color:
		swap with the left-most index from vector "index_buffer", pop that
		index from the front and push_back the index of just swapped zero.
	

	After we've finished that first for loop, where we've sorted 0's at the
	beginning:
		1. Clear index_buffer
		2. Now do the same, but start from the "last sorted zero + 1"'s index.
	
	But now push indices of 2's in index_buffer and swap once you stumble upon
	1's.

	Here is a simulation:
	[2, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 0]


	1)
		BEFORE:
			nums:
				[2, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 0]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				 i

			index_buffer:
				[]

		AFTER:
			nums:
				[2, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 0]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				    i

			index_buffer:
				[0]


	2)
		BEFORE:
			nums:
				[2, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 0]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				    i

			index_buffer:
				[0]

		AFTER:
			nums:
				[0, 2, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 0] ***SWAP***
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				       i

			index_buffer:
				[1]


	3)
		BEFORE:
			nums:
				[0, 2, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 0]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				       i

			index_buffer:
				[1]

		AFTER:
			nums:
				[0, 2, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 0]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				          i

			index_buffer:
				[1, 2]


	4)
		BEFORE:
			nums:
				[0, 2, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 0]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				          i

			index_buffer:
				[1, 2]

		AFTER:
			nums:
				[0, 2, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 0]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				             i

			index_buffer:
				[1, 2, 3]


	5)
		BEFORE:
			nums:
				[0, 2, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 0]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				             i

			index_buffer:
				[1, 2, 3]

		AFTER:
			nums:
				[0, 0, 1, 2, 2, 2, 2, 1, 0, 2, 1, 1, 2, 0] ***SWAP***
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                i

			index_buffer:
				[2, 3, 4]


	6)
		BEFORE:
			nums:
				[0, 0, 1, 2, 2, 2, 2, 1, 0, 2, 1, 1, 2, 0]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                i

			index_buffer:
				[2, 3, 4]

		AFTER:
			nums:
				[0, 0, 1, 2, 2, 2, 2, 1, 0, 2, 1, 1, 2, 0]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                   i

			index_buffer:
				[2, 3, 4, 5]


	7)
		BEFORE:
			nums:
				[0, 0, 1, 2, 2, 2, 2, 1, 0, 2, 1, 1, 2, 0]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                   i

			index_buffer:
				[2, 3, 4, 5]

		AFTER:
			nums:
				[0, 0, 1, 2, 2, 2, 2, 1, 0, 2, 1, 1, 2, 0]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                      i

			index_buffer:
				[2, 3, 4, 5, 6]


	8)
		BEFORE:
			nums:
				[0, 0, 1, 2, 2, 2, 2, 1, 0, 2, 1, 1, 2, 0]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                      i

			index_buffer:
				[2, 3, 4, 5, 6]

		AFTER:
			nums:
				[0, 0, 1, 2, 2, 2, 2, 1, 0, 2, 1, 1, 2, 0]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                         i

			index_buffer:
				[2, 3, 4, 5, 6, 7]


	9)
		BEFORE:
			nums:
				[0, 0, 1, 2, 2, 2, 2, 1, 0, 2, 1, 1, 2, 0]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                         i

			index_buffer:
				[2, 3, 4, 5, 6, 7]

		AFTER:
			nums:
				[0, 0, 0, 2, 2, 2, 2, 1, 1, 2, 1, 1, 2, 0] ***SWAP***
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                            i

			index_buffer:
				[3, 4, 5, 6, 7, 8]


	10)
		BEFORE:
			nums:
				[0, 0, 0, 2, 2, 2, 2, 1, 1, 2, 1, 1, 2, 0]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                            i

			index_buffer:
				[3, 4, 5, 6, 7, 8]

		AFTER:
			nums:
				[0, 0, 0, 2, 2, 2, 2, 1, 1, 2, 1, 1, 2, 0]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                               i

			index_buffer:
				[3, 4, 5, 6, 7, 8, 9]


	11)
		BEFORE:
			nums:
				[0, 0, 0, 2, 2, 2, 2, 1, 1, 2, 1, 1, 2, 0]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                               i

			index_buffer:
				[3, 4, 5, 6, 7, 8, 9]

		AFTER:
			nums:
				[0, 0, 0, 2, 2, 2, 2, 1, 1, 2, 1, 1, 2, 0]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                                  i

			index_buffer:
				[3, 4, 5, 6, 7, 8, 9, 10]


	12)
		BEFORE:
			nums:
				[0, 0, 0, 2, 2, 2, 2, 1, 1, 2, 1, 1, 2, 0]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                                  i

			index_buffer:
				[3, 4, 5, 6, 7, 8, 9, 10]

		AFTER:
			nums:
				[0, 0, 0, 2, 2, 2, 2, 1, 1, 2, 1, 1, 2, 0]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                                     i

			index_buffer:
				[3, 4, 5, 6, 7, 8, 9, 10, 11]


	13)
		BEFORE:
			nums:
				[0, 0, 0, 2, 2, 2, 2, 1, 1, 2, 1, 1, 2, 0]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                                     i

			index_buffer:
				[3, 4, 5, 6, 7, 8, 9, 10, 11]

		AFTER:
			nums:
				[0, 0, 0, 2, 2, 2, 2, 1, 1, 2, 1, 1, 2, 0]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                                        i

			index_buffer:
				[3, 4, 5, 6, 7, 8, 9, 10, 11, 12]


	14)
		BEFORE:
			nums:
				[0, 0, 0, 2, 2, 2, 2, 1, 1, 2, 1, 1, 2, 0]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                                        i

			index_buffer:
				[3, 4, 5, 6, 7, 8, 9, 10, 11, 12]

		AFTER:
			nums:
				[0, 0, 0, 0, 2, 2, 2, 1, 1, 2, 1, 1, 2, 2] ***SWAP***
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                                           i // Out of Bounds

			index_buffer:
				[4, 5, 6, 7, 8, 9, 10, 11, 12, 13]


		*** END OF FIRST FOR LOOP***
		Clear "index_buffer".


	15)
		BEFORE:
			nums:
				[0, 0, 0, 0, 2, 2, 2, 1, 1, 2, 1, 1, 2, 2]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				             i

			index_buffer:
				[]

		AFTER:
			nums:
				[0, 0, 0, 0, 2, 2, 2, 1, 1, 2, 1, 1, 2, 2]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                i

			index_buffer:
				[4]
	


	16)
		BEFORE:
			nums:
				[0, 0, 0, 0, 2, 2, 2, 1, 1, 2, 1, 1, 2, 2]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                i

			index_buffer:
				[4]

		AFTER:
			nums:
				[0, 0, 0, 0, 2, 2, 2, 1, 1, 2, 1, 1, 2, 2]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                   i

			index_buffer:
				[4, 5]
	


	17)
		BEFORE:
			nums:
				[0, 0, 0, 0, 2, 2, 2, 1, 1, 2, 1, 1, 2, 2]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                   i

			index_buffer:
				[4, 5]

		AFTER:
			nums:
				[0, 0, 0, 0, 2, 2, 2, 1, 1, 2, 1, 1, 2, 2]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                      i

			index_buffer:
				[4, 5, 6]
	


	17)
		BEFORE:
			nums:
				[0, 0, 0, 0, 2, 2, 2, 1, 1, 2, 1, 1, 2, 2]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                      i

			index_buffer:
				[4, 5, 6]

		AFTER:
			nums:
				[0, 0, 0, 0, 1, 2, 2, 2, 1, 2, 1, 1, 2, 2] ***SWAP***
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                         i

			index_buffer:
				[5, 6, 7]
	


	18)
		BEFORE:
			nums:
				[0, 0, 0, 0, 1, 2, 2, 2, 1, 2, 1, 1, 2, 2]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                         i

			index_buffer:
				[5, 6, 7]

		AFTER:
			nums:
				[0, 0, 0, 0, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2] ***SWAP***
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                            i

			index_buffer:
				[6, 7, 8]
	


	19)
		BEFORE:
			nums:
				[0, 0, 0, 0, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                            i

			index_buffer:
				[6, 7, 8]

		AFTER:
			nums:
				[0, 0, 0, 0, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                               i

			index_buffer:
				[6, 7, 8, 9]
	


	20)
		BEFORE:
			nums:
				[0, 0, 0, 0, 1, 1, 2, 2, 2, 2, 1, 1, 2, 2]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                               i

			index_buffer:
				[6, 7, 8, 9]

		AFTER:
			nums:
				[0, 0, 0, 0, 1, 1, 1, 2, 2, 2, 2, 1, 2, 2] ***SWAP***
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                                  i

			index_buffer:
				[7, 8, 9, 10]
	


	21)
		BEFORE:
			nums:
				[0, 0, 0, 0, 1, 1, 1, 2, 2, 2, 2, 1, 2, 2]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                                  i

			index_buffer:
				[7, 8, 9, 10]

		AFTER:
			nums:
				[0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                                     i

			index_buffer:
				[8, 9, 10, 11]
	


	22)
			nums:
				[0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                                     i

			index_buffer:
				[8, 9, 10, 11]

		AFTER:
			nums:
				[0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                                        i

			index_buffer:
				[8, 9, 10, 11, 12]
	


	23)
			nums:
				[0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                                        i

			index_buffer:
				[8, 9, 10, 11, 12]

		AFTER:
			nums:
				[0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2]
				 0  1  2  3  4  5  6  7  8  9  10 11 12 13
				                                           i // Out of Bounds

			index_buffer:
				[8, 9, 10, 11, 12, 13]

*/


/* Time  Beats: 100% */
/* Space Beats: 31.29% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Readable{
public:
	void sortColors(std::vector<int>& nums)
	{
		int n = nums.size();
		if (n == 1)
			return;
		else if (n == 2 && nums[0] > nums[1])
		{
			std::swap(nums[0], nums[1]);
			return;
		}

		std::vector<int> index_buffer;	
		int last_sorted_zero_index = -1;

		/* Sort 0's */
		for (int i = 0; i < n; i++)
		{
			if (nums[i] == 0 && index_buffer.empty())
			{
				last_sorted_zero_index = i;
				continue;
			}

			if (nums[i] != 0)
				index_buffer.push_back(i);
			else
			{
				int tmp = index_buffer.front();

				index_buffer.erase(index_buffer.begin());
				std::swap(nums[tmp], nums[i]);
				index_buffer.push_back(i);

				last_sorted_zero_index = tmp;
			}
		}

		index_buffer.clear();

		/* Sort 1's and 2's */
		for (int i = last_sorted_zero_index + 1; i < n; i++)
		{
			if (nums[i] == 1 && index_buffer.empty())
				continue;

			if (nums[i] == 2) // nums[i] != 1
				index_buffer.push_back(i);
			else
			{
				int tmp = index_buffer.front();

				index_buffer.erase(index_buffer.begin());
				std::swap(nums[tmp], nums[i]);
				index_buffer.push_back(i);
			}
		}
	}
};


void
print_array(std::vector<int>& nums)
{
	bool first = true;
	std::cout << ": [";
	for (auto x: nums)
	{
		if (!first)
			std::cout << ", ";

		std::cout << x;
		first = false;
	}
	std::cout << "]\n";
}


int
main()
{
	Solution sol;
	Solution_Readable sol_r;

	/* Example 1 */
	// std::vector<int> nums = {2, 0, 2, 1, 1, 0};

	/* Example 2 */
	// std::vector<int> nums = {2, 0, 1};

	/* Example 3 */
	// std::vector<int> nums = {2, 0, 1, 2, 0, 2, 2, 1, 2, 1, 1, 2, 0};

	/* Example 4 */
	// std::vector<int> nums = {1, 2, 0};

	/* Example 5 */
	// std::vector<int> nums = {1, 2, 1};

	/* Example 6 */
	std::vector<int> nums = {2, 0, 1, 2, 0, 2, 2, 1, 0, 2, 1, 1, 2, 0};

	std::cout << "\n\t===================";
	std::cout << "\n\t=== SORT COLORS ===";
	std::cout << "\n\t===================\n";


	/* Write Input */
	std::cout << "\n\tArray ";
	print_array(nums);


	/* Solution */
	// sol.sortColors(nums);
	sol_r.sortColors(nums);


	/* Write Output */
	std::cout << "\n\tSorted";
	print_array(nums);
	std::cout << "\n";


	return 0;
}
