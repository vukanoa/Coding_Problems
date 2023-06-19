#include <iostream>

/*
	============
	=== EASY ===
	============

	==================================
	350) Intersection Of Two Arrays II
	==================================

	============
	Description:
	============

	Given two integer arrays nums1 and nums2, return an array of their
	intersection. Each element in the result must appear as many times as it
	shows in both arrays and you may return the result in any order.


	Follow up:

    1. What if the given array is already sorted? How would you optimize your
	   algorithm?

    2. What if nums1's size is small compared to nums2's size? Which algorithm
	   is better?

    3. What if elements of nums2 are stored on disk, and the memory is limited
	   such that you cannot load all elements into the memory at once?

	========================================================================
	FUNCTION: vector<int> intersect(vector<int>& nums1, vector<int>& nums2);
	========================================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: nums1 = [1,2,2,1], nums2 = [2,2]
	Output: [2,2]

	--- Example 2 ---
	Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
	Output: [4,9]
	Explanation: [9,4] is also accepted.


	*** Constraints ***
	1 <= nums1.length, nums2.length <= 1000
	0 <= nums1[i], nums2[i] <= 1000

*/


/*
	------------
	--- IDEA ---
	------------

	nums1 = [4, 9, 5]
	nums2 = [9, 4, 9, 8, 4]

	Hash Map is going to have:

	   (num)   (occurrence)
		Key  :  Value
		 4   :   1
		 9   :   1
		 5   :   1
	
	Then just iterate through nums2 and if nums2[i] exists in the map, meaning
	it's value is > 0, then put in the results vector and decrease the value
	in the Hash Map for that key.
	
*/

/* Time  Beats: 57.37% */
/* Space Beats: 16.16% */

/* Time  Complexity: O(m + n) */
/* Space Complexity: O(m) */
class Solution{
public:
	std::vector<int> intersect(std::vector<int>& nums1, std::vector<int>& nums2)
	{
		std::unordered_map<int, int> umap;
		std::vector<int> results;

		for(const int& n1 : nums1)
			umap[n1]++;

		for (const int& n2 : nums2)
		{
			if (umap[n2] > 0)
			{
				umap[n2]--;
				results.push_back(n2);
			}
		}

		return results;
	}
};




/*
	------------
	--- IDEA ---
	------------

	Same idea, however, we're told in the constraints that the maximum size
	of nums1 and num2 is 1000:

		0 <= nums1[i], nums2[i] <= 1000

	Thus we can have a vector of 1000 elements and that would technically make
	this Solution O(1) even though we're using more Space than in the previous
	Solution. At lest on aveage. But the size of Space we're using doesn't
	depends on the size of nums1 or nums2, thus it's Space O(1).

	And it runs a bit faster when we're using a vector, than when we're using
	a std::unordered_map.
	
*/

/* Time  Beats: 91.94% */
/* Space Beats: 45.21% */

/* Time  Complexity: O(m + n) */
/* Space Complexity: O(1) */
class Solution{
public:
	std::vector<int> intersect(std::vector<int>& nums1, std::vector<int>& nums2)
	{
		std::vector<int> map(1001, 0);
		std::vector<int> results;

		for(const int& n1 : nums1)
			map[n1]++;

		for (const int& n2 : nums2)
		{
			if (map[n2] > 0)
			{
				map[n2]--;
				results.push_back(n2);
			}
		}

		return results;
	}
};




/*
	------------
	--- IDEA ---
	------------

    1. What if the given array is already sorted? How would you optimize your
	   algorithm?
	
	In that case we have two indexes(pointer), one in nums1 and the other in
	nums2.

	Which ever goes out of bounds first, we return the current state of the
	vector "results".
	
*/

/* Time  Beats: 100% */
/* Space Beats: 54.46% */

/* Time  Complexity: O(max(M * logM, N * logN)) */
/*
	Space Complexity: O(1)
	Assuming Sorting is possible in O(1) Space. For example Heap Sort.
*/
class Solution{
public:
	std::vector<int> intersect(std::vector<int>& nums1, std::vector<int>& nums2)
	{
		std::vector<int> results;

		std::sort(nums1.begin(), nums1.end());
		std::sort(nums2.begin(), nums2.end());
		
		int i = 0;
		int j = 0;

		while (i < nums1.size() && j < nums2.size())
		{
			if (nums1[i] < nums2[j])
				i++;
			else if (nums1[i] > nums2[j])
				j++;
			else if (nums1[i] == nums2[j]) // Just else, but it's more verbose
			{
				results.push_back(nums1[i]);
				i++;
				j++;
			}
		}

		return results;
	}
};


/*
	------------
	--- IDEA ---
	------------

	
    2. What if nums1's size is small compared to nums2's size? Which algorithm
	   is better?

	Out of the two above, the first one is better. The one where we don't sort.
	(Solution with a vector, since that is O(1) Space Complexity)

	
*/


/*
	------------
	--- IDEA ---
	------------

    3. What if elements of nums2 are stored on disk, and the memory is limited
	   such that you cannot load all elements into the memory at once?
	
	We load as much as we can into RAM and then if index 'i'(of nums1) becomes
	greater than or equal to nums1.size() that means we've done all of the
	elements and that we don't even have to load the remaining of nums2.

	Example:
		nums1 = [1, 1, 2, 3, 4, 5]
		nums2 = [1, 2, 8, 8, 8, 9, 9, 9, 10]

	Let's say that we can load 3 elements:
		nums1 = [1, 1, 2, 3, 4, 5]
		nums2 = [1, 2, 8]
		
	Simulation would go like this:
	But this assumes that nums2 is sorted.

*/
