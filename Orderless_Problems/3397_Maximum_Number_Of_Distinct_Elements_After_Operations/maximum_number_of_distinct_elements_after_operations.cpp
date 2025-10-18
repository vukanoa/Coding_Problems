/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================================
    3397) Maximum Number of Distinct Elements After Operations
    ==========================================================

    ============
    Description:
    ============

    You are given an integer array nums and an integer k.

    You are allowed to perform the following operation on each element of the
    array at most once:

        + Add an integer in the range [-k, k] to the element.

    Return the maximum possible number of distinct elements in nums after
    performing the operations.

    ============================================================
    FUNCTION: int maxDistinctElements(vector<int>& nums, int k);
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,2,3,3,4], k = 2
    Output: 6
    Explanation:
    nums changes to [-1, 0, 1, 2, 3, 4] after performing operations on the
    first four elements.

    --- Example 2 ---
    Input: nums = [4,4,4,4], k = 1
    Output: 3
    Explanation:
    By adding -1 to nums[0] and 1 to nums[1], nums changes to [3, 5, 4, 4].


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^9
    0 <= k <= 10^9

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

/* Time  Beats: 91.75% */
/* Space Beats: 68.89% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(logN)     */ // Because of C++'s Intro Sort
class Solution {
public:
    int maxDistinctElements(vector<int>& nums, int k)
    {
        const int N = nums.size();

        if ((2*k + 1) >= N)
            return N; // N Distinct numbers

        int result = 0;

        // O(N * logN)
        sort(nums.begin(), nums.end());

        long long last = INT_MIN;
        for (int i = 0; i < N; i++)
        {
            long long take = max(1LL * nums[i] - k, last);

            if (take <= nums[i] + k)
            {
                last = take+1;
                result++;
            }
        }

        return result;
    }
};
