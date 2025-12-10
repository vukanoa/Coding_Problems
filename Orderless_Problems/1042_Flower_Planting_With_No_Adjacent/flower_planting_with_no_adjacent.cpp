/*
    ==============
    === MEDIUM ===
    ==============

    ======================================
    1042) Flower Planting with No Adjacent
    ======================================

    ============
    Description:
    ============

    You have n gardens, labeled from 1 to n, and an array paths where paths[i]
    = [xi, yi] describes a bidirectional path between garden xi to garden yi.
    In each garden, you want to plant one of 4 types of flowers.

    All gardens have at most 3 paths coming into or leaving it.

    Your task is to choose a flower type for each garden such that, for any two
    gardens connected by a path, they have different types of flowers.

    Return any such a choice as an array answer, where answer[i] is the type of
    flower planted in the (i+1)th garden. The flower types are denoted 1, 2, 3,
    or 4. It is guaranteed an answer exists.

    =====================================================================
    FUNCTION: vector<int> gardenNoAdj(int n, vector<vector<int>>& paths);
    =====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 3, paths = [[1,2],[2,3],[3,1]]
    Output: [1,2,3]
    Explanation:
    Gardens 1 and 2 have different types.
    Gardens 2 and 3 have different types.
    Gardens 3 and 1 have different types.
    Hence, [1,2,3] is a valid answer. Other valid answers include [1,2,4], [1,4,2], and [3,2,1].

    --- Example 2 ---
    Input: n = 4, paths = [[1,2],[3,4]]
    Output: [1,2,1,2]

    --- Example 3 ---
    Input: n = 4, paths = [[1,2],[2,3],[3,4],[4,1],[1,3],[2,4]]
    Output: [1,2,3,4]


    *** Constraints ***
    1 <= n <= 10^4
    0 <= paths.length <= 2 * 10^4
    paths[i].length == 2
    1 <= xi, yi <= n
    xi != yi
    Every garden has at most 3 paths coming into or leaving it.

*/

#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Basic "Graph Coloring" Problem.
    TODO

*/

/* Time  Beats: 16.75% */
/* Space Beats: 18.28% */

/* Time  Complexity: O(V + E) */
/* Space Complexity: O(V + E) */
class Solution  {
public:
    vector<int> gardenNoAdj(int N, vector<vector<int>>& paths) 
    {
        vector<int> result(N, 0);

        // Create a graph using an Adjacency List
        unordered_map<int, unordered_set<int>> adj_list;
        for (int i = 0; i < N; i++)
            adj_list[i] = unordered_set<int>();

        // Add the edges
        for (const auto& edge : paths) 
        {
            // It's "1-based indexing" that's why we must do " - 1" part.
            int one = edge[0] - 1;
            int two = edge[1] - 1;

            adj_list[one].insert(two);
            adj_list[two].insert(one);
        }


        // Graph coloring
        for (int i = 0; i < N; i++) 
        {
            // We initialize 5 instead of 4 because it's 1-based incexing
            bool used_color[5] = {false};

            for (const int& neighbor : adj_list[i])
                used_color[result[neighbor]] = true;

            // Be Greedy: Assign the first available color
            for (int color_id = 4; color_id >= 1; color_id--) 
            {
                if ( ! used_color[color_id])
                    result[i] = color_id;
            }
        }

        return result;
    }
};
