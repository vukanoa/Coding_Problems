#include <iostream>
#include <vector>
#include <unordered_map>

/*
	============
	=== EASY ===
	============

	=================================
	1207) Unique Number of Occurrences
	=================================

	============
	Description:
	============

	Given an array of integers arr, return true if the number of occurrences of
	each value in the array is unique or false otherwise

	===================================================
	FUNCTION: bool uniqueOccurrences(vector<int>& arr);
	===================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: arr = [1,2,2,1,1,3] Output: true Explanation: The value 1 has 3
	occurrences, 2 has 2 and 3 has 1. No two values have the same number of
	occurrences.

	--- Example 2 ---
	Input: arr = [1,2]
	Output: false

	--- Example 3 ---
	Input: arr = [-3,0,1,-3,1,1,1,-3,10,0]
	Output: true


	*** Constraints ***
	1 <= arr.length <= 1000
	-1000 <= arr[i] <= 1000

*/

/* Time  Beats: 100% */
/* Space Beats: 45.28% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
	bool uniqueOccurrences(std::vector<int>& arr) 
	{
		std::unordered_map<int, int> umap;

		for (const auto& num : arr)
			umap[num]++;

		std::unordered_map<int, int> freq;
		for (const auto& entry : umap)
		{
			if (freq.count(entry.second))
				return false;

			freq[entry.second]++;
		}

		return true;
	}
};
