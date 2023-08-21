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

/*
	------------
	--- IDEA ---
	------------

	There are 3 possibilities:
	        1. It's before the first interval
	        2. It's after  the last  interval
	        3. It's overlapping
	        4. It's a separate new interval that needs to be pushed somewhere in the middle

	Consider this example:
	        intervals = [[3, 5], [8, 10], [15, 18]]

	All the possible cases:
	        1.  [0, 1]   // Before the first interval
	        2.  [0, 4]   // Overlapping
	        3.  [0, 16]  // Overlapping
	        4.  [0, 19]  // Overlapping
	        5.  [3, 8]   // Overlapping
	        6.  [3, 15]  // Overlapping
	        7.  [6, 7]   // New separate interval
	        8.  [6, 17]  // Overlapping
	        9.  [6, 19]  // Overlapping
	        10. [16, 20] // Overlapping
	        11. [19, 20] // After the last interval
	
	It's pretty much self-explanatory.

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




/*
	------------
	--- IDEA ---
	------------

	This Solution is more in the spirit of C++

*/

/* Time  Beats: 98.73% */
/* Space Beats: 51.03% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
	std::vector<std::vector<int>> insert(std::vector<std::vector<int>>& intervals, std::vector<int>& newInterval)
	{
		int n = intervals.size();
		int i = 0;
		std::vector<std::vector<int>> result;
		
		// Case 1: no overlapping case before the merge intervals
		// Compare ending point of intervals to starting point of newInterval
		while(i < n && intervals[i][1] < newInterval[0])
		{
			result.push_back(intervals[i]);
			i++;
		}                           

		// Case 2: overlapping case and merging of intervals
		while(i < n && newInterval[1] >= intervals[i][0])
		{
			newInterval[0] = min(newInterval[0], intervals[i][0]);
			newInterval[1] = max(newInterval[1], intervals[i][1]);
			i++;
		}
		result.push_back(newInterval);

		// Case 3: no overlapping of intervals after newinterval being merged
		while(i < n)
		{
			result.push_back(intervals[i]);
			i++;
		}

		return result;
	}
};
