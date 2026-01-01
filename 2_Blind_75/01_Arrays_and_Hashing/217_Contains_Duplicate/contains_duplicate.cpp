/*
    ============
    === EASY ===
    ============

    ===========================
    217) Contains Duplicate
    ===========================

    ============
    Description:
    ============

    Given an integer array nums, return true if any value appears at least
    twice in the array, and return false if every element is distinct.

    ====================================================
    FUNCTION: bool containsDuplicate(vector<int>& nums);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1, 2, 3, 1]
    Output: true

    --- Example 2 ---
    Input: nums = [1, 2, 3, 4]
    Output: false

    --- Example 3 ---
    Input: nums = [1, 1, 1, 3, 3, 4, 3, 2, 4, 2]
    Output: true

    *** Constraints ***
    1 <= nums.length <= 105
    -109 <= nums[i] <= 109

*/

#include <vector>
#include <unordered_set>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Simply check if the current element has already been seen. We're achieving
    that by using a HashSet(unordered).

*/

/* Time  Beats: 73.85% */
/* Space Beats: 73.85% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    bool containsDuplicate(vector<int>& nums)
    {
        const int N = nums.size();

        unordered_set<int> seen;

        // O(N) (entire-block)
        for (const int& num : nums) // O(N)
        {
            if (seen.count(num)) // O(1) Average-case
                return true;

            seen.insert(num); // O(1) Amortized due to rehashing
        }

        return false;
    }
};
