/*
    ============
    === HARD ===
    ============

    ===========================
    391) Perfect Rectangle
    ===========================

    ============
    Description:
    ============

    Given an array rectangles where rectangles[i] = [xi, yi, ai, bi] represents
    an axis-aligned rectangle. The bottom-left point of the rectangle is (xi,
    yi) and the top-right point of it is (ai, bi).

    Return true if all the rectangles together form an exact cover of a
    rectangular region.

    =================================================================
    FUNCTION: bool isRectangleCover(vector<vector<int>>& rectangles);
    =================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: rectangles = [[1,1,3,3],[3,1,4,2],[3,2,4,4],[1,3,2,4],[2,3,3,4]]
    Output: true
    Explanation: All 5 rectangles together form an exact cover of a rectangular
                 region.

    --- Example 2 ---
    Input: rectangles = [[1,1,2,3],[1,3,2,4],[3,1,4,2],[3,2,4,4]]
    Output: false
    Explanation: Because there is a gap between the two rectangular regions.

    --- Example 3 ---
    Input: rectangles = [[1,1,3,3],[3,1,4,2],[1,3,2,4],[2,2,4,4]]
    Output: false
    Explanation: Because two of the rectangles overlap with each other.


    *** Constraints ***
    1 <= rectangles.length <= 2 * 10^4
    rectangles[i].length == 4
    -10^5 <= xi < ai <= 10^5
    -10^5 <= yi < bi <= 10^5

*/

#include <cstdlib>
#include <map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 46.34% */
/* Space Beats: 83.26% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    bool isRectangleCover(vector<vector<int>>& rectangles)
    {
        const int N = rectangles.size();
  
        if (N == 1)
            return true;
  
        /*
           Map all points. If it is a valid rectangle, then all interior points
           should have a count of 0, however:
           + Bottom leftmost, and
           + Top    rightmost
  
           should have a value of 1.
  
           On the other hand:
           + Bottom rightmost and
           + Top    leftmost
  
           should have count -1.
  
           If it is different than this, it is NOT a perfect rectangle.
  
  */
        map<pair<int, int>, int> point_counter;
  
        for (const auto& rect : rectangles)
        {
            point_counter[ {rect[0], rect[1]} ]++;
            point_counter[ {rect[2], rect[3]} ]++;
            point_counter[ {rect[0], rect[3]} ]--;
            point_counter[ {rect[2], rect[1]} ]--;
        }
  
        int result = 0;
  
        for (auto it = point_counter.begin(); it != point_counter.end(); it++)
        {
            if (it->second != 0)
            {
                /*
                   In imperfect rectangles, overlapping corners will cause the
                   absolute value of that corner to go beyond 1.

                   So we need to prevent that.
                */
                if (abs(it->second) != 1)
                    return false;
  
                result++;
            }
        }

        return result == 4;
    }
};
