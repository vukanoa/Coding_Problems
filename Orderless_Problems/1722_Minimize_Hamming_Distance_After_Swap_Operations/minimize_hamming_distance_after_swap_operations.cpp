/*
    ==============
    === MEDIUM ===
    ==============

    =====================================================
    1722) Minimize Hamming Distance After Swap Operations
    =====================================================

    ============
    Description:
    ============

    You are given two integer arrays, source and target, both of length n. You
    are also given an array allowedSwaps where each allowedSwaps[i] = [ai, bi]
    indicates that you are allowed to swap the elements at index ai and index
    bi (0-indexed) of array source. Note that you can swap elements at a
    specific pair of indices multiple times and in any order.

    The Hamming distance of two arrays of the same length, source and target,
    is the number of positions where the elements are different. Formally, it
    is the number of indices i for 0 <= i <= n-1 where source[i] != target[i]
    (0-indexed).

    Return the minimum Hamming distance of source and target after performing
    any amount of swap operations on array source.

    ===============================
    FUNCTION:  
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: source = [1,2,3,4], target = [2,1,4,5], allowedSwaps = [[0,1],[2,3]]
    Output: 1
    Explanation: source can be transformed the following way:
    - Swap indices 0 and 1: source = [2,1,3,4]
    - Swap indices 2 and 3: source = [2,1,4,3]
    The Hamming distance of source and target is 1 as they differ in 1 position: index 3.

    --- Example 2 ---
    Input: source = [1,2,3,4], target = [1,3,2,4], allowedSwaps = []
    Output: 2
    Explanation: There are no allowed swaps.
    The Hamming distance of source and target is 2 as they differ in 2 positions: index 1 and index 2.

    --- Example 3 ---
    Input: source = [5,1,2,4,3], target = [1,5,4,2,3], allowedSwaps = [[0,4],[4,2],[1,3],[1,4]]
    Output: 0


    *** Constraints ***
    n == source.length == target.length
    1 <= n <= 10^5
    1 <= source[i], target[i] <= 10^5
    0 <= allowedSwaps.length <= 10^5
    allowedSwaps[i].length == 2
    0 <= ai, bi <= n - 1
    ai != bi

*/

#include <unordered_map>
#include <vector>
using namespace std;


class DSU {
private:
    vector<int> rank;
    vector<int> parent;

public:
    DSU(int n)
    {
        rank.resize(n);
        parent.resize(n);

        for (int i = 0; i < n; i++)
        {
            rank[i]   = 1;
            parent[i] = i; // 'i'
        }
    }

    int find_root(int node)
    {
        while (node != parent[node])
        {
            /* Inverse Ackerman function, O(1) practically */
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
            return false; // We have NOT performed a UNION

        if (rank[root_1] < rank[root_2])
            swap(root_1, root_2);

        parent[root_2] = root_1;
        rank[root_1]  += rank[root_2];

        return true; // We have INDEED performed a UNION
    }
};

/*
    ------------
    --- IDEA ---
    ------------

    Classic DSU problem. Once you realize that you can rearrange the letter in
    ANY way that you want WITHIN A SINGLE CONNECTED COMPONENT, it becomes
    trivial almost.

*/

/* Time  Beats: 15.70% */
/* Space Beats:  7.85% */

/* Time  Complexity: O(E * alpha(V)  +   V * alpha(V)) */
/* Space Complexity: O(V)                              */
class Solution_2 {
public:
    int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps)
    {
        const int V = source.size();       // Vertices
        const int E = allowedSwaps.size(); // Edges
        int result = 0;

        DSU dsu(V);

        // O(E * alpha(V)) (entire block)
        for (const auto& swaps : allowedSwaps)
        {
            const int& u = swaps[0];
            const int& v = swaps[1];

            dsu.union_components(u, v); // alpha(V)
        }

        unordered_map<int, unordered_map<int, int>> source_root__to__values;
        unordered_map<int, unordered_map<int, int>> target_root__to__values;

        // O(V * alpha(V)) (entire block)
        for (int vertex = 0; vertex < V; vertex++)
        {
            int root = dsu.find_root(vertex); // alpha(V)

            source_root__to__values[root][source[vertex]]++;
            target_root__to__values[root][target[vertex]]++;
        }

        // O((V * alpha(V)  +  V)
        vector<bool> visited(V, false);
        for (int vertex = 0; vertex < V; vertex++)
        {
            int root = dsu.find_root(vertex); // O(alpha(V)), Inverse Ackerman

            if (visited[root])
                continue;

            /* Mark component-ROOT as visited */
            visited[root] = true;

            // O(V) in total
            for (auto& [value, freq_source] : source_root__to__values[root])
            {
                int freq_target = target_root__to__values[root][value];

                if (freq_source > freq_target)
                    result += freq_source - freq_target;
            }
        }

        return result;
    }
};
