/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    130) Surrounded Regions
    ===========================

    ============
    Description:
    ============

    Given an m x n matrix board containing 'X' and 'O', capture all regions
    that are 4-directionally surrounded by 'X'.

    A region is captured by flipping all 'O's into 'X's in that surrounded
    region.

    ==================================================
    FUNCTION: void solve(vector<vector<char>>& board);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    +---+---+---+---+             +---+---+---+---+
    | X | X | X | X |             | X | X | X | X |
    +---+---+---+---+             +---+---+---+---+
    | X | O | O | X |             | X | X | X | X |
    +---+---+---+---+    ====>    +---+---+---+---+
    | X | X | O | X |             | X | X | X | X |
    +---+---+---+---+             +---+---+---+---+
    | X | O | X | X |             | X | O | X | X |
    +---+---+---+---+             +---+---+---+---+

    Input: board = [["X","X","X","X"],
                    ["X","O","O","X"],
                    ["X","X","O","X"],
                    ["X","O","X","X"]]

    Output: [["X","X","X","X"],
             ["X","X","X","X"],
             ["X","X","X","X"],
             ["X","O","X","X"]]

    Explanation: Notice that an 'O' should not be flipped if:
    - It is on the border, or
    - It is adjacent to an 'O' that should not be flipped.
    The bottom 'O' is on the border, so it is not flipped.
    The other three 'O' form a surrounded region, so they are flipped.


    --- Example 2 ---
    Input: board = [["X"]]
    Output: [["X"]]


    *** Constraints ***
    m == board.length
    n == board[i].length
    1 <= m, n <= 200
    board[i][j] is 'X' or 'O'.

*/

