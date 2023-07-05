#include <iostream>

/*
	==============
	=== MEDIUM ===
	==============

	===========================
	253) Meeting Rooms II
	===========================

	============
	Description:
	============

	Given an array of meeting time intervals consisting of start and end times
	[[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference
	rooms required.

	==============================================================
	FUNCTION: int minMeetingRooms(vector<vector<int>> &intervals);
	==============================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	Input: [[0, 30],[5, 10],[15, 20]]
	Output: 2
	Explanation:
	We need two conference rooms.
	room1: (0, 30)
	room2: (5, 10), (15, 20)

	--- Example 2 ---
	Input: [[7,10],[2,4]]
	Output: 1

	*** Constraints ***

*/

/*
	------------
	--- IDEA ---
	------------

	TODO
	
*/

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution{
public:
	int minMeetingRooms(std::vector<std::vector<int>>& intervals)
	{
		std::vector startings;
		std::vector endings;

		for (int i = 0; i < intervals.size(); i++)
		{
			startings.push_back(intervals[i][0]);
			endings.push_back(intervals[i][1]);
		}

		std::sort(startings.begin(), startings.end());
		std::sort(endings.begin(), endings.end());

		int result = 0;
		int count  = 0;

		int begin = 0;
		int end   = 0;

		while (begin < intervals.size())
		{
			if (start[begin] < endings[end])
			{
				begin++;
				count++;
			}
			else
			{
				end++;
				count--;
			}

			result = std::max(result, count);
		}

		return result;
	}
};
