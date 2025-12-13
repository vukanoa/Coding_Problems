/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    765) Couple Holding Hands
    ===========================

    ============
    Description:
    ============

    There are n couples sitting in 2n seats arranged in a row and want to hold
    hands.

    The people and seats are represented by an integer array row where row[i]
    is the ID of the person sitting in the ith seat. The couples are numbered
    in order, the first couple being (0, 1), the second couple being (2, 3),
    and so on with the last couple being (2n - 2, 2n - 1).

    Return the minimum number of swaps so that every couple is sitting side by
    side. A swap consists of choosing any two people, then they stand up and
    switch seats.

    ================================================
    FUNCTION: int minSwapsCouples(vector<int>& row);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: row = [0,2,1,3]
    Output: 1
    Explanation: We only need to swap the second (row[1]) and third (row[2])
                 person.

    --- Example 2 ---
    Input: row = [3,2,0,1]
    Output: 0
    Explanation: All couples are already seated side by side.


    *** Constraints ***
    2n == row.length
    2 <= n <= 30
    0 <= row[i] < 2n
    All the elements of row are unique.

*/

#include <vector>
#include <numeric>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  89.51% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class DSU {
public:
    vector<int> rank;
    vector<int> parent;

    DSU(int n)
    {
        rank.assign(n, 1);

        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
    }

    int find_root_node(int node)
    {
        while (node != parent[node])
        {
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

        parent[root2] = root1;
        rank[root1] += rank[root2];

        return true;
    }
};

class Solution {
public:
    int minSwapsCouples(vector<int>& row)
    {
        int N = row.size() / 2;
        DSU dsu(N);

        for (int i = 0; i < N; i++)
        {
            int a = row[2 * i];
            int b = row[2 * i + 1];

            dsu.union_components(a / 2, b / 2);
        }

        int components = 0;
        for (int i = 0; i < N; i++)
        {
            if (dsu.find_root_node(i) == i)
                components++;
        }

        return N - components;
    }
};
