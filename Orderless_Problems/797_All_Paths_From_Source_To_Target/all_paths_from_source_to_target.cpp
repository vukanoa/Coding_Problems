/*
    ==============
    === MEDIUM ===
    ==============

    ====================================
    797) All Paths From Source to Target
    ====================================

    ============
    Description:
    ============

    Given a directed acyclic graph (DAG) of n nodes labeled from 0 to n - 1,
    find all possible paths from node 0 to node n - 1 and return them in any
    order.

    The graph is given as follows: graph[i] is a list of all nodes you can
    visit from node i (i.e., there is a directed edge from node i to node
    graph[i][j]).

    ===============================================================================
    FUNCTION: vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph);
    ===============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: graph = [[1,2],[3],[3],[]]
    Output: [[0,1,3],[0,2,3]]
    Explanation: There are two paths: 0 -> 1 -> 3 and 0 -> 2 -> 3.

    --- Example 2 ---
    Input: graph = [[4,3,1],[3,2,4],[3],[4],[]]
    Output: [[0,4],[0,3,4],[0,1,3,4],[0,1,2,3,4],[0,1,4]]


    *** Constraints ***
    n == graph.length
    2 <= n <= 15
    0 <= graph[i][j] < n
    graph[i][j] != i (i.e., there will be no self-loops).
    All the elements of graph[i] are unique.
    The input graph is guaranteed to be a DAG.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    THe most basic Backtracking on an "Adjacency List".

*/

/* Time  Beats: 100.00% */
/* Space Beats:  76.06% */

/* Time  Complexity: O(2^N * N) */
/* Space Complexity: O(N)       */
class Solution {
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph)
    {
        const int N = graph.size();

        vector<vector<int>> result;
        vector<int> path = {};
        backtracking(0, path, graph, result);

        return result;
    }

private:
    void backtracking(const int node, vector<int>& path, vector<vector<int>>& graph, vector<vector<int>>& result)
    {
        const int N = graph.size();

        if (node == N-1)
        {
            path.push_back(node);
            result.push_back(path);
            path.pop_back();
            return;
        }

        for (const auto& neighbor : graph[node])
        {
            path.push_back(node);
            backtracking(neighbor, path, graph, result);
            path.pop_back();
        }
    }
};
