/*
    ==============
    === MEDIUM ===
    ==============

    ======================================
    1524) Number of Subarrays With Odd Sum
    ======================================

    ============
    Description:
    ============

    Given an array of integers arr, return the number of subarrays with an odd
    sum.

    Since the answer can be very large, return it modulo 10^9 + 7.

    ===============================================
    FUNCTION: int numOfSubarrays(vector<int>& arr);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [1,3,5]
    Output: 4
    Explanation: All subarrays are [[1],[1,3],[1,3,5],[3],[3,5],[5]]
    All sub-arrays sum are [1,4,9,3,8,5].
    Odd sums are [1,9,3,5] so the answer is 4.

    --- Example 2 ---
    Input: arr = [2,4,6]
    Output: 0
    Explanation: All subarrays are [[2],[2,4],[2,4,6],[4],[4,6],[6]]
    All sub-arrays sum are [2,6,12,4,10,6].
    All sub-arrays have even sum and the answer is 0.

    --- Example 3 ---
    Input: arr = [1,2,3,4,5,6,7]
    Output: 16


    *** Constraints ***
    1 <= arr.length <= 10^5
    1 <= arr[i] <= 100

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 73.02% */
/* Space Beats: 55.17% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int numOfSubarrays(vector<int>& arr)
    {
        const int N = arr.size();
        const int MOD = 1e9 + 7;
        int result = 0;

        int curr_sum = 0;

        int even_cnt = 0;
        int odd_cnt  = 0;

        for (int i = 0; i < N; i++)
        {
            curr_sum += arr[i];

            if (curr_sum & 1) // Odd sum
            {
                result += even_cnt;
                odd_cnt++;

                result++; // Because curr_sum is ODD here
            }
            else // Even sum
            {
                result += odd_cnt;
                even_cnt++;
            }

            result %= MOD; // To prevent Overflow
        }

        return result % MOD;
    }
};
