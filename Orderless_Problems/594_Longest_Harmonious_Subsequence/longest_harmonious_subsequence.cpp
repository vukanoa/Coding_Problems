/*
    ============
    === EASY ===
    ============

    ====================================
    594) Longest Harmonious Subseequence
    ====================================

    ============
    Description:
    ============

    We define a harmonious array as an array where the difference between its
    maximum value and its minimum value is exactly 1.

    Given an integer array nums, return the length of its longest harmonious
    subsequence among all its possible subsequences.

    =========================================
    FUNCTION: int findLHS(vector<int>& nums);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,3,2,2,5,2,3,7]
    Output: 5
    Explanation:
    The longest harmonious subsequence is [3,2,2,2,3]

    --- Example 2 ---
    Input: nums = [1,2,3,4]
    Output: 2
    Explanation:
    The longest harmonious subsequences are [1,2], [2,3], and [3,4], all of
    which have a length of 2.

    --- Example 3 ---
    Input: nums = [1,1,1,1]
    Output: 0
    Explanation:
    No harmonic subsequence exists.


    *** Constraints ***
    1 <= nums.length <= 2 * 10^4
    -10^9 <= nums[i] <= 10^9

*/

#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    Create a Frequency-HashMap ---> {element, frequence}

    Go through this (unordered) HashMap and each time take the current element
    and check if current_element_plus_1 exists in the Hashmap. It if does, then
    check if current_element's frequency + current_element_plus_1's frequency
    is the greatest so far.

    At the end return the greatest that you've found. Pretty simple.

*/

/* Time  Beats: 15.59% */
/* Space Beats: 52.07% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int findLHS(vector<int>& nums)
    {
        unordered_map<int, int> umap_counter;

        for (const int& num : nums)
            umap_counter[num]++;

        int result = 0;
        for (const auto& entry : umap_counter)
        {
            const int& key = entry.first;
            const int& val = entry.second;

            if (umap_counter.find(key + 1) != umap_counter.end()) // It DOES exist
                result = max(result, val + umap_counter[key + 1]);
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Both this "Sliding Window" and "Binary Search" Solutions are LESS efficient
    however it is good to know these technique even of trivial problems like
    this.

*/

/* Time  Beats: 94.27% */
/* Space Beats: 84.89% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(logN)     */ // This is Space Comp. for C++'s sort
class Solution_Sliding_Window {
public:
    static int findLHS(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        /* Sort */
        sort(nums.begin(), nums.end());

        int L = 0;
        int R = 0;
        while (R < N)
        {
            while (L < R && nums[L] < (nums[R] - 1))
                L++;

            if (nums[L] == (nums[R] - 1))
                result = max(result, R - L + 1);

            // Increment
            R++;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 87.57% */
/* Space Beats: 94.99% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(logN)     */ // This is Space Comp. for C++'s sort
class Solution_Binary_search {
public:
    int findLHS(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        /* Sort */
        sort(nums.begin(), nums.end());

        int L = 0;
        int R = 0;
        while (L < N)
        {
            R = upper_bound(nums.begin() + L + 1, nums.end(), nums[L] + 1) - nums.begin() - 1;

            if ((nums[L] + 1) == nums[R])
            {
                result = max(result, R - L + 1);

                L = lower_bound(nums.begin() + L + 1, nums.end(), nums[L]) - nums.begin() - 1;
            }

            // Increment
            L++;
        }

        return result;
    }
};
