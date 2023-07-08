#include <iostream>
#include <vector>
#include <algorithm>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	324) Wiggle Sort
	===========================

	============
	Description:
	============

	Given an integer array nums, reorder it such that:
	nums[0] < nums[1] > nums[2] < nums[3]....

	You may assume the input array always has a valid answer.


	Follow Up: Can you do it in O(n) time and/or in-place with O(1) extra
	space?

	=============================================
	FUNCTION: void wiggleSort(vector<int>& nums);
	=============================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: nums = [1,5,1,1,6,4]
	Output: [1,6,1,5,1,4]
	Explanation: [1,4,1,5,1,6] is also accepted.


	--- Example 2 ---
	Input: nums = [1,3,2,2,3,1]
	Output: [2,3,1,3,1,2]


	*** Constraints ***
	1 <= nums.length <= 5 * 104
	0 <= nums[i] <= 5000
	It is guaranteed that there will be an answer for the given input nums.

*/


/*
	------------
	--- IDEA ---
	------------

	Once you sort and divide into left and right group, it's easy to see that
	we have to alternate between the groups and push those items from the back
	of certain group.

*/

/* Time  Beats:    89% */
/* Space Beats: 19.57% */

/* Time  Complexity: O(n * log) */
/* Space Complexity: O(n) */
class Solution{
public:
	void wiggleSort(std::vector<int>& nums)
	{
		std::sort(nums.begin(), nums.end());

		std::vector<int> left;
		std::vector<int> right;

		int n = nums.size();
		int border = n % 2 == 0 ? n/2 : n/2 + 1;

		for (int i = 0; i < border; i++)
			left.push_back(nums[i]);

		for (int i = border; i < n; i++)
			right.push_back(nums[i]);

		for (int i = 0; i < n; i++)
		{
			if (i % 2 == 0)
			{
				nums[i] = left.back();
				left.pop_back();
			}
			else
			{
				nums[i] = right.back();
				right.pop_back();
			}
		}
	}
};




/*
	------------
	--- IDEA ---
	------------

	Same idea, written in a different way.

*/

/* Time  Beats:    89% */
/* Space Beats: 84.49% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
	void wiggleSort(std::vector<int>& nums)
	{
		std::vector<int> sorted(nums);

		std::sort(sorted.begin(), sorted.end());
		int n = nums.size();

		int i = n - 1;
		int j = 0;
		int k = i / 2 + 1;
		for (i = n - 1; i >= 0; i--)
			nums[i] = sorted[i&1 ? k++ : j++];
	}
};




/*
	------------
	--- IDEA ---
	------------

	First I find a median using nth_element. That only guarantees O(n) average
	time complexity and I don't know about space complexity. I might write this
	myself using O(n) time and O(1) space, but that's not what I want to show
	here.

	This post is about what comes after that. We can use three-way partitioning
	to arrange the numbers so that those larger than the median come first,
	then those equal to the median come next, and then those smaller than the
	median come last.

	Ordinarily, you'd then use one more phase to bring the numbers to their
	final positions to reach the overall wiggle-property. But I don't know a
	nice O(1) space way for this. Instead, I embed this right into the
	partitioning algorithm. That algorithm simply works with indexes 0 to n-1
	as usual, but sneaky as I am, I rewire those indexes where I want the
	numbers to actually end up. The partitioning-algorithm doesn't even know
	that I'm doing that, it just works like normal (it just uses A(x) instead
	of nums[x]).

	Let's say nums is [10,11,...,19]. Then after nth_element and ordinary
	partitioning, we might have this (15 is my median):

	index:     0  1  2  3   4   5  6  7  8  9
	number:   18 17 19 16  15  11 14 10 13 12

	I rewire it so that the first spot has index 5, the second spot has index
	0, etc, so that I might get this instead:

	index:     5  0  6  1  7  2  8  3  9  4
	number:   11 18 14 17 10 19 13 16 12 15

	And 11 18 14 17 10 19 13 16 12 15 is perfectly wiggly. And the whole
	partitioning-to-wiggly-arrangement (everything after finding the median)
	only takes O(n) time and O(1) space.

	If the above description is unclear, maybe this explicit listing helps:

	Accessing A(0) actually accesses nums[1].
	Accessing A(1) actually accesses nums[3].
	Accessing A(2) actually accesses nums[5].
	Accessing A(3) actually accesses nums[7].
	Accessing A(4) actually accesses nums[9].
	Accessing A(5) actually accesses nums[0].
	Accessing A(6) actually accesses nums[2].
	Accessing A(7) actually accesses nums[4].
	Accessing A(8) actually accesses nums[6].
	Accessing A(9) actually accesses nums[8].

	Props to apolloydy's solution, I knew the partitioning algorithm already
	but I didn't know the name. And apolloydy's idea to partition to reverse
	order happened to make the index rewiring simpler.

*/

/* Time  Beats: 97.86% */
/* Space Beats: 96.94% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_efficient {
public:
	void wiggleSort(vector<int>& nums)
	{
		int n = nums.size();
		
		// Find a median.
		auto midptr = nums.begin() + n / 2;
		nth_element(nums.begin(), midptr, nums.end());
		int mid = *midptr;
		
		// Index-rewiring.
		#define A(i) nums[(1+2*(i)) % (n|1)]

		// 3-way-partition-to-wiggly in O(n) time with O(1) space.
		int i = 0, j = 0, k = n - 1;
		while (j <= k)
		{
			if (A(j) > mid)
				swap(A(i++), A(j++));
			else if (A(j) < mid)
				swap(A(j), A(k--));
			else
				j++;
		}
	}
};
