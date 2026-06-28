/*
    ============
    === EASY ===
    ============

    ===========================
    136) Single Number
    ===========================

    ============
    Description:
    ============

    Given a non-empty array of integers "nums", every element appears twice
    except for one. Find that single one.


    You must implement a solution with a linear runtime and use only constant
    extra space.

    ==============================================
    FUNCTION: int singleNumber(vector<int>& nums);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  nums = [2, 2, 1]
    Output: 1

    --- Example 2 ---
    Input:  nums = [4, 1, 2, 1, 2]
    Output: 4

    --- Example 3 ---
    Input:  nums = [1]
    Output: 1

    *** Constraints ***
    1 <= nums.length <= 3 * 10^4
    -3 * 10 ^ 4 <= nums[i] <= 3 * 10^4
    Each element in the array apperas twice except for one element which
      appears only once.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Just XOR all the elements.

    If you XOR something twice with the same value it's as if you haven't done
    anything, thus if we XOR all the elements in the array, we will end up with
    one that doesn't repeat.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  83.21% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int singleNumber(vector<int>& nums)
    {
        int result = 0;

        for (const int& num : nums)
            result ^= num;

        return result;
    }
};
