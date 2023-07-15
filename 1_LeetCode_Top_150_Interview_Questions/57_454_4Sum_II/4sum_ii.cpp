#include <iostream>
#include <vector>
#include <unordered_map>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	424) 4Sum II
	===========================

	============
	Description:
	============

	Given four integer arrays nums1, nums2, nums3, and nums4 all of length n,
	return the number of tuples (i, j, k, l) such that:

		0 <= i, j, k, l < n

		nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0

	===========================================================================================================
	FUNCTION: int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4);
	===========================================================================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: nums1 = [1,2], nums2 = [-2,-1], nums3 = [-1,2], nums4 = [0,2]
	Output: 2
	Explanation:
	The two tuples are:
	1. (0, 0, 0, 1) -> nums1[0] + nums2[0] + nums3[0] + nums4[1] = 1 + (-2) + (-1) + 2 = 0
	2. (1, 1, 0, 0) -> nums1[1] + nums2[1] + nums3[0] + nums4[0] = 2 + (-1) + (-1) + 0 = 0


	--- Example 2 ---
	Input: nums1 = [0], nums2 = [0], nums3 = [0], nums4 = [0]
	Output: 1


	*** Constraints ***
    n == nums1.length
    n == nums2.length
    n == nums3.length
    n == nums4.length
    1 <= n <= 200
    -2^28 <= nums1[i], nums2[i], nums3[i], nums4[i] <= 2^28

*/

/* Time  Beats: 56.29% */
/* Space Beats: 98.80% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n) */
class Solution {
public:
	int fourSumCount(std::vector<int>& nums1, std::vector<int>& nums2, std::vector<int>& nums3, std::vector<int>& nums4)
	{
		int count = 0;
		std::unordered_map<int, int> umap;

		for (int& c : nums3)
		{
			for (int& d : nums4)
				umap[c + d]++;
		}

		for (int& a : nums1)
		{
			for (int& b : nums2)
			{
				if (umap.find((-1) * (a + b)) != umap.end())
					count += umap[(-1) * (a + b)];
			}
		}

		return count;
	}
};
