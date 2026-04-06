/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================================
    323) Number of Connected Components in an Undirected Graph
    ==========================================================

    ============
    Description:
    ============

    You have a graph of n nodes. You are given an integer n and an array edges
    where edges[i] = [ai, bi] indicates that there is an edge between ai and bi
    in the graph.

    Return the number of components in the Graph.

    ==============================================================================
    FUNCTION: int countComponents(int n, std::vector<std::pair<int, int>>& edges);
    ==============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---

            0 --- 1        3
                  |        |
                  |        |
                  2        4

    Input: n = 5, edges = [[0, 1], [1, 2], [3, 4]]
    Output: 2



    *** Constraints ***
    <Unknown>
*/

#include <vector>
#include <unordered_set>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Create an adjacency List.

    Try traversing the Graph by starting from each of the nodes. However we
    want to visit each node exactly once, therefore we'll use a "visited" set
    and mark which ones are already visited.

    If some node is alread visited, we're NOT going to do a DFS on it since the
    component it is a part of is ALREADY counted.

    The number of times we actually call a DFS is the exact number of connected
    components.

*/

/* Time  Complexity: O(V + E) */
/* Space Complexity: O(V + E) */
class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges)
    {
        // Empty
        if (n == 0)
            return 0;

        const int V = n;
        const int E = edges.size();

        vector<vector<int>> adj_list(n);

        /* Create an Adjacency List */
        for (const auto& edge : edges)
        {
            const int& u = edge[0];
            const int& v = edge[1];

            adj_list[u].push_back(v);
            adj_list[v].push_back(u);
        }


        unordered_set<int> visited;
        int count = 0;

        for (int node = 0; node < V; node++)
        {
            if (visited.count(node)) // Component which this not is a part of is already counted
                continue;

            count += dfs(node, -1, visited, adj_list);
        }

        return count;
    }

