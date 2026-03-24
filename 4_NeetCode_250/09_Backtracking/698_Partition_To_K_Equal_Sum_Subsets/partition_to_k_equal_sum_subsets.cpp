/*
    ==============
    === MEDIUM ===
    ==============

    =====================================
    698) Partition to K Equal Sum Subsets
    =====================================

    ============
    Description:
    ============

    Given an integer array nums and an integer k, return true if it is possible
    to divide this array into k non-empty subsets whose sums are all equal.

    ==================================================================
    FUNCTION: bool canPartitionSubsets(std::vector<int>& nums, int k);
    ==================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [4,3,2,3,5,2,1], k = 4
    Output: true
    Explanation: It is possible to divide it into 4 subsets (5), (1, 4), (2,3),
    (2,3) with equal sums.

    --- Example 2 ---
    Input: nums = [1,2,3,4], k = 3
    Output: false

    *** Constraints ***
    1 <= k <= nums.length <= 16
    1 <= nums[i] <= 104
    The frequency of each element is in the range [1, 4].

*/

#include <algorithm>
#include <cstring>
#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    
*/

/* Time  Beats: 12.49% */
/* Space Beats: 77.37% */

/* Time  Complexity: O(k^N) */
/* Space Complexity: O(N)   */
class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k)
    {
        int sum = accumulate(nums.begin(), nums.end(), 0);

        if (sum % k)
            return false;

        /* Sort in DESCENDING order */
        sort(nums.begin(), nums.end(), greater<int>());

        vector<bool> used(nums.size(), false);

        return backtracking(nums, 0, k, 0, used, sum / k);
    }

private:
    bool backtracking(vector<int>& nums, int start, int k, int subset_sum, vector<bool>& used, int target)
    {
        if (k == 0)
            return true;

        if (subset_sum == target)
            return backtracking(nums, 0, k-1, 0, used, target);

        const int N = nums.size();
        for (int idx = start; idx < N; idx++)
        {
            if (used[idx] || subset_sum + nums[idx] > target)
                continue;

            used[idx] = true;

            if (backtracking(nums, idx + 1, k, subset_sum + nums[idx], used, target))
                return true;

            used[idx] = false;
        }

        return false;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  71.38% */

/* Time  Complexity: O(k^N) */
/* Space Complexity: O(N)   */
class Solution_Elegant {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k)
    {
        const int N = nums.size();

        /* Sort */
        sort(nums.begin(), nums.end(), greater<int>());

        unsigned long long total_sum  = accumulate(nums.begin(), nums.end(), 0ULL);
        if (total_sum % k != 0)
            return false;

        unsigned long long target_sum = total_sum / k;

        unsigned long long sums[16];
        memset(sums, 0x00, sizeof(sums)); /* Memset */
        
        return backtracking(0, sums, target_sum, nums, k);
    }

private:
    bool backtracking(int idx, unsigned long long (&sums)[16], unsigned long long& target_sum, vector<int>& nums, int& k)
    {
        const int N = nums.size();
        if (idx == N)
            return true;

        for (int subset_idx = 0; subset_idx < k; subset_idx++)
        {
            if (sums[subset_idx] + nums[idx] > target_sum)
                continue;

            if (subset_idx > 0 && sums[subset_idx - 1] == sums[subset_idx])
                continue;

            sums[subset_idx] += nums[idx];

            if (backtracking(idx + 1, sums, target_sum, nums, k))
                return true;

            sums[subset_idx] -= nums[idx];
        }

        return false;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  71.39% */

/* Time  Complexity: O(N! / ((N/k)!)^k) */
/* Space Complexity: O(N)               */
class Solution_Bitmasking {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k)
    {
        const int N = nums.size();
        int total_sum = accumulate(nums.begin(), nums.end(), 0);

        if (total_sum % k != 0)
            return false;

        int target_sum = total_sum / k;

        /* Sort in DESCENDING order */
        sort(nums.begin(), nums.end(), greater<int>());

        return backtrack(0, (1 << N) - 1, 0, target_sum, nums, k);
    }

private:
    bool backtrack(int start, int mask, int subset_sum, int& target_sum, vector<int>& nums, int k)
    {
        if (k == 0)
            return true;

        if (subset_sum == target_sum)
            return backtrack(0, mask, 0, target_sum, nums, k - 1);

        const int N = nums.size();
        for (int i = start; i < N; i++)
        {
            if ((mask & (1 << i)) == 0 || subset_sum + nums[i] > target_sum)
                continue;

            if (backtrack(i+1, mask ^ (1 << i), subset_sum + nums[i], target_sum, nums, k))
                return true;

            if (subset_sum == 0)
                return false;
        }

        return false;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Complexity: O(K * 2^N) */
/* Space Complexity: O(2^N)     */
class Solution_Bitmasking_Memoization {
private:
    int target_sum;
    int memo[1 << 16]; // supports up to 16 elements

public:
    bool canPartitionKSubsets(vector<int>& nums, int k)
    {
        const int N = nums.size();
        int total_sum = accumulate(nums.begin(), nums.end(), 0);

        if (total_sum % k != 0)
            return false;

        target_sum = total_sum / k;

        /* Sort in DESCENDING order */
        sort(nums.begin(), nums.end(), greater<int>());

        /* Memset */
        memset(memo, -1, sizeof(memo));

        return solve((1 << N) - 1, 0, nums, k);
    }

private:
    bool solve(int mask, int subset_sum, vector<int>& nums, int k)
    {
        if (k == 0)
            return true;

        if (subset_sum == target_sum)
            return solve(mask, 0, nums, k - 1);

        if (memo[mask] != -1)
            return memo[mask];

        const int N = nums.size();
        for (int i = 0; i < N; i++)
        {
            if ((mask & (1 << i)) == 0 || subset_sum + nums[i] > target_sum)
                continue;

            if (solve(mask ^ (1 << i), subset_sum + nums[i], nums, k))
                return memo[mask] = true;

            if (subset_sum == 0)
                return memo[mask] = false;
        }

        return memo[mask] = false;
    }
};




/* Time  Beats: 54.08% */
/* Space Beats: 54.60% */

/* Time  Complexity: O(N * 2^N) */
/* Space Complexity: O(2^N)     */
class Solution_Bottom_Up_DP {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k)
    {
        const int N = nums.size();
        int total_sum = accumulate(nums.begin(), nums.end(), 0);

        if (total_sum % k != 0)
            return false;

        int target = total_sum / k;

        int dp[1 << 16];
        memset(dp, 0xff, sizeof(dp));

        dp[0] = 0;

        for (int mask = 0; mask < (1 << N); mask++)
        {
            if (dp[mask] == -1)
                continue;

            for (int i = 0; i < N; i++)
            {
                if ((mask & (1 << i)) == 0 && dp[mask] + nums[i] <= target)
                    dp[mask | (1 << i)] = (dp[mask] + nums[i]) % target;
            }
        }

        return dp[(1 << N) - 1] == 0;
    }
};
