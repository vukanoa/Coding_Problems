#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===================================================
    1557) Minimum Number of Vertices to Reach All Nodes
    ===================================================

    ============
    Description:
    ============

    Given a directed acyclic graph, with n vertices numbered from 0 to n-1, and
    an array edges where edges[i] = [fromi, toi] represents a directed edge
    from node fromi to node toi.

    Find the smallest set of vertices from which all nodes in the graph are
    reachable. It's guaranteed that a unique solution exists.

    Notice that you can return the vertices in any order.

    ===================================================================================
    FUNCTION: vector<int> findSmallestSetOfVertices(int n, vector<vector<int>>& edges);
    ===================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---

                1
                ^
               /
              /
             0 --------> 2
                        ^ \
                       /   \
                      /     v
             3 ----> 4      5

    Input: n = 6, edges = [[0,1],[0,2],[2,5],[3,4],[4,2]]
    Output: [0,3]
    Explanation: It's not possible to reach all the nodes from a single vertex.
    From 0 we can reach [0,1,2,5]. From 3 we can reach [3,4,2,5]. So we output
    [0,3].




    --- Example 2 ---

                     2 <--\
                     ^     \
                     |      \
                     |       \
             0 ----> 4 <---- 5
                     ^
                     |
                     |
                     3

    Input: n = 5, edges = [[0,1],[2,1],[3,1],[1,4],[2,4]]
    Output: [0,2,3]
    Explanation: Notice that vertices 0, 3 and 2 are not reachable from any
    other node, so we must include them. Also any of these vertices can reach
    nodes 1 and 4.





    *** Constraints ***
    2 <= n <= 10^5
    1 <= edges.length <= min(10^5, n * (n - 1) / 2)
    edges[i].length == 2
    0 <= fromi, toi < n
    All pairs (fromi, toi) are distinct.

*/

/*
    ------------
    --- IDEA ---
    ------------

    This one is fairly simple if you know a bit of theory behind the Graphs or
    if you can notice this yourself.

    For a node to be "reachable" it has to have an indegree greater than 0.
    In other words - At least one node has to point to that Node_X, to say that
    Node_X is "reachable".

    Once you know that or once you notice that, ask yourself - What is the
    minimum subset of all of these nodes that I must take into account in order
    to reach every node?

    Since we've laid out the definition before us, now it's simple. For the set
    to be "smallest" we only have to include the nodes which have an indegree
    of 0.

    In other words - Result set will be composed of nodes which are NOT
    reachable from any other node in this Graph.

    That's it.

*/

/* Time  Beats: 98.44% */
/* Space Beats: 75.21% */

/* Time  Complexity: O( max(edges.size(), n) ) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::vector<int> findSmallestSetOfVertices(int n, std::vector<std::vector<int>>& edges)
    {
        std::vector<int> indegree(n, 0);

        for (int i = 0; i < edges.size(); i++)
            indegree[edges[i][1]]++;

        std::vector<int> results;
        for (int i = 0; i < n; i++)
        {
            if (indegree[i] == 0)
                results.push_back(i);
        }

        return results;
    }
};
