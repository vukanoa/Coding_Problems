#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    =========================================================
    2192) All Ancestors of a Node in a Directed Acyclic Graph
    =========================================================

    ============
    Description:
    ============

    You are given a positive integer n representing the number of nodes of a
    Directed Acyclic Graph (DAG). The nodes are numbered from 0 to n - 1
    (inclusive).

    You are also given a 2D integer array edges, where edges[i] = [fromi, toi]
    denotes that there is a unidirectional edge from fromi to toi in the graph.

    Return a list answer, where answer[i] is the list of ancestors of the ith
    node, sorted in ascending order.

    A node u is an ancestor of another node v if u can reach v via a set of
    edges.

    ==============================================================================
    FUNCTION: vector<vector<int>> getAncestors(int n, vector<vector<int>>& edges); 
    ==============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 8, edgeList = [[0,3],[0,4],[1,3],[2,4],[2,7],[3,5],[3,6],[3,7],[4,6]]
    Output: [[],[],[],[0,1],[0,2],[0,1,3],[0,1,2,3,4],[0,1,2,3]]
    Explanation:
    The above diagram represents the input graph.
    - Nodes 0, 1, and 2 do not have any ancestors.
    - Node 3 has two ancestors 0 and 1.
    - Node 4 has two ancestors 0 and 2.
    - Node 5 has three ancestors 0, 1, and 3.
    - Node 6 has five ancestors 0, 1, 2, 3, and 4.
    - Node 7 has four ancestors 0, 1, 2, and 3.


    --- Example 2 ---
    Input: n = 5, edgeList = [[0,1],[0,2],[0,3],[0,4],[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
    Output: [[],[0],[0,1],[0,1,2],[0,1,2,3]]
    Explanation:
    The above diagram represents the input graph.
    - Node 0 does not have any ancestor.
    - Node 1 has one ancestor 0.
    - Node 2 has two ancestors 0 and 1.
    - Node 3 has three ancestors 0, 1, and 2.
    - Node 4 has four ancestors 0, 1, 2, and 3.


    *** Constraints ***
    1 <= n <= 1000
    0 <= edges.length <= min(2000, n * (n - 1) / 2)
    edges[i].length == 2
    0 <= fromi, toi <= n - 1
    fromi != toi
    There are no duplicate edges.
    The graph is directed and acyclic.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Classic Topological sort. There aren't any tricks or pitfalls. It's as
    straightforward as it gets.

*/

/* Time  Beats: 41.49% */
/* Space Beats: 48.63% */

/* Time  Complexity: O(n^2 * log(n) + n * m) */
/* Space Complexity: O(n^2)                  */
class Solution {
public:
    std::vector<std::vector<int>>
    getAncestors(int n, std::vector<std::vector<int>>& edges)
    {
        std::vector<std::vector<int>> adj_list(n, std::vector<int>(0));
        std::vector<int> indegree(n);

        for(const auto& e : edges)
        {
            adj_list[e[0]].push_back(e[1]);
            indegree[e[1]]++;
        }
        
        std::queue<int> queue;
        for(int i = 0; i < n; i++)
        {
            if (indegree[i] == 0)
                queue.push(i);
        }

        std::vector<std::unordered_set<int>> ancestors(n);

        while (queue.size() > 0)
        {
            int u = queue.front();
            queue.pop();

            for (int v : adj_list[u])
            {
                indegree[v]--;
                ancestors[v].insert(u);

                for (int ancestor : ancestors[u])
                    ancestors[v].insert(ancestor);

                if (indegree[v] == 0)
                    queue.push(v);
            }
        }
        
        std::vector<std::vector<int>> result(n);

        for (int i = 0; i < n; i++)
        {
            result[i] = std::vector<int>(ancestors[i].begin(), ancestors[i].end());
            std::sort(result[i].begin(), result[i].end());
        }

        return result;
    }
};
