/*
    ==============
    === MEDIUM ===
    ==============

    ====================================================
    2493) Divide Nodes Into the Maximum Number of Groups
    ====================================================

    ============
    Description:
    ============

    You are given a positive integer n representing the number of nodes in an
    undirected graph. The nodes are labeled from 1 to n.

    You are also given a 2D integer array edges, where edges[i] = [ai, bi]
    indicates that there is a bidirectional edge between nodes ai and bi.
    Notice that the given graph may be disconnected.

    Divide the nodes of the graph into m groups (1-indexed) such that:

        + Each node in the graph belongs to exactly one group.

        + For every pair of nodes in the graph that are connected by an edge
          [ai, bi], if ai belongs to the group with index x, and bi belongs to
          the group with index y, then |y - x| = 1.

    Return the maximum number of groups (i.e., maximum m) into which you can
    divide the nodes. Return -1 if it is impossible to group the nodes with the
    given conditions.

    =================================================================
    FUNCTION: int magnificentSets(int n, vector<vector<int>>& edges);
    =================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 6, edges = [[1,2],[1,4],[1,5],[2,6],[2,3],[4,6]]
    Output: 4
    Explanation: As shown in the image we:
    - Add node 5 to the first group.
    - Add node 1 to the second group.
    - Add nodes 2 and 4 to the third group.
    - Add nodes 3 and 6 to the fourth group.
    We can see that every edge is satisfied.
    It can be shown that that if we create a fifth group and move any node
    from the third or fourth group to it, at least on of the edges will not be
    satisfied.

    --- Example 2 ---
    Input: n = 3, edges = [[1,2],[2,3],[3,1]]
    Output: -1
    Explanation: If we add node 1 to the first group, node 2 to the second
    group, and node 3 to the third group to satisfy the first two edges, we can
    see that the third edge will not be satisfied. It can be shown that no
    grouping is possible.


    *** Constraints ***
    1 <= n <= 500
    1 <= edges.length <= 10^4
    edges[i].length == 2
    1 <= ai, bi <= n
    ai != bi
    There is at most one edge between any pair of vertices.

*/

#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 76.05% */
/* Space Beats: 65.13% */

/* Time  Complexity: O(N * (N + M)) */
/* Space Complexity: O(N)           */
class Solution {
public:
    int magnificentSets(int n, vector<vector<int>> &edges)
    {
        vector<vector<int>> adj_list(n);
        vector<int> parent(n, -1);
        vector<int> depth(n, 0);

        for (const auto& edge : edges)
        {
            adj_list[edge[0] - 1].push_back(edge[1] - 1);
            adj_list[edge[1] - 1].push_back(edge[0] - 1);
            Union(edge[0] - 1, edge[1] - 1, parent, depth);
        }

        unordered_map<int, int> umap_num_of_groups_for_component;

        for (int node = 0; node < n; node++)
        {
            int numberOfGroups = getNumberOfGroups(adj_list, node, n);

            if (numberOfGroups == -1)
                return -1;

            int root_node = find(node, parent);

            umap_num_of_groups_for_component[root_node] = max(umap_num_of_groups_for_component[root_node], numberOfGroups);
        }

        int total_number_of_groups = 0;
        for (auto [root_node, numberOfGroups] : umap_num_of_groups_for_component)
            total_number_of_groups += numberOfGroups;

        return total_number_of_groups;
    }

private:
    int find(int node, vector<int> &parent)
    {
        while (parent[node] != -1)
            node = parent[node];

        return node;
    }

    void Union(int node1, int node2, vector<int> &parent, vector<int> &depth)
    {
        node1 = find(node1, parent);
        node2 = find(node2, parent);

        if (node1 == node2)
            return;

        if (depth[node1] < depth[node2])
            swap(node1, node2);

        parent[node2] = node1;

        if (depth[node1] == depth[node2])
            depth[node1]++;
    }

    int getNumberOfGroups(vector<vector<int>> &adjList, int srcNode, int n)
    {
        queue<int> nodes_queue;
        vector<int> layer_seen(n, -1);
        nodes_queue.push(srcNode);

        layer_seen[srcNode] = 0;
        int deepest_layer = 0;

        while ( ! nodes_queue.empty())
        {
            int num_of_nodes_in_layer = nodes_queue.size();

            for (int i = 0; i < num_of_nodes_in_layer; i++)
            {
                int current_node = nodes_queue.front();
                nodes_queue.pop();

                for (int neighbor : adjList[current_node])
                {
                    if (layer_seen[neighbor] == -1)
                    {
                        layer_seen[neighbor] = deepest_layer + 1;
                        nodes_queue.push(neighbor);
                    }
                    else
                    {
                        if (layer_seen[neighbor] == deepest_layer)
                            return -1;
                    }
                }
            }
            deepest_layer++;
        }

        return deepest_layer;
    }
};
