#include <iostream>
#include <vector>
#include <unordered_set>

/*
    ============
    === EASY ===
    ============

    ===============================
    349) Intersection of Two Arrays
    ===============================

    ============
    Description:
    ============

    Given two integer arrays nums1 and nums2, return an array of their
    intersection. Each element in the result must be unique and you may return
    the result in any order.

    (The intersection of two arrays is defined as the set of elements that are
     present in both arrays)

    ===========================================================================
    FUNCTION: vector<int> intersection(vector<int>& nums1, vector<int>& nums2);
    ===========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums1 = [1,2,2,1], nums2 = [2,2]
    Output: [2]

    --- Example 2 ---
    Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
    Output: [9,4]
    Explanation: [4,9] is also accepted.


    *** Constraints ***
    1 <= nums1.length, nums2.length <= 1000
    0 <= nums1[i], nums2[i] <= 1000

*/

/*
    ------------
    --- IDEA ---
    ------------

    1. Make a Set and fill it with elements from nums1.
    2. Iterate through nums2 and is you find current number in the Set, then
        push that number in "results" and remove it from the Set

    That's it.

    The reason we've removing it from the Set is because we don't have to have
    duplicates in the "results" vectors that we're returning.

*/

/* Time  Beats: 65.85% */
/* Space Beats: 52.55% */

/* Time  Complexity: O(n + m) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::vector<int> intersection(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        std::vector<int> results;
        std::unordered_set<int> uset(nums1.begin(), nums1.end());

        for (const int& num : nums2)
        {
            if (uset.find(num) != uset.end()) // If it exists in the Set
            {
                results.push_back(num);
                uset.erase(num);
            }
        }

        return results;
    }
};
