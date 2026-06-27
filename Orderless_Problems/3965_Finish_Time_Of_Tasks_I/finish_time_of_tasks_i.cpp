/*
    ==============
    === MEDIUM ===
    ==============

    ============================
    3965) Finish Time of Tasks I
    ============================

    ============
    Description:
    ============

    You are given an integer n representing the number of tasks in a project,
    numbered from 0 to n - 1. These tasks are connected as a tree rooted at
    task 0. This is represented by a 2D integer array edges of length n - 1,
    where edges[i] = [ui, vi] indicates that task ui is the parent of task vi.

    You are also given an array baseTime of length n, where baseTime[i]
    represents the time to complete task i.

    The finish time of each task is calculated as follows:

        Leaf task: The finish time is baseTime[i].

        Non-leaf task:
            + Let earliest be the minimum finish time among its children, and
              latest be the maximum finish time among its children.

            + Let ownDuration be (latest - earliest) + baseTime[i].

            + The finish time of task i is latest + ownDuration.

    Return the finish time of the root task 0.

    =========================================================================================
    FUNCTION: long long finishTime(int n, vector<vector<int>>& edges, vector<int>& baseTime);
    =========================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 3, edges = [[0,1],[1,2]], baseTime = [9,5,3]
    Output: 17
    Explanation: 
    Task 2 is a leaf, so its finish time is baseTime[2] = 3.
    Task 1 has one child task 2:

        earliest = latest = 3
        ownDuration = (latest - earliest) + baseTime[1] = 5
        Finish time of task 1 is 3 + 5 = 8

    Task 0 has one child with finish time 8:

        earliest = latest = 8
        ownDuration = (latest - earliest) + baseTime[0] = 9
        Finish time of task 0 is 8 + 9 = 17



    --- Example 2 ---
    Input: n = 3, edges = [[0,1],[0,2]], baseTime = [4,7,6]
    Output: 12
    Explanation:
    Task 1 is a leaf, so its finish time is baseTime[1] = 7.
    Task 2 is a leaf, so its finish time is baseTime[2] = 6.
    Task 0 has two children with finish times 7 and 6:

        earliest = 6, latest = 7
        ownDuration = (latest - earliest) + baseTime[0] = (7 - 6) + 4 = 5
        Finish time of task 0 is latest + ownDuration = 7 + 5 = 12


    --- Example 3 ---
    Input: n = 4, edges = [[0,1],[0,2],[2,3]], baseTime = [5,8,2,1]
    Output: 18
    Explanation:
        Task 1 is a leaf, so its finish time is baseTime[1] = 8.
        Task 3 is a leaf, so its finish time is baseTime[3] = 1.
        Task 2 has one child task 3:
            earliest = latest = 1
            ownDuration = (latest - earliest) + baseTime[2] = 0 + 2 = 2
            Finish time of task 2 is latest + ownDuration = 1 + 2 = 3
        Task 0 has two children with finish times 8 and 3:
            earliest = 3, latest = 8
            ownDuration = (latest - earliest) + baseTime[0] = (8 - 3) + 5 = 10
            Finish time of task 0 is latest + ownDuration = 8 + 10 = 18

    *** Constraints ***
    1 <= n <= 10^5
    edges.length = n - 1
    edges[i] == [ui, vi]
    0 <= ui, vi <= n - 1
    ui != vi
    The input is generated such that edges represents a valid tree.
    baseTime.length == n
    1 <= baseTime[i] <= 10^5

*/

#include <climits>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 17.11% */
/* Space Beats:  8.04% */

/* Time  Complexity: O(V + E) */
/* Space Complexity: O(V + E) */
class Solution_DFS {
public:
    long long finishTime(int n, vector<vector<int>>& edges, vector<int>& baseTime)
    {
        const int N = baseTime.size();

        unordered_map<int, vector<int>> adj_list;
        for (const vector<int>& entry : edges)
        {
            const int& u = entry[0];
            const int& v = entry[1];

            adj_list[u].push_back(v);
        }

        vector<long long> finish_time(N, -1LL);
        dfs(0, -1, adj_list, baseTime, finish_time);

        return finish_time[0];
    }

private:
    void dfs(int node, int parent, unordered_map<int, vector<int>>& adj_list, vector<int>& baseTime, vector<long long>& finish_time)
    {
        if (adj_list[node].empty()) // I'm a LEAF
        {
            finish_time[node] = 1LL * baseTime[node];
            return;
        }

        long long earliest = LLONG_MAX;
        long long latest   = 0LL;
        for (const int& child : adj_list[node])
        {
            if (child == parent)
                continue;

            dfs(child, node, adj_list, baseTime, finish_time);

            earliest = min(earliest, finish_time[child]);
            latest   = max(latest,   finish_time[child]);
        }

        finish_time[node] = latest + ((latest - earliest) + baseTime[node]);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 50.78% */
/* Space Beats: 46.90% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_BFS {
public:
    long long finishTime(int n, vector<vector<int>>& edges, vector<int>& baseTime)
    {
        vector<vector<int>> adj_list(n);
        vector<int> out_degree(n, 0);

        for (const vector<int>& edge : edges)
        {
            int parent = edge[0];
            int child  = edge[1];

            adj_list[child].push_back(parent); // We're doing the REVERSE order
            out_degree[parent]++;
        }

        vector<long long> finish_time(n, 0LL);
        vector<long long> earliest_child(n, LLONG_MAX);
        vector<long long> latest_child(n, LLONG_MIN);
        vector<int> completed_children(n, 0);

        queue<int> queue;

        for (int node = 0; node < n; node++)
        {
            if (out_degree[node] != 0)
                continue;

            finish_time[node] = baseTime[node];
            queue.push(node);
        }

        while ( ! queue.empty())
        {
            int child = queue.front();
            queue.pop();

            for (const int& parent : adj_list[child])
            {
                earliest_child[parent] = min(earliest_child[parent], finish_time[child]);
                latest_child[parent]   = max(latest_child[parent],   finish_time[child]);

                if (++completed_children[parent] != out_degree[parent])
                    continue;

                finish_time[parent] = latest_child[parent]
                                    + (latest_child[parent] - earliest_child[parent])
                                    + baseTime[parent];

                queue.push(parent);
            }
        }

        return finish_time[0];
    }
};
