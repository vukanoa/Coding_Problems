#include <iostream>
#include <vector>
#include <numeric>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    547) Number Of Provinces
    ===========================

    ============
    Description:
    ============

    There are n cities. Some of them are connected, while some are not. If city
    a is connected directly with city b, and city b is connected directly with
    city c, then city a is connected indirectly with city c.

    A province is a group of directly or indirectly connected cities and no
    other cities outside of the group.

    You are given an n x n matrix isConnected where isConnected[i][j] = 1 if
    the ith city and the jth city are directly connected, and isConnected[i][j]
    = 0 otherwise.

    Return the total number of provinces.

    ==============================================================
    FUNCTION: int findCircleNum(vector<vector<int>>& isConnected);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---

            1 --- 2
               3

    Input: isConnected = [[1,1,0],[1,1,0],[0,0,1]]
    Output: 2





    --- Example 2 ---

            1     2
               3

    Input: isConnected = [[1,0,0],[0,1,0],[0,0,1]]
    Output: 3





    *** Constraints ***
    1 <= n <= 200
    n == isConnected.length
    n == isConnected[i].length
    isConnected[i][j] is 1 or 0.
    isConnected[i][i] == 1
    isConnected[i][j] == isConnected[j][i]

*/

/*
    ------------
    --- IDEA ---
    ------------

    Union & Find Algorithm.

    Same as in problem 323 in this directory.

*/

/* Time  Beats: 97.84% */
/* Space Beats: 39.91% */

/* Time  Complexity: O(m * n) */
/* Space Complexity: O(m) */
class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected)
    {
        int m = isConnected.size();
        int n = isConnected[0].size();

        std::vector<std::pair<int, int>> edges;

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i == j)
                    continue;

                if (isConnected[i][j] && isConnected[j][i])
                    edges.push_back({i, j});
            }
        }

        // m is the number of nodes
        std::vector<int> parent(m);
        std::vector<int> rank(m, 1);

        std::iota(parent.begin(), parent.end(), 0);

        int count = m;
        for (std::pair<int, int>& edge : edges)
            count -= Union(edge.first, edge.second, parent, rank);

        return count;
    }

private:
    int Find(int node_val, std::vector<int>& parent)
    {
        int tmp = node_val;

        while (tmp != parent[tmp])
        {
            parent[tmp] = parent[parent[tmp]];
            tmp = parent[tmp];
        }

        return tmp;
    }

    int Union(int node_val_1, int node_val_2, std::vector<int>& parent, std::vector<int>& rank)
    {
        // Parent 1 & Parent 2
        int p1 = Find(node_val_1, parent);
        int p2 = Find(node_val_2, parent);

        if (p1 == p2)
            return 0;

        if (rank[p1] > rank[p2])
        {
            parent[p2] = p1;
            rank[p1] += rank[p2];
        }
        else // rank[p2] >= rank[p1]
        {
            parent[p1] = p2;
            rank[p2] += rank[p1];
        }

        return 1;
    }
};
