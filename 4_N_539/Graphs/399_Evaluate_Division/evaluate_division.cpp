#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    399) Evaluate Division
    ===========================

    ============
    Description:
    ============

    You are given an array of variable pairs equations and an array of real
    numbers values, where equations[i] = [Ai, Bi] and values[i] represent the
    equation Ai / Bi = values[i]. Each Ai or Bi is a string that represents a
    single variable.

    You are also given some queries, where queries[j] = [Cj, Dj] represents the
    jth query where you must find the answer for Cj / Dj = ?.

    Return the answers to all queries. If a single answer cannot be determined,
    return -1.0.

    =====
    Note: The input is always valid. You may assume that evaluating the queries
          will not result in division by zero and that there is no
          contradiction.
    =====

    =====
    Note: The variables that do not occur in the list of equations are
          undefined, so the answer cannot be determined for them.
    =====

    ==================================================================================================================================
    FUNCTION: vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries);
    ==================================================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries =
    [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
    Output: [6.00000,0.50000,-1.00000,1.00000,-1.00000]
    Explanation:
    Given: a / b = 2.0, b / c = 3.0
    queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ?
    return: [6.0, 0.5, -1.0, 1.0, -1.0 ]
    note: x is undefined => -1.0


    --- Example 2 ---
    Input: equations = [["a","b"],["b","c"],["bc","cd"]], values =
    [1.5,2.5,5.0], queries = [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
    Output: [3.75000,0.40000,5.00000,0.20000]


    --- Example 3 ---
    Input: equations = [["a","b"]], values = [0.5], queries =
    [["a","b"],["b","a"],["a","c"],["x","y"]]
    Output: [0.50000,2.00000,-1.00000,-1.00000]


    *** Constraints ***
    1 <= equations.length <= 20
    equations[i].length == 2
    1 <= Ai.length, Bi.length <= 5
    values.length == equations.length
    0.0 < values[i] <= 20.0
    1 <= queries.length <= 20
    queries[i].length == 2
    1 <= Cj.length, Dj.length <= 5
    Ai, Bi, Cj, Dj consist of lower case English letters and digits.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:   100% */
/* Space Beats: 67.81% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::vector<double> calcEquation(std::vector<std::vector<std::string>>& equations,
                                     std::vector<double>& values,
                                     std::vector<std::vector<std::string>>& queries)
    {
        std::unordered_map<std::string, std::vector<std::pair<std::string, double>>> adj_list;

        for (int i = 0; i < equations.size(); i++)
        {
            adj_list[equations[i][0]].push_back( {equations[i][1], 1.0 * values[i]} );
            adj_list[equations[i][1]].push_back( {equations[i][0], 1.0 / values[i]} );
        }

        std::vector<double> result;
        for (auto& query : queries)
            result.push_back( BFS(adj_list, query[0], query[1]) );

        return result;
    }

private:
    double BFS(std::unordered_map<std::string, std::vector<std::pair<std::string, double>>>& adj_list,
               std::string& source,
               std::string& target)
    {
        if (adj_list.find(source) == adj_list.end() || adj_list.find(target) == adj_list.end())
            return -1.0;

        std::queue<std::pair<std::string, double>> queue;
        queue.push( {source, 1.0} );

        std::unordered_set<std::string> visited;
        visited.insert(source);

        while(!queue.empty())
        {
            std::string node   = queue.front().first;
            double      weight = queue.front().second;
            queue.pop();

            if (node == target)
                return weight;

            for (auto& entry : adj_list[node])
            {
                std::string neighbor = entry.first;
                double curr_weight   = entry.second;

                if (visited.find(neighbor) == visited.end())
                {
                    queue.push({neighbor, weight * curr_weight});
                    visited.insert(neighbor);
                }
            }
        }

        return -1.0;
    }
};
