#include <iostream>
#include <vector>
#include <unordered_set>

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

/*
    ------------
    --- IDEA ---
    ------------

    Make an adjacency list which then makes it easy to do a DFS search on the
    entire Graph.

    Go through every single node, starting at 0, then do a DFS Search from it.
    Since that is the node we're starting the DFS from, we're going to mark it
    as "beginning" node, i.e. we'll pass the bool value of "true" to the DFS
    function.

    Then do a DFS to all the directly connected nodes to our "beginning" node
    and do that recursively until you traverse all of them.

    While you're traversing, be sure to always check if that node was already
    visited. If it was, just return from that function call.

    If it's not, then mark it as visited right now by inserting it in a Set.

    After you're done with all the calls from the "beginning" node, return and
    make the next node as a "beginning" one.

    Note that the number of components only gets updated(incremented) if the
    beginning node wasn't visited. That's the only case.

    At the end, return variable count.

*/

/* Time  Complexity: O(e + v) */
/* Space Complexity: O(n) */
class Solution {
public:
    int countComponents(int n, std::vector<std::pair<int, int>>& edges)
    {
        // Empty
        if (n == 0)
            return 0;

        std::vector<std::vector<int>> map(n);

        // Represent Graph using adjacency list
        for (int i = 0; i < edges.size(); i++)
        {
            std::pair<int, int> edge = edges[i];

            // Because it's an UNDIRECTED Graph
            map[edge.first].push_back(edge.second);
            map[edge.second].push_back(edge.first);
        }

        std::unordered_set<int> uset;
        int count = 0;

        for (int i = 0; i < n; i++)
            dfs(map, i, uset, count, true);

        return count;
    }

private:
    void dfs(std::vector<std::vector<int>>& map, int i, std::unordered_set<int>& uset, int& count, bool beginning)
    {
        if (uset.find(i) != uset.end())
            return;

        if (beginning)
            count++;

        uset.insert(i);

        for (int x = 0; x < map[i].size(); x++)
            dfs(map, map[i][x], uset, count, false);
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
class Solution_Union_&_Find {
public:
    int countComponents(int n, std::vector<std::pair<int, int>>& edges)
    {
        std::vector<int> parents(n);
        std::vector<int> ranks(n, 1);

        // Vector parent = [0, 1, 2, ..., n-1]
        std::iota(parents.begin(), parents.end(), 0);

        // Iota equivalent to this
        // for (int i = 0; i < n; i++)
        //     parent.push_back(i);

        int count = n;
        for (std::pair<int, int> edge : edges)
        {
            if (Union(edge, parents, ranks))
                count--;
        }

        return count;
    }

private:
    int Find(int node, std::vector<int>& parents)
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

    int Union(std::pair<int, int>& edge, std::vector<int>& parents, std::vector<int>& ranks)
    {
        // Parent 1 & Parent 2
        int p1 = Find(edge.first,  parents);
        int p2 = Find(edge.second, parents);

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
