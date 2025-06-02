/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================
    3568) Minimum Moves to Clean the Classroom
    ==========================================

    ============
    Description:
    ============

    You are given an m x n grid classroom where a student volunteer is tasked
    with cleaning up litter scattered around the room. Each cell in the grid is
    one of the following:

        'S': Starting position of the student

        'L': Litter that must be collected (once collected, the cell becomes
                                           empty)

        'R': Reset area that restores the student's energy to full capacity,
             regardless of their current energy level (can be used multiple
             times)

        'X': Obstacle the student cannot pass through

        '.': Empty space

    You are also given an integer energy, representing the student's maximum
    energy capacity. The student starts with this energy from the starting
    position 'S'.

    Each move to an adjacent cell (up, down, left, or right) costs 1 unit of
    energy. If the energy reaches 0, the student can only continue if they are
    on a reset area 'R', which resets the energy to its maximum capacity energy

    Return the minimum number of moves required to collect all litter items,
    or -1 if it's impossible.

    ==============================================================
    FUNCTION: int minMoves(vector<string>& classroom, int energy);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: classroom = ["S.", "XL"], energy = 2
    Output: 2
    Explanation:
        The student starts at cell (0, 0) with 2 units of energy.
        Since cell (1, 0) contains an obstacle 'X', the student cannot move directly downward.
        A valid sequence of moves to collect all litter is as follows:
            Move 1: From (0, 0) → (0, 1) with 1 unit of energy and 1 unit remaining.
            Move 2: From (0, 1) → (1, 1) to collect the litter 'L'.
        The student collects all the litter using 2 moves. Thus, the output is 2.


    --- Example 2 ---
    Input: classroom = ["LS", "RL"], energy = 4
    Output: 3
    Explanation:
        The student starts at cell (0, 1) with 4 units of energy.
        A valid sequence of moves to collect all litter is as follows:
            Move 1: From (0, 1) → (0, 0) to collect the first litter 'L' with 1 unit of energy used and 3 units remaining.
            Move 2: From (0, 0) → (1, 0) to 'R' to reset and restore energy back to 4.
            Move 3: From (1, 0) → (1, 1) to collect the second litter 'L'.
        The student collects all the litter using 3 moves. Thus, the output is 3.


    --- Example 3 ---
    Input: classroom = ["L.S", "RXL"], energy = 3
    Output: -1
    Explanation:
    No valid path collects all 'L'.


    *** Constraints ***
    1 <= m == classroom.length <= 20
    1 <= n == classroom[i].length <= 20
    classroom[i][j] is one of 'S', 'L', 'R', 'X', or '.'
    1 <= energy <= 50
    There is exactly one 'S' in the grid.
    There are at most 10 'L' cells in the grid.

*/

#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <tuple>
#include <climits>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Dijkstra with 3 states.

    TODO

*/

/* Time  Beats:  7.69% */
/* Space Beats: 92.31% */

/* Time  Complexity: O(ROWS * COLS * 2^number_of_litter_spots) */
/* Space Complexity: O(ROWS * COLS * 2^number_of_litter_spots) */
using namespace std;
class Solution {
public:
    int minMoves(vector<string>& classroom, int energy)
    {
        const int ROWS = classroom.size();
        const int COLS = classroom[0].size();

        unordered_map<int, int> umap_litter;

        int start_row = -1;
        int start_col = -1;

        int litter_index = 0;

        for (int i = 0; i < ROWS; ++i)
        {
            for (int j = 0; j < COLS; ++j)
            {
                if (classroom[i][j] == 'S')
                {
                    start_row = i;
                    start_col = j;
                }
                else if (classroom[i][j] == 'L')
                {
                    umap_litter[i * COLS + j] = litter_index++;
                }
            }
        }

        int total_litter = litter_index;
        if (total_litter == 0)
            return 0;

        /* Signing Cross */
        vector<pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};

        // moves, row, col, energy_left, mask
        using State = tuple<int, int, int, int, int>;

        priority_queue<State, vector<State>, greater<State>> max_heap;
        max_heap.emplace(0, start_row, start_col, energy, 0);

        unordered_map<long long, int> visited;

        /* Dijksta */
        while ( ! max_heap.empty())
        {
            auto [moves, row, col, energy_left, mask] = max_heap.top();
            max_heap.pop();

            if (mask == (1 << total_litter) - 1)
                return moves;

            long long state_key = ((long long)row << 40) | ((long long)col << 30) | mask;
            if (visited.count(state_key) && visited[state_key] >= energy_left)
                continue;

            visited[state_key] = energy_left;

            for (const auto& dir : directions)
            {
                int new_row = row + dir.first;
                int new_col = col + dir.second;

                if (new_row < 0 || new_col < 0 || new_row >= ROWS || new_col >= COLS)
                    continue;

                char cell = classroom[new_row][new_col];
                if (cell == 'X')
                    continue;

                if (energy_left == 0)
                    continue;

                int next_energy = (cell == 'R') ? energy : energy_left - 1;
                if (next_energy < 0)
                    continue;

                int next_mask = mask;
                int pos_key = new_row * COLS + new_col;

                if (cell == 'L' && umap_litter.count(pos_key))
                    next_mask |= (1 << umap_litter[pos_key]);

                max_heap.emplace(moves + 1, new_row, new_col, next_energy, next_mask);
            }
        }

        return -1;
    }
};
