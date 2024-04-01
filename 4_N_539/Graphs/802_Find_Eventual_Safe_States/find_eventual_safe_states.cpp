#include <iostream>
#include <vector>

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

/*
    ------------
    --- IDEA ---
    ------------

    This is a messier approach than the second Solution down below(Solution_2).

    I wanted to have both slower and faster Implementation to prove a point and
    to be able to compare and see why Solution_2 is better.

    Here we're correctly "remembering" if we've visited some node with a
    HashSet "visited" and we're having a persisting vector of booleans
    "safe_nodes".

    However, each time we finish processing from some starting node, we're
    going to CLEAR a HashSet. If we were not to do that in this one, we would
    have incorrect results at the very end.

    Therefore, we MUST clear "visited" HashSet, however that's why this
    Solution is slower than Solution_2.

    Here we'd have to go, manually, through every "neighbor"(aka "nei") in
    every node's list. Even though we'll be hitting that "continue" most of the
    time, we're still going to iterate over all the "neighbor"s in the list.

    That's why this Solution isn't fast. However, it's good to have it here for
    didactic purposes.

*/

/* Time  Beats: 5.01% */
/* Space Beats: 5.03% */

/* Time  Complexity: O(E + V) */
/* Space Complexity: O(E + V) */
class Solution {
public:
    std::vector<int> eventualSafeNodes(std::vector<std::vector<int>>& graph)
    {
        const int N = graph.size();
        std::vector<int> results;

        std::unordered_set<int> visited;
        std::vector<bool> safe_nodes(N, false);

        for (int i = 0; i < N; i++)
        {
            if (dfs(graph, safe_nodes, visited, i))
                results.push_back(i);

            visited.clear();
        }

        return results;
    }

private:
    bool dfs(std::vector<std::vector<int>>& graph,
             std::vector<bool>& safe_nodes,
             std::unordered_set<int>& visited,
             int node)
    {
        visited.insert(node);

        for (const int& nei : graph[node])
        {
            if (safe_nodes[nei])
                continue;
            else if (visited.count(nei))
                return false;

            if (! dfs(graph, safe_nodes, visited, nei))
                return false;
        }

        visited.erase(node);
        safe_nodes[node] = true;

        return true;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is an Elegant IDEA of the above Solution. Instead of having a HashSet
    "visited" and a vector of booleans "safe_nodes", we can have a HashMap
    named "safe", which will do the trick much more efficient.

    The optimization in this Solution comes from the fact that we're
    immediately going to return from some node if that node was already
    processed and put into HashMap "safe" with corresponding boolean value.

    If from that node we're able to get to the terminal node with each path,
    then, in the HashMap "safe", we'll push {node, true}.

    However, if, on the other hand, we find out that from this node we're not
    able to get to terminal nodes with any path, i.e. we have a loop at some
    point, then, in the HashMap "safe", we'll push {node, false}.

    That way once we processed, say, the 0th node and it happens NOT to be a
    "safe" node, then anytime we stumble upon that node, we can IMMEDIATELY
    return "false" since we're sure that this node ISN'T "safe".

    That's where the optimization comes in this Solution.

*/

/* Time  Beats: 63.37% */
/* Space Beats: 60.35% */

/* Time  Complexity: O(E + V) */
/* Space Complexity: O(E + V) */
class Solution_2 {
public:
    std::vector<int> eventualSafeNodes(std::vector<std::vector<int>>& graph)
    {
        const int N = graph.size();
        std::unordered_map<int, bool> safe;

        std::vector<int> results;
        for (int i = 0; i < N; i++)
        {
            if (dfs(graph, i, safe))
                results.push_back(i);
        }

        return results;
    }

private:
    bool dfs(std::vector<std::vector<int>>& graph, int node, std::unordered_map<int, bool>& safe)
    {
        if (safe.find(node) != safe.end())
            return safe[node];

        safe[node] = false;

        for (int& neighbor : graph[node])
        {
            if (!dfs(graph, neighbor, safe))
                return safe[node]; // False
        }

        safe[node] = true;
        return safe[node]; // True
    }
};
