/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    4040) Minimum Operations to Form Subset Sum I
    =============================================

    ============
    Description:
    ============

    You are given an integer array nums and an integer sum.

    In one operation, choose an element with current value x and replace it
    with either 2 * x or floor(x / 2).

    For each element, all multiplication operations performed on it must occur
    before any division operations performed on it.

    Return the minimum number of operations needed so that some of the
    resulting array has a sum exactly equal to sum. If it is impossible, return
    -1.

    The floor() function returns the integer part of the division.

    ========================================================
    FUNCTION: int minOperations(vector<int>& nums, int sum);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [5,6,10], sum = 4
    Output: 3
    Explanation:
        Divide nums[0] = 5 twice: 5 → 2 → 1, costing 2 operations.
        Divide nums[1] = 6 once: 6 → 3, costing 1 operation.
        After these operations, nums = [1, 3, 10]. The subset {1, 3} sums to 4
        using 3 operations in total.


    --- Example 2 ---
    Input: nums = [10,2], sum = 13
    Output: 3
    Explanation:
        Divide nums[0] = 10 once: 10 → 5, costing 1 operation.
        Multiply nums[1] = 2 twice: 2 → 4 → 8, costing 2 operations.
        After these operations, nums = [5, 8]. The subset {5, 8} sums to 13
        using 3 operations in total.


    --- Example 3 ---
    Input: nums = [6,3], sum = 8
    Output: -1
    Explanation:
        No sequence of operations lets a subset of nums sum to 8, so the answer
        is -1.


    *** Constraints ***
    1 <= nums.length <= 100
    1 <= nums[i] <= 500
    1 <= sum <= 5000

*/

#include <climits>
#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 23.97% */
/* Space Beats: 93.84% */

/* Time  Complexity: O(N * sum * log(max(sum))) */
/* Space Complexity: O(N * sum * log(max(sum))) */
class Solution_Top_Down__Memoization {
private:
    int memo[101][5001];

public:
    int minOperations(vector<int>& nums, int sum)
    {
        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        int result = solve(0, sum, nums);
        return result == INT_MAX ? -1 : result;
    }

private:
    int solve (int idx, int sum, vector<int>& nums)
    {
        const int N = nums.size();

        if (sum == 0)
            return 0;

        if (idx >= N || sum < 0 || sum > 5000)
            return INT_MAX;

        if (memo[idx][sum] != -1)
            return memo[idx][sum];

        int result = INT_MAX;

        ////////////
        /// Skip ///
        ////////////
        result = min(result, solve(idx+1, sum, nums));



        ////////////
        /// Take ///    (sum - nums[idx]) will be tried twice, but w/e
        ////////////

        // First: Try MULTIPLICATIONS of nums[idx], but WITHOUT any prior
        // division of nums[idx], i.e. {val, val*2, val*4, ...}
        //         used_operations -->   0     1      2    ... 
        int val             = nums[idx];
        int used_operations = 0;
        while (val <= 5000)
        {
            int subproblem_result = solve(idx+1, sum - val, nums);

            if (subproblem_result != INT_MAX)
                subproblem_result = subproblem_result + used_operations;

            result = min(result, subproblem_result);

            ++used_operations;
            val *= 2; // Multiply
        }

        // Second: Try all DIVISIONS of nums[idx], i.e. {val, va/2, va/4, ...}
        //                          used_operations -->   0     1     2   ... 
        val             = nums[idx];
        used_operations = 0;
        while (val > 0)
        {
            int subproblem_result = solve(idx+1, sum - val, nums);

            if (subproblem_result != INT_MAX)
                subproblem_result = subproblem_result + used_operations;

            result = min(result, subproblem_result);

            ++used_operations;
            val /= 2; // Divide
        }

        return memo[idx][sum] = result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 59.77% */
/* Space Beats: 50.29% */

/* Time  Complexity: O(N * sum * log(max(sum))) */
/* Space Complexity: O(N * sum * log(max(sum))) */
class Solution_Bottom_Up__Tabulation {
public:
    int minOperations(vector<int>& nums, int sum)
    {
        vector<int> dp(sum+1, INT_MAX);
        dp[0] = 0;

        for (int number : nums)
        {
            vector<pair<int,int>> options;

            long long operations = 0;
            long long val        = number;
            while (val <= sum)
            {
                options.push_back({(int)val, (int)operations});

                ++operations;
                val *= 2;
            }

            operations = 1;
            val        = number;
            while (val > 0)
            {
                if (val/2 > 0 && val/2 <= sum)
                    options.push_back( {val/2, operations} );

                ++operations;
                val /= 2;
            }

            vector<int> next = dp;
            for (auto& [val, operations] : options)
            {
                for (int curr_sum = sum; curr_sum >= val; curr_sum--)
                {
                    if (dp[curr_sum - val] != INT_MAX)
                        next[curr_sum] = min(next[curr_sum], dp[curr_sum - val] + operations);
                }
            }

            dp = next;
        }

        return dp[sum] == INT_MAX ? -1 : dp[sum];
    }
};
