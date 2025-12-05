/*
    ==============
    === MEDIUM ===
    ==============

    ================================
    1202) Smallest String With Swaps
    ================================

    ============
    Description:
    ============

    You are given a string s, and an array of pairs of indices in the string
    pairs where pairs[i] = [a, b] indicates 2 indices(0-indexed) of the string.

    You can swap the characters at any pair of indices in the given pairs any
    number of times.

    Return the lexicographically smallest string that s can be changed to after
    using the swaps.

    ===============================================================================
    FUNCTION: string smallestStringWithSwaps(string s, vector<vector<int>>& pairs);
    ===============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "dcab", pairs = [[0,3],[1,2]]
    Output: "bacd"
    Explaination:
    Swap s[0] and s[3], s = "bcad"
    Swap s[1] and s[2], s = "bacd"

    --- Example 2 ---
    Input: s = "dcab", pairs = [[0,3],[1,2],[0,2]]
    Output: "abcd"
    Explaination:
    Swap s[0] and s[3], s = "bcad"
    Swap s[0] and s[2], s = "acbd"
    Swap s[1] and s[2], s = "abcd"

    --- Example 3 ---
    Input: s = "cba", pairs = [[0,1],[1,2]]
    Output: "abc"
    Explaination:
    Swap s[0] and s[1], s = "bca"
    Swap s[1] and s[2], s = "bac"
    Swap s[0] and s[1], s = "abc"


    *** Constraints ***
    1 <= s.length <= 10^5
    0 <= pairs.length <= 10^5
    0 <= pairs[i][0], pairs[i][1] < s.length
    s only contains lower case English letters.

*/

#include <algorithm>
#include <numeric>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 99.54% */
/* Space Beats: 72.79% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class DSU {
public:
    vector<int> rank;
    vector<int> parent;

    DSU(int n)
    {
        rank.assign(n, 1);

        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
        // iota(parent.begin(), parent.end(), 1);
    }

    int find_root_node(int node)
    {
        // Get root parent
        while (node != parent[node])
        {
            // Huge Optimization (From O(n) to Amortized O(1) Time Complexity)
            // If there is no grandparent, nothing will happen
            parent[node] = parent[parent[node]];

            node = parent[node];
        }

        return node;
    }

    bool union_components(int node1, int node2)
    {
        int root1 = find_root_node(node1);
        int root2 = find_root_node(node2);

        if (root1 == root2)
            return false;

        if (rank[root1] < rank[root2])
            swap(root1, root2);

        // Make sure that to merge TOWARDS the smaller node, i.e. root1
        parent[root2] = root1;
        rank[root1] += rank[root2];

        return true;
    }
};

class Solution {
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs)
    {
        const int N = s.size();
        DSU dsu(N);

        // Build connected components
        for (const auto& p : pairs)
            dsu.union_components(p[0], p[1]);

        // Group indices by root
        vector<vector<int>> component_indices(N);
        for (int i = 0; i < N; i++)
        {
            int root = dsu.find_root_node(i);
            component_indices[root].push_back(i);
        }

        // For each component, collect letters, sort, and put back
        for (auto& indices : component_indices)
        {
            if (indices.empty())
                continue;

            string collected = "";
            for (const int& idx : indices)
                collected += s[idx];

            /* Sort */
            sort(collected.begin(), collected.end());
            sort(indices.begin(), indices.end());

            for (int i = 0; i < static_cast<int>(indices.size()); i++)
                s[indices[i]] = collected[i];
        }

        return s;
    }
};
