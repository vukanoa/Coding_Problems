/*
    ==============
    === MEDIUM ===
    ==============

    ======================================================
    2610) Convert An Array Into a 2D Array With Conditions
    ======================================================

    ============
    Description:
    ============

    You are given an integer array nums. You need to create a 2D array from
    nums satisfying the following conditions:

        + The 2D array should contain only the elements of the array nums.
        + Each row in the 2D array contains distinct integers.
        + The number of rows in the 2D array should be minimal.

    Return the resulting array. If there are multiple answers, return any of
    them.


    =====
    Note: Note that the 2D array can have a different number of elements on
          each row.
    =====

    ============================================================
    FUNCTION: vector<vector<int>> findMatrix(vector<int>& nums);
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,3,4,1,2,3,1]
    Output: [[1,3,4,2],[1,3],[1]]
    Explanation: We can create a 2D array that contains the following rows:
    - 1,3,4,2
    - 1,3
    - 1
    All elements of nums were used, and each row of the 2D array contains
    distinct integers, so it is a valid answer.  It can be shown that we cannot
    have less than 3 rows in a valid array.


    --- Example 2 ---
    Input: nums = [1,2,3,4]
    Output: [[4,3,2,1]]
    Explanation: All elements of the array are distinct, so we can keep all of
                 them in the first row of the 2D array.


    *** Constraints ***
    1 <= nums.length <= 200
    1 <= nums[i] <= nums.length

*/

#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 74.04% */
/* Space Beats: 55.03% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    vector<vector<int>> findMatrix(vector<int>& nums)
    {
        const int N = nums.size();

        int max_freq = 0;
        vector<int> freq(201, 0);

        for (int i = 0; i < N; i++)
        {
            freq[nums[i]]++;
            max_freq = max(max_freq, freq[nums[i]]);
        }

        vector<vector<int>> result(max_freq);
        for (int i = 0; i < N; i++)
        {
            while (freq[nums[i]] > 0)
            {
                result[freq[nums[i]] - 1].push_back(nums[i]);
                freq[nums[i]]--;
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This Solution is Safer if we're NOT dealing with these small Constraints.
    Essentially they're the same, it's good to be able to see both
    implementations.

*/

/* Time  Beats: 59.32% */
/* Space Beats:  7.27% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Safer {
public:
    vector<vector<int>> findMatrix(vector<int>& nums)
    {
        int max_freq = 0;

        unordered_map<int, int> freq;
        for (const auto& num : nums)
        {
            freq[num]++;
            max_freq = max(max_freq, freq[num]);
        }

        unordered_map<int, vector<int>> bucket;
        for (const auto& entry : freq)
            bucket[entry.second].push_back(entry.first);

        vector<vector<int>> result(max_freq);

        for (const auto& entry : bucket)
        {
            int         curr_freq = entry.first;
            vector<int> curr_nums = entry.second;

            while (curr_freq > 0)
            {
                result[curr_freq - 1].insert(result[curr_freq - 1].end(), curr_nums.begin(), curr_nums.end());

                // Decrement
                curr_freq--;
            }
        }

        return result;
    }
};
