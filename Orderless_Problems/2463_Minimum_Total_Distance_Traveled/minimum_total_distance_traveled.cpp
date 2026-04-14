/*
    ============
    === HARD ===
    ============

    =====================================
    2463) Minimum Total Distance Traveled
    =====================================

    ============
    Description:
    ============


    There are some robots and factories on the X-axis. You are given an integer
    array robot where robot[i] is the position of the ith robot. You are also
    given a 2D integer array factory where factory[j] = [positionj, limitj]
    indicates that positionj is the position of the jth factory and that the
    jth factory can repair at most limitj robots.

    The positions of each robot are unique. The positions of each factory are
    also unique. Note that a robot can be in the same position as a factory
    initially.

    All the robots are initially broken; they keep moving in one direction. The
    direction could be the negative or the positive direction of the X-axis.
    When a robot reaches a factory that did not reach its limit, the factory
    repairs the robot, and it stops moving.

    At any moment, you can set the initial direction of moving for some robot.
    Your target is to minimize the total distance traveled by all the robots.

    Return the minimum total distance traveled by all the robots. The test
    cases are generated such that all the robots can be repaired.

    Note that

        + All robots move at the same speed.

        + If two robots move in the same direction, they will never collide.

        + If two robots move in opposite directions and they meet at some
          point, they do not collide. They cross each other.

        + If a robot passes by a factory that reached its limits, it crosses it
          as if it does not exist.

        + If the robot moved from a position x to a position y, the distance it
          moved is |y - x|.

    ===========================================================================================
    FUNCTION: long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory);
    ===========================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: robot = [0,4,6], factory = [[2,2],[6,2]]
    Output: 4
    Explanation: As shown in the figure:
    - The first robot at position 0 moves in the positive direction. It will be repaired at the first factory.
    - The second robot at position 4 moves in the negative direction. It will be repaired at the first factory.
    - The third robot at position 6 will be repaired at the second factory. It does not need to move.
    The limit of the first factory is 2, and it fixed 2 robots.
    The limit of the second factory is 2, and it fixed 1 robot.
    The total distance is |2 - 0| + |2 - 4| + |6 - 6| = 4. It can be shown that we cannot achieve a better total distance than 4.

    --- Example 2 ---
    Input: robot = [1,-1], factory = [[-2,1],[2,1]]
    Output: 2
    Explanation: As shown in the figure:
    - The first robot at position 1 moves in the positive direction. It will be repaired at the second factory.
    - The second robot at position -1 moves in the negative direction. It will be repaired at the first factory.
    The limit of the first factory is 1, and it fixed 1 robot.
    The limit of the second factory is 1, and it fixed 1 robot.
    The total distance is |2 - 1| + |(-2) - (-1)| = 2. It can be shown that we cannot achieve a better total distance than 2.


    *** Constraints ***
    1 <= robot.length, factory.length <= 100
    factory[j].length == 2
    -10^9 <= robot[i], positionj <= 10^9
    0 <= limitj <= robot.length
    The input will be generated such that it is always possible to repair every robot.

*/

#include <vector>
#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 76.03% */
/* Space Beats: 69.18% */

/* Time  Complexity: O(N * M) */
/* Space Complexity: O(N * M) */
class Solution_Botom_Up {
public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory)
    {
        sort(robot.begin(), robot.end());
        sort(factory.begin(), factory.end());

        const int N = robot.size();
        const int M = factory.size();

        const long long INF = 1e18;

        // dp[i][j] <==> Min cost to fix first i robots using first j factories
        vector<vector<long long>> dp(N + 1, vector<long long>(M + 1, INF));

        // Base case: 0 robots --> 0 cost
        for (int j = 0; j <= M; j++)
            dp[0][j] = 0LL;

        for (int j = 1; j <= M; j++)
        {
            int factory_idx   = factory[j - 1][0]; // j-1 because its 0-indexed
            int factory_limit = factory[j - 1][1]; // j-1 because its 0-indexed

            for (int i = 0; i <= N; i++)
            {
                long long skip = dp[i][j - 1];
                long long take = INF;

                long long distance = 0;

                int k = 1;
                while (k <= factory_limit && i - k >= 0)
                {
                    distance += abs(robot[i - k] - factory_idx);

                    take = min(take, dp[i - k][j - 1] + distance);

                    // Increment
                    k++;
                }

                dp[i][j] = min(take, skip);
            }
        }

        return dp[N][M];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 82.76% */
/* Space Beats: 84.38% */

/* Time  Complexity: O(N * M) */
/* Space Complexity: O(N * M) */
class Solution_Memoization {
public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory)
    {
        const int N = robot.size();
        const int M = factory.size();

        /* Sort */
        sort(robot.begin(), robot.end());
        sort(factory.begin(), factory.end());

        // Initialize "memo"
        vector<vector<long long>> memo(N, vector<long long>(M, -1));

        return solve(robot, factory, memo, 0, 0);
    }

private:
    long long solve(vector<int>& robot,
                  vector<vector<int>>& factory,
                  vector<vector<long long>>& memo,
                  int i,
                  int j)
    {
        const int N = robot.size();
        const int M = factory.size();

        long long infinity = 1e13;

        if (i == N)
            return 0;

        if (j == M)
            return infinity;

        if (memo[i][j] != -1)
            return memo[i][j];

        // Skip the current factory
        long long result = solve(robot, factory, memo, i, j+1);
        long long sum = 0;

        // Attempt to assign robots to the current factory
        for (int k = i; k < N && k-i+1 <= factory[j][1]; k++)
        {
            sum += abs(robot[k] - factory[j][0]);
            result = min(result, sum + solve(robot, factory, memo, k+1, j+1));
        }

        memo[i][j] = result;

        return result;
    }
};
