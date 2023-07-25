#include <iostream>
#include <vector>

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

	TODO
	
*/

/* Time  Beats: 95.55% */
/* Space Beats: 66.70% */

/* Time  Complexity: O(n^3) */
/* Space Complexity: O(n) */
class Solution {
public:
    int maxPoints(vector<vector<int>>& points)
	{
        int max_on_a_line = 1; 
        int n = points.size();

        // Slope of every point with selected point
        for(int i = 0; i < n - 1; i++)
		{
            std::map<double,int> map;

            for(int j = i + 1; j < n; j++)
			{
                // Calculating the slope
                double x = (double)(points[j][1] - points[i][1]) / (double)(points[j][0]-points[i][0]);

				// Infinite slop for Perpendicular line
                if((points[j][1] - points[i][1] < 0) && ((points[j][0] - points[i][0]) == 0) )
					map[abs(x)]++; 
                else
                    map[x]++; // Storing the slop into map
            }

            // Same slope w.r.t.that selected point
            int temap = 0;
            for(auto it : map)
                temap = std::max(temap, it.second+1);    // +1 for the current point(point itself)

            max_on_a_line = std::max(temap, max_on_a_line);
        }

        return max_on_a_line;
    }
};
