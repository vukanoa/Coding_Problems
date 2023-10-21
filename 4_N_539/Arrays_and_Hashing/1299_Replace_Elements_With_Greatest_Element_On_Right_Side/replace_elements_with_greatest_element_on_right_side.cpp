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

/* Time  Beats: 92.45% */
/* Space Beats: 55.42% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    vector<int> replaceElements(vector<int>& arr)
    {
        int n = arr.size();
        std::vector<int> dp(n, -1);

        for (int i = n-2; i >= 0; i--)
            dp[i] = std::max(arr[i+1], dp[i+1]);

        return dp;
    }
};




/* Time  Beats: 92.45% */
/* Space Beats: 48.18% */ // Somehow I cannot get better numbers than above

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    vector<int> replaceElements(vector<int>& arr)
    {
        int n = arr.size();
        int next = arr[n-1];

        for (int i = n-2; i >= 0; i--)
        {
            int tmp = arr[i];
            arr[i] = std::max(arr[i+1], next);
            next = tmp;
        }
        arr[n-1] = -1;

        return arr;
    }
};
