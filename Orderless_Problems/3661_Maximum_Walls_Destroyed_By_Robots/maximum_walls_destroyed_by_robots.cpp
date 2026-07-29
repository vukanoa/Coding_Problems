/*
    ============
    === HARD ===
    ============

    =======================================
    3661) Maximum Walls Destroyed by Robots
    =======================================

    ============
    Description:
    ============

    There is an endless straight line populated with some robots and walls. You
    are given integer arrays robots, distance, and walls:

        + robots[i] is the position of the ith robot.
        + distance[i] is the maximum distance the ith robot's bullet can travel
        + walls[j] is the position of the jth wall.

    Every robot has one bullet that can either fire to the left or the right at most distance[i] meters.

    A bullet destroys every wall in its path that lies within its range. Robots
    are fixed obstacles: if a bullet hits another robot before reaching a wall,
    it immediately stops at that robot and cannot continue.

    Return the maximum number of unique walls that can be destroyed by the
    robots.

    =====
    Note: A wall and a robot may share the same position; the wall can be
          destroyed by the robot at that position. Robots are not destroyed by
          bullets.
    =====

    =======================================================================================
    FUNCTION: int maxWalls(vector<int>& robots, vector<int>& distance, vector<int>& walls);
    =======================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: robots = [4], distance = [3], walls = [1,10]
    Output: 1
    Explanation:
        robots[0] = 4 fires left with distance[0] = 3, covering [1, 4] and
        destroys walls[0] = 1. Thus, the answer is 1.

    --- Example 2 ---
    Input: robots = [10,2], distance = [5,1], walls = [5,2,7]
    Output: 3
    Explanation:
        robots[0] = 10 fires left with distance[0] = 5, covering [5, 10] and
        destroys walls[0] = 5 and walls[2] = 7.
        robots[1] = 2 fires left with distance[1] = 1, covering [1, 2] and
        destroys walls[1] = 2.
        Thus, the answer is 3.

    --- Example 3 ---
    Input: robots = [1,2], distance = [100,1], walls = [10]
    Output: 0
    Explanation:
    In this example, only robots[0] can reach the wall, but its shot to the
    right is blocked by robots[1]; thus the answer is 0.



    *** Constraints ***
    1 <= robots.length == distance.length <= 10^5
    1 <= walls.length <= 10^5
    1 <= robots[i], walls[j] <= 10^9
    1 <= distance[i] <= 10^5
    All values in robots are unique
    All values in walls are unique

*/

#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 61.64% */
/* Space Beats: 60.35% */

/* Time  Complexity: O(N log N + M log M) */
/* Space Complexity: O(N)                 */
class Solution {
public:
    int maxWalls(vector<int>& robots, vector<int>& distance, vector<int>& walls)
    {
        const int N = robots.size();

        unordered_map<int, int> dist;
        for (int i = 0; i < N; i++)
            dist[robots[i]] = distance[i];

        /* Sort */
        sort(robots.begin(), robots.end());
        sort(walls.begin(), walls.end());

        vector<int> left(N);
        vector<int> right(N);
        vector<int> between(N);

        for (int i = 0; i < N; i++)
        {
            const int robot = robots[i];

            const int wall_after = upper_bound(walls.begin(), walls.end(), robot) - walls.begin();

            int left_limit = robot - dist[robot];
            if (i > 0)
                left_limit = max(left_limit, robots[i - 1] + 1);

            const int left_wall = lower_bound(walls.begin(), walls.end(), left_limit) - walls.begin();

            left[i] = wall_after - left_wall;

            int right_limit = robot + dist[robot];
            if (i + 1 < N)
                right_limit = min(right_limit, robots[i + 1] - 1);

            const int right_wall  = upper_bound(walls.begin(), walls.end(), right_limit) - walls.begin();
            const int wall_before = lower_bound(walls.begin(), walls.end(), robot      ) - walls.begin();

            right[i] = right_wall - wall_before;

            if (i == 0)
                continue;

            const int prev_wall = lower_bound(walls.begin(), walls.end(), robots[i - 1]) - walls.begin();

            between[i] = wall_after - prev_wall;
        }

        int dp_left  = left[0];
        int dp_right = right[0];

        for (int i = 1; i < N; i++)
        {
            const int new_left = max(dp_left + left[i],
                                     dp_right - right[i - 1] + min(left[i] + right[i - 1], between[i]));

            const int new_right = max(dp_left + right[i],
                                      dp_right + right[i]);

            dp_left  = new_left;
            dp_right = new_right;
        }

        return max(dp_left, dp_right);
    }
};
