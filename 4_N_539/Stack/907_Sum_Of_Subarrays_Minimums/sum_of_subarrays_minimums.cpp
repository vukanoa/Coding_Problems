#include <iostream>
#include <vector>
#include <stack>

/*
    ==============
    === MEDIUM ===
    ==============

    =============================
    907) Sum of Subarray Minimums
    =============================

    ============
    Description:
    ============

    Given an array of integers arr, find the sum of min(b), where b ranges over
    every (contiguous) subarray of arr. Since the answer may be large, return
    the answer modulo 109 + 7.

    ================================================
    FUNCTION: int sumSubarrayMins(vector<int>& arr);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [3,1,2,4]
    Output: 17
    Explanation:
    Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4], [3,1,2,4].
    Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1.
    Sum is 17.

    --- Example 2 ---
    Input: arr = [11,81,94,43,3]
    Output: 444


    *** Constraints ***
    1 <= arr.length <= 3 * 10^4
    1 <= arr[i] <= 3 * 10^4

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 62.93% */
/* Space Beats: 18.96% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int sumSubarrayMins(vector<int>& arr)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        stack<pair<int, int>> in_stk_prev;
        stack<pair<int, int>> in_stk_next;

        // Left is for the distance to previous less element
        // Right is for the distance to next less element
        vector<int> left(arr.size()), right(arr.size());

        // Initialize
        for (int i = 0; i < arr.size(); i++)
            left[i] =  i + 1;

        for (int i = 0; i < arr.size(); i++)
            right[i] = arr.size() - i;

        for (int i = 0; i < arr.size(); i++)
        {
            // For previous less
            while ( ! in_stk_prev.empty() && in_stk_prev.top().first > arr[i])
                in_stk_prev.pop();

            left[i] = in_stk_prev.empty() ? i + 1: i - in_stk_prev.top().second;
            in_stk_prev.push({arr[i],i});

            // For next less
            while ( ! in_stk_next.empty() && in_stk_next.top().first > arr[i])
            {
                auto x = in_stk_next.top();
                in_stk_next.pop();

                right[x.second] = i - x.second;
            }

            in_stk_next.push({arr[i], i});
        }

        unsigned long long result = 0;
        unsigned long long mod = 1e9 +7;

        for (int i = 0; i < arr.size(); i++)
            result = (result + static_cast<unsigned long long>(arr[i]) * left[i] * right[i]) % mod;


        return result % mod;
    }
};
