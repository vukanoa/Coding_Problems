/*
    ============
    === HARD ===
    ============

    ==============================
    3710) Maximum Partition Factor
    ==============================

    ============
    Description:
    ============

    You are given a 2D integer array points, where points[i] = [xi, yi]
    represents the coordinates of the ith point on the Cartesian plane.

    The Manhattan distance between two points points[i] = [xi, yi] and
    points[j] = [xj, yj] is |xi - xj| + |yi - yj|.

    Split the n points into exactly two non-empty groups. The partition factor
    of a split is the minimum Manhattan distance among all unordered pairs of
    points that lie in the same group.

    Return the maximum possible partition factor over all valid splits.

    =====
    Note: A group of size 1 contributes no intra-group pairs. When n = 2 (both
          groups size 1), there are no intra-group pairs, so define the
          partition factor as 0. 
    =====

    ==============================================================
    FUNCTION: int maxPartitionFactor(vector<vector<int>>& points);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: points = [[0,0],[0,2],[2,0],[2,2]]
    Output: 4
    Explanation:
    We split the points into two groups: {[0, 0], [2, 2]} and {[0, 2], [2, 0]}.
        In the first group, the only pair has Manhattan distance |0 - 2| + |0 - 2| = 4.
        In the second group, the only pair also has Manhattan distance |0 - 2| + |2 - 0| = 4.
    The partition factor of this split is min(4, 4) = 4, which is maximal.


    --- Example 2 ---
    Input: points = [[0,0],[0,1],[10,0]]
    Output: 11
    Explanation:
    We split the points into two groups: {[0, 1], [10, 0]} and {[0, 0]}.
        In the first group, the only pair has Manhattan distance |0 - 10| + |1 - 0| = 11.
        The second group is a singleton, so it contributes no pairs.
    The partition factor of this split is 11, which is maximal.


    *** Constraints ***
    2 <= points.length <= 500
    points[i] = [xi, yi]
    -10^8 <= xi, yi <= 10^8

*/

#include <cstdlib>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 66.92% */
/* Space Beats: 88.72% */

// D = maximum Manhattan distance between any two points
/* Time  Complexity: O(N^2 * alpha(N) * log(D)) */
/* Space Complexity: O(N)                       */
class DSU {
private:
    vector<int> parent;
    vector<int> size;
    int components;

public:
    DSU(int n)
    {
        components = n;

        parent.resize(n);
        size.resize(n);

        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
            size[i]   = 1;
        }
    }

    int find_root(int node)
    {
        while (node != parent[node])
        {
            /* Inverse Ackerman function, <= 5 for all practical Inputs */
            parent[node] = parent[parent[node]]; // O(alpha(V)) --> O(1)

            node = parent[node];
        }

        return node;
    }

    bool union_components(int node_1, int node_2)
    {
        int root_1 = find_root(node_1); // O(alpha(V)) --> O(1)
        int root_2 = find_root(node_2); // O(alpha(V)) --> O(1)

        if (root_1 == root_2)
            return false;

        if (size[root_1] < size[root_2])
            swap(root_1, root_2);

        parent[root_2] = root_1;
        size[root_1]  += size[root_2];

        --components;

        return true;
    }

    int number_of_components()
    {
        return components;
    }

    bool are_connected(int node_1, int node_2)
    {
        return find_root(node_1) == find_root(node_2);
    }
};


class Solution {
public:
    int maxPartitionFactor(vector<vector<int>>& points)
    {
        const int N = points.size();

        if (N == 2)
            return 0;

        /* Find the Search Space */
        int low  = 0;
        int high = 0;

        for (int i = 0; i < N; i++)
        {
            for (int j = i+1; j < N; j++)
                high = max(high, manhattan_distance(points[i], points[j]));
        }


        /* Binary Search On the Answer range */
        int result = 0;

        while (low < high)
        {
            int mid = low + (high - low) / 2; // Low-leaning mid

            if (is_bipartite(points, mid))
            {
                result = mid;  // take THIS         min_distance
                low = mid + 1; // try with a LARGER min_distance
            }
            else
                high = mid;
        }

        if (is_bipartite(points, low)) // In case we've always been in "else"
            result = low;

        return result;
    }

private:
    int manhattan_distance(const vector<int>& a, const vector<int>& b)
    {
        return abs(a[0] - b[0]) + abs(a[1] - b[1]);
    }

    bool is_bipartite(const vector<vector<int>>& points, int min_distance)
    {
        const int N = points.size();

        DSU dsu(2 * N);

        /* Build the DSU */
        for (int i = 0; i < N; i++)
        {
            for (int j = i+1; j < N; j++)
            {
                int manhattan_dist = manhattan_distance(points[i], points[j]);

                if (manhattan_dist < min_distance)
                {
                    dsu.union_components(i    , j + N);
                    dsu.union_components(i + N, j    );
                }
            }
        }

        /* Check for Contradictions */
        for (int i = 0; i < N; i++)
        {
            if (dsu.are_connected(i, i + N))
                return false;
        }

        return true;
    }
};
