#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <functional>
#include <climits>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    286) Walls and Gates
    ===========================

    ============
    Description:
    ============

    You are given a m x n 2D grid initialized with these three possible values.

        1. -1 - A wall or an obstacle.
        2. 0 - A gate.
        3. INF - Infinity means an empty room. We use the value 231 - 1 =
           2147483647 to represent INF as you may assume that the distance to a
           gate is less than 2147483647.

    Fill each empty room with the distance to its nearest gate. If it is
    impossible to reach a gate, it should be filled with INF.

    ========================================================================
    FUNCTION: vector<vector<int>> wallsAndGates(vector<vector<int>>& rooms);
    ========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
        INF  -1  0  INF
        INF INF INF  -1
        INF  -1 INF  -1
          0  -1 INF INF

    Input:  [[INF, -1, 0, INF], [INF, INF, INF, -1], [INF, -1, INF, -1],
             [0, -1, INF, INF]]

    Output: [[3, -1, 0, 1], [2, 2, 1, -1], [1, -1, 2, -1], [0, -1, 3, 4]]

        3  -1   0   1
        2   2   1  -1
        1  -1   2  -1
        0  -1   3   4

    *** Constraints ***
    <Unknown>

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Complexity: O(m * n) */
/* Space Complexity: O(m * n) */
class Solution{
private:
    // Custom comparison function for pairs
    struct HashFunction {
        std::size_t operator () (const std::pair<int, int>& p) const
        {
            auto h1 = std::hash<int>()(p.first);
            auto h2 = std::hash<int>()(p.second);

            // Combine the hash values using a bitwise operation
            return h1 & (h2 << 1);
        }
    };

public:
    void WallsAndGates(std::vector<std::vector<int>>& rooms)
    {
        int ROWS = rooms.size();
        int COLS = rooms[0].size();

        std::unordered_set<std::pair<int, int>, HashFunction> visited;
        std::queue<std::pair<int, int>> queue;

        std::function<void(int, int)> add_rooms;

        /* Lambda */
        add_rooms = [&](int r, int c) -> void
        {
            if (r < 0 || r == ROWS ||
                c < 0 || c == COLS ||
                visited.find({r, c}) != visited.end() ||
                rooms[r][c] == -1)
            {
                return;
            }

            visited.insert({r, c});
            queue.push({r, c});
        };

        for (int r = 0; r < ROWS; r++)
        {
            for (int c = 0; c < COLS; c++)
            {
                if (rooms[r][c] == 0)
                {
                    queue.push({r, c});
                    visited.insert({r, c});
                }
            }
        }

        int distance = 0;
        while (!queue.empty())
        {
            int size = queue.size();
            for (int i = 0; i < size; i++)
            {
                std::pair<int, int> pair = queue.front();
                queue.pop();

                int r = pair.first;
                int c = pair.second;

                rooms[r][c] = distance;

                add_rooms(r-1, c  );
                add_rooms(r+1, c  );
                add_rooms(r  , c-1);
                add_rooms(r  , c+1);
            }

            distance++;
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same idea implemented in a much more simple way. Especially because in C++
    you have to write your own Hash Fuctions to be able to use std::pair as a
    key in a HashSet or a HashMap.

    With this implementation, we got rid of it and simplified it overall.

    We don't check if some field is the wall or if we've already visited it.
    Instead, what we do is we only check if the current field is within the
    bounds of matrix "rooms" and check if the CURRENT value is "INF".

    If and only if those conditions are true, we set it's field to "distance"
    which denotes the distance from the closest gate. If later some other field
    realizes that some "INF" field is right next to it, it won't overwrite it
    with a "longer" distance since that field won't be "INF", but some value
    of the distance we've assigned to it before.

*/

/* Time  Complexity: O(m * n) */
/* Space Complexity: O(m * n) */
class Solution_Simplified {
public:
    std::vector<std::vector<int>> wallsAndGates(std::vector<std::vector<int>>& rooms)
    {
        const int ROWS = rooms.size();
        const int COLS = rooms[0].size();

        const int INF = INT_MAX;

        std::queue<std::pair<int, int>> queue;
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                if (rooms[i][j] == 0)
                    queue.push({i, j});
            }
        }

        int distance = 1;
        while (!queue.empty())
        {
            int curr_size = queue.size();

            while (curr_size--)
            {
                auto curr_pos = queue.front();
                queue.pop();

                std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
                for (auto& dir : directions)
                {
                    int row = curr_pos.first  + dir.first;
                    int col = curr_pos.second + dir.second;

                    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && rooms[row][col] == INF)
                    {
                        rooms[row][col] = distance;
                        queue.push({row, col});
                    }
                }
            }

            distance++;
        }

        return rooms;
    }
};


int
main()
{
    Solution            sol;
    Solution_Simplified sol_simplified;

    const int INF = 2147483647;

    /* Example 1 */
    std::vector<std::vector<int>> rooms = {{INF, -1, 0, INF},
                                           {INF, INF, INF, -1},
                                           {INF, -1, INF, -1},
                                           {0, -1, INF, INF}};

    std::cout << "\n\t=======================";
    std::cout << "\n\t=== WALLS AND GATES ===";
    std::cout << "\n\t=======================\n";

    /* Write Input */
    bool first = true;
    std::cout << "\n\tRooms: \n\t[";
    for (auto x: rooms)
    {
        if (!first)
            std::cout << " ";

        bool first_first = true;
        std::cout << "[";
        for (const auto& xx : x)
        {
            if (!first_first)
                std::cout << ", ";

            if (xx == INF)
                std::cout << "INF";
            else if (xx == -1)
                std::cout << " " << xx;
            else
                std::cout << "  " << xx;

            first_first = false;
        }
        std::cout << "]\n\t";

        first = false;
    }
    std::cout << "]\n\n";


    /* Solution */
    // sol.WallsAndGates(rooms);
    sol_simplified.wallsAndGates(rooms);

    /* Write Output */
    first = true;
    std::cout << "\n\tResults: \n\t[";
    for (auto x: rooms)
    {
        if (!first)
            std::cout << " ";

        bool first_first = true;
        std::cout << "[";
        for (const auto& xx : x)
        {
            if (!first_first)
                std::cout << ", ";

            if (xx == -1)
                std::cout << xx;
            else
                std::cout << " " << xx;

            first_first = false;
        }
        std::cout << "]\n\t";

        first = false;
    }
    std::cout << "]\n\n";

    return 0;
}
