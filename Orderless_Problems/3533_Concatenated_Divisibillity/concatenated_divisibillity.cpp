/*
    ============
    === HARD ===
    ============

    ===============================
    3533) Concatenated Divisibility
    ===============================

    ============
    Description:
    ============

    You are given an array of positive integers nums and a positive integer k.

    A permutations of nums is said to form a divisible concatenation if, when
    you concatenate the decimal representations of the numbers in the order
    specified by the permutation, the resulting number is divisible by k.

    Return the lexicographically smallest permutation (when considered as a
    list of integers) that forms a divisible concatenation. If no such
    permutation exists, return an empty list.

    =========================================================================
    FUNCTION: vector<int> concatenatedDivisibility(vector<int>& nums, int k);
    =========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,12,45], k = 5
    Output: [3,12,45]
    Permutation    Concatenated Value    Divisible by 5
    [3, 12, 45]          31245              Yes
    [3, 45, 12]          34512              No
    [12, 3, 45]          12345              Yes
    [12, 45, 3]          12453              No
    [45, 3, 12]          45312              No
    [45, 12, 3]          45123              No

    The lexicographically smallest permutation that forms a divisible
    concatenation is [3,12,45].


    --- Example 2 ---
    Input: nums = [10,5], k = 10
    Output: [5,10]
    Permutation    Concatenated Value    Divisible by 10
    [5, 10]              510                Yes
    [10, 5]              105                No


    --- Example 3 ---
    Input: nums = [1,2,3], k = 5
    Output: []
    Explanation: Since no permutation of nums forms a valid divisible
                 concatenation, return an empty list.



    *** Constraints ***
    1 <= nums.length <= 13
    1 <= nums[i] <= 10^5
    1 <= k <= 100

*/

#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    TODO
    Way too difficult.

*/

/* Time  Beats: 57.20% */
/* Space Beats: 43.48% */

/* Time  Complexity: O(2^N * K * N) */
/* Space Complexity: O(2^N * K + N) */
class Solution {
private:
    vector<vector<int>> memo;

public:
    vector<int> concatenatedDivisibility(vector<int>& nums, int k)
    {
        const int N = nums.size();
        memo.resize((1 << N) + 1, vector<int>(k + 1, -1));

        /* Sort the numbers to maintain a consistent order */
        sort(nums.begin(), nums.end());

        vector<int> sequence;
        solve(nums, k, 0x0, sequence, 0, 0);

        return sequence;
    }

private:
    int solve(vector<int>& nums, int k, int mask, vector<int>& sequence, int curr_val, int curr_remainder)
    {
        const int N = nums.size();

        if (mask == (1 << N) - 1)
            return curr_remainder == 0; // return "true" if curr_remainder == 0

        if (memo[mask][curr_val] != -1)
            return memo[mask][curr_val];

        for (int index = 0; index < N; index++)
        {
            if (mask & (1 << index))
                continue;

            int next_mask = mask | (1 << index);

            int number_of_digits = to_string(nums[index]).size();

            int power_of_ten_mod_k = pow(10, number_of_digits);
            power_of_ten_mod_k %= k;

            // int curr_mod     = curr_val % k;
            int curr_mod     = curr_val;
            int next_num_mod = nums[index] % k;

            int combined_mod = (curr_mod * power_of_ten_mod_k + next_num_mod) % k;

            sequence.push_back(nums[index]);
            if (solve(nums, k, next_mask, sequence, combined_mod, combined_mod))
                return 1;

            sequence.pop_back();
        }

        return memo[mask][curr_val] = 0;
    }
};