#include <queue>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This is one of those problems where you have to think in reverse, i.e. you
    have to INVERT the problem.

    Instead of asking yourself:
        "How do I capture all regions where Os are surrounded by X?"

    Ask this instead:
        "How do I mark all the Os that are 4-directionally connected to one of
         four edges of this entire matrix?"


    We will use boundary DFS to solve this problem.
    Consider these two cases for clarity:

            Os won't be flipped           Os will be flipped
            +---+---+---+---+---+        +---+---+---+---+---+   
            | X | O | X | X | X |        | X | O | X | X | X |   
            +---+---+---+---+---+        +---+---+---+---+---+   
            | X | O | O | O | X |        | X | O | O | O | X |   
            +---+---+---+---+---+        +---+---+---+---+---+   
            | X | O | X | X | X |        | X | O | X | X | X |   
            +---+---+---+---+---+        +---+---+---+---+---+   
            | X | X | X | X | X |        | X | X | X | X | X |   
            +---+---+---+---+---+        +---+---+---+---+---+   

    As we've said - We want to ask ourselves:
    "How do I mark all the Os that are 4-directionally connected to one of
     four edges of this entire matrix?"

    Why do we want to mark them in the first place?

    Because once we mark those Os that are connected to any edge by a
    4-directional Os, then and only then can we flip all of the remaining
    Os(the ones that are NOT connected to any edge, i.e. the ones that are
    indeed surrounded entirely by X) without messing up the rest of the grid.

    Once we capture those surrounded O's, then all we have to do is flip our
    previously marked Os(let's say we've marked them with a '#') back to O and
    voila.


    Steps to Solve:
    1. Move over the boundary of board, and find Os

    2. Every time we find an O, perform DFS from it's position

    3. In DFS convert all 'O's to '#'
       (why? so that we can differentiate which 'O' can be flipped and which
        CANNOT be)

    4. After all DFSs have been performed, board contains three elements:
       '#', 'O' and 'X'

    5. 'O' are left over elements which are not connected to any boundary O,
       therefore - Flip them to 'X'(i.e. capture all of those O's).

    6. '#' are elements(O's) which cannot be flipped to 'X', so flip them
       back to 'O'

*/

/* Time  Beats: 100.00% */
/* Space Beats:  89.87% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution_DFS {
public:
    void solve(vector<vector<char>>& board)
    {
        const int ROWS = board.size();
        const int COLS = board[0].size();

        // First and last ROW
        for (int col = 0; col < COLS; col++)
        {
            dfs(0,      col, board);
            dfs(ROWS-1, col, board);
        }

        // First and last COLUMN
        for (int row = 0; row < ROWS; row++)
        {
            dfs(row, 0     , board);
            dfs(row, COLS-1, board);
        }

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (board[row][col] == '#')
                    board[row][col] = 'O';
                else
                    board[row][col] = 'X';
            }
        }
    }

private:
    void dfs(int row, int col, vector<vector<char>>& board)
    {
        const int ROWS = board.size();
        const int COLS = board[0].size();

        if (row < 0 || col < 0 || row >= ROWS || col >= COLS)
            return;

        if (board[row][col] != 'O')
            return;

        board[row][col] = '#';

        /* Signing Cross */
        dfs(row-1, col  , board); // Up
        dfs(row+1, col  , board); // Down
        dfs(row  , col-1, board); // Left
        dfs(row  , col+1, board); // Right
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Just a BFS Implementation.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  46.65% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution_BFS_Surrounding {
public:
    void solve(vector<vector<char>>& board)
    {
        const int ROWS = board.size();
        const int COLS = board[0].size();

        // First and last ROW
        for (int col = 0; col < COLS; col++)
        {
            if (board[0     ][col] == 'O') bfs(0,      col, board);
            if (board[ROWS-1][col] == 'O') bfs(ROWS-1, col, board);
        }

        // First and last COLUMN
        for (int row = 0; row < ROWS; row++)
        {
            if (board[row][0     ] == 'O') bfs(row, 0     , board);
            if (board[row][COLS-1] == 'O') bfs(row, COLS-1, board);
        }

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (board[row][col] == '#')
                    board[row][col] = 'O';
                else
                    board[row][col] = 'X';
            }
        }
    }

private:
    void bfs(int row, int col, vector<vector<char>>& board)
    {
        const int ROWS = board.size();
        const int COLS = board[0].size();

        queue<pair<int,int>> queue;
        queue.push( {row, col} );

        board[row][col] = '#';

        vector<pair<int,int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};

        /* BFS */
        while ( ! queue.empty())
        {
            auto [curr_row, curr_col] = queue.front();
            queue.pop();

            for (const auto& dir : directions)
            {
                int new_row = curr_row + dir.first;
                int new_col = curr_col + dir.second;

                if (new_row < 0 || new_col < 0 || new_row >= ROWS || new_col >= COLS)
                    continue;

                if (board[new_row][new_col] != 'O')
                    continue;

                board[new_row][new_col] = '#';
                queue.push( {new_row, new_col} );
            }
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is a bit unusual DSU because it takes advantage of a "dummy node".

    The technique of using a "dummy node" is usually associated with Linked
    List problems, however it's VERY beneficial to understand this one as well.

    It is just an additional node that we've invented "out of the blue" and are
    using to see if 'O' nodes are connected to it or not.

    If they ARE, then that means they're the 'O's that are connected to the
    edge.

    Otherwise they're no and we shall capture them later.


    Also, it's important to note that this DSU Solution is using a technique
    called:

        "1D Flatteing technique"

    which treats the grid as if it's a one continuous row.

    In order to get to some [row][col] you index it like this:

            [row * COLS + col]

    We're using a lambda function to calculate the proper index based on the
    provided "row" and "col".

*/

/* Time  Beats: 100.00% */
/* Space Beats:  35.37% */

/* Time  Complexity: O(ROWS * COLS * alpha(ROWS * COLS)) */
/* Space Complexity: O(ROWS * COLS)                      */
class DSU {
private:
    vector<int> rank;
    vector<int> parent;

public:
    DSU(int n)
    {
        // +1 because of the DUMMY node, connected to the border
        rank.resize(n + 1);
        parent.resize(n + 1);

        for (int i = 0; i < n+1; i++) // n+1 and not just "n" because of dummy
        {
            rank[i]   = 1;
            parent[i] = i;
        }
    }

    int find_root(int node)
    {
        while (node != parent[node])
        {
            /* Reverse Ackerman function */
            parent[node] = parent[parent[node]];

            node = parent[node];
        }

        return node;
    }

    bool union_components(int node_1, int node_2)
    {
        int root_1 = find_root(node_1);
        int root_2 = find_root(node_2);

        if (root_1 == root_2)
            return false;

        if (rank[root_1] < rank[root_2])
            swap(root_1, root_2);

        parent[root_2] = root_1;
        rank[root_1]  += rank[root_2];

        return true;
    }

    bool connected(int node_1, int node_2)
    {
        return find_root(node_1) == find_root(node_2);
    }
};

class Solution_DSU_Dummy_Node {
public:
    void solve(vector<vector<char>>& board)
    {
        const int ROWS = board.size();
        const int COLS = board[0].size();

        vector<pair<int,int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};

        /* Lambda */
        auto index = [COLS](int row, int col) { return row * COLS + col; };

        DSU dsu(ROWS * COLS);

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (board[row][col] != 'O')
                    continue;

                if (row == 0 || col == 0 || row == ROWS-1 || col == COLS-1)
                {
                    int curr_node = index(row , col);
                    int edge_node = index(ROWS, 0  ); // Dummy node

                    dsu.union_components(curr_node, edge_node);
                }
                else
                {
                    for (const auto& dir : directions)
                    {
                        int new_row = row + dir.first;
                        int new_col = col + dir.second;

                        // Here it's IMPOSSIBLE to be Out-of-Bounds

                        if (board[new_row][new_col] != 'O')
                            continue;

                        int curr_node = index(row    , col    );
                        int next_node = index(new_row, new_col);

                        dsu.union_components(curr_node, next_node);
                    }
                }
            }
        }


        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                int curr_node = index(row , col);
                int edge_node = index(ROWS, 0  ); // Dummy node

                if ( ! dsu.connected(curr_node, edge_node))
                    board[row][col] = 'X';
            }
        }
    }
};
