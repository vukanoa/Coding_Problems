/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    2685) Count the Number of Complete Components
    =============================================

    ============
    Description:
    ============

    You are given an integer n. There is an undirected graph with n vertices,
    numbered from 0 to n - 1. You are given a 2D integer array edges where
    edges[i] = [ai, bi] denotes that there exists an undirected edge
    connecting vertices ai and bi.

    Return the number of complete connected components of the graph.

    A connected component is a subgraph of a graph in which there exists a path
    between any two vertices, and no vertex of the subgraph shares an edge with
    a vertex outside of the subgraph.

    A connected component is said to be complete if there exists an edge
    between every pair of its vertices.

    =========================================================================
    FUNCTION: int countCompleteComponents(int n, vector<vector<int>>& edges);
    =========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 6, edges = [[0,1],[0,2],[1,2],[3,4]]
    Output: 3
    Explanation: From the picture above, one can see that all of the
                 components of this graph are complete.


    --- Example 2 ---
    Input: n = 6, edges = [[0,1],[0,2],[1,2],[3,4],[3,5]]
    Output: 1
    Explanation: The component containing vertices 0, 1, and 2 is complete
                 since there is an edge between every pair of two vertices. On
                 the other hand, the component containing vertices 3, 4, and 5
                 is not complete since there is no edge between vertices 4 and
                 5. Thus, the number of complete components in this graph is 1.


    *** Constraints ***
    1 <= n <= 50
    0 <= edges.length <= n * (n - 1) / 2
    edges[i].length == 2
    0 <= ai, bi <= n - 1
    ai != bi
    There are no repeated edges.

*/

#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;




/*
    ------------
    --- IDEA ---
    ------------

    The most common way to represent a graph is through an adjacency list,
    where each node points to a list of all the nodes it is directly connected
    to.

    For example, consider a graph where vertices 0, 1, and 2 form a complete
    component. Their adjacency lists would look like this:

        Vertex 0’s neighbors: [1, 2]
        Vertex 1’s neighbors: [0, 2]
        Vertex 2’s neighbors: [0, 1]

    Now, let’s take a moment to include each vertex as its own neighbor. This
    does not violate any constraints since every node is naturally reachable
    from itself. After this adjustment, the adjacency lists would look like:

        Vertex 0’s neighbors: [0, 1, 2]
        Vertex 1’s neighbors: [0, 1, 2]
        Vertex 2’s neighbors: [0, 1, 2]

    This leads to a key insight: in a complete connected component, every
    vertex must have the exact same set of neighbors (including itself).
    This forms a unique "adjacency pattern" that is shared by all vertices in
    the same component.

    Let us create the adjacency list for the graph and include each vertex as a
    neighbor in its own list. Now, we need to identify all vertices that share
    the same neighbor pattern.

    To do this, we can use a hash map where the key represents a unique
    neighbor pattern, and the value keeps track of how many times this pattern
    appears in the graph. However, there may be cases where two neighbor
    patterns are the same but appear differently in the adjacency list

    (for example, 0: [0, 1, 2] and 2: [2, 1, 0]). To ensure they are grouped
    together, we first sort each neighbor list before adding it to the map.

    Next, we go through each entry in the map to count how many unique patterns
    were collected. But one final check is needed: the size of the adjacency
    list must match the number of vertices that share this pattern.

    In other words, the size of the list should be equal to its frequency of
    occurrence in the map.

    Why?
    Because in a complete component with k vertices, each vertex must have
    exactly k neighbors (including itself). And exactly k vertices must share
    this pattern - one for each member of the component.

    Finally, we count the number of entries in the map that pass this
    validation and return this count as our answer.

*/

/* Time  Beats:  9.11% */
/* Space Beats: 19.27% */

/* Time  Complexity: O(N + M * logN) */
/* Space Complexity: O(N + M + S)    */
class Solution {
public:
    int countCompleteComponents(int n, vector<vector<int>>& edges)
    {
        vector<vector<int>> adj_list(n);

        unordered_map<string, int> component_freq;

        for (int vertex = 0; vertex < n; vertex++)
            adj_list[vertex].push_back(vertex);

        for (const auto& edge : edges)
        {
            adj_list[edge[0]].push_back(edge[1]);
            adj_list[edge[1]].push_back(edge[0]);
        }

        for (int vertex = 0; vertex < n; vertex++)
        {
            vector<int> neighbors = adj_list[vertex];
            sort(neighbors.begin(), neighbors.end());

            // neighbors = [0,1,2,3] --> "0,1,2,3,"  // ',' as the last char
            string key;
            for (int num : neighbors)
                key += to_string(num) + ",";

            component_freq[key]++;
        }

        int result = 0;
        for (const auto& entry : component_freq)
        {
            int size = count(entry.first.begin(), entry.first.end(), ',');

            if (size == entry.second)
                result++;
        }

        return result;
    }
};
