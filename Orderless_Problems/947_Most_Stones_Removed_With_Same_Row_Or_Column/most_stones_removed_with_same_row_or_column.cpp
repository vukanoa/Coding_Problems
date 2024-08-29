#include <iostream>
#include <vector>
#include <bitset>

/*
    ==============
    === MEDIUM ===
    ==============

    ================================================
    947) Most Stones Removed with Same Row or Column
    ================================================

    ============
    Description:
    ============

    On a 2D plane, we place n stones at some integer coordinate points. Each
    coordinate point may have at most one stone.

    A stone can be removed if it shares either the same row or the same column
    as another stone that has not been removed.

    Given an array stones of length n where stones[i] = [xi, yi] represents the
    location of the ith stone, return the largest possible number of stones
    that can be removed.

    ========================================================
    FUNCTION: int removeStones(vector<vector<int>>& stones);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
    Output: 5
    Explanation: One way to remove 5 stones is as follows:
    1. Remove stone [2,2] because it shares the same row as [2,1].
    2. Remove stone [2,1] because it shares the same column as [0,1].
    3. Remove stone [1,2] because it shares the same row as [1,0].
    4. Remove stone [1,0] because it shares the same column as [0,0].
    5. Remove stone [0,1] because it shares the same row as [0,0].
    Stone [0,0] cannot be removed since it does not share a row/column with
    another stone still on the plane.

    --- Example 2 ---
    Input: stones = [[0,0],[0,2],[1,1],[2,0],[2,2]]
    Output: 3
    Explanation: One way to make 3 moves is as follows:
    1. Remove stone [2,2] because it shares the same row as [2,0].
    2. Remove stone [2,0] because it shares the same column as [0,0].
    3. Remove stone [0,2] because it shares the same row as [0,0].
    Stones [0,0] and [1,1] cannot be removed since they do not share a
    row/column with another stone still on the plane.

    --- Example 3 ---
    Input: stones = [[0,0]]
    Output: 0
    Explanation: [0,0] is the only stone on the plane, so you cannot remove it.


    *** Constraints ***
    1 <= stones.length <= 1000
    0 <= xi, yi <= 10^4
    No two stones are at the same coordinate point.

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 46.56% */
/* Space Beats: 70.48% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    vector<int> row[10001];
    vector<int> col[10001];

    bitset<1001> visited;// bitset is good

    void dfs(int idx, vector<vector<int>>& stones)
    {
        const int i = stones[idx][0];
        const int j = stones[idx][1];

        visited[idx] = 1;

        for (auto k : row[i])
        {
            if ( ! visited[k])
                dfs(k, stones);
        }

        for (auto k : col[j])
        {
            if ( ! visited[k])
                dfs(k, stones);
        }
    }

    int removeStones(vector<vector<int>>& stones)
    {
        const int n = stones.size();

        for (int idx = 0; idx < n; idx++)
        {
            const int i = stones[idx][0];
            const int j = stones[idx][1];

            row[i].push_back(idx);
            col[j].push_back(idx);
        }

        int component = 0;
        for  (int idx = 0; idx < n; idx++)
        {
            const int i = stones[idx][0];
            const int j = stones[idx][1];

            if ( ! visited[idx])
            {
                dfs(idx, stones);
                component++;
            }
        }

        return n - component;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 65.95% */
/* Space Beats: 46.90% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Union_and_Find {
public:
    unordered_map<short, vector<short>> row_col_adj_list;
    bitset<20003> visited;

    int removeStones(vector<vector<int>>& stones)
    {
        const int n = stones.size();
        const int M = 10001;

        row_col_adj_list.reserve(200);

        for (int idx = 0; idx < n; idx++)
        {
            const int i = stones[idx][0];
            const int j = stones[idx][1];

            row_col_adj_list[i].push_back(j+M);
            row_col_adj_list[M+j].push_back(i);
        }

        int component = 0;

        for (auto& [i, _] : row_col_adj_list)
        {
            if (visited[i] == 0)
            {
                dfs(i);
                component++;
            }
        }

        return n - component;
    }

private:
    void dfs(short idx)
    {
        visited[idx] = 1;

        for (short k : row_col_adj_list[idx])
        {
            if (visited[k] == 0)
                dfs(k);
        }
    }
};
