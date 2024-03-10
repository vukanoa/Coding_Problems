#include <iostream>
#include <vector>
#include <unordered_map>

/*
    ==============
    === MEDIUM ===
    ==============

    ==================================================
    1443) Minimum Time to Collect All Apples in a Tree
    ==================================================

    ============
    Description:
    ============

    Given an undirected tree consisting of n vertices numbered from 0 to n-1,
    which has some apples in their vertices. You spend 1 second to walk over
    one edge of the tree. Return the minimum time in seconds you have to spend
    to collect all apples in the tree, starting at vertex 0 and coming back to
    this vertex.

    The edges of the undirected tree are given in the array edges, where
    edges[i] = [ai, bi] means that exists an edge connecting the vertices ai
    and bi. Additionally, there is a boolean array hasApple, where hasApple[i]
    = true means that vertex i has an apple; otherwise, it does not have any
    apple.

    ===============================
    FUNCTION:
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---

            ___________0___________
            _____1__________[2]____
            _[4]___[5]____3_____6__

    Input: n = 7,
           edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]],
           hasApple = [false,false,true,false,true,true,false]
    Output: 8
    Explanation: The figure above represents the given tree where red vertices
    have an apple. One optimal path to collect all apples is shown by the green
    arrows.


    --- Example 2 ---
            ___________0___________
            _____1__________[2]____
            __4____[5]____3_____6__

    Input: n = 7,
           edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]],
           hasApple = [false,false,true,false,false,true,false]
    Output: 6
    Explanation: The figure above represents the given tree where red vertices
    have an apple. One optimal path to collect all apples is shown by the green
    arrows.


    --- Example 3 ---
    Input: n = 7,
           edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]],
           hasApple = [false,false,false,false,false,false,false]
    Output: 0


    *** Constraints ***
    1 <= n <= 10^5
    edges.length == n - 1
    edges[i].length == 2
    0 <= ai < bi <= n - 1
    hasApple.length == n

*/

/*
    ------------
    --- IDEA ---
    ------------

    The only "difficult" part here is to realize that you need to add +2 to
    seconds everytime you're coming back from a subtree that has at least one
    apple in its subtree.
    (It can be the root of that subtree as well)

    Also we must "skip" counting seconds for node=0 since it would be redundant

*/

/* Time  Beats: 57.58% */
/* Space Beats: 26.98% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple)
    {
        std::unordered_map<int, std::vector<int>> adj_list;

        for (auto& entry : edges)
        {
            adj_list[entry[0]].push_back(entry[1]);
            adj_list[entry[1]].push_back(entry[0]);
        }

        int seconds = 0;
        dfs(adj_list, hasApple, -1, 0, seconds);

        return seconds;
    }

private:
    bool dfs(std::unordered_map<int, std::vector<int>>& adj_list,
             std::vector<bool>& hasApple,
             int  prev_node,
             int  curr_node,
             int& seconds)
    {
        bool apple = hasApple[curr_node];

        for (int& neighbor : adj_list[curr_node])
        {
            if (neighbor == prev)
                continue;

            if (dfs(adj_list, hasApple, curr_node, neighbor, seconds))
                apple = true;
        }

        if (apple && curr_node > 0)
            seconds += 2;

        return apple;
    }
};
