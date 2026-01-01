/*
    ==============
    === MEDIUM ===
    ==============

    ==============================
    802) Find Eventual Safe States
    ==============================

    ============
    Description:
    ============

    There is a directed graph of n nodes with each node labeled from 0 to n -
    1. The graph is represented by a 0-indexed 2D integer array graph where
    graph[i] is an integer array of nodes adjacent to node i, meaning there is
    an edge from node i to each node in graph[i].

    A node is a terminal node if there are no outgoing edges. A node is a safe
    node if every possible path starting from that node leads to a terminal
    node (or another safe node).

    Return an array containing all the safe nodes of the graph. The answer
    should be sorted in ascending order.

    ====================================================================
    FUNCTION: vector<int> eventualSafeNodes(vector<vector<int>>& graph);
    ====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
    Output: [2,4,5,6]
    Explanation: The given graph is shown above.  Nodes 5 and 6 are terminal
    nodes as there are no outgoing edges from either of them.  Every path
    starting at nodes 2, 4, 5, and 6 all lead to either node 5 or 6.

    --- Example 2 ---
    Input: graph = [[1,2,3,4],[1,2],[3,4],[0,4],[]]
    Output: [4]
    Explanation:
    Only node 4 is a terminal node, and every path starting at node 4 leads to node 4.


    *** Constraints ***
    n == graph.length
    1 <= n <= 10^4
    0 <= graph[i].length <= n
    0 <= graph[i][j] <= n - 1
    graph[i] is sorted in a strictly increasing order.
    The graph may contain self-loops.
    The number of edges in the graph will be in the range [1, 4 * 10^4].

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    If you do a basic DFS, with some "Sets"(It's important to notice that
    when you have graph problems and nodes are from [0, n-1], you can ALWAYS
    use a vector of n booleans instead of HashSets. That makes it faster).

    Also, it's important to use everything they say, in Description, to your
    advantage.

    They've told us in "Constraints" that:

        "graph[i] is sorted in a strictly increasing order."

    We can, then, begin at node 0 and do a DFS. If any node along the path
    has 0 outgoing edges, we're going to mark it as a "safe" node in our vector
    of booleans.

    Similarly, if at any point of doing a DFS on neighbor nodes of some node
    we realize that not every path leads to a terminal node(or a safe node),
    therefore we can immediately stop the traversal for the current node and
    mark the current not as NON_SAFE, i.e. we're going to mark it as "true" in
    non_safe vector.

    Also, since they've told us that the graph contains self-loops, we need to
    keep track of "the current path";

    In the first example:

        (Also, note that this is an ADJACENCY LIST!!)

        Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]


        (read this line below until the end, it's not linear)
        We'd start at node 0, then go to node 1, then to node 2, then to node 5

        This is one path: 0 -> 1 -> 2 -> 5

        If we had the case that from node 5 we are jumping to node 0, then we
        would need to stop that, to prevent infinite loop, and we'd need to say
        that all these nodes are NON_SAFE.

        That's the purpose of having a curr_path vector of booleans.


    Also, one perk of having both "safe" and "non_safe" vectors of booleans is
    that we will NEVER visit the same node twice. This optimizes the Time
    Complexity by a lot, especially on large graphs.

*/

/* Time  Beats: 92.06% */
/* Space Beats: 99.70% */

/* Time  Complexity: O(E + V) */
/* Space Complexity: O(E + V) */
class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph)
    {
        const int N = graph.size();
        vector<int> result;

        vector<bool> curr_path(N, false);
        vector<bool> safe(N, false);
        vector<bool> non_safe(N, false);

        for (int i = 0; i < N; i++)
        {
            if (safe[i] || non_safe[i]) // Meaning, it's checked already
                continue;

            dfs(graph, curr_path, safe, non_safe, i);
        }

        for (int i = 0; i < N; i++)
        {
            if (safe[i])
                result.push_back(i);
        }

        return result;
    }

private:
    bool dfs(vector<vector<int>>& graph, vector<bool>& curr_path, vector<bool>& safe, vector<bool>& non_safe, int node)
    {
        curr_path[node] = true;

        bool is_safe_node = true;
        for (const int& neighbor : graph[node])
        {
            if (safe[neighbor])
                continue;
            else if (non_safe[neighbor] || curr_path[neighbor])
            {
                is_safe_node = false;
                break;
            }

            if ( ! dfs(graph, curr_path, safe, non_safe, neighbor))
            {
                is_safe_node = false;
                break;
            }
        }

        if (is_safe_node)
            safe[node] = true;
        else
            non_safe[node] = true;

        curr_path[node] = false;

        return is_safe_node;
    }
};
