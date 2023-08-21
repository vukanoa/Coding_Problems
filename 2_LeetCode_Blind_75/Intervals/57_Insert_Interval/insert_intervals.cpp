#include <iostream>
#include <vector>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	57) Insert Interval
	===========================

	============
	Description:
	============

	You are given an array of non-overlapping intervals intervals where
	intervals[i] = [starti, endi] represent the start and the end of the ith
	interval and intervals is sorted in ascending order by starti. You are also
	given an interval newInterval = [start, end] that represents the start and
	end of another interval.

	Insert newInterval into intervals such that intervals is still sorted in
	ascending order by starti and intervals still does not have any overlapping
	intervals (merge overlapping intervals if necessary).

	Return intervals after the insertion.

	===============================================================================================
	FUNCTION: vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval);
	===============================================================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
	Output: [[1,5],[6,9]]

	--- Example 2 ---
	Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
	Output: [[1,2],[3,10],[12,16]]
	Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].

	*** Constraints ***
	0 <= intervals.length <= 104
	intervals[i].length == 2
	0 <= starti <= endi <= 105
	intervals is sorted by starti in ascending order.
	newInterval.length == 2
	0 <= start <= end <= 105

*/

/* Time  Beats: 69.92% */
/* Space Beats: 26.73% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
	std::vector<std::vector<int>> insert(std::vector<std::vector<int>>& intervals, std::vector<int>& newInterval)
	{
		std::vector<std::vector<int>> result;

		for (int i = 0; i < intervals.size(); i++)
		{
			if (newInterval[1] < intervals[i][0])
			{
				result.push_back(newInterval);

				result.insert(std::end(result), std::begin(intervals) + i, std::end(intervals));

				return result;
			}
			else if (newInterval[0] > intervals[i][1])
				result.push_back(intervals[i]);
			else // (newInterval[1] >= intervals[i][0])
			{
				newInterval[0] = std::min(newInterval[0], intervals[i][0]);
				newInterval[1] = std::max(newInterval[1], intervals[i][1]);
			}
		}

		result.push_back(newInterval);

		return result;
	}
};
