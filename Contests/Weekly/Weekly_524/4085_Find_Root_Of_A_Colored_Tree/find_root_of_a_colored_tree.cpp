/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    4085) Find Root of a Colored Tree
    =================================

    ============
    Description:
    ============

    You are given an undirected tree of n nodes labeled from 0 to n - 1,
    represented by a 2D integer array edges of length n - 1, where edges[i] =
    [ui, vi] indicates that there is an undirected edge between nodes ui and
    vi.

    You are also given a string colors of length n, where colors[i] is one of
    'R', 'B', or 'W', and denotes the color of node i.

    A node chosen as root must satisfy both of the following conditions once
    the tree is oriented away from it:

        Binary-tree property: Every node has at most two children.
        Layered color pattern: All nodes at the same depth have the same color.
        Starting at depth 0, these colors follow one of the three repeating
        sequences:

            R → B → W → R → B → W → ...
            B → W → R → B → W → R → ...
            W → R → B → W → R → B → ...

    Return the index of any root that satisfies both conditions, or -1 if no
    such root exists.

    A tree is a connected undirected graph with no cycles.

    The depth of a node is the number of edges on the path from the root to
    that node. The root has depth 0. A child of a node is an adjacent node
    whose depth is one greater.

    The degree of a node is the number of edges incident to it.

    =========================================================================
    FUNCTION: int findColoredRoot(vector<vector<int>>& edges, string colors);
    =========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: edges = [[3,1],[3,2],[1,4],[2,0]], colors = "BRRWB"
    Output: 3
    Explanation:
    Rooting at node 3 gives each node at most two children and every edge
    advances to the next color in the cycle (W → R → B), so return 3.


    --- Example 2 ---
    Input: edges = [[0,1],[1,2],[2,3]], colors = "RBRB"
    Output: -1
    Explanation:
    No root satisfies the required color step on every edge, so return -1.


    *** Constraints ***
    2 <= n <= 10^5
    edges.length == n - 1
    edges[i] = [ui, vi]
    0 <= ui, vi < n
    colors.length == n
    colors[i] is one of 'R', 'B', 'W'.
    The input graph is a tree and every node has degree at most three.

*/

#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 59.13% */
/* Space Beats: 61.39% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int findColoredRoot(vector<vector<int>>& edges, string colors)
    {
        const int N = colors.size();

        vector<int>   degree(N, 0);
        vector<int> indegree(N, 0);

        unordered_map<char,int> idx_of_color;
        idx_of_color['R'] = 0;
        idx_of_color['B'] = 1;
        idx_of_color['W'] = 2;

        for (const auto& edge : edges)
        {
            int u = edge[0];
            int v = edge[1];

            ++degree[u];
            ++degree[v];

            int color_u = idx_of_color[colors[u]];
            int color_v = idx_of_color[colors[v]];

            int steps = (color_v - color_u + 3) % 3;
            if (steps == 0)
                return -1;

            if (steps == 1)
                ++indegree[v]; // u --> v  (u=PARENT, v=child)
            else
                ++indegree[u]; // v --> u  (v=PARENT, u=child) 
        }


        int root                 = -1;
        int nodes_without_parent =  0;
        for (int node = 0; node < N; node++)
        {
            if (indegree[node] == 0)
            {
                root = node;
                ++nodes_without_parent;
            }
        }

        // There MUST be EXACTLY 1 root
        if (nodes_without_parent != 1)
            return -1;



        /**************************/
        /* Binary Tree properties */
        /**************************/

         // Root must have a degree of AT MOST 2, 2 child nodes and NO parent
        if (degree[root] > 2)
            return -1;

        // Other nodes must have a degree of AT MOST 3 nodes, 2 child nodes and
        // 1 parent
        for (int node = 0; node < N; node++)
        {
            if (node != root && degree[node] > 3)
                return -1;
        }

        return root;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    THe exact same idea, however the "tricky" part is writte in another way.
    This may "click" for you.

*/

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_2 {
public:
    int findColoredRoot(vector<vector<int>>& edges, string colors)
    {
        const int N = colors.size();

        vector<int>   degree(N, 0);
        vector<int> indegree(N, 0);

        unordered_map<char,int> color_to_number;
        color_to_number['R'] = 0;
        color_to_number['B'] = 1;
        color_to_number['W'] = 2;

        for (const auto& edge : edges)
        {
            int u = edge[0];
            int v = edge[1];

            ++degree[u];
            ++degree[v];

            int color_u = color_to_number[colors[u]];
            int color_v = color_to_number[colors[v]];

            if (color_u == color_v)
                return -1;

            int next_color_of_u = (color_u + 1) % 3;

            if (next_color_of_u == color_v) // u --> v (u=PARENT, v=child)
                ++indegree[v];
            else                            // v --> u (v=PARENT, u=child)
                ++indegree[u];
        }

        int root                 = -1;
        int nodes_without_parent =  0;
        for (int node = 0; node < N; node++)
        {
            if (indegree[node] == 0)
            {
                root = node;
                ++nodes_without_parent;
            }
        }

        // There MUST be EXACTLY 1 root
        if (nodes_without_parent != 1)
            return -1;



        /**************************/
        /* Binary Tree properties */
        /**************************/

        // ROOT node must have a degree of AT MOST 2 nodes:
        //
        //     2 child nodes and NO parent
        //
        if (degree[root] > 2)
            return -1;


        // OTHER, non-ROOT, nodes must have a degree of AT MOST 3 nodes:
        // 
        //     2 child nodes and 1 parent
        //
        for (int node = 0; node < N; node++)
        {
            if (node != root && degree[node] > 3)
                return -1;
        }

        return root;
    }
};
