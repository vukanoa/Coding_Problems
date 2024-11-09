#include <iostream>
#include <vector>
#include <unordered_map>

/*
    ============
    === EASY ===
    ============

    ===========================
    697) Degree of an Array
    ===========================

    ============
    Description:
    ============

    Given a non-empty array of non-negative integers nums, the degree of this
    array is defined as the maximum frequency of any one of its elements.

    Your task is to find the smallest possible length of a (contiguous)
    subarray of nums, that has the same degree as nums.

    ======================================================
    FUNCTION: int findShortestSubArray(vector<int>& nums);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,2,3,1]
    Output: 2
    Explanation:
    The input array has a degree of 2 because both elements 1 and 2 appear
    twice. Of the subarrays that have the same degree:
    [1, 2, 2, 3, 1], [1, 2, 2, 3], [2, 2, 3, 1], [1, 2, 2], [2, 2, 3], [2, 2]
    The shortest length is 2. So return 2.


    --- Example 2 ---
    Input: nums = [1,2,2,3,1,4,2]
    Output: 6
    Explanation:
    The degree is 3 because the element 2 is repeated 3 times.
    So [2,2,3,1,4,2] is the shortest subarray, therefore returning 6.


    *** Constraints ***
    nums.length will be between 1 and 50,000.
    nums[i] will be an integer between 0 and 49,999.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Here is how our HashMap(unorderd) looks like:

        {element :  {frequency : {first_appearance_idx : last_appearance_idx}}}

    Once we have that and once we have "max_freq" we can iterate through the
    HashMap and only if the current "frequency" is equal "max_freq" only then
    we potentially update "smallest_length" if:

        last_appearance_idx - first_appearance_idx

    is smaller than "smallest_length".

    At the end simply return "smallest_length".

*/

/* Time  Beats: 82.75% */
/* Space Beats: 77.85% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int findShortestSubArray(vector<int>& nums)
    {
        unordered_map<int, pair<int, pair<int, int>>> umap;

        int max_freq = 1;
        for (int i = 0; i < nums.size(); i++)
        {
            if (umap.find(nums[i]) == umap.end())
                umap.insert( {nums[i], {1, {i,i}}} );
            else
            {
                // Increment frequency
                int& curr_freq = umap[nums[i]].first;
                curr_freq++;

                // Potentially update max_freq
                max_freq = max(max_freq, curr_freq);

                // Update new "end" index for this nums[i]
                pair<int,int>& begin_end = umap[nums[i]].second;
                begin_end.second = i;
            }
        }

        int smallest_length = INT_MAX;
        for (const auto& entry : umap)
        {
            const int& curr_freq           = entry.second.first;
            const pair<int,int>& begin_end = entry.second.second;

            const int& begin = begin_end.first;
            const int& end   = begin_end.second;

            if (max_freq == curr_freq)
                smallest_length = min(smallest_length, begin_end.second - begin_end.first + 1);
        }

        return smallest_length;
    }
};
