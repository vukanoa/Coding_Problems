#include <iostream>

/*
    ============
    === EASY ===
    ============

    =======================================
    2215) Find the Difference of Two Arrays
    =======================================

    ============
    Description:
    ============

    Given two 0-indexed integer arrays nums1 and nums2, return a list answer of
    size 2 where:

        answer[0] is a list of all distinct integers in nums1 which are not
        present in nums2.  answer[1] is a list of all distinct integers in
        nums2 which are not present in nums1.

    Note that the integers in the lists may be returned in any order.

    =====================================================================================
    FUNCTION: vector<vector<int>> findDifference(vector<int>& nums1, vector<int>& nums2);
    =====================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums1 = [1,2,3], nums2 = [2,4,6]
    Output: [[1,3],[4,6]]
    Explanation:
    For nums1, nums1[1] = 2 is present at index 0 of nums2, whereas nums1[0] =
    1 and nums1[2] = 3 are not present in nums2. Therefore, answer[0] = [1,3].

    For nums2, nums2[0] = 2 is present at index 1 of nums1, whereas nums2[1] =
    4 and nums2[2] = 6 are not present in nums2. Therefore, answer[1] = [4,6].



    --- Example 2 ---
    Input: nums1 = [1,2,3,3], nums2 = [1,1,2,2]
    Output: [[3],[]]
    Explanation:
    For nums1, nums1[2] and nums1[3] are not present in nums2.
    Since nums1[2] == nums1[3], their value is only included once and
    answer[0] = [3].  Every integer in nums2 is present in nums1. Therefore:
    answer[1] = [].



    *** Constraints ***
    1 <= nums1.length, nums2.length <= 1000
    -1000 <= nums1[i], nums2[i] <= 1000

*/

/* Time  Beats: 94.82% */
/* Space Beats: 60.48% */

/* Time  Complexity: O(m + n) */
/* Space Complexity: O(m + n) */
class Solution {
public:
    std::vector<std::vector<int>> findDifference(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        std::unordered_set<int> uset1;
        std::unordered_set<int> uset2;

        for (int& num1 : nums1)
            uset1.insert(num1);

        for (int& num2: nums2)
            uset2.insert(num2);

        std::vector<std::vector<int>> answer(2);
        for (auto& num1 : uset1)
        {
            if (uset2.count(num1) == 0) // Doesn't exist in Set_2
                answer[0].push_back(num1);
        }

        for (auto& num2 : uset2)
        {
            if (uset1.count(num2) == 0)
                answer[1].push_back(num2);
        }

        return answer;
    }
};
