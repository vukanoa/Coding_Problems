/*
    ==============
    === MEDIUM ===
    ==============

    ===========================================================
    3047) Find the Largest Area of Square Inside Two Rectangles
    ===========================================================

    ============
    Description:
    ============


    There exist n rectangles in a 2D plane with edges parallel to the x and y
    axis. You are given two 2D integer arrays bottomLeft and topRight where
    bottomLeft[i] = [a_i, b_i] and topRight[i] = [c_i, d_i] represent the
    bottom-left and top-right coordinates of the ith rectangle, respectively.

    You need to find the maximum area of a square that can fit inside the
    intersecting region of at least two rectangles. Return 0 if such a square
    does not exist.

    ======================================================================================================
    FUNCTION: long long largestSquareArea(vector<vector<int>>& bottomLeft, vector<vector<int>>& topRight);
    ======================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: bottomLeft = [[1,1],[2,2],[3,1]], topRight = [[3,3],[4,4],[6,6]]
    Output: 1
    Explanation: A square with side length 1 can fit inside either the
                 intersecting region of rectangles 0 and 1 or the intersecting
                 region of rectangles 1 and 2. Hence the maximum area is 1. It
                 can be shown that a square with a greater side length can not
                 fit inside any intersecting region of two rectangles.

    --- Example 2 ---
    Input: bottomLeft = [[1,1],[1,3],[1,5]], topRight = [[5,5],[5,7],[5,9]]
    Output: 4
    Explanation: A square with side length 2 can fit inside either the
                 intersecting region of rectangles 0 and 1 or the intersecting
                 region of rectangles 1 and 2. Hence the maximum area is
                 2 * 2 = 4. It can be shown that a square with a greater side
                 length can not fit inside any intersecting region of two
                 rectangles.

    --- Example 3 ---
    Input: bottomLeft = [[1,1],[2,2],[1,2]], topRight = [[3,3],[4,4],[3,4]]
    Output: 1
    Explanation: A square with side length 1 can fit inside the intersecting
                 region of any two rectangles. Also, no larger square can, so
                 the maximum area is 1. Note that the region can be formed by
                 the intersection of more than 2 rectangles.

    --- Example 3 ---
    Input: bottomLeft = [[1,1],[3,3],[3,1]], topRight = [[2,2],[4,4],[4,2]]
    Output: 0
    Explanation:
    No pair of rectangles intersect, hence, the answer is 0.


    *** Constraints ***
    n == bottomLeft.length == topRight.length
    2 <= n <= 10^3
    bottomLeft[i].length == topRight[i].length == 2
    1 <= bottomLeft[i][0], bottomLeft[i][1] <= 10^7
    1 <= topRight[i][0], topRight[i][1] <= 10^7
    bottomLeft[i][0] < topRight[i][0]
    bottomLeft[i][1] < topRight[i][1]

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Simple brute-force solution.

*/

/* Time  Beats: 81.51% */
/* Space Beats: 15.97% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(1)   */
class Solution {
public:
    long long largestSquareArea(vector<vector<int>>& nums1, vector<vector<int>>& nums2)
    {
        const int N = nums1.size();
        const int M = nums2.size();

        long long area = 0;

        for (int i = 0; i < N; i++)
        {
            for (int j = i+1; j < M; j++)
            {
                long long min_x = max(nums1[i][0], nums1[j][0]);
                long long max_x = min(nums2[i][0], nums2[j][0]);

                long long min_y = max(nums1[i][1], nums1[j][1]);
                long long max_y = min(nums2[i][1], nums2[j][1]);

                if (min_x < max_x && min_y < max_y)
                {
                    long long min_side = min(max_x - min_x, max_y - min_y);
                    area = max(area, min_side * min_side);
                }
            }
        }

        return area;
    }
};
