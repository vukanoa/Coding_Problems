#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ==========================================================
    1299) Replace Elements with Greatest Element on Right Side
    ==========================================================

    ============
    Description:
    ============

    Given an array arr, replace every element in that array with the greatest
    element among the elements to its right, and replace the last element with
    -1.

    After doing so, return the array.

    ========================================================
    FUNCTION: vector<int> replaceElements(vector<int>& arr);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [17,18,5,4,6,1]
    Output: [18,6,6,6,1,-1]
    Explanation:
    - index 0 --> the greatest element to the right of index 0 is index 1 (18).
    - index 1 --> the greatest element to the right of index 1 is index 4 (6).
    - index 2 --> the greatest element to the right of index 2 is index 4 (6).
    - index 3 --> the greatest element to the right of index 3 is index 4 (6).
    - index 4 --> the greatest element to the right of index 4 is index 5 (1).
    - index 5 --> there are no elements to the right of index 5, so we put -1.


    --- Example 2 ---
    Input: arr = [400]
    Output: [-1]
    Explanation: There are no elements to the right of index 0.



    *** Constraints ***
    1 <= arr.length <= 10^4
    1 <= arr[i] <= 10^5

*/



/*
    ------------
    --- IDEA ---
    ------------

    One of the most basic uses of Dynamic Programming. Instead of calculating
    the max element to the right of every position "manually" and "repeatedly"
    we memorize the result of the previous(right one) and use that to determine
    the new maximum.

    That way we do it in O(n) instead of O(n^2).

*/

/* Time  Beats: 92.45% */
/* Space Beats: 55.42% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::vector<int> replaceElements(std::vector<int>& arr)
    {
        int n = arr.size();
        std::vector<int> dp(n, -1);

        for (int i = n-2; i >= 0; i--)
            dp[i] = std::max(arr[i+1], dp[i+1]);

        return dp;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Idea equivalent as above, however we can notice that we don't need to use
    a whole vector "dp" because at each index 'i' we are iterating, we only use
    the dp[i+1], therefore, we don't need to keep an entire vector, but a
    single variable. We'll call it dp_next;

*/

/* Time  Beats: 100.00% */
/* Space Beats:  18.42% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Space_Efficient {
public:
    std::vector<int> replaceElements(std::vector<int>& arr)
    {
        const int n = arr.size();
        vector<int> result(n);

        int dp = -1;
        for (int i = n-1; i >= 0; i--)
        {
            result[i] = dp;
            dp = max(dp, arr[i]);
        }

        return
    }
};
