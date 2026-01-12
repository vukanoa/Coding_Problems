/*
    ==============
    === MEDIUM ===
    ==============

    =============================
    11) Container With Most Water
    =============================

    ============
    Description:
    ============

    You are given an integer array height of length n. There are n vertical
    lines drawn such that the two endpoints of the i-th line are (i, 0) and
    (i, height[i]).

    Find two lines that together with the x-axis form a container, such that
    the container contains the most water.

    Return the maximum amount of water a container can store.

    =====
    Node: Notice that you may not slant the container.
    =====

    ===========================================
    FUNCTION: int maxArea(vector<int>& height);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---

    8     #              #
    7     #~~~~~~~~~~~~~~#~~~~~#
    6     #  #           #     #
    5     #  #     #     #     #
    4     #  #     #  #  #     #
    3     #  #     #  #  #  #  #
    2     #  #  #  #  #  #  #  #
    1  #  #  #  #  #  #  #  #  #
    0  #  #  #  #  #  #  #  #  #

    Input: height = [1, 8, 6, 2, 5, 4, 8, 3, 7]
    Output: 49
    Explanation: The above vertical lines are represented by array:
    [1, 8, 6, 2, 4, 3, 8, 3, 7]

    --- Example 2 ---
    Input: height = [1, 1]
    Output: 1

    *** Constraints ***
    n == height.length
    2 <= n <= 10^5
    0 <= height[i] <= 10^4
*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Two Pointers Technique.
    "L" points to the very first element and "R" points to the very last
    element, at the beginning of while loop.

    Since we are looking for max area, that means it's a rectangle. The formula
    for calculating area of a rectangle is: width * height.

    Width, in this case is the difference between positions in the array:

        R - L

    We will denote it as "distance" in the code.
    And height is the height of the shorter_line.

    Multiplying these two values will give us the area.

    Since we are using a "Two Pointer Technique", we only move either L or
    R pointer. ("L" one step forward or "R" one step backward)

    How do we decide which pointer to move?
    We always move the shorter one.

    Why?

    Because if we were to move a taller one then that area certainly won't be
    larger than the previous, because the area is ALWAYS determined by the
    SHORTER_LINE!

    So always move the shorter one, that's it.

    Repeat this until "L" and "R" pointer aren't pointing at the same line.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  77.30% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maxArea(vector<int>& height)
    {
        const int N = height.size();
        int result = 0;

        int L = 0;
        int R = N-1;

        // O(N) (entire block)
        while (L < R)
        {
            int shorter_line = min(height[L], height[R]);
            int distance = R - L;

            int current_area = distance * shorter_line;

            result = max(result, current_area); // O(1)

            if (height[L] <= height[R])
                L++;
            else
                R--;
        }

        return result;
    }
};
