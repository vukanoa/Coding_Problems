#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ==================================
    350) Intersection of Two Arrays II
    ==================================

    ============
    Description:
    ============

    Given two integer arrays nums1 and nums2, return an array of their
    intersection. Each element in the result must appear as many times as it
    shows in both arrays and you may return the result in any order.

    ========================================================================
    FUNCTION: vector<int> intersect(vector<int>& nums1, vector<int>& nums2);
    ========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums1 = [1,2,2,1], nums2 = [2,2]
    Output: [2,2]

    --- Example 2 ---
    Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
    Output: [4,9]
    Explanation: [9,4] is also accepted.


    *** Constraints ***
    1 <= nums1.length, nums2.length <= 1000
    0 <= nums1[i], nums2[i] <= 1000

*/

/*
    ------------
    --- IDEA ---
    ------------

    Intuitive.

*/

/* Time  Beats: 100.00% */
/* Space Beats: 44.72% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::vector<int> intersect(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        std::vector<int> freq1(1001, 0);
        std::vector<int> freq2(1001, 0);

        std::vector<int> result;

        for (const int& num1 : nums1)
            freq1[num1]++;

        for (const int& num2 : nums2)
            freq2[num2]++;

        for (int num = 0; num <= 1000; num++)
        {
            int min_freq = std::min(freq1[num], freq2[num]);

            while (min_freq-- > 0)
                result.push_back(num);
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is an improved version of the above approach.

*/

/* Time  Beats: 81.88% */
/* Space Beats: 34.02% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_2 {
public:
    std::vector<int> intersect(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        std::vector<int> result;
        std::unordered_map<int,int> umap;

        for(const int& num : nums1)
            umap[num]++;

        for(const int& num : nums2)
        {
            if(umap.find(num) != umap.end() && umap[num] > 0)
            {
                result.push_back(num);
                umap[num]--;
            }
        }

        return result;
    }
};
