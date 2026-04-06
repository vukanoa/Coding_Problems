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

#include <numeric>
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
    You probably already know, but it's an individual portion of the graph
    that's all contiguous.

    Let's consider this first example:

            0 --- 1        3
                  |        |
                  |        |
                  2        4

    These two connected components are not conneted to each other, but each of
    the nodes separately is connected within the component.

    Note that one node by itself, that has no edges, does count as a connected
    component.

    If we were given n nodes where none of them have any edges, then we would
    return n as a result since that's how many connected components there are.

    There are a couple of ways to solve this problem.

    1. To solve it as we've solve it above - Make an adjacency list which then
       makes it easy to do a DFS search on the entire Graph.

    2. Union & Find(this solution). If you know this algorithm you probably
       know that this algorithm is literally made for this type of problem.

    ************************
    ***** Union & Find *****
    ************************

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
    Index 0 represents the 0 node.
    Index 1 represents the 1 node.
    Index 2 represents the 2 node.
    Index 3 represents the 3 node.
    Index 4 represents the 4 node.

    And the value in every single node clearly matches that initially.
    What that basically means is that - Each node is the parent of itself.

    So the way the Union & Find works is basically a forest of trees, so we're
    going to have multiple trees initially. We'll have n trees.
    One for every single node, initially.

    And as we go through every single edge in list of edges:
        edges = [[0, 1], [1, 2], [3, 4]]

    Say [0, 1].

    What we're going to do is - We'll say:"Okay 0 is going to be the parent. So
    0 is the parent of itself, but what we're going to do to 1 is say that 1's
    parent now is going to be 0.

    Basically what we're doing is just connecting the two nodes.

    And since we know that we'just made the single connection, what we can say
    now is that:"Okay, we've started out with 5 different connected components
    and we just merged two of them."

    Every time we perform a merge, we're basically taking the number of
    connected components we have, decrementing it by 1. So that's how we can
    keep track of the connected components.

    And there is one slight non-required optimization that drastically makes
    the code faster. (It is commented above the line that does the
    optimization)


    ~~~~~~~~~
    ~~~ 2 ~~~
    ~~~~~~~~~
    We're going to maintiang the rank of every single component. Basically for
    every single node, we're going to maintain what's the size of it.

    If say, 2 is the parent in this Graph:

            0 <-- 1        3


                  2        4

    What's the size of its connected components? It's 1 initially and it's 1
    in this case, as well.

    Initially it's going to be 1 for every node.

    rank = [1, 1, 1, 1, 1]

    But since we've just made the merge(merged 1 and 0, i.e. connected 1 to 0)
    we leave the rank of 1 as it is because it's not the parent, but for the
    parent node(0 in this example), we can say:"Okay the rank is now 2. We're
    just talking about the size.

    The reason we're maintaining this vector rank is basically just an
    optimization.

    Let's focus on the (0 -- 1) and (2) component. If we're merging these two:
    Would we want to merge (0 -- 1) as a child of (2) or would we want to merge
    (2) as a child of (0 -- 1).

    If we did the former, we'd get a Linked List:

            0 <-- 1        3
            |
            |
            ----> 2        4

    If we did the latter, we'd merge the smaller component under the bigger:

            0 <-- 1        3
            ^
            |
            ----- 2        4

    Now if we consider this a tree, which it is, then the height of the tree
    is minimized. Now it's a binary tree if you adjust your head to 90 degrees.

    So let's do an entire simulation:



    ##################
    ### SIMULATION ###
    ##################

    Example 1:

    I)

            0     1        3               parent = [0, 1, 2, 3, 4]

                                           rank = [1, 1, 1, 1, 1]
                  2        4

        edges = [[0, 1], [1, 2], [3, 4]]    count = 5
                  ^^^^




    II)
                                                    change
                                                        |
                                                        v
            0 <-- 1        3               parent = [0, 0, 2, 3, 4]

                                           rank = [2, 1, 1, 1, 1]
                  2        4                       ^
                                                   | (incremented)
                                                change
                                                    | (decremented)
                                                    v
        edges = [[0, 1], [1, 2], [3, 4]]    count = 4
                          ^^^^




    III)
                                                       change
                                                           |
                                                           v
            0 <-- 1        3               parent = [0, 0, 0, 3, 4]
            ^
            |                              rank = [3, 1, 1, 1, 1]
            ----- 2        4                       ^
                                                   | (incremented)
                                                change
                                                    | (decremented)
                                                    v
        edges = [[0, 1], [1, 2], [3, 4]]    count = 3
                                  ^^^^




    IV)
                                                             change
                                                                 |
                                                                 v
            0 <-- 1        3               parent = [0, 0, 0, 3, 3]
            ^              ^
            |              |               rank = [3, 1, 1, 2, 1]
            ----- 2        4                                ^
                                                            | (incremented)
                                                         change
                                                             | (decremented)
                                                    ----------
                                                    |
                                                    v
                                            count = 2

    // count = 2
    return count;

*/

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Union_and_Find {
public:
    int countComponents(int n, vector<pair<int, int>>& edges)
    {
        vector<int> parents(n);
        vector<int> ranks(n, 1);

        // Vector parent = [0, 1, 2, ..., n-1]
        iota(parents.begin(), parents.end(), 0);

        // Iota equivalent to this
        // for (int i = 0; i < n; i++)
        //     parent.push_back(i);

        int components = n;
        for (pair<int, int> edge : edges)
        {
            int node_1 = edge.first;
            int node_2 = edge.second;

            if (Union(node_1, node_2, parents, ranks))
                components--;
        }

        return components;
    }

private:
    int Find(int node, vector<int>& parents)
    {
        // Get root parent
        while (node != parents[node])
        {
            // Huge Optimization (From O(n) to Amortized O(1) Time Complexity)
            // If there is no grandparent, nothing will happen
            parents[node] = parents[parents[node]];

            node = parents[node];
        }

        return node;
    }

    bool Union(int node_1, int node_2, vector<int>& parents, vector<int>& ranks)
    {
        // Parent 1 & Parent 2
        int p1 = Find(node_1, parents);
        int p2 = Find(node_2, parents);

        if (p1 == p2)
            return false;

        if (ranks[p2] > ranks[p1])
        {
            parents[p1] = p2;
            ranks[p2] += ranks[p1];
        }
        else // ranks[p1] > ranks[p2]
        {
            parents[p2] = p1;
            ranks[p1] += ranks[p2];
        }

        return true;
    }
};
