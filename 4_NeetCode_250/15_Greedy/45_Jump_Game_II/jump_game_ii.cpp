/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    45) Jump Game II
    ===========================

    ============
    Description:
    ============

    You are given a 0-indexed array of integers nums of length n. You are
    initially positioned at nums[0].

    Each element nums[i] represents the maximum length of a forward jump from
    index i. In other words, if you are at nums[i], you can jump to any
    nums[i + j] where:

        0 <= j <= nums[i] and i + j < n

    Return the minimum number of jumps to reach nums[n - 1]. The test cases are
    generated such that you can reach nums[n - 1].

    ======================================
    FUNCTION: int jump(vector<int>& nums);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,3,1,1,4]
    Output: 2
    Explanation: The minimum number of jumps to reach the last index is 2.
                 Jump 1 step from index 0 to 1, then 3 steps to the last index.


    --- Example 2 ---
    Input: nums = [2,3,0,1,4]
    Output: 2


    *** Constraints ***
    1 <= nums.length <= 104
    0 <= nums[i] <= 1000
    It's guaranteed that you can reach nums[n - 1].

*/

#include <climits>
#include <queue>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Something between Solution_DP and Solution_BFS in this file.
    A kind of combination of the two.

    Better than the first(Solution_DP) and worse than the last(Solution_BFS).

*/

/* Time  Beats: 32.55% */
/* Space Beats: 19.33% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Dynamic_Programming {
public:
    int jump(vector<int>& nums)
    {
        const int N = nums.size();
        vector<int> dp(N, INT_MAX);

        dp[0] = 0;
        for (int i = 0; i < N; i++)
        {
            for (int jump_len = 1; jump_len <= nums[i]; jump_len++)
            {
                if (i + jump_len >= N)
                    continue;

                if (dp[i + jump_len] == INT_MAX) // Not yet level-marked
                    dp[i + jump_len] = dp[i] + 1;

                if (i + jump_len == N-1)
                    return dp[i + jump_len];
            }
        }

        return 0;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    BFS_Greedy max reachability Solution.

*/

/* Time  Beats: 13.15% */
/* Space Beats: 25.26% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_BFS_Greedy_Max_Reachability {
public:
    int jump(vector<int>& nums)
    {
        const int N = nums.size();

        if (N == 1)
            return 0;

        queue<int> queue;
        queue.push(0);

        int max_reach_idx = 0;
        int jumps = 0;

        while ( ! queue.empty())
        {
            int size = queue.size();
            while (size > 0)
            {
                int i = queue.front();
                queue.pop();

                for (int j = max(max_reach_idx + 1, i+1); j <= min(i + nums[i], N-1); j++)
                    queue.push(j);

                max_reach_idx = max(max_reach_idx, i + nums[i]);

                // Decrement
                size--;
            }

            jumps++;

            if (max_reach_idx >= N-1)
                break;
        }

        return jumps;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    You can think of this as kind of a BFS in a way. It's actually Greedy, but
    the way we're "traversing" the vector is in a "BFS-like" way.

*/

/* Time  Beats: 95.10% */
/* Space Beats: 43.87% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Greedy {
public:
    int jump(vector<int>& nums)
    {
        const int N = nums.size();
        int jumps = 0;

        int left  = 0;
        int right = 0;

        while (right < N-1)
        {
            int farthest = 0;
            for (int j = left; j <= right; j++)
                farthest = max(farthest, j + nums[j]);

            left  = right + 1;
            right = farthest;

            jumps++;
        }

        return jumps;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is just another way of implementing this BFS-Greedy Solution.

    It's always beneficial to see more than a simgle way to solve a problem.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  61.40% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Greedy_2 {
public:
    int jump(vector<int>& nums)
    {
        const int N = nums.size();

        if (N == 1)
            return 0;

        int jumps = 0;
        int max_reach = 0;

        int i = 0;
        for (;;)
        {
            int level_end = max_reach;

            while (i <= level_end)
            {
                max_reach = max(max_reach, i + nums[i]);

                if (max_reach >= N-1)
                    return jumps + 1;

                // Increment
                i++;
            }

            jumps++;
        }

        return -1; // Unreachable, as we'll ALWAYS be able to reach nums[N-1]
    }
};
