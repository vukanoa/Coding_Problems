#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

/*
    ==============
    === MEDIUM ===
    ==============

    =====================================================
    3243) Shortest Distance After Road Addition Queries I
    =====================================================

    ============
    Description:
    ============

    You are given an integer n and a 2D integer array queries.

    There are n cities numbered from 0 to n - 1. Initially, there is a
    unidirectional road from city i to city i + 1 for all 0 <= i < n - 1.

    queries[i] = [ui, vi] represents the addition of a new unidirectional road
    from city ui to city vi. After each query, you need to find the length of
    the shortest path from city 0 to city n - 1.

    Return an array answer where for each i in the range [0, queries.length -
    1], answer[i] is the length of the shortest path from city 0 to city n - 1
    after processing the first i + 1 queries.

    ========================================================================================
    FUNCTION: vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries);
    ========================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 5, queries = [[2,4],[0,2],[0,4]]
    Output: [3,2,1]
    Explanation:

                                    _____________
                                    |           |
                                    |           v
                        0 --> 1 --> 2 --> 3 --> 4

    After the addition of the road from 2 to 4, the length of the shortest path
    from 0 to 4 is 3.


                        _____________  __________
                        |           | /         |
                        |           v/          v
                        0 --> 1 --> 2 --> 3 --> 4

    After the addition of the road from 0 to 2, the length of the shortest path
    from 0 to 4 is 2.

                  _____________________________________
                  |                                   |
                  |      ____________  __________     |
                  |     |           | /         |     |
                  |     |           v/          v     |
                  |---- 0 --> 1 --> 2 --> 3 --> 4  <---

    After the addition of the road from 0 to 4, the length of the shortest path
    from 0 to 4 is 1.



    --- Example 2 ---
    Input: n = 4, queries = [[0,3],[0,2]]
    Output: [1,1]
    Explanation:

                        ___________________
                        |           |     |
                        |           v     v
                        0 --> 1 --> 2 --> 3

    After the addition of the road from 0 to 3, the length of the shortest path
    from 0 to 3 is 1.


                        ___________________
                        |                 |
                        |                 v
                        0 --> 1 --> 2 --> 3

    After the addition of the road from 0 to 2, the length of the shortest path
    remains 1.



    *** Constraints ***
    3 <= n <= 500
    1 <= queries.length <= 500
    queries[i].length == 2
    0 <= queries[i][0] < queries[i][1] < n
    1 < queries[i][1] - queries[i][0]
    There are no repeated roads among the queries.

*/

/*

   Which one of the two Solutions listed down below is more efficient?
   Depends!


    | Aspect                      | Solution 1 (BFS)                         | Solution 2 (DP)                           |
    |-----------------------------+------------------------------------------|-------------------------------------------+
    | Graph Representation        | `adj_list` (outgoing edges)              | `reversed_adj_list` (incoming edges)      |
    | Shortest Path Calc          | BFS for node 0 to node n-1               | Bottom-up DP for all nodes                |
    | Efficiency on Dense Graphs  | Worse (explores reachable nodes only)    | Better (processes all nodes in parallel)  |
    | Efficiency on Sparse Graphs | Better (stops once destination is found) | Worse (processes all nodes unnecessarily) |
    | Ease of Implementation      | Relatively simple                        | Moderate                                  |
    | Total Complexity            | O(Q  (n + E))                            | O(Q  (n + E))                             |

*/


using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 9.52% */
/* Space Beats: 9.76% */

/* Time  Complexity: O(Q * (n + Q)) */ // Q <==> queries.length()
/* Space Complexity: O(n + Q)       */
class Solution {
public:
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries)
    {
        vector<int> answer; // Result

        vector<vector<int>> adj_list(n, vector<int>());

        // Default graph-structure for this problem
        for (int i = 0; i < n; i++)
            adj_list[i].push_back(i+1);

        // Add query-by-query in adj_list and calculate shortest-distance
        for (const vector<int>& query : queries)
        {
            const int& src = query[0];
            const int& dst = query[1];

            adj_list[src].push_back(dst);

            answer.push_back(shortest_distance(n, adj_list));
        }

        return answer;
    }

private:
    int shortest_distance(int n, vector<vector<int>>& adj_list)
    {
        queue<pair<int,int>> queue; // {node, min-distance(jumps) from node_0}
        queue.push({0,0});

        unordered_set<int> visited;
        visited.insert(0);

        while ( ! queue.empty())
        {
            int size = queue.size();

            for (int x = 0; x < size; x++)
            {
                pair<int, int> curr_pair = queue.front();
                queue.pop();

                int& curr_node = curr_pair.first;
                int& min_dist  = curr_pair.second;

                if (curr_node == n-1)
                    return min_dist; // We are "destined" to get here

                for (const int& nei : adj_list[curr_node])
                {
                    if (visited.find(nei) == visited.end()) // nei NOT visited
                    {
                        queue.push({nei, min_dist + 1});
                        visited.insert(nei);
                    }
                }
            }
        }

        return -1; // This one will never execute
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 76.19% */
/* Space Beats: 76.59% */

/* Time  Complexity: O(Q * (n + Q)) */ // Q <==> queries.length()
/* Space Complexity: O(n + Q)       */
class Solution_Reversed_Adj_List__Bottom_Up_DP {
public:
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries)
    {
        vector<int> answer; // Result

        vector<vector<int>> reversed_adj_list(n, vector<int>());

        // Default reversed_adj_list graph-structure for this problem
        for (int i = 1; i < n; i++)
            reversed_adj_list[i].push_back(i-1);

        // Add query-by-query in adj_list and calculate shortest-distance
        for (const vector<int>& query : queries)
        {
            const int& src = query[0];
            const int& dst = query[1];

            reversed_adj_list[dst].push_back(src);

            answer.push_back(shortest_distance(n, reversed_adj_list));
        }

        return answer;
    }

private:
    /* Bottom-Up Dynamic Programming */
    int shortest_distance(int n, vector<vector<int>>& reversed_adj_list)
    {
        const int ONE_MORE_THAN_MAX_POSSIBLE = n+1;
        vector<int> dp(n, ONE_MORE_THAN_MAX_POSSIBLE);
        dp[0] = 0;

        for (int i = 1; i < n; i++)
        {
            for (const int& nei : reversed_adj_list[i])
            {
                // "nei" is a node that POINTS TO current node
                dp[i] = min(dp[i], dp[nei]);
            }

            dp[i]++; // Include a jump from the node with min-distance to curr_node
        }

        return dp[n-1];
    }
};
