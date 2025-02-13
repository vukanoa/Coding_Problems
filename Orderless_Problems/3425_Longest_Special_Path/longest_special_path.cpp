/*
    ============
    === HARD ===
    ============

    ===========================
    3425) Longest Special Path
    ===========================

    ============
    Description:
    ============

    You are given an undirected tree rooted at node 0 with n nodes numbered from
    0 to n - 1, represented by a 2D array edges of length n - 1, where
    edges[i] = [ui, vi, lengthi] indicates an edge between nodes ui and vi with
    length lengthi. You are also given an integer array nums, where nums[i]
    represents the value at node i.

    A special path is defined as a downward path from an ancestor node to a
    descendant node such that all the values of the nodes in that path are
    unique.

    Note that a path may start and end at the same node.

    Return an array result of size 2, where result[0] is the length of the
    longest special path, and result[1] is the minimum number of nodes in all
    possible longest special paths.

    ========================================================================================
    FUNCTION: vector<int> longestSpecialPath(vector<vector<int>>& edges, vector<int>& nums);
    ========================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: edges = [[0,1,2],[1,2,3],[1,3,5],[1,4,4],[2,5,6]], nums = [2,1,2,1,3,1]
    Output: [6,2]
    Explanation:
    In the image below, nodes are colored by their corresponding values in
    The longest special paths are 2 -> 5 and 0 -> 1 -> 4, both having a length
    of 6. The minimum number of nodes across all longest special paths is 2.


    --- Example 2 ---
    Input: edges = [[1,0,8]], nums = [2,2]
    Output: [0,1]
    Explanation:
    The longest special paths are 0 and 1, both having a length of 0. The
    minimum number of nodes across all longest special paths is 1.


    *** Constraints ***
    2 <= n <= 5 * 10^4
    edges.length == n - 1
    edges[i].length == 3
    0 <= ui, vi < n
    1 <= lengthi <= 10^3
    nums.length == n
    0 <= nums[i] <= 5 * 10^4
    The input is generated such that edges represents a valid tree.

*/

#include <utility>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 92.46% */
/* Space Beats: 95.13% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    pair<int, int> max_special_path{0, 1};
    int node_depth[50001] = {};

    vector<int> longestSpecialPath(vector<vector<int>>& edges, vector<int>& nums)
    {
        vector<vector<pair<int, int>>> adj_list(nums.size());

        for (const auto& edge : edges)
        {
            adj_list[edge[0]].push_back({edge[1], edge[2]});
            adj_list[edge[1]].push_back({edge[0], edge[2]});
        }

        depth_first_search(adj_list, nums, vector<int>() = {0}, 0, -1, 0, 1);

        return {-max_special_path.first, max_special_path.second};
    }

private:
    void depth_first_search(vector<vector<pair<int, int>>>& adj_list,
                            vector<int>& nums,
                            vector<int>& path_sums,
                            int current_node,
                            int parent_node,
                            int leftmost_node,
                            int current_depth)
    {
        int previous_depth = exchange(node_depth[nums[current_node]], current_depth);

        leftmost_node = max(leftmost_node, previous_depth);
        max_special_path = min(max_special_path, {-(path_sums.back() - path_sums[leftmost_node]), current_depth - leftmost_node});

        for (auto& [next_node, edge_weight] : adj_list[current_node])
        {
            if (next_node != parent_node)
            {
                path_sums.push_back(path_sums.back() + edge_weight);
                depth_first_search(adj_list, nums, path_sums, next_node, current_node, leftmost_node, current_depth + 1);
                path_sums.pop_back();
            }
        }

        node_depth[nums[current_node]] = previous_depth;
    }
};
