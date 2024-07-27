#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    ======================================
    2976) Minimum Cost To Convert String I
    ======================================

    ============
    Description:
    ============

    You are given two 0-indexed strings source and target, both of length n and
    consisting of lowercase English letters. You are also given two 0-indexed
    character arrays original and changed, and an integer array cost, where
    cost[i] represents the cost of changing the character original[i] to the
    character changed[i].

    You start with the string source. In one operation, you can pick a
    character x from the string and change it to the character y at a cost of z
    if there exists any index j such that cost[j] == z, original[j] == x, and
        changed[j] == y.

    Return the minimum cost to convert the string source to the string target
    using any number of operations. If it is impossible to convert source to
    target, return -1.

    Note that there may exist indices i, j such that original[j] == original[i]
    and changed[j] == changed[i].

    ================================================================================================================================
    FUNCTION: long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost);
    ================================================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: source = "abcd", target = "acbe", original = ["a","b","c","c","e","d"], changed = ["b","c","b","e","b","e"], cost = [2,5,5,1,2,20]
    Output: 28
    Explanation: To convert the string "abcd" to string "acbe":
    - Change value at index 1 from 'b' to 'c' at a cost of 5.
    - Change value at index 2 from 'c' to 'e' at a cost of 1.
    - Change value at index 2 from 'e' to 'b' at a cost of 2.
    - Change value at index 3 from 'd' to 'e' at a cost of 20.
    The total cost incurred is 5 + 1 + 2 + 20 = 28.
    It can be shown that this is the minimum possible cost.


    --- Example 2 ---
    Input: source = "aaaa", target = "bbbb", original = ["a","c"], changed = ["c","b"], cost = [1,2]
    Output: 12
    Explanation: To change the character 'a' to 'b' change the character 'a' to
                 'c' at a cost of 1, followed by changing the character 'c' to
                 'b' at a cost of 2, for a total cost of 1 + 2 = 3. To change
                 all occurrences of 'a' to 'b', a total cost of 3 * 4 = 12 is
                 incurred.


    --- Example 3 ---
    Input: source = "abcd", target = "abce", original = ["a"], changed = ["e"], cost = [10000]
    Output: -1
    Explanation: It is impossible to convert source to target because the value
                 at index 3 cannot be changed from 'd' to 'e'.


    *** Constraints ***
    1 <= source.length == target.length <= 10^5
    source, target consist of lowercase English letters.
    1 <= cost.length == original.length == changed.length <= 2000
    original[i], changed[i] are lowercase English letters.
    1 <= cost[i] <= 10^6
    original[i] != changed[i]

*/

using namespace std;

/* Works for given Examples, but ultimately results in TLE */
class Solution {
public:
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost)
    {
        const int N = source.length();
        int result = 0;

        /* Create Adjacency List */
        unordered_map<char, vector<pair<char, int>> > adj_list;
        for (int i = 0; i < original.size(); i++)
            adj_list[original[i]].push_back( {changed[i], cost[i]} );

        for (int i = 0; i < N; i++)
        {
            if (source[i] != target[i])
            {
                int shortest_path = INT_MAX;
                unordered_set<int> uset_visited;

                for (const auto& entry : adj_list[source[i]])
                {
                    int next   = entry.first;
                    int weight = entry.second;

                    uset_visited.insert(source[i]); // Insert
                    uset_visited.insert(next);      // Insert

                    pair<bool, int> curr_path = find_shortest_path(adj_list, next, target[i], weight, uset_visited);

                    uset_visited.erase(next);       // Erase
                    uset_visited.erase(source[i]);  // Erase

                    if (curr_path.first == true)
                        shortest_path = min(shortest_path, curr_path.second);
                }

                if (INT_MAX == shortest_path)
                    return -1; // We aren't able to "fix" this discrepancy

                result += shortest_path;
            }
        }

        return result == 0 ? -1 : result;
    }

private:
    pair<bool, int> find_shortest_path(unordered_map<char, vector<pair<char, int>> >& adj_list,
                                       int next,
                                       int goal,
                                       int path,
                                       unordered_set<int>& uset_visited)
    {
        if (next == goal)
            return {true, path};

        pair<bool, int> result = {false, INT_MAX};

        for (const auto& entry : adj_list[next])
        {
            int node   = entry.first;
            int weight = entry.second;

            if (uset_visited.find(node) != uset_visited.end()) // Exists
                continue;

            uset_visited.insert(node); // Insert
            pair<bool, int> curr_result = find_shortest_path(adj_list, node, goal, path+weight, uset_visited);
            uset_visited.erase(node);  // Erase

            if (curr_result.first == true && curr_result.second < result.second)
                result = curr_result;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

    We don't have to do it for N characters, we can do it for all 26 lowercase
    character and then each time we have the same character, we can use the
    precalculated one.

    That's where the above TLE comes down to this.

*/

/* Time  Beats: 13.53% */
/* Space Beats: 19.14% */

/* Time  Complexity: O(26 * M + N) ==> O(M + N) */
/* Space Complexity: O(M)                       */
class Solution {
public:
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost)
    {
        const int N = source.length();

        // Create Adjacency List
        unordered_map<char, vector<pair<char, int>>> adj_list;
        for (int i = 0; i < original.size(); i++)
            adj_list[original[i]].push_back({changed[i], cost[i]});

        unordered_map<char, unordered_map<char, int>> umap_min_cost_maps;

        // Iterate over the set of unique characters in the source string
        unordered_set<char> unique_chars(source.begin(), source.end());
        for (const char& chr : unique_chars)
            umap_min_cost_maps[chr] = dijkstra(adj_list, chr);

        long long result = 0;
        for (int i = 0; i < N; i++)
        {
            char src = source[i];
            char dst = target[i];

            // If we cannot convert src into dst in any way, then return -1
            if (umap_min_cost_maps[src].find(dst) == umap_min_cost_maps[src].end())
                return -1;

            result += umap_min_cost_maps[src][dst];
        }

        return result;
    }

private:
    unordered_map<char, int> dijkstra(unordered_map<char, vector<pair<char, int>>>& adj_list, char src)
    {
        priority_queue<pair<int, char>, vector<pair<int, char>>, greater<pair<int, char>>> min_heap;
        unordered_map<char, int> min_cost_map;
        unordered_set<char> visited;

        // Initialize the priority queue with the source node
        min_heap.push({0, src});

        while ( ! min_heap.empty())
        {
            int cost  = min_heap.top().first;
            char node = min_heap.top().second;
            min_heap.pop();

            if (visited.find(node) != visited.end())
                continue;

            visited.insert(node);
            min_cost_map[node] = cost;

            for (auto& entry : adj_list[node])
            {
                char nei      = entry.first;
                int  nei_cost = entry.second;

                if (visited.find(nei) == visited.end())
                    min_heap.push({cost + nei_cost, nei});
            }
        }

        return min_cost_map;
    }
};
