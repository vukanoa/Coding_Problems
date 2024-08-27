#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ===================================
    1514) Path with Maximum Probability
    ===================================

    ============
    Description:
    ============

    You are given an undirected weighted graph of n nodes (0-indexed),
    represented by an edge list where edges[i] = [a, b] is an undirected edge
    connecting the nodes a and b with a probability of success of traversing
    that edge succProb[i].

    Given two nodes start and end, find the path with the maximum probability
    of success to go from start to end and return its success probability.

    If there is no path from start to end, return 0. Your answer will be
    accepted if it differs from the correct answer by at most 1e-5.

    ===========================================================================================================================
    FUNCTION: double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node);
    ===========================================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.2], start = 0, end = 2
    Output: 0.25000
    Explanation: There are two paths from start to end, one having a
                 probability of success = 0.2 and the other has 0.5 * 0.5 =
                 0.25.


    --- Example 2 ---
    Input: n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.3], start = 0, end = 2
    Output: 0.30000


    --- Example 3 ---
    Input: n = 3, edges = [[0,1]], succProb = [0.5], start = 0, end = 2
    Output: 0.00000
    Explanation: There is no path between 0 and 2


    *** Constraints ***
    2 <= n <= 10^4
    0 <= start, end < n
    start != end
    0 <= a, b < n
    a != b
    0 <= succProb.length == edges.length <= 2*10^4
    0 <= succProb[i] <= 1
    There is at most one edge between every two nodes.

*/

/*
    ------------
    --- IDEA ---
    ------------

    This is the first thing that comes to mind to anyone with a slight
    experience in Graph Problems.

    If works, but it exceeds Time Limit, i.e. it's a TLE.

    It is here for didactic purposes.

*/

/* TLE(Brut Force) */

/* Time  Complexity: O(E^V) */
/* Space Complexity: O(V) */
class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node)
    {
        if (edges.empty())
            return 0;

        unordered_map<int, vector<pair<int,double>>> adj_list;

        for (int i = 0; i < edges.size(); i++)
        {
            adj_list[edges[i][0]].push_back({edges[i][1], succProb[i]});
            adj_list[edges[i][1]].push_back({edges[i][0], succProb[i]});
        }



        unordered_set<int> visited;
        double biggest_chance = 0;

        dfs(adj_list, start_node, end_node, visited, 1.0, biggest_chance);

        return biggest_chance;
    }

private:
    void dfs(unordered_map<int, vector<pair<int,double>>>& adj_list,
            int curr_node,
            int end_node,
            unordered_set<int>& visited,
            double  curr_chance,
            double& biggest_chance)
    {
        if (curr_node == end_node)
        {
            biggest_chance = max(biggest_chance, curr_chance);
            return;
        }
        else if (visited.find(curr_node) != visited.end()) // If present in the Set
            return;

        visited.insert(curr_node);

        for (auto& neighbor : adj_list[curr_node])
        {
            int    neighbor_node = neighbor.first;
            double neighbor_prob = neighbor.second;

            dfs(adj_list, neighbor_node, end_node, visited, curr_chance * neighbor_prob, biggest_chance);
        }

        visited.erase(curr_node);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/


/* Time  Beats: 65.76% */
/* Space Beats: 10.22% */

/* Time  Complexity: O(E * logV) */
/* Space Complexity: O(V) */
class Solution_Dijkstra {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        if (edges.empty())
            return 0;

        unordered_map<int, vector<pair<int,double>>> adj_list;

        // Create Adjacency list.
        for (int i = 0; i < edges.size(); i++)
        {
            adj_list[edges[i][0]].push_back({edges[i][1], succProb[i]});
            adj_list[edges[i][1]].push_back({edges[i][0], succProb[i]});
        }

        priority_queue<pair<double,int>, vector<pair<double,int>>> max_heap;
        unordered_set<int> visited;

        max_heap.push({1.0, start_node});

        while ( ! max_heap.empty())
        {
            auto entry = max_heap.top();
            max_heap.pop();

            double prob = entry.first;
            int    curr = entry.second;

            visited.insert(curr);

            if (curr == end_node)
                return prob;

            for (auto& neighbor : adj_list[curr])
            {
                int    nei_curr = neighbor.first;
                double nei_prob = neighbor.second;

                if (visited.find(nei_curr) == visited.end()) // Not Found in Set
                    max_heap.push({prob * nei_prob, nei_curr});
            }
        }

        return 0;
    }
};
