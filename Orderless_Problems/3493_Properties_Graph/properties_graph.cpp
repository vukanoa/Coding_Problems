/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    3493) Properties Graph
    ===========================

    ============
    Description:
    ============

    You are given a 2D integer array properties having dimensions n x m and an
    integer k.

    Define a function intersect(a, b) that returns the number of distinct
    integers common to both arrays a and b.

    Construct an undirected graph where each index i corresponds to
    properties[i]. There is an edge between node i and node j if and only if
    intersect(properties[i], properties[j]) >= k, where i and j are in the
    range [0, n - 1] and i != j.

    Return the number of connected components in the resulting graph.

    =========================================================================
    FUNCTION: int numberOfComponents(vector<vector<int>>& properties, int k);
    =========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: properties = [[1,2],[1,1],[3,4],[4,5],[5,6],[7,7]], k = 1
    Output: 3

    --- Example 2 ---
    Input: properties = [[1,2,3],[2,3,4],[4,3,5]], k = 2
    Output: 1

    --- Example 3 ---
    Input: properties = [[1,1],[1,1]], k = 2
    Output: 2
    Explanation: intersect(properties[0], properties[1]) = 1, which is less
                 than k. This means there is no edge between properties[0] and
                 properties[1] in the graph.


    *** Constraints ***
    1 <= n == properties.length <= 100
    1 <= m == properties[i].length <= 100
    1 <= properties[i][j] <= 100
    1 <= k <= m

*/

#include <algorithm>
#include <numeric>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Since the Constraints are small we can calculate the intersection using
    Brute-Force, however when it comes down to, then, calculating the number of
    components, that's a by-the-book Union-and-Find(Disjoint Set) algorithm.

    Make sure you understand Union-and-Find algorithm and them come back. It
    will be a breeze.

*/

/* Time  Beats: 32.49% */
/* Space Beats: 35.61% */

/* Time  Complexity: O(N^2 * M * logM) */
/* Space Complexity: O(N + M)          */
class Solution {
public:
    int numberOfComponents(vector<vector<int>>& properties, int k)
    {
        const int N = properties.size();
        const int M = properties[0].size();

        vector<int> rank(N, 1);
        vector<int> parent(N);
        iota(parent.begin(), parent.end(), 0);

        int count = N;
        for (int i = 0; i < N; i++)
        {
            for (int j = i + 1; j < N; j++)
            {
                if (intersect(properties[i], properties[j]) >= k)
                {
                    if (Union(i, j, parent, rank))
                        count--;
                }
            }
        }

        return count;
    }

private:
    int intersect(vector<int>& a, vector<int>& b)
    {
        unordered_set<int> uset;
        int same = 0;

        sort(a.begin(), a.end());
        sort(b.begin(), b.end());

        int i = 0;
        int j = 0;
        while (i < a.size() && j < b.size())
        {
            if (a[i] < b[j])
            {
                i++;
            }
            else if (b[j] < a[i])
            {
                j++;
            }
            else
            {
                if ( ! uset.count(a[i]))
                {
                    same++;
                    uset.insert(a[i]);
                }

                i++;
                j++;
            }

        }

        return same;
    }

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

    bool Union(int i, int j, vector<int>& parent, vector<int>& rank)
    {
        int root1 = Find(i, parent);
        int root2 = Find(j, parent);

        if (root1 == root2)
            return false;

        if (rank[root2] > rank[root1])
        {
            parent[root1] = root2;
            rank[root2] += rank[root1];
        }
        else // ranks[p1] > ranks[p2]
        {
            parent[root2] = root1;
            rank[root1] += rank[root2];
        }

        return true;
    }
};
