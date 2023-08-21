#include <iostream>
#include <vector>
#include <algorithm>

/*
	==============
	=== MEDIUM ===
	==============

	==============================
	435) Non-Overlapping Intervals
	==============================

	============
	Description:
	============

	Given an array of intervals intervals where intervals[i] = [starti, endi],
	return the minimum number of intervals you need to remove to make the rest
	of the intervals non-overlapping.

	====================================================================
	FUNCTION: int eraseOverlapIntervals(vector<vector<int>>& intervals); 
	====================================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
	Output: 1
	Explanation: [1,3] can be removed and the rest of the intervals are
	             non-overlapping.

	--- Example 2 ---
	Input: intervals = [[1,2],[1,2],[1,2]]
	Output: 2
	Explanation: You need to remove two [1,2] to make the rest of the intervals
	             non-overlapping.

	--- Example 3 ---
	Input: intervals = [[1,2],[2,3]]
	Output: 0
	Explanation: You don't need to remove any of the intervals since they're
	             already non-overlapping.

	*** Constraints ***
	1 <= intervals.length <= 105
	intervals[i].length == 2
	-5 * 104 <= starti < endi <= 5 * 104

*/

/*
	------------
	--- IDEA ---
	------------

	First, as in most interval problems - Sort by starting point.

	1--------3
	     2---3
	1----2
	         3---4
	

	Here are some examples that make this solution obvious:

	I)
	     1----------5  7--------9
	

	II)
	           3-------7
	     1----------6     8---------10
	

	III)
	           3----------8
	     1----------6  7------------10
	

	IV)
	         2----5    7------------10
	     1-----------------8
	

	Each time two adjacent intervals are overlapping, continue with the one
	that has a smaller ending point. (That assures that we'll have minimum
	amount of removal)

	So if the "left" one has smaller ending point, then just continue(i will be
	incremented in the for loop)
	
	If "left" one has bigger ending point or if they are not overlapping then: 
		left = i;

*/

/* Time  Complexity: O(94.67) */
/* Space Complexity: O(53.74) */

/*
	Time  Complexity: O(n * logn)
*/
/*
	Space Complexity: O(n)
	Depends on the sort that is used. Heapsort has O(1) Space Complexity.
*/
class Solution{
public:
	int eraseOverlapIntervals(std::vector<std::vector<int>>& intervals)
	{
		std::sort(intervals.begin(), intervals.end());

		int count = 0;
		int left  = 0;
		for (int i = 1; i < intervals.size(); i++)
		{
			if (intervals[left][1] > intervals[i][0])
			{
				count++;

				if (intervals[left][1] < intervals[i][1])
					continue;
			}

			// If "left" one has bigger ending point or if they are not
			// overlapping at all
			left = i;
		}

		return count;
	}
};
