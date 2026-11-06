/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================
    453) Minimum Moves to Equal Array Elements
    ==========================================

    ============
    Description:
    ============

    You are given an integer array nums of size n.

    Return the minimum number of moves required to make all array elements
    equal.

    In one move, you must increment n - 1 elements of the array by 1.

    ==========================================
    FUNCTION: int minMoves(vector<int>& nums);
    ==========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3]
    Output: 3
    Explanation: Only three moves are needed (remember each move increments two elements):
    [1,2,3]  =>  [2,3,3]  =>  [3,4,3]  =>  [4,4,4]

    --- Example 2 ---
    Input: nums = [1,1,1]
    Output: 0


    *** Constraints ***
    n == nums.length
    1 <= nums.length <= 10^5
    -10^9 <= nums[i] <= 10^9
    The answer is guaranteed to fit in a 32-bit integer.

*/

#include <algorithm>
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
/* Space Beats:  56.31% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minMoves(vector<int>& nums) {
        return accumulate(nums.begin(), nums.end(), 0ll) -
                         (nums.size() * *min_element(nums.begin(), nums.end()));
    }
};
