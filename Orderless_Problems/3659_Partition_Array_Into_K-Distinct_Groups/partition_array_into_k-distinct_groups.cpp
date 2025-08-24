/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    3659) Partition Array into K-Disctinct Groups
    =============================================

    ============
    Description:
    ============

    You are given an integer array nums and an integer k.

    Your task is to determine whether it is possible to partition all
    elements of nums into one or more groups such that:

        + Each group contains exactly k distinct elements.
        + Each element in nums must be assigned to exactly one group.

    Return true if such a partition is possible, otherwise return false.

    ========================================================
    FUNCTION: bool partitionArray(vector<int>& nums, int k);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,4], k = 2
    Output: true
    Explanation:
    One possible partition is to have 2 groups:
        Group 1: [1, 2]
        Group 2: [3, 4]
    Each group contains k = 2 distinct elements, and all elements are used
    exactly once.

    --- Example 2 ---
    Input: nums = [3,5,2,2], k = 2
    Output: true
    Explanation:
    One possible partition is to have 2 groups:
        Group 1: [2, 3]
        Group 2: [2, 5]
    Each group contains k = 2 distinct elements, and all elements are used
    exactly once.

    --- Example 3 ---
    Input: nums = [1,5,2,3], k = 3
    Output: false
    Explanation:
    We cannot form groups of k = 3 distinct elements using all values exactly
    once.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^5
    1 <= k <= nums.length

*/

#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 12.50% */
/* Space Beats: 12.50% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    bool partitionArray(vector<int>& nums, int k)
    {
        const int N = nums.size();
        int amount_of_groups = N / k;

        /* Edge cases */
        if (k == 1)
            return true;

        if (N % k != 0)
            return false;

        unordered_set<int> uset_tmp(nums.begin(), nums.end());
        if (N == k)
            return uset_tmp.size() == N;

        map<int, vector<int>, greater<int>> max_map; // freq to set

        /* Counting Sort */
        unordered_map<int,int> freq;
        for (const int& num : nums)
        {
            freq[num]++;

            if (freq[num] > amount_of_groups)
                return false;
        }

        for (const auto& [num, count] : freq)
            max_map[count].push_back(num);

        /*
            Be careful! It's exactly 'k' elements out of which ALL should be
            DISTINCT!

                {1, 1, 2, 3}, is NOT(!!!) a valid partition for k=3.

            It's poorly worded.
        */
        while (amount_of_groups > 0)
        {
            unordered_map<int, vector<int>> umap_used_in_this_group;

            for (int i = 0; i < k; i++)
            {
                if (max_map.empty())
                    return false;

                int   curr_freq = max_map.begin()->first;
                auto& curr_vec  = max_map.begin()->second; // Refference!!!

                int num = curr_vec.back();

                umap_used_in_this_group[curr_freq - 1].push_back(num);

                // Take it off
                curr_vec.pop_back();
                if (curr_vec.empty())
                    max_map.erase(curr_freq);
            }

            for (const auto& entry : umap_used_in_this_group)
            {
                const int&         instances = entry.first;
                const vector<int>& values    = entry.second;

                max_map[instances].insert(max_map[instances].end(), values.begin(), values.end());
            }

            // Decrement
            amount_of_groups--;
        }

        return true;
    }
};
