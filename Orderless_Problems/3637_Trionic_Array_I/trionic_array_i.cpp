/*
    ============
    === EASY ===
    ============

    ===========================
    3637) Trionic Array I
    ===========================

    ============
    Description:
    ============

    You are given an integer array nums of length n.

    An array is trionic if there exist indices 0 < p < q < n − 1 such that:

        nums[0...p] is strictly increasing,
        nums[p...q] is strictly decreasing,
        nums[q...n − 1] is strictly increasing.

    Return true if nums is trionic, otherwise return false.

    ============================================
    FUNCTION: bool isTrionic(vector<int>& nums);
    ============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,3,5,4,2,6]
    Output: true
    Explanation:
    Pick p = 2, q = 4:
        nums[0...2] = [1, 3, 5] is strictly increasing (1 < 3 < 5).
        nums[2...4] = [5, 4, 2] is strictly decreasing (5 > 4 > 2).
        nums[4...5] = [2, 6] is strictly increasing (2 < 6).

    --- Example 2 ---
    Input: nums = [2,1,3]
    Output: false
    Explanation:
    There is no way to pick p and q to form the required three segments.


    *** Constraints ***
    3 <= n <= 100
    -1000 <= nums[i] <= 1000

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  96.31% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool isTrionic(vector<int>& nums)
    {
        const int N = nums.size();

        int i = 1;
        while (i < N && nums[i - 1] < nums[i])
            i++;

        int p = i - 1;
        while (i < N && nums[i - 1] > nums[i])
            i++;

        int q = i - 1;
        while (i < N && nums[i - 1] < nums[i])
            i++;

        int flag = i - 1;
        return (p != 0) && (q != p) && (flag == N - 1 && flag != q);
    }
};
