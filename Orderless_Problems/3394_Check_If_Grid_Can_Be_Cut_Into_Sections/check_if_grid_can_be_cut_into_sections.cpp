/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    3394) Check if Grid can be Cut into Sections
    ============================================

    ============
    Description:
    ============

    You are given an integer n representing the dimensions of an n x n grid,
    with the origin at the bottom-left corner of the grid. You are also given
    a 2D array of coordinates rectangles, where rectangles[i] is in the form
    [startx, starty, endx, endy], representing a rectangle on the grid.

    Each rectangle is defined as follows:

        (startx, starty): The bottom-left corner of the rectangle.
        (endx, endy): The top-right corner of the rectangle.

    Note that the rectangles do not overlap. Your task is to determine if it is
    possible to make either two horizontal or two vertical cuts on the grid
    such that:

        + Each of the three resulting sections formed by the cuts contains at
          least one rectangle.

        + Every rectangle belongs to exactly one section.

    Return true if such cuts can be made; otherwise, return false.

    ======================================================================
    FUNCTION: bool checkValidCuts(int n, vector<vector<int>>& rectangles);
    ======================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 5, rectangles = [[1,0,5,2],[0,2,2,4],[3,2,5,3],[0,4,4,5]]
    Output: true
    Explanation: The grid is shown in the diagram. We can make horizontal cuts
                 at y = 2 and y = 4. Hence, output is true.


    --- Example 2 ---
    Input: n = 4, rectangles = [[0,0,1,1],[2,0,3,4],[0,2,2,3],[3,0,4,3]]
    Output: true
    Explanation: We can make vertical cuts at x = 2 and x = 3. Hence, output is
                 true.


    --- Example 3 ---
    Input: n = 4, rectangles = [[0,2,2,4],[1,0,3,2],[2,2,3,4],[3,0,4,2],[3,2,4,4]]
    Output: false
    Explanation: We cannot make two horizontal or two vertical cuts that
                 satisfy the conditions. Hence, output is false.


    *** Constraints ***
    3 <= n <= 10^9
    3 <= rectangles.length <= 10^5
    0 <= rectangles[i][0] < rectangles[i][2] <= n
    0 <= rectangles[i][1] < rectangles[i][3] <= n
    No two rectangles overlap.

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Atypical Line-Sweep approach. You do NOT have to know Line-Sweep in order
    to come up with this Solution.

*/

/* Time  Beats: 76.15% */
/* Space Beats: 98.03% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(logn)     */ // Because of std::sort
class Solution {
public:
    bool checkValidCuts(int n, vector<vector<int>>& rectangles)
    {
        return checkCuts(rectangles, 0) ||  // Horizontal
               checkCuts(rectangles, 1);    // Vertical
    }

private:
    // Check if valid cuts can be made in a specific dimension (0 - Hor, 1 - Ver)
    bool checkCuts(vector<vector<int>>& rectangles, int dimension)
    {
        const int M = rectangles.size();

        auto comparator = [dimension](const vector<int>& a, const vector<int>& b) {
            return a[dimension] < b[dimension];
        };
        // Sort rectangles by their starting coordinate in the given dimension
        sort(rectangles.begin(), rectangles.end(), comparator);


        int gap_count = 0;
        int furthest_end = rectangles[0][dimension + 2]; // +2 is corresponding end

        for (int i = 1; i < M; i++)
        {
            const vector<int>& rect = rectangles[i];

            // If current rectangle starts after the furthest end we've seen,
            // we found a gap where a cut can be made
            if (furthest_end <= rect[dimension])
                gap_count++;

            // Update the furthest ending coordinate
            furthest_end = max(furthest_end, rect[dimension + 2]);
        }

        // We need at least 2 gaps to create 3 sections
        return gap_count >= 2;
    }
};
