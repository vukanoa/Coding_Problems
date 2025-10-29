/*
    ============
    === EASY ===
    ============

    =====================================================
    1013) Partition Array Into Three Parts With Equal Sum
    =====================================================

    ============
    Description:
    ============

    Given an array of integers arr, return true if we can partition the array
    into three non-empty parts with equal sums.

    Formally, we can partition the array if we can find indexes i + 1 < j with
    (arr[  0  ] + arr[  1  ] + ... + arr[i]     ==
     arr[i + 1] + arr[i + 2] + ... + arr[j - 1] ==
     arr[  j  ] + arr[j + 1] + ... + arr[arr.length - 1])

    =======================================================
    FUNCTION: bool canThreePartsEqualSum(vector<int>& arr);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [0,2,1,-6,6,-7,9,1,2,0,1]
    Output: true
    Explanation: 0 + 2 + 1 = -6 + 6 - 7 + 9 + 1 = 2 + 0 + 1

    --- Example 2 ---
    Input: arr = [0,2,1,-6,6,7,9,-1,2,0,1]
    Output: false

    --- Example 3 ---
    Input: arr = [3,3,6,5,-2,2,5,1,-9,4]
    Output: true
    Explanation: 3 + 3 = 6 = 5 - 2 + 2 + 5 + 1 - 9 + 4

    *** Constraints ***
    3 <= arr.length <= 5 * 10^4
    -104 <= arr[i] <= 10^4

*/

#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  11.10% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool canThreePartsEqualSum(vector<int>& arr)
    {
        const int N = arr.size();

        int total_sum = accumulate(arr.begin(), arr.end(), 0);

        if (total_sum % 3 != 0)
            return false;

        int target = total_sum / 3;
        int curr_sum = 0;
        int count = 0;

        for (int i = 0; i < N-1; i++)
        {
            curr_sum += arr[i];

            if (curr_sum == target)
            {
                curr_sum = 0;
                count++;

                if (count == 2)
                    return true;
            }
        }

        return false;
    }
};
