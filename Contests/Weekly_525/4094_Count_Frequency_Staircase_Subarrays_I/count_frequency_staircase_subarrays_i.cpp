/*
    ==============
    === MEDIUM ===
    ==============

    ===========================================
    4094) Count Frequency Staircase Subarrays I
    ===========================================

    ============
    Description:
    ============

    You are given an integer array nums.

    Consider the distinct values of a subarray in the order in which they first
    appear.

    If there are k distinct values, the subarray is called a frequency
    staircase if the first distinct value occurs exactly once, the second
    distinct value occurs exactly twice, and so on, with the kth distinct value
    occurring exactly k times.

    Equivalently, the frequencies of the distinct values, in the order of their
    first occurrence, must be exactly 1, 2, 3, ..., k.

    Return the number of frequency staircase subarrays in nums.

    A subarray is a contiguous non-empty sequence of elements within an array.

    The frequency of a value in a subarray is the number of times it occurs in
    that subarray.

    ================================================
    FUNCTION: int countStaircase(vector<int>& nums);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [5,8,8,2,2,2]
    Output: 9
    Explanation:
    Every single-element subarray has frequencies [1], and there are 6 of them.
    3 longer subarrays also qualify:

    Subarray                            Values by
                                      first appearance         Frequencies
    nums[0...2] = [5, 8, 8]             5, then 8                 [1, 2]
    nums[2...4] = [8, 2, 2]             8, then 2                 [1, 2]
    nums[0...5] = [5, 8, 8, 2, 2, 2]    5, then 8, then 2         [1, 2, 3]
    So the answer is 6 + 3 = 9.


    --- Example 2 ---
    Input: nums = [6,6,9,9]
    Output: 5
    Explanation:
    Every single-element subarray has frequencies [1], and there are 4 of them.
    1 longer subarray also qualifies:
    Subarray                            Values by
                                      first appearance         Frequencies
    nums[1...3] = [6, 9, 9]            6, then 9                 [1, 2]
    So the answer is 4 + 1 = 5.


    --- Example 3 ---
    Input: nums = [2,3,4,4,3,4]
    Output: 8
    Explanation:
    Every single-element subarray has frequencies [1], and there are 6 of them.
    2 longer subarrays also qualify:
    Subarray                            Values by
                                      first appearance         Frequencies
    nums[1...3] = [3, 4, 4]             3, then 4                 [1, 2]
    nums[0...5] = [2, 3, 4, 4, 3, 4]    2, then 3, then 4         [1, 2, 3]

    So the answer is 6 + 2 = 8.



    *** Constraints ***
    1 <= nums.length <= 1500
    1 <= nums[i] <= 10^5

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 63.64% */
/* Space Beats: 68.18% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N)   */
class Solution {
public:
    int countStaircase(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        vector<int> sorted_UNIQ_nums = nums;
        sort(sorted_UNIQ_nums.begin(), sorted_UNIQ_nums.end()); // in ASCENDING order

        sorted_UNIQ_nums.erase(
            unique(sorted_UNIQ_nums.begin(), sorted_UNIQ_nums.end()),
            sorted_UNIQ_nums.end()
        );

        const int UNIQUE_VALUES = sorted_UNIQ_nums.size();

        vector<int> compressed_values(N, 0);
        for (int i = 0; i < N; i++)
        {
            auto it = lower_bound(sorted_UNIQ_nums.begin(), sorted_UNIQ_nums.end(), nums[i]);

            int index = it - sorted_UNIQ_nums.begin();
            compressed_values[i] = index;
        }


        for (int left = 0; left < N; left++)
        {
            vector<int>                      freq(UNIQUE_VALUES, 0);
            vector<int> first_appearance_position(UNIQUE_VALUES, 0); // 0 means "didn't appear yet"

            int distinct_count  = 0;
            int satisfied_count = 0;

            for (int right = left; right < N; right++)
            {
                int value = compressed_values[right];

                if (first_appearance_position[value] == 0) // had NOT appear yet
                {
                    ++distinct_count;
                    first_appearance_position[value] = distinct_count;
                    freq[value] = 1;

                    if (freq[value] == first_appearance_position[value])
                        ++satisfied_count;
                }
                else
                {
                    if (freq[value] == first_appearance_position[value])
                        --satisfied_count;

                    ++freq[value];

                    if (freq[value] == first_appearance_position[value])
                        ++satisfied_count;
                }

                if (satisfied_count == distinct_count)
                    ++result;
            }
        }

        return result;
    }
};
