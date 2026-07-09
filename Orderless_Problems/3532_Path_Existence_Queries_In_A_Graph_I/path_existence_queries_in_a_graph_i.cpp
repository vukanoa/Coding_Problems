/*
    ==============
    === MEDIUM ===
    ==============

    =========================================
    3532) Path Existence Queries in a Graph I
    =========================================

    ============
    Description:
    ============

    You are given an integer n representing the number of nodes in a graph,
    labeled from 0 to n - 1.

    You are also given an integer array nums of length n sorted in
    non-decreasing order, and an integer maxDiff.

    An undirected edge exists between nodes i and j if the absolute difference
    between nums[i] and nums[j] is at most maxDiff
    (i.e., |nums[i] - nums[j]| <= maxDiff).

    You are also given a 2D integer array queries.
    For each queries[i] = [ui, vi], determine whether there exists a path
    between nodes ui and vi.

    Return a boolean array answer, where answer[i] is true if there exists a
    path between ui and vi in the ith query and false otherwise.

    =================================================================================================================
    FUNCTION: vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries);
    =================================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 2, nums = [1,3], maxDiff = 1, queries = [[0,0],[0,1]]
    Output: [true,false]
    Explanation:
        Query [0,0]: Node 0 has a trivial path to itself.
        Query [0,1]: There is no edge between Node 0 and Node 1 because
        |nums[0] - nums[1]| = |1 - 3| = 2, which is greater than maxDiff.
        Thus, the final answer after processing all the queries is [true, false].


    --- Example 2 ---
    Input: n = 4, nums = [2,5,6,8], maxDiff = 2, queries = [[0,1],[0,2],[1,3],[2,3]]
    Output: [false,false,true,true]
    Explanation:
    The resulting graph is:
        Query [0,1]: There is no edge between Node 0 and Node 1 because
        |nums[0] - nums[1]| = |2 - 5| = 3, which is greater than maxDiff.
        Query [0,2]: There is no edge between Node 0 and Node 2 because
        |nums[0] - nums[2]| = |2 - 6| = 4, which is greater than maxDiff.
        Query [1,3]: There is a path between Node 1 and Node 3 through Node 2
        since |nums[1] - nums[2]| = |5 - 6| = 1 and
        |nums[2] - nums[3]| = |6 - 8| = 2, both of which are within maxDiff.
        Query [2,3]: There is an edge between Node 2 and Node 3 because
        |nums[2] - nums[3]| = |6 - 8| = 2, which is equal to maxDiff.
        Thus, the final answer after processing all the queries is
        [false, false, true, true].


    *** Constraints ***
    1 <= n == nums.length <= 10^5
    0 <= nums[i] <= 10^5
    nums is sorted in non-decreasing order.
    0 <= maxDiff <= 10^5
    1 <= queries.length <= 10^5
    queries[i] == [ui, vi]
    0 <= ui, vi < n

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

/* Time  Complexity: O(n + Q) */
/* Space Complexity: O(n)     */
class Solution_3 {
private:
    static constexpr int MAX_SIZE = 1e5;

public:
    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries)
    {
        const int Q = queries.size();

        vector<bool> result;
        result.reserve(Q);

        int component[MAX_SIZE] = {0};

        for (int i = 1; i < n; i++)
        {
            if (nums[i] - nums[i-1] <= maxDiff)
                component[i] = component[i-1];
            else
                component[i] = component[i-1] + 1;
        }


        for (const auto &query : queries)
        {
            const int& u = query[0];
            const int& v = query[1];

            result.push_back(component[u] == component[v]);
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    We could also do this by using DSU. It's a bit more cmoplicated than the
    above Solution, however it's very very beneficial to be very comfortable
    with DSU for other Graph problems.

    It is a Fundamental Graph technique alongside DFS & BFS.

*/

/* Time  Beats: 59.18% */
/* Space Beats: 55.07% */

/* Time  Complexity: O(n * alpha(n)  +  Q * alpha(n)) */
/* Space Complexity: O(n)                             */
class DSU {
private:
    vector<int> parent;
    vector<int> size;
    int components;

public:
    DSU (int n)
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

    // TC: alpha(n), practically <= 5 for all practical Input, therefore we
    //     could tread it as a constant, but formally it's alpha(n).
    int find_root(int node)
    {
        while (node != parent[node])
        {
            // Reverse Ackerman function, <= 5 for all practical Inputs
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
            return false; // We have NOT merged, they are already connected

        if (size[root_1] < size[root_2])
            swap(root_1, root_2);

        parent[root_2] = root_1;
        size[root_1]  += size[root_2];

        components--;

        return true; // We have INDEED Marged two components
    }

    int number_of_components()
    {
        return components;
    }

    bool are_connected(int node_1, int node_2)
    {
        int root_1 = find_root(node_1);
        int root_2 = find_root(node_2);

        return root_1 == root_2;
    }
};

class Solution_DSU {
public:
    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries)
    {
        const int M = nums.size();
        const int Q = queries.size();

        DSU dsu(n);

        int left  = 0;
        int right = 1;
        while (right < M)
        {
            while (left < right && abs(nums[right] - nums[left]) > maxDiff)
                left++;

            while (left < right)
            {
                dsu.union_components(left, right);
                left++;
            }

            // Increment
            right++;
        }

        
        vector<bool> result;
        result.reserve(Q);
        for (const auto& query : queries)
        {
            const int& u = query[0];
            const int& v = query[1];

            result.push_back(dsu.are_connected(u, v));
        }

        return result;
    }
};
