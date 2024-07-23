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




/*
    ------------
    --- IDEA ---
    ------------

    Counting sort is by far the most efficient.

    TODO

*/

/* Time  Beats: 73.10% */
/* Space Beats: 78.88% */

/* Time  Complexity: O(n + m) */
/* Space Complexity: O(m)     */
class Solution_Counting_Sort {
public:
    vector<int> frequencySort(vector<int>& nums)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        const int n = nums.size();
        vector<int> freq(201, 0);

        int maxF = 0;
        int maxX = -1;

        for (int x : nums)
        {
            x += 100; // x-min_x where min_x=-100
            int f = ++freq[x];

            maxX = max(x, maxX);
            maxF = max(f, maxF);
        }

        vector<vector<int>> freq_x(maxF + 1);
        for (int x = 0; x <= maxX; x++)
        {
            if (freq[x] > 0)
                freq_x[freq[x]].push_back(x - 100); // Adjust value back
        }

        int i = 0;
        for (int curr_freq = 1; curr_freq <= maxF; curr_freq++)
        {
            auto& arr = freq_x[curr_freq];
            counting_sort(arr);

            // Each x occurs f times
            for (int x : arr)
            {
                fill(nums.begin() + i, nums.begin() + i + curr_freq, x);
                i += curr_freq;
            }
        }

        return nums;
    }

public:

    // Counting sort in the decreasing order
    void counting_sort(auto& arr)
    {
        if (arr.empty())
            return;

        auto [x_min, x_max] = minmax_element(arr.begin(), arr.end());
        int min_val  = *x_min;
        int diff_val = *x_max - min_val + 1;

        vector<int> count(diff_val, 0);

        for (int x : arr)
            count[x - min_val]++;

        int i = 0;
        // Sort in decreasing order
        for (int y = diff_val - 1; y >= 0; y--)
        {
            int f = count[y];
            fill(arr.begin() + i, arr.begin() + i + f, y + min_val);
            i += f;
        }
    }
};
