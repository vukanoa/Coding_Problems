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

	In the Description, when they've said: 
		"Find the minimum number of conference rooms required"
	what they really mean is:
		"What is the maximum number of overlapping meetings at any give point
		 in time"

	It's kind of difficult to come up with the code if you look at the example
	in "vector" representation.

	So let's draw it:

			[[0, 30], [5, 10], [15, 20]]

			0                                30
			|--------------------------------|

			    5    10
			    |-----|    15    20
			                |-----|
	
	Again, let's emphasize the right question:
		"What is the maximum number of overlapping meetings at any give point
		 in time"

	Now if we just go from left to right we'll see:
		Okay, 0 is the first meeting that starts. If we keep going then we're
		going to stumble upon a 5, which is also the beginning(of a conference)
		it's not that the first meeting is ending.

		So what does that tells us?
		It tells us that two meeting have started so far but none has ended.

		So at this point in time:
			   |____
			       |
			       v

			       |
			0      |                         30
			|------|-------------------------|
			       |
			    5  | 10
			    |--|--|    15    20
			               |-----|


		We have 2 meetings that are going on at the same amount of time.

		So we're going to be maintaining is a variable "count", which tells us
		at any given point in time, what is the number of meetings going on.

		Right now it's 2, but we're going to be returning whatever the max
		value of it happened to be.

		Next is the point 10, which is the first ending point.
		So what does that tell us?
		That tells us that a meeting has just ended. So what are we going to do
		with out "count"?

		We knew we have 2 meetings going on at the same time, but now, after
		this point:
			 |
			 |_________
			          |
			          v

			          |
			0         |                      30
			|---------|----------------------|
			          |
			    5    1|0
			    |-----|    15    20
			          |     |-----|

		
		We're only going to have one meeting going on, therefore we're going
		to se the number of meetings to 1.

		Next one is 15 and it happens to be the starting point.
		So now, once again, there are two meeting going on at the same time.
		We increment one count.

		Next is 20, which is an ending point. We know a meeting is ending, but
		we don't know which one. But that's not even important. The only thing
		that is important is the we are tracking how many meeting are going on
		at the same time. After this 20, it's 1.

		And the last point is 30, it's an ending point, again decrement the
		"count".

		At the end we return the maximum value of count at any given time.
		In our case, it was 2.

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
