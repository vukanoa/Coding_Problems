#include <iostream>
#include <vector>
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    ================================================================================
    1438) Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit
    ================================================================================

    ============
    Description:
    ============

    Given an array of integers nums and an integer limit, return the size of
    the longest non-empty subarray such that the absolute difference between
    any two elements of this subarray is less than or equal to limit.

    ============================================================
    FUNCTION: int longestSubarray(vector<int>& nums, int limit);
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [8,2,4,7], limit = 4
    Output: 2 
    Explanation: All subarrays are: 
    [8] with maximum absolute diff |8-8| = 0 <= 4.
    [8,2] with maximum absolute diff |8-2| = 6 > 4. 
    [8,2,4] with maximum absolute diff |8-2| = 6 > 4.
    [8,2,4,7] with maximum absolute diff |8-2| = 6 > 4.
    [2] with maximum absolute diff |2-2| = 0 <= 4.
    [2,4] with maximum absolute diff |2-4| = 2 <= 4.
    [2,4,7] with maximum absolute diff |2-7| = 5 > 4.
    [4] with maximum absolute diff |4-4| = 0 <= 4.
    [4,7] with maximum absolute diff |4-7| = 3 <= 4.
    [7] with maximum absolute diff |7-7| = 0 <= 4. 
    Therefore, the size of the longest subarray is 2.


    --- Example 2 ---
    Input: nums = [10,1,2,4,7,2], limit = 5
    Output: 4 
    Explanation: The subarray [2,4,7,2] is the longest since the maximum
    absolute diff is |2-7| = 5 <= 5.


    --- Example 3 ---
    Input: nums = [4,2,2,2,4,4,2,2], limit = 0
    Output: 3


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^9
    0 <= limit <= 10^9

*/

/*
    ------------
    --- IDEA ---
    ------------
    
    TODO

*/

/* Time  Beats: 37.05% */
/* Space Beats: 17.55% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(1) */
class Solution_Sliding_Window_Plus_Multiset {
public:
    int longestSubarray(std::vector<int>& nums, int limit)
    {
        std::multiset<int, std::greater<int>> multi_set;

        int longest = 0;

        int left  = 0;
        int right = 0;

        while (right < nums.size())
        {
            multi_set.insert(nums[right]);

            int largest  = *multi_set.begin();
            int smallest = *multi_set.rbegin();

            while (std::abs(largest - smallest) > limit)
            {
                multi_set.erase(multi_set.find(nums[left]));

                left++;
                largest  = *multi_set.begin();
                smallest = *multi_set.rbegin();
            }

            longest = std::max(longest, right - left + 1);

            right++; // Extend the window
        }

        return longest;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 99.83% */
/* Space Beats: 59.41% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Efficient {
public:
    int longestSubarray(std::vector<int>& nums, int limit)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        const int N = nums.size();

        int left  = 0;
        int right = 0;

        std::deque<int> deq_mini;
        std::deque<int> deq_maxi;
        int result = 0;

        while (right < N)
        {
            while ( ! deq_mini.empty() && deq_mini.back() > nums[right])
            {
                deq_mini.pop_back();
            }
            deq_mini.push_back(nums[right]);

            while ( ! deq_maxi.empty() && deq_maxi.back() < nums[right])
            {
                deq_maxi.pop_back();
            }
            deq_maxi.push_back(nums[right]);

            while (deq_maxi.front() - deq_mini.front() > limit)
            {
                if (nums[left] == deq_maxi.front())
                    deq_maxi.pop_front();

                if (nums[left] == deq_mini.front())
                    deq_mini.pop_front();

                left++;
            }

            result = std::max(result, right-left+1);

            right++; // Extend the Window
        }

        return result;
    }
};
