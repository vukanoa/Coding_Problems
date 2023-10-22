#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ===================================================
    2001) Number of Pairs of Interchangeable Rectangles
    ===================================================

    ============
    Description:
    ============

    You are given n rectangles represented by a 0-indexed 2D integer array
    rectangles, where rectangles[i] = [widthi, heighti] denotes the width and
    height of the ith rectangle.

    Two rectangles i and j (i < j) are considered interchangeable if they have
    the same width-to-height ratio. More formally, two rectangles are
    interchangeable if widthi/heighti == widthj/heightj (using decimal
    division, not integer division).

    Return the number of pairs of interchangeable rectangles in rectangles.


    ===============================================================================
    FUNCTION: long long interchangeableRectangles(vector<vector<int>>& rectangles);
    ===============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: rectangles = [[4,8],[3,6],[10,20],[15,30]]
    Output: 6
    Explanation: The following are the interchangeable pairs of rectangles by
                 index (0-indexed):
    - Rectangle 0 with rectangle 1: 4/8 == 3/6.
    - Rectangle 0 with rectangle 2: 4/8 == 10/20.
    - Rectangle 0 with rectangle 3: 4/8 == 15/30.
    - Rectangle 1 with rectangle 2: 3/6 == 10/20.
    - Rectangle 1 with rectangle 3: 3/6 == 15/30.
    - Rectangle 2 with rectangle 3: 10/20 == 15/30.



    --- Example 2 ---
    Input: rectangles = [[4,5],[7,8]]
    Output: 0
    Explanation: There are no interchangeable pairs of rectangles.



    *** Constraints ***
    n == rectangles.length
    1 <= n <= 10^5
    rectangles[i].length == 2
    1 <= widthi, heighti <= 10^5

*/

/* Time  Beats: 76.51% */
/* Space Beats: 47.57% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    long long interchangeableRectangles(std::vector<std::vector<int>>& rectangles)
    {
        std::unordered_map<double, int> umap;

        for (int i = 0; i < rectangles.size(); i++)
        {
            double ratio = rectangles[i][0] * 1.0 / rectangles[i][1];

            if (umap.count(ratio) == 0)
                umap.insert({ratio, 1});
            else
                umap[ratio]++;
        }

        unsigned long long result = 0;
        for (auto& entry : umap)
        {
            if (entry.second > 1)
                result += ((unsigned long long)entry.second * (unsigned long long)(entry.second - 1)) / 2;
        }

        return result;
    }
};
