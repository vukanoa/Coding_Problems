#include <iostream>
#include <vector>
#include <limits>

/*
	============
	=== HARD ===
	============

	===========================
	149) Max Points on a Line
	===========================

	============
	Description:
	============

	Given an array of points where points[i] = [xi, yi] represents a point on
	the X-Y plane, return the maximum number of points that lie on the same
	straight line.

	=====================================================
	FUNCTION: int maxPoints(vector<vector<int>>& points); 
	=====================================================

	==========================================================================
	================================ EXAMPLES ================================
	==========================================================================

	--- Example 1 ---

	    ^
	  5 |
	    |
	  4 |
	    |
	  3 |      x
	    |     /
	  2 |    x
	    |   /
	  1 |  x
	    |
	  0 ------------->
	       1 2 3 4 5

	Input: points = [[1,1],[2,2],[3,3]]
	Output: 3





	--- Example 2 ---

	    ^
	  5 |
	    |
	  4 |  x
	    |   \
	  3 |    x     x
	    |     \
	  2 |      x
	    |       \
	  1 |  x     x 
	    |
	  0 -------------->
	       1 2 3 4 5

	Input: points = [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
	Output: 4

	*** Constraints ***
    1 <= points.length <= 300
    points[i].length == 2
    -10^4 <= xi, yi <= 10^4
    All the points are unique.

*/

/*
	------------
	--- IDEA ---
	------------

	The very first quesiton that we need to ask is: How do we know if points
	are on the same line?

	We need the "slope" to determine that.
	
	Let's look at the very first Example:

	                    ^
	                  5 |
	                    |
	                  4 |
	                    |
	                  3 |      x
	                    |     /
	                  2 |    x
	                    |   /
	                  1 |  x
	                    |
	                  0 ------------->
	                       1 2 3 4 5


	Any two points are on the same line!
	No matter where they are located, we can always connect them via straight
	line.
	But when we introduce a third point, we have to make sure that it
	intersects the "previous" line.

	How can we know that? As we've said - We know that it has to be on the same
	slope!

	The main idea is - Slope. That's what's important.

	However, even after realizing this, we can come up with two Solutions.

		1. The less optimal one with O(n^3) Time Complexity.

		2. More optimal one with O(n^2) Time Complexity by making a simple
		   observation which can get the previous one to be more efficient.
	

	The first Solution, the O(n^3), the most brute-force one, would be to go to
	every single possible pair of points, because we knot that the pair of
	points is going to give us a slope.
	Then, once we have a slope, we go to **every other point in the grid** and
	calculate with those points.

	And if the slope already exists, meaning some 2(atleast 2) points are
	already on the same slope, then increment the number of points that are on
	that "x" slope.

	However, the problem with this approach is:
		1. We're going through every pair of points, which is one outer loop.
	
		2. We'll have another for loop, which goes through every point with
		   which we'll make a line(slope).

		3. We'll have a for loop that goes through all the rest of the points,
		   which ends up being O(n^3)
	
	So it would loop something like:
		for i to n:
			for j to n:
				for k to n:

	Which would give us O(n^3);

	So how can we fix this?
	We obviously have to have the first two for loops, it's impossible to do it
	without them, so the goal becomes - How can we remove the last inner-most
	loop?

		The answer is: Hash Map(though unordered)
	
	So now, conceptually, we're going through every single point and we're
	considering:
		Is the current point the one that is lying on the longest line?

		How do we determine that?
		For current point we're going through every other point(2nd for loop)
		and calculate the slope.

		And using **that** slope, we're going to calculate how many points are
		on the same line(slope).

	How do we calculate the slope?
	It's pretty simple:
		for i to n:
			for j to n:
				// y2 - y1 / x2 - x1
				slope = (point[j][1] - point[i][1]) / (point[j][0] - point[i][0])
	
	For our example:

	                    ^
	                  5 |
	                    |
	                  4 |
	                    |
	                  3 |      x
	                    |     /
	                  2 |    x
	                    |   /
	                  1 |  x
	                    |
	                  0 ------------->
	                       1 2 3 4 5
	
	We start on [1, 1] in the first loop, and we start from [2, 2] in the 2nd
	loop.

	The slope in this case is: 1.0

	             Hash Map
	        |  Key  :  Value |
	        +----------------|
	        |  1.0  :    1   |
	        +----------------|

	What about [1, 1] and [3, 3]? The slope is: 1.0 as well. So increment that.

	             Hash Map
	        |  Key  :  Value |
	        +----------------|
	        |  1.0  :    2   |
	        +----------------|

	Now let's say that we had an additional point at [3, 5]:

	                    ^
	                  5 |      x
	                    |
	                  4 |
	                    |
	                  3 |      x
	                    |     /
	                  2 |    x
	                    |   /
	                  1 |  x
	                    |
	                  0 ------------->
	                       1 2 3 4 5
	
	
	The slope between [1, 1] and [3, 5] would be: 2.0. Thus our HashMap is now:

	             Hash Map
	        |  Key  :  Value |
	        +----------------|
	        |  1.0  :    2   |
	        +----------------|
	        |  2.0  :    1   |
	        +----------------|

	Since we're going to go through every single point in the outer loop, we
	don't have to worry about the fact that HashMap starts value with 0 and not
	1.

	What do I mean by this?
	If we have two points on a line, the value for that slope should be 2 and
	not 1, right?
	However, the default initial value in the HashMap is 0, but since we're
	going to count that same slope twice(from both points as a starting point)
	then this doesn't pose a problem.

	So what is the greatest value over here: It's 3 and that's what we return.

	             Hash Map
	        |  Key  :  Value |
	        +----------------|
	        |  1.0  :    3   |
	        +----------------|
	        |  2.0  :    2   |
	        +----------------+
	

	However, we haven't finished the algorithm here.
	What about the points that are on the same vertical line?
		In our example: [3, 3] and [3, 5]
	
	If we would to count the slope in the same way with:
		// y2 - y1 / x2 - x1
		slope = (point[j][1] - point[i][1]) / (point[j][0] - point[i][0])
	
	We'd have a problem since our denominator would be 0.

	So in that case we're just going to use the Maximum double value(infinity)
	as a key in the HashMap.

	
	~~~~~~~~~~~~~~~
	~~~ SUMMARY ~~~
	~~~~~~~~~~~~~~~

	1. Count all points with same slope
	2. Update result with max
	3. Return result

*/

/* Time  Beats: 98.72% */
/* Space Beats: 62.28% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n) */
class Solution {
public:
	int maxPoints(std::vector<std::vector<int>>& points)
	{
		int result = 1; 
		int n = points.size();

		// Slope of every point with selected point
		for(int i = 0; i < n - 1; i++)
		{
			std::unordered_map<double, int> count;

			for(int j = i + 1; j < n; j++)
			{
				double slope;

				if (points[j][0] == points[i][0])
					slope = DBL_MAX;
				else
					slope = (double)(points[j][1] - points[i][1]) / (double)(points[j][0] - points[i][0]);

				count[slope]++;

				result = std::max(result, count[slope] + 1); // Because initially it should be 1
			}
		}

			return result;
	}
};
