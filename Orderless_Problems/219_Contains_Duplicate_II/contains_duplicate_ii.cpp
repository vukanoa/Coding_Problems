#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

/*
	============
	=== EASY ===
	============

	===========================
	219) Contains Duplicate
	===========================

	============
	Description:
	============

	Given an integer array nums and an integer k, return true if there are two
	distinct indices i and j in the array such that nums[i] == nums[j] and
	abs(i - j) <= k.

	=================================================================
	FUNCTION: bool containsNearbyDuplicate(vector<int>& nums, int k);
	=================================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: nums = [1,2,3,1], k = 3
	Output: true

	--- Example 2 ---
	Input: nums = [1,0,1,1], k = 1
	Output: true

	--- Example 3 ---
	Input: nums = [1,2,3,1,2,3], k = 2
	Output: false


	*** Constraints ***
	1 <= nums.length <= 10^5
	-10^9 <= nums[i] <= 10^9
	0 <= k <= 10^5

*/


/* Time  Beats: 70.77% */
/* Space Beats: 57.79% */
class Solution_Sliding_Window {
public:
	bool containsNearbyDuplicate(std::vector<int>& nums, int k)
	{
		if (nums.size() == 1 || k == 0)
			return false;

		std::unordered_map<int, int> umap;

		for (int i = 0; i < k && i < nums.size(); i++)
		{
			if (umap.count(nums[i]))
				return true;

			umap[nums[i]]++;
		}


		int left  = 0;
		int right = k;

		while (right < nums.size())
		{
			umap[nums[right]]++;

			if (umap[nums[left]] > 1)
				return true;

			umap[nums[left]]--;
			left++;
			right++;
		}
		
		while (left < nums.size())
		{
			if (umap[nums[left]] > 1)
				return true;

			umap[nums[left]]--;
			left++;
		}

		return false;
	}
};




/* Time  Beats: 71.54% */
/* Space Beats: 38.06% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Sliding_Window_Concise {
public:
	bool containsNearbyDuplicate(vector<int>& nums, int k)
	{
		std::unordered_map<int, int>umap;

		int left  = 0;
		int right = 0;

		while (right < nums.size())
		{
			if(right > k)
				umap[nums[left++]]--;

			if(umap[nums[right]] > 0)
				return true;

			umap[nums[right++]]++;
		}

		return false;
	}
};




/* Time  Beats: 72.17% */
/* Space Beats: 97.00% */
class Solution_Sliding_Window_USet{
public:
	bool containsNearbyDuplicate(std::vector<int>& nums, int k)
	{
        if (k == 0)
            return false;
        
        int n = nums.size();
        if (k >= n)
            k = n - 1;

        std::unordered_set<int> uset;
        
        for (int i = 0; i < n; i++)
        {
            if (i > k)
                uset.erase(nums[i - k - 1]);
            
            if (uset.count(nums[i]))
                return true;

            uset.insert(nums[i]);
        }

        return false;
	}
};
