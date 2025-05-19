/*
    ==============
    === MEDIUM ===
    ==============

    =========================================================
    3040) Maximum Number of Operations With the Same Score II
    =========================================================

    ============
    Description:
    ============

    Given an array of integers called nums, you can perform any of the
    following operation while nums contains at least 2 elements:

        + Choose the first two elements of nums and delete them.
        + Choose the last two elements of nums and delete them.
        + Choose the first and the last elements of nums and delete them.

    The score of the operation is the sum of the deleted elements.

    Your task is to find the maximum number of operations that can be
    performed, such that all operations have the same score.

    Return the maximum number of operations possible that satisfy the condition
    mentioned above.

    ===============================================
    FUNCTION: int maxOperations(vector<int>& nums);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,2,1,2,3,4]
    Output: 3
    Explanation: We perform the following operations:
    - Delete the first two elements, with score 3 + 2 = 5, nums = [1,2,3,4].
    - Delete the first and the last elements, with score 1 + 4 = 5, nums = [2,3]
    - Delete the first and the last elements, with score 2 + 3 = 5, nums = [].
    We are unable to perform any more operations as nums is empty.

    --- Example 2 ---
    Input: nums = [3,2,6,1,4]
    Output: 2
    Explanation: We perform the following operations:
    - Delete the first two elements, with score 3 + 2 = 5, nums = [6,1,4].
    - Delete the last two elements, with score 1 + 4 = 5, nums = [6].
    It can be proven that we can perform at most 2 operations.


    *** Constraints ***
    2 <= nums.length <= 2000
    1 <= nums[i] <= 1000

*/

#include <cstring>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Classic Memoization Solution.

*/

/* Time  Beats: 29.94% */
/* Space Beats: 89.22% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N^2) */
class Solution {
private:
    int memo[2001][2001];
public:
    int maxOperations(vector<int>& nums)
    {
        int N = nums.size();
        int result = 0;

        /* Memset */
        memset(memo, -1, sizeof(memo));

        int L = 0;
        int R = N - 1;

        result = max(result, 1 + solve(L+2, R  , nums[L  ] + nums[L+1], nums));
        result = max(result, 1 + solve(L+1, R-1, nums[L  ] + nums[R  ], nums));
        result = max(result, 1 + solve(L  , R-2, nums[R-1] + nums[R  ], nums));

        return result;
    }

private:
    int solve(int L, int R, int sum, vector<int>& nums)
    {
        if (L >= R)
            return 0;

        if (memo[L][R] != -1)
            return memo[L][R];

        int result = 0;
        if (nums[L  ] + nums[L+1] == sum)
            result = max(result, 1 + solve(L+2, R  , sum, nums));

        if (nums[L  ] + nums[R  ] == sum)
            result = max(result, 1 + solve(L+1, R-1, sum, nums));

        if (nums[R-1] + nums[R  ] == sum)
            result = max(result, 1 + solve(L  , R-2, sum, nums));

        return memo[L][R] = result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Tabulation Solution, i.e. Bottom-Up Dynamic Programming.

*/

/* Time  Beats: 30.54% */
/* Space Beats: 31.14% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N^2) */
class Solution_Tabulation {
public:
    int maxOperations(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        if (N < 2)
            return 0;

        unordered_set<int> uset_sum {
            nums[0    ] + nums[1    ],
            nums[0    ] + nums[N - 1],
            nums[N - 2] + nums[N - 1]
        };

        for (const int& target_sum : uset_sum)
        {
            vector<vector<int>> dp(N + 1, vector<int>(N + 1));

            for (int idx = 2; idx <= N; idx++)
            {
                int L = 0;
                int R = L + idx - 1;

                while (R < N)
                {
                    if (L + 1 < N && nums[L] + nums[L + 1] == target_sum)
                        dp[idx][L] = max(dp[idx][L], 1 + dp[idx - 2][L + 2]);

                    if (R < N && nums[L] + nums[R] == target_sum)
                        dp[idx][L] = max(dp[idx][L], 1 + dp[idx - 2][L + 1]);

                    if (R - 1 >= 0 && nums[R - 1] + nums[R] == target_sum)
                        dp[idx][L] = max(dp[idx][L], 1 + dp[idx - 2][L   ]);

                    L++;
                    R++;
                }
            }

            result = max(result, dp[N][0]);
        }

        return result;
    }
};
