#include <iostream>

/*
	============
	=== HARD ===
	============

	========================================
	315) Count of Smaller Numbers After Self
	========================================

	============
	Description:
	============

	Given an integer array nums, return an integer array counts where counts[i]
	is the number of smaller elements to the right of nums[i].

	======================================================
	FUNCTION: vector<int> countSmaller(vector<int>& nums);
	======================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: nums = [5,2,6,1]
	Output: [2,1,1,0]
	Explanation:
	To the right of 5 there are 2 smaller elements (2 and 1).
	To the right of 2 there is only 1 smaller element (1).
	To the right of 6 there is 1 smaller element (1).
	To the right of 1 there is 0 smaller element.


	--- Example 2 ---
	Input: nums = [-1]
	Output: [0]


	--- Example 3 ---
	Input: nums = [-1,-1]
	Output: [0,0]


	*** Constraints ***
	1 <= nums.length <= 10^5
	-10^4 <= nums[i] <= 10^4

*/

/*
	------------
	--- IDEA ---
	------------

	TODO
	
*/

/* Time  Beats: 78.05% */
/* Space Beats: 39.90% */
class Solution {
public:
	void merge(int left, int mid, int right, std::vector<std::pair<int, int>>& vec,std::vector<int>& count)
	{
		std::vector<std::pair<int, int>> tmp(right - left + 1);

		int i = left;
		int j = mid + 1;
		int k = 0;

		while(i <= mid && j <= right)
		{
			if(vec[i].first <= vec[j].first)
			{
			    tmp[k++] = vec[j++]; 
			}
			else
			{
			    count[vec[i].second] += (right - j + 1);
			    
			    tmp[k++] = vec[i++];
			}
		}

		while(i <= mid)
		{
			tmp[k++] = vec[i++];
		}
		
		while(j <= right)
		{
			tmp[k++] = vec[j++];
		}
		
		for(int l = left; l <= right; l++)
			vec[l] = tmp[l - left];
	}

	void mergeSort(int left, int right, std::vector<std::pair<int, int>>& vec, std::vector<int>& count)
	{
		if(left >= right)
		{
			return;
		}
		
		int mid = left + (right - left) / 2;
		
		mergeSort(left, mid, vec, count);
		mergeSort(mid + 1, right, vec, count);
		
		merge(left, mid, right, vec, count);
	}

	std::vector<int> countSmaller(std::vector<int>& nums)
	{
		int n = nums.size();
		std::vector<std::pair<int, int>> vec;

		for(int i = 0; i < n; i++)
		{
			vec.push_back({nums[i], i});
		}
		
		std::vector<int> count(n, 0);
		
		mergeSort(0, n - 1, vec, count);
		
		return count;
	}
};
