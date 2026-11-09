/*
    ============
    === EASY ===
    ============

    ==============================================================
    3774) Absolute Difference Between Maximum and Minimum Elements
    ==============================================================

    ============
    Description:
    ============

    You are given an integer array nums and an integer k.

    Find the absolute difference between:

        the sum of the k largest elements in the array; and
        the sum of the k smallest elements in the array.

    Return an integer denoting this difference.

    ======================================================
    FUNCTION: int absDifference(vector<int>& nums, int k);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [5,2,2,4], k = 2
    Output: 5
    Explanation:
        The k = 2 largest elements are 4 and 5. Their sum is 4 + 5 = 9.
        The k = 2 smallest elements are 2 and 2. Their sum is 2 + 2 = 4.
        The absolute difference is abs(9 - 4) = 5.

    --- Example 2 ---
    Input: nums = [100], k = 1
    Output: 0
    Explanation:
        The largest element is 100.
        The smallest element is 100.
        The absolute difference is abs(100 - 100) = 0.


    *** Constraints ***
    1 <= n == nums.length <= 100
    1 <= nums[i] <= 100
    1 <= k <= n

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 27.36% */
/* Space Beats: 15.49% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(1)        */
class Solution {
public:
    int absDifference(vector<int>& nums, int k)
    {
        const int N = nums.size();

        sort(nums.begin(), nums.end());

        int smallest = 0;
        int largest  = 0;
        for (int i = 0; i < k; i++)
        {
            smallest += nums[i];
            largest  += nums[N-1 - i];
        }

        return abs(smallest - largest);
    }
};
