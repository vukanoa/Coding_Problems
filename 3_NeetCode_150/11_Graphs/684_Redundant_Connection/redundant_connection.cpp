/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    684) Redundant Connection
    ===========================

    ============
    Description:
    ============

    In this problem, a tree is an undirected graph that is connected and has no
    cycles.

    You are given a graph that started as a tree with n nodes labeled from 1 to
    n, with one additional edge added. The added edge has two different
    vertices chosen from 1 to n, and was not an edge that already existed. The
    graph is represented as an array edges of length n where edges[i] = [ai,
    bi] indicates that there is an edge between nodes ai and bi in the graph.

    Return an edge that can be removed so that the resulting graph is a tree of
    n nodes. If there are multiple answers, return the answer that occurs last
    in the input.

    ==========================================================================
    FUNCTION: vector<int> findRedundantConnection(vector<vector<int>>& edges);
    ==========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---

            1 --- 2
            |   /
            |  /
            | /
            |/
            3

    Input: edges = [[1,2],[1,3],[2,3]]
    Output: [2,3]

    --- Example 2 ---

            2 --- 1 --- 5
            |     |
            |     |
            |     |
            3 --- 4

    Input: edges = [[1,2],[2,3],[3,4],[1,4],[1,5]]
    Output: [1,4]


    *** Constraints ***
    n == edges.length
    3 <= n <= 1000
    edges[i].length == 2
    1 <= ai < bi <= edges.length
    ai != bi
    There are no repeated edges.
    The given graph is connected.

*/

#include <queue>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This is a typical Union_&_Find(aka "Disjoint-Set Union") Problem.

    If you haven't done "Number of Connected Components in an Undirected Graph"
    do that first.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  53.63% */

/* Time  Complexity: O(E * alpha(V)) */
/* Space Complexity: O(E)            */
class DSU {
private:
    vector<int> rank;
    vector<int> parent;

public:
    DSU(int n)
    {
        rank.resize(n+1);
        parent.resize(n+1);

        for (int i = 1; i <= n; i++)
        {
            rank[i]   = 1;
            parent[i] = i;
        }
    }

    int find_root(int node)
    {
        while (node != parent[node])
        {
            /* Reverse Ackerman function, i.e. <= 5 in practice */
            parent[node] = parent[parent[node]];

            node = parent[node];
        }

        return node;
    }

    bool union_components(int node_1, int node_2)
    {
        int root_1 = find_root(node_1);
        int root_2 = find_root(node_2);

        if (root_1 == root_2)
            return false;

        if (rank[root_1] < rank[root_2])
            swap(root_1, root_2);

        parent[root_2] = root_1;
        rank[root_1]  += rank[root_2];

        return true;
    }

    bool already_connected(int node_1, int node_2)
    {
        return find_root(node_1) == find_root(node_2);
    }
};

class Solution_DSU {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges)
    {
        const int N = edges.size();

        DSU dsu(N);

        for (const auto& edge : edges)
        {
            if (dsu.already_connected(edge[0], edge[1]))
                return edge; // Because there's AT MOST ONE extra edge

            dsu.union_components(edge[0], edge[1]);
        }

        return {}; // Unreachable
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  18.46% */

/* Time  Complexity: O(V + E) */
/* Space Complexity: O(V + E) */
class Solution_DFS_Cycle_Detection {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges)
    {
        const int N = edges.size();

        vector<vector<int>> adj_list(N+1);

        for (const auto& edge : edges)
        {
            const int& a = edge[0];
            const int& b = edge[1];

            adj_list[a].push_back(b);
            adj_list[b].push_back(a);
        }

        vector<bool> visited(N+1, false);
        unordered_set<int> uset_cycle;

        int start_of_cycle = -1;

        dfs(1, -1, visited, start_of_cycle, uset_cycle, adj_list);

        /* Iterate in REVERSE */
        for (int i = N-1; i >= 0; i--)
        {
            int& a = edges[i][0];
            int& b = edges[i][1];

            if (uset_cycle.count(a) && uset_cycle.count(b))
                return {a, b};
        }

        return {};
    }

private:
    bool dfs(int node, int prev, vector<bool>& visited, int& start_of_cycle, unordered_set<int>& uset_cycle, vector<vector<int>>& adj_list)
    {
        if (visited[node])
        {
            start_of_cycle = node;
            return true; // It's a CYCLE
        }

        visited[node] = true;

        for (const int& neighbor : adj_list[node])
        {
            if (neighbor == prev)
                continue;

            if (dfs(neighbor, node, visited, start_of_cycle, uset_cycle, adj_list))
            {
                if (start_of_cycle != -1)
                    uset_cycle.insert(node);

                if (node == start_of_cycle)
                    start_of_cycle = -1;

                return true;
            }
        }

        return false; // It's NOT a CYCLE
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Even if Graph is "undirected" we can still remove nodes with indegree == 1.

    1. Nodes with indegree == 1 CANNOT be inside the cycle(every cycle requires
       all of its nodes to hvae indegree >= 2)

    2. Initially push all the nodes with indegree == 1 in a Queue.

    3. When we remove the front node from the Queue, the indegree of all of its
       neighbors is decremented by one and if that neighbor's indegree is now
       1 itself, then push it in a Queue.

    4. Once the entire process is finished, nodes with indegree > 0 are
       CERTAINLY "cycles nodes".


    The redundant edge MUST be the edge where its BOTH NODES are still inside
    the cycle.

    However, since we're required to return the LAST such edge from the Input,
    we must iterate through edges in REVERSE order and return the first edge
    that connects remaining nodes.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  20.41% */

/* Time  Complexity: O(V + E) */
/* Space Complexity: O(V + E) */
class Solution_Topological_Trimming {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges)
    {
        const int N = edges.size();

        vector<vector<int>> adj_list(N+1);
        vector<int> indegree(N+1, 0);

        for (const auto& edge : edges)
        {
            const int& a = edge[0];
            const int& b = edge[1];

            adj_list[a].push_back(b);
            adj_list[b].push_back(a);

            indegree[a]++;
            indegree[b]++;
        }

        queue<int> queue;
        for (int node = 1; node < N+1; node++)
        {
            if (indegree[node] == 1)
                queue.push( {node} );
        }

        while ( ! queue.empty())
        {
            int node = queue.front();
            queue.pop();

            indegree[node]--;

            for (const auto& neighbor : adj_list[node])
            {
                indegree[neighbor]--;

                if (indegree[neighbor] == 1)
                    queue.push(neighbor);
            }
        }

        /* Iterate in REVERSE */
        for (int i = N-1; i >= 0; i--)
        {
            int& a = edges[i][0];
            int& b = edges[i][1];

            if (indegree[a] == 2 && indegree[b] > 0)
                return {a, b};
        }

        return {}; // Unreachable
    }
};
