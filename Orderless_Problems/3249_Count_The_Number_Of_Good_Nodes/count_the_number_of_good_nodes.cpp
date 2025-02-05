/*
    ==============
    === MEDIUM ===
    ==============

    ====================================
    3249) Count the Number of Good Nodes
    ====================================

    ============
    Description:
    ============

    There is an undirected tree with n nodes labeled from 0 to n - 1, and
    rooted at node 0. You are given a 2D integer array edges of length n - 1,
    where edges[i] = [ai, bi] indicates that there is an edge between nodes
    ai and bi in the tree.

    A node is good if all the subtrees rooted at its children have the same
    size.

    Return the number of good nodes in the given tree.

    A subtree of treeName is a tree consisting of a node in treeName and all of
    its descendants.

    =========================================================
    FUNCTION: int countGoodNodes(vector<vector<int>>& edges);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: edges = [[0,1],[0,2],[1,3],[1,4],[2,5],[2,6]]
    Output: 7

    --- Example 2 ---
    Input: edges = [[0,1],[1,2],[2,3],[3,4],[0,5],[1,6],[2,7],[3,8]]
    Output: 6

    --- Example 3 ---
    Input: edges = [[0,1],[1,2],[1,3],[1,4],[0,5],[5,6],[6,7],[7,8],[0,9],[9,10],[9,12],[10,11]]
    Output: 12


    *** Constraints ***
    2 <= n <= 10^5
    edges.length == n - 1
    edges[i].length == 2
    0 <= ai, bi < n
    The input is generated such that edges represents a valid tree.

*/

#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    A classic "graph-like" Tree problem.

    Since we're told that there are N nodes and exactly N-1 edges and since
    we're told that:

        "The input is generated such that edges represents a valid tree."

    We don't have to think about the cycles. That makes it substantually
    easier.


    First--as in almost any graph-like type of problem--buuild an adjacency
    list from given "edges".

    Then, we must begin at node 0, which is considered the root of the Tree.
    Do a simple DFS where we're counting the size of all the subtrees of the
    current node.

    One thing that is problematic is--since edges are UNDIRECTED--how do we
    make sure not to count our parent as one of the children?

    Simply keep a "prev" pointer. That's why it's important that there are no
    cycles, which makes this problem much easier.

    If the "neighbor" of some node, in its adjacency list, is equal to "prev",
    simply skip that one.

    The rest is self-explanatory. Literally do what you're told.

*/

/* Time  Beats: 11.19% */
/* Space Beats:  5.27% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int countGoodNodes(vector<vector<int>>& edges)
    {
        const int N = edges.size() + 1;
        int result = 0;

        std::unordered_map<int, std::vector<int>> adj_list;

        for (auto& entry : edges)
        {
            adj_list[entry[0]].push_back(entry[1]);
            adj_list[entry[1]].push_back(entry[0]);
        }

        dfs(adj_list, -1, 0, result);

        return result;
    }

private:
    pair<int, bool> dfs(unordered_map<int, std::vector<int>>& adj_list, int prev, int curr_node, int& result)
    {
        unordered_set<int> uset;
        vector<int> subtrees;

        for (const int& neighbor : adj_list[curr_node])
        {
            if (neighbor == prev)
                continue;

            auto [size_of_subtree, good_subtree] = dfs(adj_list, curr_node, neighbor, result);

            uset.insert(size_of_subtree);
            subtrees.push_back(size_of_subtree);
        }

        int sum = accumulate(subtrees.begin(), subtrees.end(), 0);

        if (uset.size() <= 1)
        {
            result++;
            return {sum + 1, true};
        }

        return {sum + 1, false};
    }
};
