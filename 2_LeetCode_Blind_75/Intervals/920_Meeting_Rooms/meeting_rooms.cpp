#include <iostream>
#include <vector>
#include <algorithm>

/*
	============
	=== EASY ===
	============

	===========================
	920) Meeting Rooms
	===========================

	============
	Description:
	============

	Given an array of meeting time intervals consisting of start and end times
	[[s1, e1], [s2, e2], ...] (si < ei), determine if a person could attend all
	meetings.

	=====
	Node: (0, 8), (8, 10) is not a conflict at 8
	=====

	===========================================================================
	FUNCTION: bool canAttendMeetings(std::vector<std::vector<int>>& intervals);
	===========================================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input:  Intervals = [(0, 30), (15, 20), (15, 20)]
	Output: false
	Explanation:
	(0, 30), (5, 10) and (0, 30), (15, 20) will conflict

	*** Constraints ***
	<Unknown>

*/

/*
	------------
	--- IDEA ---
	------------

	Sort the input(intervals) based on the start time.

	If the previous interval's "end time" is larger than curren't interval's
	"start time" - That means that they overlap, hence we return false.

*/

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1) */
class Solution{
public:
	bool canAttendMeetings(std::vector<std::vector<int>>& intervals)
	{
		if (intervals.empty())
			return true;

		std::sort(intervals.begin(), intervals.end());

		for (int i = 1; i < intervals.size(); i++)
		{
			if (intervals[i-1][1] > intervals[i][0])
				return false;
		}

		return true;
	}
};
