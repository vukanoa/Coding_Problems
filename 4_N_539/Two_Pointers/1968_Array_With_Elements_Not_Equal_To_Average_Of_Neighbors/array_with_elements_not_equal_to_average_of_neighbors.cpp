#include <iostream>
#include <vector>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    ========================================================
    1968) Array With Elements Not Equal to Average Neighbors
    ========================================================

    ============
    Description:
    ============

    You are given a 0-indexed array nums of distinct integers. You want to
    rearrange the elements in the array such that every element in the
    rearranged array is not equal to the average of its neighbors.

    More formally, the rearranged array should have the property such that for
    every i in the range 1 <= i < nums.length - 1, (nums[i-1] + nums[i+1]) / 2
    is not equal to nums[i].

    Return any rearrangement of nums that meets the requirements.

    ========================================================
    FUNCTION: vector<int> rearrangeArray(vector<int>& nums);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,4,5]
    Output: [1,2,4,5,3]
    Explanation:
    When i=1, nums[i] = 2, and the average of its neighbors is (1+4) / 2 = 2.5.
    When i=2, nums[i] = 4, and the average of its neighbors is (2+5) / 2 = 3.5.
    When i=3, nums[i] = 5, and the average of its neighbors is (4+3) / 2 = 3.5.

    --- Example 2 ---
    Input: nums = [6,2,0,9,7]
    Output: [9,7,6,2,0]
    Explanation:
    When i=1, nums[i] = 7, and the average of its neighbors is (9+6) / 2 = 7.5.
    When i=2, nums[i] = 6, and the average of its neighbors is (7+2) / 2 = 4.5.
    When i=3, nums[i] = 2, and the average of its neighbors is (6+0) / 2 = 3.


    *** Constraints ***
    3 <= nums.length <= 105
    0 <= nums[i] <= 105

*/

/*
    ------------
    --- IDEA ---
    ------------

    Sort "nums", put smallest n/2 elements at even positions.
    Put remaining elements on the odd positions.

*/

/* Time  Beats: 45.80% */
/* Space Beats: 77.10% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1)        */ // Depending on the sort
class Solution {
public:
    std::vector<int> rearrangeArray(vector<int>& nums)
    {
        std::sort(nums.begin(), nums.end());

        int left_half = nums.size() / 2;
        left_half += nums.size() & 1 ? 1 : 0;

        std::vector<int> results(nums.size());

        int pos = 0;
        for(int i = 0; i < left_half; i++)
        {
            results[pos] = nums[i];
            pos += 2;
        }

        pos = 1;
        for (int i = left_half; i < nums.size(); i++)
        {
            results[pos] = nums[i];
            pos += 2;
        }

        return results;
    }
};



/* Time  Beats: 27.45% */
/* Space Beats: 10.49% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1)        */ // Depending on the sort
class Solution {
public:
    std::vector<int> rearrangeArray(vector<int>& nums)
    {
        std::sort(nums.begin(), nums.end());

        int left  = 0;
        int right = nums.size() - 1;

        std::vector<int> results;
        while (results.size() != nums.size())
        {
            results.push_back(nums[left++]);

            if (left <= right)
                results.push_back(nums[right--]);
        }

        return results;
    }
};





/* Time  Beats: 79.37% */
/* Space Beats: 77.10% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1)        */ // Depending on the sort
class Solution {
public:
    std::vector<int> rearrangeArray(vector<int>& nums)
    {
        int x = 0;
        int y = 1;

        for(int i = 2; i < nums.size(); i++)
        {
            if((nums[i]<nums[y] && nums[y]<nums[x]) ||
               (nums[i]>nums[y] && nums[y]>nums[x]))
            {
                std::swap(nums[i], nums[y]);
            }

            y++;
            x++;
        }
        return nums;
    }
};
