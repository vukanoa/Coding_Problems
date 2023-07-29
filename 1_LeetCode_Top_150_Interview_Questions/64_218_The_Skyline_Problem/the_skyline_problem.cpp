#include <iostream>
#include <vector>
#include <set>
#include <algorihtm>

/*
	============
	=== HARD ===
	============

	===========================
	218) The Skyline Problem
	===========================

	============
	Description:
	============

	A city's skyline is the outer contour of the silhouette formed by all the
	buildings in that city when viewed from a distance. Given the locations and
	heights of all the buildings, return the skyline formed by these buildings
	collectively.

	The geometric information of each building is given in the array buildings
	where buildings[i] = [lefti, righti, heighti]:

		lefti is the x coordinate of the left edge of the ith building.
		righti is the x coordinate of the right edge of the ith building.
		heighti is the height of the ith building.

	You may assume all buildings are perfect rectangles grounded on an
	absolutely flat surface at height 0.

	The skyline should be represented as a list of "key points" sorted by their
	x-coordinate in the form [[x1,y1],[x2,y2],...]. Each key point is the left
	endpoint of some horizontal segment in the skyline except the last point in
	the list, which always has a y-coordinate 0 and is used to mark the
	skyline's termination where the rightmost building ends. Any ground
	between the leftmost and rightmost buildings should be part of the
	skyline's contour.


	=====
	Node: There must be no consecutive horizontal lines of equal height in the
	      output skyline. For instance:
			  [...,[2 3],[4 5],[7 5],[11 5],[12 7],...] is not acceptable;

		  The three lines of height 5 should be merged into one in the final
		  output as such:
			  [...,[2 3],[4 5],[12 7],...]
	=====

	=========================================================================
	FUNCTION: vector<vector<int>> getSkyline(vector<vector<int>>& buildings); 
	=========================================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---
	                                   A
	   ^
	15 |        *************
	14 |        *************
	13 |        *****!!!!!!!!!!!!!!!!!!!!!!
	12 |        *****!!!!!!!!!!!!!!!!!!!!!!
	11 |        *****!!!!!!!!!!!!!!!!!!!!!!
	10 |     ######################!!!!!!!!        $$$$$$$$$$$$$$$$
	9  |     ######################!!!!!!!!        $$$$$$$$$$$$$$$$
	8  |     ######################!!!!!!!!        $$$$$$$$$$$$^^^^^^^^^^^^^^^^
	7  |     ######################!!!!!!!!        $$$$$$$$$$$$^^^^^^^^^^^^^^^^
	6  |     ######################!!!!!!!!        $$$$$$$$$$$$^^^^^^^^^^^^^^^^
	5  |     ######################!!!!!!!!        $$$$$$$$$$$$^^^^^^^^^^^^^^^^
	4  |     ######################!!!!!!!!        $$$$$$$$$$$$^^^^^^^^^^^^^^^^
	3  |     ######################!!!!!!!!        $$$$$$$$$$$$^^^^^^^^^^^^^^^^
	2  |     ######################!!!!!!!!        $$$$$$$$$$$$^^^^^^^^^^^^^^^^
	1  |     ######################!!!!!!!!        $$$$$$$$$$$$^^^^^^^^^^^^^^^^
	0  |---------------------------------------------------------------------------->
	   0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25




	                                   B
	   ^
	15 |        X____________
	14 |        |           |
	13 |        |           X______________
	12 |        |                         |
	11 |     X__|                         |
	10 |     |                            |        X_______________
	9  |     |                            |        |              |
	8  |     |                            |        |              X____________
	7  |     |                            |        |                          |
	6  |     |                            |        |                          |
	5  |     |                            |        |                          |
	4  |     |                            |        |                          |
	3  |     |                            |        |                          |
	2  |     |                            |        |                          |
	1  |     |                            X________|                          X
	0  |---------------------------------------------------------------------------->
	   0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25


	Input: buildings = [[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]]
	Output: [[2,10],[3,15],[7,12],[12,0],[15,10],[20,8],[24,0]]
	Explanation:
	Figure A shows the buildings of the input.
	Figure B shows the skyline formed by those buildings. The red points in
	figure B represent the key points in the output list.





	--- Example 2 ---
	Input: buildings = [[0,2,3],[2,5,3]]
	Output: [[0,3],[5,0]]


	*** Constraints ***
	1 <= buildings.length <= 10^4
	0 <= lefti < righti <= 2^31 - 1
	1 <= heighti <= 2^31 - 1
	buildings is sorted by lefti in non-decreasing order.

*/




