/*
    ============
    === HARD ===
    ============

    ===========================================
    3547) Maximum Sum of Edge Values in a Graph
    ===========================================

    ============
    Description:
    ============

    You are given an undirected connected graph of n nodes, numbered from 0 to
    n - 1. Each node is connected to at most 2 other nodes.

    The graph consists of m edges, represented by a 2D array edges, where
    edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi

    You have to assign a unique value from 1 to n to each node. The value of an
    edge will be the product of the values assigned to the two nodes it
    connects.

    Your score is the sum of the values of all edges in the graph.

    Return the maximum score you can achieve.

    ================================================================
    FUNCTION: long long maxScore(int n, vector<vector<int>>& edges);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 4, edges = [[0,1],[1,2],[2,3]]
    Output: 23
    Explanation:
    The diagram above illustrates an optimal assignment of values to nodes.
    The sum of the values of the edges is: (1 * 3) + (3 * 4) + (4 * 2) = 23.


    --- Example 2 ---
    Input: n = 6, edges = [[0,3],[4,5],[2,0],[1,3],[2,4],[1,5]]
    Output: 82
    Explanation:
    The diagram above illustrates an optimal assignment of values to nodes.
    The sum of the values of the edges is:
    (1 * 2) + (2 * 4) + (4 * 6) + (6 * 5) + (5 * 3) + (3 * 1) = 82.


    *** Constraints ***
    1 <= n <= 5 * 10^4
    m == edges.length
    1 <= m <= n
    edges[i].length == 2
    0 <= ai, bi < n
    ai != bi
    There are no repeated edges.
    The graph is connected.
    Each node is connected to at most 2 other nodes.

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 46.83% */
/* Space Beats: 15.57% */

/* Time  Complexity: O(N * logN + M) */
/* Space Complexity: O(N + M)        */
class Solution {
public:
    vector<bool> visited; 

    long long maxScore(int n, vector<vector<int>>& edges)
    { 
        int curr_val = n;

        vector<vector<int>> adj_list(n + 1);
        for (const auto& edge : edges)
        {
            adj_list[edge[0]].push_back(edge[1]);
            adj_list[edge[1]].push_back(edge[0]); 
        }

        visited = vector<bool>(n + 1, false);
        vector<pair<int, int>> cyclic_components;  // {component_size, start_node}
        vector<pair<int, int>> acyclic_components; // {component_size, start_node}

        for (int vertex = 0; vertex < n; vertex++)
        {
            if (visited[vertex])
                continue;

            int component_size = 0;

            if (is_cyclic_component(vertex, -1, adj_list, component_size, vertex))
            {
                cyclic_components.push_back( {component_size, vertex} );
            }
            else
            {
                acyclic_components.push_back( {component_size, vertex} );
            }
        }

        sort(cyclic_components.rbegin(), cyclic_components.rend());
        sort(acyclic_components.rbegin(), acyclic_components.rend());
        //
        // Or like this, the effect is the same--Sort in DESCENDING order
        //
        // sort(cyclic_components.begin(),  cyclic_components.end(),  greater<int>());
        // sort(acyclic_components.begin(), acyclic_components.end(), greater<int>());


        long long max_score = 0;
        visited = vector<bool>(n + 1, false);
        curr_val = n;

        // Process cyclic components first
        for (const auto& component : cyclic_components)
        {
            int component_size = component.first;
            vector<long long> node_values(component_size);

            int start_value = curr_val - component_size + 1;
            int j = 0;

            for (j = 0; j < component_size / 2; j++)
            {
                node_values[j] = start_value++;
                node_values[component_size - j - 1] = start_value++;
            }

            if (component_size % 2)
                node_values[j] = start_value;

            for (int i = 1; i < component_size; i++)
                max_score += (node_values[i] * node_values[i - 1]);

            // Closing the cycle
            max_score += node_values.back() * node_values.front();
            curr_val -= component_size;
        }

        // Process acyclic components
        for (auto& component : acyclic_components)
        {
            int component_size = component.first;
            vector<long long> node_values(component_size);

            int start_val = curr_val - component_size + 1;
            int j = 0;

            for (j = 0; j < component_size / 2; j++)
            {
                node_values[j] = start_val++;
                node_values[component_size - j - 1] = start_val++;
            }

            if (component_size % 2)
                node_values[j] = start_val;

            for (int i = 1; i < component_size; i++)
                max_score += (node_values[i] * node_values[i - 1]);

            curr_val -= component_size;
        } 

        return max_score;
    }

private:
    bool is_cyclic_component(int current_node, int parent_node, vector<vector<int>>& graph, int& component_size, int start_node)
    {
        visited[current_node] = true;
        component_size++;

        for (int neighbor : graph[current_node])
        {
            if ( ! visited[neighbor])
            {
                if (is_cyclic_component(neighbor, current_node, graph, component_size, start_node))
                    return true;
            }
            else if (neighbor != parent_node)
            {
                return true;
            }
        }

        return false; 
    }
};
