#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>

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

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  53.75% */

/* Time  Complexity: O(m * n) */
/* Space Complexity: O(m * n) */
class Solution {
public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory)
    {
        int m = robot.size();
        int n = factory.size();

        sort(robot.begin(), robot.end());
        sort(factory.begin(), factory.end());

        // dp[i][j] is minimum total distance for robots[i] using factories[j]
        vector<vector<long long>> dp(m + 1, vector<long long>(n + 1, LLONG_MAX));

        for (int j = n-1; j >= 0; j--)
        {
            // Track cumulative distance from current factory to robots
            long long prefix = 0;

            // Deque stores pairs of (robot index, minimum distance)
            deque<pair<int, long long>> deque;
            deque.push_back({m, 0});

            for (int i = m-1; i >= 0; i--)
            {
                // Add distance from current robot to current factory
                prefix += abs(robot[i] - factory[j][0]);

                // Remove entries that exceed factory capacity
                while ( ! deque.empty() && deque.front().first > i + factory[j][1])
                    deque.pop_front();

                // Maintain monotonic property of deque
                while ( ! deque.empty() && deque.back().second >= dp[i][j + 1] - prefix)
                    deque.pop_back();

                // Add current state to deque
                deque.push_back({i, dp[i][j + 1] - prefix});

                // Calculate minimum distance for current state
                dp[i][j] = deque.front().second + prefix;
            }
        }

        // Return minimum total distance starting from first robot and first factory
        return dp[0][0];
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

/* Time  Complexity: O(m * n) */
/* Space Complexity: O(m * n) */
class Solution_Memoization {
public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory)
    {
        int m = robot.size();
        int n = factory.size();

        sort(robot.begin(), robot.end());
        sort(factory.begin(), factory.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0];
        });

        // Memoization table
        vector<vector<long long>> memo(m, vector<long long>(n, -1));

        return dfs(robot, factory, memo, 0, 0);
    }

private:
    long long dfs(vector<int>& robot,
                  vector<vector<int>>& factory,
                  vector<vector<long long>>& memo,
                  int i,
                  int j)
    {
        int m = robot.size();
        int n = factory.size();

        long long infinity = 1e13;

        if (i == m)
            return 0;

        if (j == n)
            return infinity;

        if (memo[i][j] != -1)
            return memo[i][j];

        // Skip the current factory
        long long result = dfs(robot, factory, memo, i, j+1);
        long long sum = 0;

        // Attempt to assign robots to the current factory
        for (int k = i; k < m && k-i+1 <= factory[j][1]; k++)
        {
            sum += std::abs(robot[k] - factory[j][0]);
            result = min(result, sum + dfs(robot, factory, memo, k+1, j+1));
        }

        memo[i][j] = result;

        return result;
    }
};
