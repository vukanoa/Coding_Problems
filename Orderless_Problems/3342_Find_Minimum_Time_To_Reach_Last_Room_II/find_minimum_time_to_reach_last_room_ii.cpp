/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    3342) Find Minimum Time to Reach Last Room II
    =============================================

    ============
    Description:
    ============

    There is a dungeon with n x m rooms arranged as a grid.

    You are given a 2D array moveTime of size n x m, where moveTime[i][j]
    represents the minimum time in seconds when you can start moving to that
    room. You start from the room (0, 0) at time t = 0 and can move to an
    adjacent room. Moving between adjacent rooms takes one second for one move
    and two seconds for the next, alternating between the two.

    Return the minimum time to reach the room (n - 1, m - 1).

    Two rooms are adjacent if they share a common wall, either horizontally or
    vertically.

    =============================================================
    FUNCTION: int minTimeToReach(vector<vector<int>>& move_time);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: moveTime = [[0,4],[4,4]]
    Output: 7
    Explanation:
    The minimum time required is 7 seconds.
        At time t == 4, move from room (0, 0) to room (1, 0) in one second.
        At time t == 5, move from room (1, 0) to room (1, 1) in two seconds.


    --- Example 2 ---
    Input: moveTime = [[0,0,0,0],[0,0,0,0]]
    Output: 6
    Explanation:
    The minimum time required is 6 seconds.
        At time t == 0, move from room (0, 0) to room (1, 0) in one second.
        At time t == 1, move from room (1, 0) to room (1, 1) in two seconds.
        At time t == 3, move from room (1, 1) to room (1, 2) in one second.
        At time t == 4, move from room (1, 2) to room (1, 3) in two seconds.


    --- Example 3 ---
    Input: moveTime = [[0,1],[1,2]]
    Output: 4


    *** Constraints ***
    2 <= n == moveTime.length <= 750
    2 <= m == moveTime[i].length <= 750
    0 <= moveTime[i][j] <= 10^9

*/

#include <queue>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    It may seem to you that this can be done using Memoizaton, however,
    especially if you're allocating "memo" on the stack, it would take:

        751 * 751 * 2 = 1128002

    Which is more than 10^6 and that is the unoffocial maximum for Stack Size
    on LeetCode.


    But even if it didn't look like a Memoization problem at all, the fact that
    it says "Find MINIMUM time to reach cell X" is highgly indicative that you
    ought to use Dijkstra's algorithm.

*/

/* Time  Beats: 75.53% */
/* Space Beats: 93.88% */

/* Time  Complexity: O(ROWS * COLS * log(ROWS * COLS)) */
/* Space Complexity: O(ROWS * COL)                     */
class Solution {
private:
    struct State {
        int row;
        int col;
        int distance;

        State(int r, int c, int d) : row(r), col(c), distance(d) {}
    };

    static const inline auto cmp = [](const State& a, const State& b) { return a.distance > b.distance; };

    const int INF = 0x3f3f3f3f; // Safe value, to prevent Overflow

public:
    int min_time_to_reach(vector<vector<int>>& move_time)
    {
        const int ROWS = move_time.size();
        const int COLS = move_time[0].size();

        vector<vector<int>>  distances(ROWS, vector<int> (COLS, INF));
        vector<vector<bool>> visited  (ROWS, vector<bool>(COLS, false));

        priority_queue<State, vector<State>, decltype(cmp)> min_heap(cmp);
        min_heap.push(State(0, 0, 0));
        distances[0][0] = 0;

        /* Signing Cross */
        vector<pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};

        /* Dijkstra */
        while ( ! min_heap.empty())
        {
            State current = min_heap.top();
            min_heap.pop();

            if (visited[current.row][current.col])
                continue;

            visited[current.row][current.col] = true;

            if (current.row == ROWS - 1 && current.col == COLS - 1)
                break;

            for (const auto& dir : directions)
            {
                int next_row = current.row + dir.first;
                int next_col = current.col + dir.second;

                if (next_row < 0 || next_col < 0 || next_row >= ROWS || next_col >= COLS)
                    continue;

                int time_penalty = (current.row + current.col) % 2 + 1; // Since penalties are alternating
                int new_distance = time_penalty + max(distances[current.row][current.col], move_time[next_row][next_col]);

                if (new_distance < distances[next_row][next_col])
                {
                    distances[next_row][next_col] = new_distance;
                    min_heap.push(State(next_row, next_col, new_distance));
                }
            }
        }

        return distances[ROWS - 1][COLS - 1];
    }
};
