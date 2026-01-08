/*
    ============
    === HARD ===
    ============

    =========================================
    1458) Max Dot Product of Two Subsequences
    =========================================

    ============
    Description:
    ============

    Given two arrays nums1 and nums2.

    Return the maximum dot product between non-empty subsequences of nums1 and
    nums2 with the same length.

    A subsequence of a array is a new array which is formed from the original
    array by deleting some (can be none) of the characters without disturbing
    the relative positions of the remaining characters. (ie, [2,3,5] is a
    subsequence of [1,2,3,4,5] while [1,5,3] is not).

    ====================================================================
    FUNCTION: int maxDotProduct(vector<int>& nums1, vector<int>& nums2);
    ====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums1 = [2,1,-2,5], nums2 = [3,0,-6]
    Output: 18
    Explanation: Take subsequence [2,-2] from nums1 and subsequence [3,-6] from
                 nums2. Their dot product is (2*3 + (-2)*(-6)) = 18.

    --- Example 2 ---
    Input: nums1 = [3,-2], nums2 = [2,-6,7]
    Output: 21
    Explanation: Take subsequence [3] from nums1 and subsequence [7] from
                 nums2. Their dot product is (3*7) = 21.

    --- Example 3 ---
    Input: nums1 = [-1,-1], nums2 = [1,1]
    Output: -1
    Explanation: Take subsequence [-1] from nums1 and subsequence [1] from
                 nums2. Their dot product is -1.


    *** Constraints ***
    1 <= nums1.length, nums2.length <= 500
    -1000 <= nums1[i], nums2[i] <= 1000

*/

#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 33.60% */
/* Space Beats: 86.00% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N^2) */
class Solution {
private:
    static constexpr int NEG_INF = -1000000000;
    int memo[501][501];

public:
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2)
    {
        memset(memo, 0xff, sizeof(memo));

        return solve(0, 0, nums1, nums2);
    }

private:
    int solve(int i, int j, vector<int>& nums1, vector<int>& nums2)
    {
        const int N = nums1.size();
        const int M = nums2.size();

        if (i == N || j == M)
            return NEG_INF;

        if (memo[i][j] != -1)
            return memo[i][j];

        int take = nums1[i] * nums2[j];
        int take_continue = take + solve(i+1, j+1, nums1, nums2);
        int skip_nums1    =  0   + solve(i+1, j  , nums1, nums2);
        int skip_nums2    =  0   + solve(i  , j+1, nums1, nums2);

        return memo[i][j] = max( {take, take_continue, skip_nums1, skip_nums2} );
    }
};
