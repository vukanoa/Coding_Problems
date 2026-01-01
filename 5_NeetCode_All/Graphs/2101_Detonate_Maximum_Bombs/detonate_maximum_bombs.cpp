#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    ============================
    2101) Detonate Maximum Bombs
    ============================

    ============
    Description:
    ============

    You are given a list of bombs. The range of a bomb is defined as the area
    where its effect can be felt. This area is in the shape of a circle with
    the center as the location of the bomb.

    The bombs are represented by a 0-INDEXED 2D integer array bombs where
    bombs[i] = [xi, yi, ri]. xi and yi denote the X-coordinate and Y-coordinate
    of the location of the ith bomb, whereas ri denotes the radius of its
    range.

    You may choose to detonate a SINGLE bomb. When a bomb is detonated, it will
    detonate ALL BOMBS that lie in its range. These bombs will further detonate
    the bombs that lie in their ranges.

    Given the list of bombs, return the maximum number of bombs that can be
    detonated if you are allowed to detonate ONLY ONE bomb.

    ============================================================
    FUNCTION: int maximumDetonation(vector<vector<int>>& bombs);
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---

    ^
    |
    |              ______________________
    |             /                      \
    |            /                        \
    |     ______/_____                     \
    |    /     /      \                     \
    |   /      |       \                     |
    |  |       |        |                    |
    |  |       x        |    x               |
    |--|-------|--------|--------------------|-------------------------->
    |  |       |        |                    |
    |   \       \      /                    /
    |    \_______\____/                    /
    |             \                       /
    |              \_____________________/
    |
    |


    Input: bombs = [[2,1,3],[6,1,4]]
    Output: 2
    Explanation:
    The above figure shows the positions and ranges of the 2 bombs.
    If we detonate the left bomb, the right bomb will not be affected.
    But if we detonate the right bomb, both bombs will be detonated.
    So the maximum bombs that can be detonated is max(1, 2) = 2.





    --- Example 2 ---

           ^
           |
           |
           |                     ____________
           |                    /            \
           |                   /              \
           |                  |                |
           |                  |       x        |
           |                  |                |
           |                  |                |
           |                   \              /
           |                    \____________/
           |
           |
          _|___________
         / |           \
        /  |            \
       |   |             |
       |   |    x        |
       |   |             |
 ------| --|-------------|---------------------------------------------------->
        \  |            /
         \_|___________/
           |
           |
           |
           |

    Input: bombs = [[1,1,5],[10,10,5]]
    Output: 1
    Explanation:
    Detonating either bomb will not detonate the other bomb, so the maximum
    number of bombs that can be detonated is 1.|





    --- Example 3 ---

        Drawing would be too impractical

    Input: bombs = [[1,2,3],[2,3,1],[3,4,2],[4,5,3],[5,6,4]]
    Output: 5
    Explanation:
    The best bomb to detonate is bomb 0 because:
    - Bomb 0 detonates bombs 1 and 2. The red circle denotes the range of bomb
      0.
    - Bomb 2 detonates bomb 3. The blue circle denotes the range of bomb 2.
    - Bomb 3 detonates bomb 4. The green circle denotes the range of bomb 3.

    Thus all 5 bombs are detonated.


    *** Constraints ***
    1 <= bombs.length <= 100
    bombs[i].length == 3
    1 <= xi, yi, ri <= 10^5

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:  7.41% */
/* Space Beats: 29.50% */

/* Time  Complexity: O(n^3) */
/* Space Complexity: O(n^2) */
class Solution_BFS {
public:
    int maximumDetonation(std::vector<std::vector<int>>& bombs)
    {
        int result = 0;
        std::unordered_set<int> visited;

        for (int i = 0; i < bombs.size(); i++)
        {
            int detonated = BFS(bombs, visited, i);
            visited.clear();

            result = std::max(result, detonated);
        }

        return result;
    }

private:
    double distance(int& x1, int& y1, int& x2, int& y2)
    {
        return 1.0 * std::sqrt(1.0*(x2 - x1)*(x2 - x1) + 1.0*(y2 - y1)*(y2 - y1));
    }

    int BFS(std::vector<std::vector<int>>& bombs,
            std::unordered_set<int>& visited,
            int  bomb)
    {
        visited.insert(bomb);

        std::queue<int> queue;
        queue.push(bomb);

        int detonated = 1;

        /* BFS */
        while (!queue.empty())
        {
            int size = queue.size();

            for (int x = 0; x < size; x++)
            {
                int curr_bomb = queue.front();
                queue.pop();

                int curr_x = bombs[curr_bomb][0];
                int curr_y = bombs[curr_bomb][1];
                int curr_r = bombs[curr_bomb][2]; // radius

                for (int i = 0; i < bombs.size(); i++)
                {
                    int i_x = bombs[i][0];
                    int i_y = bombs[i][1];
                    int i_r = bombs[i][2]; // radius

                    if (visited.count(i))
                        continue;
                    else if (distance(curr_x, curr_y, i_x, i_y) > 1.0*curr_r)
                        continue;

                    visited.insert(i);
                    queue.push(i);
                    detonated++;
                }
            }
        }

        return detonated;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 18.09% */
/* Space Beats: 24.72% */

/* Time  Complexity: O(n^3) */
/* Space Complexity: O(n^2) */
class Solution_DFS {
public:
    int maximumDetonation(std::vector<std::vector<int>>& bombs)
    {
        std::unordered_map<int, std::vector<int>> adj_list;

        for (int i = 0; i < bombs.size(); i++)
        {
            int x1 = bombs[i][0];
            int y1 = bombs[i][1];
            int r1 = bombs[i][2];

            for (int j = i+1; j < bombs.size(); j++)
            {
                int x2 = bombs[j][0];
                int y2 = bombs[j][1];
                int r2 = bombs[j][2];

                double dist= distance(x1, y1, x2, y2);

                if (dist <= 1.0*r1)
                    adj_list[i].push_back(j);

                if (dist <= 1.0*r2)
                    adj_list[j].push_back(i);
            }
        }

        int result = 0;
        for (int i = 0; i < bombs.size(); i++)
        {
            std::unordered_set<int> new_visited;
            int detonated = dfs(bombs, adj_list, new_visited, i);

            result = std::max(result, detonated);
        }

        return result;
    }

private:
    double distance(int& x1, int& y1, int& x2, int& y2)
    {
        return 1.0 * std::sqrt(1.0*(x2 - x1)*(x2 - x1) + 1.0*(y2 - y1)*(y2 - y1));
    }

    int dfs(std::vector<std::vector<int>>& bombs,
            std::unordered_map<int, std::vector<int>>& adj_list,
            std::unordered_set<int>& visited,
            int i)
    {
        if (visited.count(i))
            return 0;

        visited.insert(i);
        for (const auto& nei : adj_list[i])
            dfs(bombs, adj_list, visited, nei);

        return visited.size();
    }
};
