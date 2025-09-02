/*
    ============
    === HARD ===
    ============

    ===============================================
    801) Minimum Swaps To Make Sequences Increasing
    ===============================================

    ============
    Description:
    ============

    You are given two integer arrays of the same length nums1 and nums2. In one
    operation, you are allowed to swap nums1[i] with nums2[i].

        For example, if nums1 = [1,2,3,8], and nums2 = [5,6,7,4], you can swap
        the element at i = 3 to obtain nums1 = [1,2,3,4] and nums2 = [5,6,7,8].

    Return the minimum number of needed operations to make nums1 and nums2
    strictly increasing. The test cases are generated so that the given input
    always makes it possible.

    An array arr is strictly increasing if and only if arr[0] < arr[1] < arr[2]
    < ... < arr[arr.length - 1].

    ==============================================================
    FUNCTION: int minSwap(vector<int>& nums1, vector<int>& nums2);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums1 = [1,3,5,4], nums2 = [1,2,3,7]
    Output: 1
    Explanation:
    Swap nums1[3] and nums2[3]. Then the sequences are:
    nums1 = [1, 3, 5, 7] and nums2 = [1, 2, 3, 4]
    which are both strictly increasing.


    --- Example 2 ---
    Input: nums1 = [0,3,5,8,9], nums2 = [2,1,4,6,9]
    Output: 1


    *** Constraints ***
    2 <= nums1.length <= 10^5
    nums2.length == nums1.length
    0 <= nums1[i], nums2[i] <= 2 * 10^5

*/

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 95.93% */
/* Space Beats: 82.35% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Tabulation {
public:
    int minSwap(vector<int>& nums1, vector<int>& nums2)
    {
        int N = nums1.size();
        int dp[N][2];

        for(int i = 0; i < N; i++)
        {
            dp[i][0] = INT_MAX;
            dp[i][1] = INT_MAX;
        }

        dp[0][0] = 0;
        dp[0][1] = 1;
        int prev_nums1;
        int prev_nums2;

        for(int i = 1; i < N; i++)
        {
            // Prev position swapped
            prev_nums1 = nums2[i-1];
            prev_nums2 = nums1[i-1];

            if (dp[i-1][1] != INT_MAX)
            {
                // Swap at current position
                if (nums2[i] > prev_nums1 && nums1[i] > prev_nums2)
                    dp[i][1] = 1 + dp[i-1][1];

                // No swap at current position
                if (nums1[i] > prev_nums1 && nums2[i] > prev_nums2)
                    dp[i][0] = dp[i-1][1];
            }

            // Prev position no swap
            prev_nums1 = nums1[i-1];
            prev_nums2 = nums2[i-1];
            if (dp[i-1][0] != INT_MAX)
            {
                // Swap at current position
                if (nums2[i] > prev_nums1 && nums1[i] > prev_nums2)
                    dp[i][1] = min(dp[i][1], 1 + dp[i-1][0]);

                // No swap at current position
                if (nums1[i] > prev_nums1 && nums2[i] > prev_nums2)
                    dp[i][0] = min(dp[i][0], dp[i-1][0]);
            }
        }

        return min(dp[N-1][0], dp[N-1][1]);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/
/* Time  Beats: 17.92% */
/* Space Beats: 40.80% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Memoization {
private:
    vector<vector<int>> memo;

public:
    int minSwap(vector<int>& nums1, vector<int>& nums2)
    {
        const int N = nums1.size();
        nums1.insert(nums1.begin(), -1);
        nums2.insert(nums2.begin(), -1);
        int swapped = 0; // 0 <==> false

        /* Allocate memo with the new size */
        memo.assign(N + 1, vector<int>(2, -1));

        return solve(1, swapped, nums1, nums2);
    }

private:
    int solve(int idx, int swapped, vector<int>& nums1, vector<int>& nums2)
    {
        const int N = nums1.size();

        if (idx == nums1.size())
           return 0;

        if (memo[idx][swapped] != -1)
            return memo[idx][swapped];

        int no_swap = INT_MAX;
        int do_swap = INT_MAX;

        int prev1 = nums1[idx - 1];
        int prev2 = nums2[idx - 1];

        if (swapped)
            swap(prev1, prev2);

        // NO swap
        if (nums1[idx] > prev1 && nums2[idx] > prev2)
            no_swap = 0 + solve(idx+1, 0, nums1, nums2);
        
        // INDEED swap
        if (nums1[idx] > prev2 && nums2[idx] > prev1)
            do_swap = 1 + solve(idx+1, 1, nums1, nums2);

        return memo[idx][swapped] = min(no_swap, do_swap);
    }
};