private:
    int dfs(int node, int prev, unordered_set<int>& visited, vector<vector<int>>& adj_list)
    {
        if (visited.count(node))
            return 0;

        visited.insert(node);

        for (const int& neighbor : adj_list[node])
        {
            dfs(neighbor, node, visited, adj_list);
        }

        return 1;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    First of all - What is a connected component in a graph?
    It's a connected group of nodes(a single node is a component as well)

    Let's consider this first example:

            0 --- 1        3
                  |        |
                  |        |
                  2        4

    If we were given n nodes where none of them have any edges, then we would
    return n as a result since that's how many connected components there are.

    There are a couple of ways to solve this problem.

    1. To solve it as we've solve it above - Make an adjacency list which then
       makes it easy to do a DFS search on the entire Graph.

    2. Disjoint-Set Union(aka "Union and Find"). If you know this algorithm you
       probably know that this algorithm is literally made for this type of
       problem.

    **********************************************
    ***** Disjoint-Set Union(Union and Find) *****
    **********************************************

    Example 1:

            0 --- 1        3
                  |        |
                  |        |
                  2        4

    edges = [[0, 1], [1, 2], [3, 4]]

    We're mainly going to be maintaining two arrays(vectors):
        1. Parent vector
        2. Rank   vector

    ~~~~~~~~~
    ~~~ 1 ~~~
    ~~~~~~~~~
    Parent vector is going to have values of all the nodes in the Graph.
    Since n = 5, initially we'll have parent = [0, 1, 2, 3, 4].
                                                0  1  2  3  4

    Each index represents the corresponding node.

        Index 0 represents node 0.
        Index 1 represents node 1.
        Index 2 represents node 2.
        Index 3 represents node 3.
        Index 4 represents node 4.


    And the value in every single node clearly matches that initially.
    What that basically means is that - Each node is the parent of itself.

    So the way Disjoint-Set Union(aka "Union & Find") works is basically a
    forest of trees, so we're going to have multiple trees initially.

    We'll have n trees. One for every single node, initially.

    And as we go through every single edge in list of edges:
        edges = [[0, 1], [1, 2], [3, 4]]

    Say [0, 1].

    What we're going to do is - We'll say:"Okay 0 is going to be the parent. So
    0 is the parent of itself, but what we're going to do to 1 is say that 1's
    parent is now going to be 0.

    What we're doing is connecting the two nodes.

    Every time we perform a merge(i.e. we connect two yet unconnected nodes),
    we're taking the number of connected components we have, decrementing it by
    1 so that's how we can keep track of the connected components.

    And there is one slight non-required optimization that drastically makes
    the code faster. (It is commented above the line that does the
    optimization)


    ~~~~~~~~~
    ~~~ 2 ~~~
    ~~~~~~~~~
    We're going to maintain the rank for every single component.
    For every single node, we're going to maintain what's the size of it.

    Initially it's going to be 1 for every node.

        rank = [1, 1, 1, 1, 1]

    But since we've just made the merge(merged 1 and 0, i.e. connected 1 to 0)
    we leave the rank of 1 as it is because it's not the parent, but for the
    parent node(0 in this example), we are going to add the size of the other
    component we're merging at the moment.

    Since both components were individual nodes, i.e. both components' size was
    exactly 1, now the size of the PARENT node 0 is going to be: 1 + 1 = 2.

            0 <-- 1        3


                  2        4


        rank = [2, 1, 1, 1, 1]
                0  1  2  3  4


    The reason we're maintaining this vector rank is purely because it's going
    to be an optimization.

    Let's focus on the (0 -- 1) and (2) components.
    If we're merging these two:

    Would we want to merge:
        a)    (0 -- 1) as a child of (2)     , or
        b)    (2)      as a child of (0 -- 1).

    If we did the former(i.e. option "a)" ), we'd get a Graph that looks like
    this:

            0 <-- 1        3
            |
            |
            ----> 2        4


    If we did the latter(i.e. option "b)"), we'd merge the smaller component
    TOWARDS the bigger:

            0 <-- 1        3
            ^
            |
            ----- 2        4

    Now if we consider this a tree, which it is, then the height of the tree
    is MINIMIZED if we do the latter(i.e. "b)" option).

    Now it's a binary tree if you adjust your head to 90 degrees.


    So let's do an entire simulation:

    ##################
    ### SIMULATION ###
    ##################

    Example 1:

    I)
            0     1        3               parent = [0, 1, 2, 3, 4]
                                                     0  1  2  3  4

                                           rank =   [1, 1, 1, 1, 1]
                  2        4                         0  1  2  3  4


        edges = [[0, 1], [1, 2], [3, 4]]    components = 4
                  ^^^^




    II)
                                                      change
                                                        |
                                                        |
                                                        v
            0 <-- 1        3               parent = [0, 0, 2, 3, 4]
                                                     0  1  2  3  4

                                           rank =   [2, 1, 1, 1, 1]
                  2        4                         0  1  2  3  4
                                                     ^
                                                     |
                                                     | (incremented)
                                                     |
                                                  change
                                                    |
                                                    |  (decremented)
                                                    |_____
                                                         |
                                                         v
        edges = [[0, 1], [1, 2], [3, 4]]    components = 4
                          ^^^^




    III)
                                                       change
                                                           |
                                                           |
                                                           v
            0 <-- 1        3               parent = [0, 0, 0, 3, 4]
            ^                                        0  1  2  3  4
            |
            |                              rank =   [3, 1, 1, 1, 1]
            ----- 2        4                         0  1  2  3  4
                                                     ^
                                                     |
                                                     | (incremented)
                                                     |
                                                  change
                                                    |
                                                    |  (decremented)
                                                    |_____
                                                         |
                                                         v
        edges = [[0, 1], [1, 2], [3, 4]]    components = 4
                                  ^^^^^




    IV)
                                                             change
                                                                 |
                                                                 v
            0 <-- 1        3               parent = [0, 0, 0, 3, 3]
            ^              ^
            |              |               rank =   [3, 1, 1, 2, 1]
            |              |                         0  1  2  3  4
            ----- 2        4                                  ^
                                                            __|
                                                            |
                                                            | (incremented)
                                                            |
                                                         change
                                                            |
                                                            |  (decremented)
                                                            |_____
                                                                 |
                                                                 v
                                                    components = 2
*/

/* Time  Complexity: O(V + E * alpha(V)) */
/* Space Complexity: O(V)                */
class DSU {
private:
    vector<int> rank;
    vector<int> parent;
    int components;

public:
    DSU (int n)
    {
        components = n;

        rank.resize(n);
        parent.resize(n);

        for (int i = 0; i < n; i++)
        {
            rank[i]   = 1;
            parent[i] = i; // Or i+1, depends on the problem
        }
    }

    int find_root(int node)
    {
        while (node != parent[node])
        {
            /* Reverse Ackerman function */
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

        components--;

        return true;
    }

    int number_of_components()
    {
        return components;
    }
};

class Solution_DSU {
public:
    int countComponents(int n, vector<vector<int>>& edges)
    {
        DSU dsu(n);

        for (const auto& edge : edges)
            dsu.union_components(edge[0], edge[1]);

        return dsu.number_of_components();
    }
};