/*
	------------
	--- IDEA ---
	------------

	This one really broke my back.
	Okay, so the question is a bit complicated but fret not, we're gonna take
	things slowly.	

	Input: [ [2,9,10], [3,7,15], [5,12,12], [15,20,10], [19,24,8]]
	Output: [[2,10], [3,15], [7,12], [12,0], [15,10], [20,8], [24,0]]


	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	~~~ LET'S GO THROUGH ALL THE POINTS ~~~
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	We're at 0 firstly, our ongoing height is 0 for obvious reasons.
	So at 2, the height is 10, great! Height at 2 is greater than our ongoing
	height 0. We change ongoing height to 10 (and also add 10 to our fallback
	heights list, I'll explain what it is).

	At 3, we get another point with height 15. Now we choose between the
	ongoing height that was 10 and the new height that's 15. We choose the new
	height obviously (our ongoing height changed again, we'll add it to
	fallback list). Now the ongoing height is 15.

	we arrive at 5 where the height is 12. Ongoing height 15 is still greater
	than the new point's height 12. So we keep the height as is for now
	(but 12 is still a height to consider, so add it to fallback list).

	Then we arrive at 7, which is the end point for height 15, which means we
	need a fallback. Our ongoing height will no longer be 15. The fallback is
	chosen from other heights that we have right now. So we currently have 12
	and 10, from green and blue buildings. 12 is the greatest, so 12 becomes
	our fallback ongoing height.

	Then we arrive at 9, end point for height 10 from blue building. So, we
	cannot consider 10 as our fallback from now, since it just ended, so we'll
	remove it from our fallback height's list. The ongoing height is still 12.

	Now we arrive at 12, this is our end point for the height 12, so we need a
	fallback height. Welp, there's none since height 10 and 15 ended already.

	So, take the fallback as 0 and our ongoing height now becomes 0.


	~~~~~~~~~~~~~~~~~~
	~~~ CONCLUSION ~~~
	~~~~~~~~~~~~~~~~~~

	So what did we get? How many times did we change our ongoing height? For 2
	height was 10. For 3 height was 15. For 5, we didn't change the height, so
	15. For 7 height was 12. For 9, we didn't change the height, so 12. For 12
	we changed the height to 0.

	All the times we changed the height, that was our output:
		[2, 10], [3, 15], [7, 12], [12, 0]

	Getting it now? Yeah? Awesome!
	No? Read it again ;)


	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	~~~ HOW DOES THE CODE WORK? ~~~
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	So, since we need to consider all the points, let's create an array named
	points that will contain all the points and their heights, yeah? What we do
	here is we pair the starting point and the height but we change height
	to -ve sign so that the negative sign can help us determine whether the
	point is starting or ending one.
	We'll insert the ending point with positive height in the points array.

	Now our array is ready. Let's sort it so that we go through all the points
	sequentially, just like we did earlier but before that, we know our ongoing
	height will always start with 0.

	Let's go through all the points in points array.
	So first check if the height at the current point is negative or positive:

	If it's negative, we know it's a starting point which means we can add this
	to our fallback height list in case the ongoing height ends and we have to
	find another height to fallback on.

	If it's positive, we know that this height at current point will no longer
	be a part of our fallback height list, as this point just ended
	(positive height sign). So we can remove this from our fallback height
	list.

	What's this fallback list going to be like? Glad you asked :D

	Notice how we only pick the maximum height available from our fallback
	list?

	Wouldn't priority queue be great for creating such a list where we can
	access the maximum element easily? Hey, that's not a bad idea.

	But what about when we need to remove a height from our fallback list?
	Hmm, C++ provides no way to do it easily without increasing the time
	complexity. That's a problem.

	So what do we do? The answer is set, multiset specifically. Why multiset?
	Because in C++, multiset stores elements in increasing order, the last
	element is always the greatest and also, set in C++ lets us erase elements
	easily. So we can use multiset like a priority queue, yay!

	Why multiset and not set though? Simply because there can be multiple
	buildings with the same height, so we need to consider duplicate heights
	in our fallback list as ending one height does not mean another same
	height is not available for fallback. Got it? Great!

	Now notice that according to the sign of the current point, we either
	added it to our fallback list or removed it from our fallback list 'pq'.
	Which might mean that at the current point, either the height could
	increase or decrease to fallback but that's only possible when the ongoing
	height is not the same as the maximum height in fallback list. As ongoing
	height is the maximum height, it will exist in the fallback list at the
	same time.

	So if after inserting the height at current point in our fallback list, if
	the fallback list's maximum height has increased in case of height at
	current point being greater than ongoing height or decreased due to height
	at current point being the end of ongoing height so fallback is needed,
	what's gonna happen is we're going to change our ongoing height.

	As I said before, whenever ongoing height changes, our answer gets a new
	entry.
	So we do both:

	Set the ongoing height as the maximum height from the 'pq' multiset.
	Basically the maximum fallback height available.
	In the ans array, push currentPoint and the newly updated ongoing height
	(the new fallback height).

	That's it! We're done! Writing this took me a lot of time, so I hope you
	guys like this :)

*/

/* Time  Beats: 99.76% */
/* Space Beats: 47.52% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution {
public:
	std::vector<std::vector<int>> getSkyline(std::vector<std::vector<int>>& buildings)
	{
		std::vector<std::vector<int>> result;
		std::multiset<int> pq{0};
		
		std::vector<std::pair<int, int>> points;
		
		for(auto b: buildings)
		{
			points.push_back({b[0], -b[2]});
			points.push_back({b[1], b[2]});
		}

		std::sort(points.begin(), points.end());
		
		int on_going_height = 0;
		
		// points.first = x coordinate, points.second = height
		for(int i = 0; i < points.size(); i++)
		{
			int current_point = points[i].first;
			int height_at_current_point = points[i].second;
			
			if(height_at_current_point < 0)
				pq.insert(-height_at_current_point);
			else 
				pq.erase(pq.find(height_at_current_point));

			// After inserting/removing height At I, if there's a change
			auto pqTop = *pq.rbegin();

			if(on_going_height != pqTop)
			{
				on_going_height = pqTop;
				result.push_back({current_point, on_going_height});
			}
		}

		return result;
	}
};
