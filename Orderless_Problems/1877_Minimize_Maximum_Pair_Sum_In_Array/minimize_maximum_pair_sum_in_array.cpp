/*
    ==============
    === MEDIUM ===
    ==============

    =========================================
    1877) Minimize Maximize Pair Sum in Array
    =========================================

    ============
    Description:
    ============

    The pair sum of a pair (a,b) is equal to a + b. The maximum pair sum is the
    largest pair sum in a list of pairs.

        + For example, if we have pairs (1,5), (2,3), and (4,4), the maximum
          pair

        + sum would be max(1+5, 2+3, 4+4) = max(6, 5, 8) = 8.

    Given an array nums of even length n, pair up the elements of nums into
    n / 2 pairs such that:

        + Each element of nums is in exactly one pair, and

        + The maximum pair sum is minimized.

    Return the minimized maximum pair sum after optimally pairing up the
    elements.

    ============================================
    FUNCTION: int minPairSum(vector<int>& nums);
    ============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,5,2,3]
    Output: 7
    Explanation: The elements can be paired up into pairs (3,3) and (5,2).
    The maximum pair sum is max(3+3, 5+2) = max(6, 7) = 7.

    --- Example 2 ---
    Input: nums = [3,5,4,2,4,6]
    Output: 8
    Explanation: The elements can be paired up into pairs (3,5), (4,4), and
                 (6,2). The maximum pair sum is max(3+5, 4+4, 6+2) =
                 max(8, 8, 8) = 8.


    *** Constraints ***
    n == nums.length
    2 <= n <= 10^5
    n is even.
    1 <= nums[i] <= 10^5

*/

#include <algorithm>
#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 34.42% */
/* Space Beats: 60.30% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(logN)     */ // Because that's Space Comp. of C++'s Sort
class Solution {
public:
    int minPairSum(vector<int>& nums)
    {
        const int N = nums.size();

        /* Sort */
        sort(nums.begin(), nums.end());

        int L = 0;
        int R = N-1;

        int result = INT_MIN;
        while (L < R)
        {
            result = max(result, nums[L++] + nums[R--]);
        }

        return result;
    }
};
