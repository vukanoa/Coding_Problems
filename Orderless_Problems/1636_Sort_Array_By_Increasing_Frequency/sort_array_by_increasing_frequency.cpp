#include <iostream>
#include <vector>
#include <algorithm>

/*
    ============
    === EASY ===
    ============

    ========================================
    1636) Sort Array By Increasing Frequency
    ========================================

    ============
    Description:
    ============

    Given an array of integers nums, sort the array in increasing order based
    on the frequency of the values. If multiple values have the same frequency,
    sort them in decreasing order.

    Return the sorted array.

    =======================================================
    FUNCTION: vector<int> frequencySort(vector<int>& nums);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,1,2,2,2,3]
    Output: [3,1,1,2,2,2]
    Explanation: '3' has a frequency of 1, '1' has a frequency of 2, and '2'
                 has a frequency of 3.

    --- Example 2 ---
    Input: nums = [2,3,1,3,2]
    Output: [1,3,3,2,2]
    Explanation: '2' and '3' both have a frequency of 2, so they are sorted in
                 decreasing order.

    --- Example 3 ---
    Input: nums = [-1,1,-6,4,5,-6,1,4,1]
    Output: [5,-1,4,4,-6,-6,1,1,1]


    *** Constraints ***
    1 <= nums.length <= 100
    -100 <= nums[i] <= 100

*/

/*
    ------------
    --- IDEA ---
    ------------

    Intuitive approach.

*/

/* Time  Beats: 55.39% */
/* Space Beats:  5.99% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n)        */
class Solution {
public:
    vector<int> frequencySort(vector<int>& nums)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        unordered_map<int, int> umap_freq;
        for (int& num : nums)
            umap_freq[num]++;

        map<int, vector<int>> map;
        for (auto& entry : umap_freq)
        {
            int value = entry.first;
            int freq  = entry.second;

            map[freq].push_back(value);
        }

        bool needs_reversal = false;
        vector<int> result;
        for (auto& entry : map)
        {
            int freq = entry.first;
            vector<int> values = entry.second;

            if (values.size() > 1)
                sort(values.rbegin(), values.rend());

            for (int i = 0; i < values.size(); i++)
            {
                for (int j = 0; j < freq; j++)
                    result.push_back(values[i]);
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Using custom sort.

*/

/* Time  Beats: 34.26% */
/* Space Beats:  8.78% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n)        */
class Solution_Custom_Sort {
public:
    vector<int> frequencySort(vector<int>& nums)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates
        
        int n = nums.size();
        unordered_map<int, int> freq;

        for(int num : nums)
            freq[num]++;
        
        sort(nums.begin(), nums.end(), [&](int a, int b){
            return (freq[a] == freq[b]) ? a > b : freq[a] < freq[b];
        });

        return nums;
    }
};

