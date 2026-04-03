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

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:   100% */
/* Space Beats: 72.56% */

/* Time  Complexity: O(N * W  +  M * N * @) */
/* Space Complexity: O(N * W)               */
class Solution_BFS {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries)
    {
        const int N = equations.size();
        const int M = queries.size();

        unordered_map<string, unordered_map<string, double>> adj_list;

        // O(N * W), where 'W' is the length of the longest string in equations
        for (int i = 0; i < N; i++)
        {
            const string& a = equations[i][0];
            const string& b = equations[i][1];

            adj_list[a].insert( {b, values[i]      } );
            adj_list[b].insert( {a, 1.0 / values[i]} ); // Reverse
        }


        vector<double> result(M, -1.0);
        for (int j = 0; j < M; j++)
            result[j] = BFS(queries[j][0], queries[j][1], adj_list);

        return result;
    }

private:
    double BFS(string& source, string& target, unordered_map<string, unordered_map<string, double>>& adj_list)
    {
        if (adj_list.find(source) == adj_list.end() || adj_list.find(target) == adj_list.end())
            return -1.0;

        queue<pair<string, double>> queue;
        queue.push( {source, 1.0} );

        unordered_set<string> visited;
        visited.insert(source);

        while ( ! queue.empty())
        {
            auto [curr_str, curr_value] = queue.front();
            queue.pop();

            if (curr_str == target)
                return curr_value;

            for (auto& [neighbor_str, neighbor_value] : adj_list[curr_str])
            {
                if (visited.count(neighbor_str))
                    continue;

                queue.push( {neighbor_str, curr_value * neighbor_value} );
                visited.insert(neighbor_str);
            }
        }

        return -1.0;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same idea, just using BFS.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  72.56% */

/* Time  Complexity: O(N * W  +  M * N * W) */
/* Space Complexity: O(N * W)               */
class Solution_DFS {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries)
    {
        const int N = equations.size();
        const int M = queries.size();

        unordered_map<string, unordered_map<string, double>> adj_list;

        // O(N * W), where 'W' is the length of the longest string in equations
        for (int i = 0; i < N; i++)
        {
            const string& a = equations[i][0];
            const string& b = equations[i][1];

            adj_list[a].insert( {b, values[i]      } );
            adj_list[b].insert( {a, 1.0 / values[i]} ); // Reverse
        }

        // O(M * N * W)
        vector<double> results(M, -1.0);
        for (int j = 0; j < M; j++)
        {
            unordered_set<string> path;
            results[j] = dfs(1.0, queries[j][0], queries[j][1], path, adj_list);
        }

        return results;
    }

private:
    double dfs(double curr_value, string curr_str, string& target_str, unordered_set<string>& path, unordered_map<string, unordered_map<string, double>>& adj_list)
    {
        if (adj_list.find(curr_str) == adj_list.end() || adj_list[curr_str].empty())
            return -1.0;

        if (curr_str == target_str)
            return 1.0;

        if (adj_list[curr_str].find(target_str) != adj_list[curr_str].end())
            return curr_value * adj_list[curr_str][target_str];

        path.insert(curr_str);

        // O(N * W), where 'W' is the length of the longest string in equations
        double result = -1.0;
        for (const auto& neighbor_entry : adj_list[curr_str])
        {
            const auto& neighbor_str   = neighbor_entry.first;
            const auto& neighbor_value = neighbor_entry.second;

            if (path.count(neighbor_str))
                continue;

            result = dfs(curr_value * neighbor_value, neighbor_str, target_str, path, adj_list); 
            if (result != -1)
                break;
        }

        path.erase(curr_str);

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Very unusual DSU, be careful when implementing a Solution like this.

*/


/* Time  Beats: 100.00% */
/* Space Beats:  82.80% */

/* Time  Complexity: O(N * M * alpha(N)) */
/* Space Complexity: O(N + M)            */
class DSU {
public:
    unordered_map<string, string> parent;
    unordered_map<string, int>    rank;
    unordered_map<string, double> weight; // node --> parent ratio

    void initialize_node_if_missing(const string& node)
    {
        if (parent.count(node))
            return;

        parent[node] = node;
        rank[node]   = 1;
        weight[node] = 1.0;
    }

    string find_root_node(const string& node)
    {
        if (node != parent[node])
        {
            string original_parent = parent[node];
            parent[node] = find_root_node(parent[node]);
            weight[node] *= weight[original_parent];
        }

        return parent[node];
    }

    bool union_components(const string& node_1, const string& node_2, double value)
    {
        initialize_node_if_missing(node_1);
        initialize_node_if_missing(node_2);

        string root_1 = find_root_node(node_1);
        string root_2 = find_root_node(node_2);

        if (root_1 == root_2)
            return false;

        parent[root_2] = root_1;
        weight[root_2] = value * weight[node_1] / weight[node_2];

        // rank still preserved but not actually used
        rank[root_1] += rank[root_2];

        return true;
    }

    double get_ratio(const string& node_1, const string& node_2)
    {
        if ( ! parent.count(node_1) ||  ! parent.count(node_2))
            return -1.0;

        string root_1 = find_root_node(node_1);
        string root_2 = find_root_node(node_2);

        if (root_1 != root_2)
            return -1.0;

        return weight[node_2] / weight[node_1];
    }
};

class Solution_Unusual_DSU {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries)
    {
        const int N = equations.size();
        DSU dsu;

        for (int i = 0; i < N; i++)
        {
            string& a = equations[i][0];
            string& b = equations[i][1];

            dsu.union_components(a, b, values[i]);
        }

        vector<double> result;
        for (const auto& query : queries)
        {
            const string& a = query[0];
            const string& b = query[1];

            result.push_back(dsu.get_ratio(a, b));
        }

        return result;
    }
};
