/*
    ============
    === HARD ===
    ============

    ===========================
    332) Reconstruct Itinerary
    ===========================

    ============
    Description:
    ============

    You are given a list of airline tickets where tickets[i] = [fromi, toi]
    represent the departure and the arrival airports of one flight. Reconstruct
    the itinerary in order and return it.

    All of the tickets belong to a man who departs from "JFK", thus, the
    itinerary must begin with "JFK". If there are multiple valid itineraries,
    you should return the itinerary that has the smallest lexical order when
    read as a single string.

        For example, the itinerary ["JFK", "LGA"] has a smaller lexical order
        than ["JFK", "LGB"].

    You may assume all tickets form at least one valid itinerary. You must use
    all the tickets once and only once.

    ========================================================================
    FUNCTION: vector<string> findItinerary(vector<vector<string>>& tickets);
    ========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: tickets = [["MUC","LHR"],["JFK","MUC"],["SFO","SJC"],["LHR","SFO"]]
    Output: ["JFK","MUC","LHR","SFO","SJC"]

    --- Example 2 ---
    Input: tickets =
    [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
    Output: ["JFK","ATL","JFK","SFO","ATL","SFO"]
    Explanation: Another possible reconstruction is
    ["JFK","SFO","ATL","JFK","ATL","SFO"] but it is larger in lexical order.


    *** Constraints ***
    1 <= tickets.length <= 300
    tickets[i].length == 2
    fromi.length == 3
    toi.length == 3
    fromi and toi consist of uppercase English letters.
    fromi != toi

*/

#include <functional>
#include <queue>
#include <unordered_set>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 90.01% */
/* Space Beats:  5.50% */

/* Time  Complexity: O(E * logD) */ // Where D is max-out degree
/* Space Complexity: O(E)        */
class Solution_Min_Heap {
private:
    unordered_map<string, priority_queue<string, vector<string>, greater<string>>> adj_list;
public:
    vector<string> findItinerary(vector<vector<string>>& tickets)
    {
        const int V = tickets.size();

        /* If self-loops are ALLOWED, then E = V*V, otherwise E = V * (V-1) */
        vector<string> result;
        result.reserve(V * V);

        unordered_map<string, priority_queue<string, vector<string>, greater<string>>> adj_list;
        for (const auto& ticket : tickets)
        {
            const string& from = ticket[0];
            const string& to   = ticket[1];

            adj_list[from].push(to);
        }

        /* Postorder DFS */
        postorder_dfs("JFK", result, adj_list);

        /* Reverse the result since we've done a POSTORDER dfs */
        reverse(result.begin(), result.end());

        return result;
    }

private:
    void postorder_dfs(string node,
                       vector<string>& result,
                       unordered_map<string, priority_queue<string, vector<string>, greater<string>>>& adj_list)
    {
        while ( ! adj_list[node].empty())
        {
            string neighbor = adj_list[node].top();
            adj_list[node].pop();

            postorder_dfs(neighbor, result, adj_list);
        }

        /* Postorder DFS */
        result.push_back(node);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 79.29% */
/* Space Beats:  5.04% */

/* Time  Complexity: O(E * logE   +   V + E) ---> O(E * logE) */
/* Space Complexity: O(E)                                     */
class Solution_Hierholzer_Algorithm {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets)
    {
        const int E = tickets.size();

        /* Sort REVERSE-lexicographically */
        sort(tickets.rbegin(), tickets.rend()); // O(E * logE)

        // Worst case for a simple directed graph without self-loops:
        // E <= V * (V-1)
        //
        // With self-loops ALLOWED:
        // E <= V * V
        vector<string> result;
        result.reserve(E + 1);

        unordered_map<string, vector<string>> adj_list;
        unordered_map<string, int> indegree;
        unordered_map<string, int> outdegree;

        unordered_set<string> cities;

        // O(E) (entire block)
        for (const auto& ticket : tickets)
        {
            const string& from = ticket[0];
            const string& to   = ticket[1];

            cities.insert(from); // O(1)
            cities.insert(to);   // O(1)

            adj_list[from].push_back(to); // O(1) Amortized

            outdegree[from]++;
            indegree[to]++;
        }

        /*
           In this problem I check if "Eulerian Path" exist which is logically
           correct, however it it completely necessary.

           Why?

           Because the problem GUARANTEES a VALID itinerary(i.e. route/journey)
           from "JFK", therefore this whole block below can be removed without
           affecting correctness.

           However in general "Hierholzer's Algorithm", this is a NECESSARY
           check-up.

           So I'll leave it here for didactic purposes.



           ***************************************
           *** For an Eulearian Path to exist: ***
           ***************************************

           AT MOST ONE node can have: (starting node)

                outdegree[city] - indegree[city] = 1

           and AT MOST ONE node can have: (ending node)

                indegree[city] - outdegree[city] = 1

           and ALL the other nodes MUST have:

                indegree[city] == outdegree[city]
        */
        const int CITIES = cities.size();
        int valid_starting_nodes = 0;
        int valid_ending_nodes   = 0;
        int equal = 0;

        // O(V)
        for (const auto& city : cities)
        {
            if (outdegree[city] - indegree[city] == 1)
                valid_starting_nodes++;

            if (indegree[city] - outdegree[city] == 1)
                valid_ending_nodes++;

            if (indegree[city] == outdegree[city])
                equal++;
        }

        if (valid_starting_nodes > 1 || valid_ending_nodes > 1)
            return {};

        if (valid_starting_nodes + valid_ending_nodes + equal < CITIES)
            return {};



        /* Postorder DFS */
        // O(E)
        postorder_dfs("JFK", outdegree, result, adj_list);

        /* Reverse the result since we've done a POSTORDER dfs */
        // O(E + 1) --> O(E)
        reverse(result.begin(), result.end());

        return result;
    }

private:
    // O(E) (entire block), in general it's O(V + E)
    //                      but for Hierholzer it's O(E)
    void postorder_dfs(string node,
                       unordered_map<string, int>& outdegree,
                       vector<string>& result,
                       unordered_map<string, vector<string>>& adj_list)
    {
        while (outdegree[node] > 0)
        {
            string neighbor = adj_list[node][outdegree[node] - 1];

            outdegree[node]--;

            postorder_dfs(neighbor, outdegree, result, adj_list);
        }

        /* Postorder push */
        result.push_back(node);
    }
};
