#include <iostream>
#include <vector>

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

/*
    ------------
    --- IDEA ---
    ------------

    Two Pointers Technique.
    "left" points to the very first element and "right" points to the very last
    element, at the beginning of while loop.

    Since we are looking for max area, that means it's a rectangle. The formula
    for calculating area of a rectangle is: width * height.

    Width, in this case is the difference between positions in the array:
        right - left

    We will denote it as "distance" in the code.

    And height is the height of the shorter bar, since that determines how many
    water can be trapped.

    Multiplying these two values will give us the area.

    Since we are using a "Two Pointer Technique", we only move either left or
    right pointer. ("left" one step forward or "right" one step backward)

    How do we decide which pointer to move? We always move the shorter one.
    Why?
    Because if we were to move a taller one then that area certainly won't be
    larger than the previous, thus we won't find Max Area.

    So always move the shorter one.
    Repeat this until "left" pointer exceeds the "right" pointer.

*/

/* Time  Beats: 91.98% */
/* Space Beats: 26.01% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maxArea(std::vector<int>& height)
    {
        int left = 0;
        int right = height.size() - 1;

        int max_area = 0;

        while (left < right)
        {
            int shorter_bar = std::min(height[left], height[right]);
            int distance    = right - left;

            max_area = std::max(max_area, shorter_bar * distance);

            if (height[left] <= height[right])
                left++;
            else
                right--;
        }

        return max_area;
    }
};


int
main()
{
    Solution sol;

    /* Example 1 */
    std::vector<int> height = {1, 8, 6, 2, 4, 3, 8, 3, 7};

    /* Example 2 */
    // std::vector<int> height = {1, 1};

    /* Example 3 */
    // std::vector<int> height = {3, 2, 1, 2, 8, 3, 9, 3, 5};

    /* Example 4 */
    // std::vector<int> height = {3, 2, 1, 2, 8, 3, 9, 1, 1};

    /* Example 5 */
    // std::vector<int> height = {1, 1, 1, 1, 1, 9, 2, 1, 9};

    /* Example 6 */
    // std::vector<int> height = {1, 2};


    std::cout << "\n\t================";
    std::cout << "\n\t=== MAX AREA ===";
    std::cout << "\n\t================\n";

    bool first = true;
    std::cout << "\n\tHeights: [";
    for (const auto& x: height)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n";

    int max_area = sol.maxArea(height);
    std::cout << "\n\tMax area is: " << max_area << "\n\n";

    return 0;
}
