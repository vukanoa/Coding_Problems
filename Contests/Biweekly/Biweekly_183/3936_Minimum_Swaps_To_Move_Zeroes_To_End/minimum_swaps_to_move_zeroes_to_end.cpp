/*
    ============
    === EASY ===
    ============

    =========================================
    3936) Minimum Swaps to Move Zeroes to End
    =========================================

    ============
    Description:
    ============

    You are given an integer array nums.

    In one operation, you can choose any two distinct indices i and j and swap
    nums[i] and nums[j].

    Return an integer denoting the minimum number of operations required to
    move all 0s to the end of the array.

    ==============================================
    FUNCTION: int minimumSwaps(vector<int>& nums);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [0,1,0,3,12]
    Output: 2
    Explanation:
    We perform the following swap operations:
        Swap nums[0] and nums[3], giving nums = [3, 1, 0, 0, 12].
        Swap nums[2] and nums[4], giving nums = [3, 1, 12, 0, 0].
    Thus, the answer is 2.


    --- Example 2 ---
    Input: nums = [0,1,0,2]
    Output: 1
    Explanation:
    We perform the following swap operations:
        Swap nums[0] and nums[3], giving nums = [2, 1, 0, 0].
    Thus, the answer is 1.


    --- Example 3 ---
    Input: nums = [1,2,0]
    Output: 0
    Explanation:
    The array already satisfies the condition. Therefore, no swap operations
    are needed.


    *** Constraints ***
    1 <= nums.length <= 100
    0 <= nums[i] <= 100

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  57.54% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minimumSwaps(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        int L = 0;
        int R = N-1;

        while (L < R)
        {
            while (L < R && nums[R] == 0)
                R--;

            while (L < R && nums[L] != 0)
                L++;

            if (L == R)
                break;

            result++;
            L++;
            R--;
        }

        return result;
    }
};
