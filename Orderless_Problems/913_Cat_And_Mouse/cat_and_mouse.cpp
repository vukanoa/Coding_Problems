#include <iostream>

/*
    ============
    === HARD ===
    ============

    ===========================
    913) Cat and Mouse
    ===========================

    ============
    Description:
    ============

    A game on an undirected graph is played by two players, Mouse and Cat, who
    alternate turns.

    The graph is given as follows: graph[a] is a list of all nodes b such that
    ab is an edge of the graph.

    The mouse starts at node 1 and goes first, the cat starts at node 2 and
    goes second, and there is a hole at node 0.

    During each player's turn, they must travel along one edge of the graph
    that meets where they are.  For example, if the Mouse is at node 1, it must
    travel to any node in graph[1].

    Additionally, it is not allowed for the Cat to travel to the Hole (node 0).

    Then, the game can end in three ways:

        + If ever the Cat occupies the same node as the Mouse, the Cat wins.

        + If ever the Mouse reaches the Hole, the Mouse wins.

        + If ever a position is repeated (i.e., the players are in the same
          position as a previous turn, and it is the same player's turn to
          move), the game is a draw.

    Given a graph, and assuming both players play optimally, return

        1 if the mouse wins the game,
        2 if the cat wins the game, or
        0 if the game is a draw.


    =======================================================
    FUNCTION: int catMouseGame(vector<vector<int>>& graph); 
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---

            4 --------- 3 --------- 1
            |           |
            |           |
            2 --------- 5
            |          /
            |         /
            |        /
            0 -------

    Input: graph = [[2,5],[3],[0,4,5],[1,4,5],[2,3],[0,2,3]]
    Output: 0



    --- Example 2 ---
            0 --------- 1
            |
            |
            3 --------- 2
    Input: graph = [[1,3],[0],[3],[0,2]]
    Output: 1



    *** Constraints ***
    3 <= graph.length <= 50
    1 <= graph[i].length < graph.length
    0 <= graph[i][j] < graph.length
    graph[i][j] != i
    graph[i] is unique.
    The mouse and the cat can always move. 

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 23.16% */
/* Space Beats: 28.95% */

/* Time  Complexity: O(n^3) */
/* Space Complexity: O(n^2) */
class Solution {
public:
    std::vector<std::vector<int>> adj_list;
    std::set<std::pair< std::pair<int,int>, int>> uset;

    int dp[51][51][2];

    int catMouseGame(std::vector<std::vector<int>>& graph)
    {
        adj_list=graph;
        int result;
        for(int turn=0;turn<50;turn++)
        {
            for(int i = 0; i < 51;i++)
            {
                for(int j = 1; j < 51; j++)
                {
                    for(int k = 0; k < 2; k++)
                    {
                        if(dp[i][j][k] == 0)
                            dp[i][j][k] -= 1;
                    }
                }
            }

            result=solve(1,2,0,1);
        }

        return result;
    }

private:

    int solve (int i, int j, int k,int win)
    {
        if (i==j)
            return 2;
        else if (i==0)
            return 1;
        if (dp[i][j][k] != -1 )
             return dp[i][j][k];
        if (uset.find({{i,j},k}) != uset.end())
            return 0;
        else
            uset.insert({{i,j},k});

        bool won  = false;
        bool draw = false;

        if (k == 0)
        {
            int temp;
            for (auto it:adj_list[i])
            {
                temp = solve(it,j,1,2);

                if(temp == 0)
                    draw=true;
                else if (temp == 1)
                {
                    won = true;
                    break;
                }
            }

        }
        else
        {
            int temp;
            for(auto it:adj_list[j])
            {
                if (it == 0)
                    continue;

                temp = solve(i,it,0,1);

                if (temp == 0)
                    draw = true;
                else if (temp==2)
                {
                    won = true;
                    break;
                }
            }
        }

        uset.erase({{i,j},k});

        if (won)
            return dp[i][j][k]=win;
        else if (draw)
            return dp[i][j][k]= 0;
        else
        {
            if (win == 1)
                return dp[i][j][k]=2;
            else
                return dp[i][j][k]=1;

        }
    }
};
