#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

/*
    ============
    === EASY ===
    ============

    ===========================
    1436) Destination City
    ===========================

    ============
    Description:
    ============

    You are given the array paths, where paths[i] = [cityAi, cityBi] means
    there exists a direct path going from cityAi to cityBi. Return the
    destination city, that is, the city without any path outgoing to another
    city.

    It is guaranteed that the graph of paths forms a line without any loop,
    therefore, there will be exactly one destination city.

    =========================================================
    FUNCTION: string destCity(vector<vector<string>>& paths);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: paths = [["London","New York"],["New York","Lima"],["Lima","Sao Paulo"]]
    Output: "Sao Paulo"
    Explanation: Starting at "London" city you will reach "Sao Paulo" city
    which is the destination city. Your trip consist of: "London" -> "New York"
    -> "Lima" -> "Sao Paulo".


    --- Example 2 ---
    Input: paths = [["B","C"],["D","B"],["C","A"]]
    Output: "A"
    Explanation: All possible trips are:
    "D" -> "B" -> "C" -> "A".
    "B" -> "C" -> "A".
    "C" -> "A".
    "A".
    Clearly the destination city is "A".


    --- Example 3 ---
    Input: paths = [["A","Z"]]
    Output: "Z"


    *** Constraints ***
    1 <= paths.length <= 100
    paths[i].length == 2
    1 <= cityAi.length, cityBi.length <= 10
    cityAi != cityBi
    All strings consist of lowercase and uppercase English letters and the space character.

*/

using namespace std;

/* Time  Beats: 49.72% */
/* Space Beats: 28.48% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    string destCity(vector<vector<string>>& paths)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        unordered_map<string, int> umap;

        for (vector<string>& one_path : paths)
        {
            string start = one_path[0];
            string  end  = one_path[1];

            umap[start]++;
            umap.insert( {end, 0} );
        }

        for (auto& entry : umap)
        {
            if (entry.second == 0)
                return entry.first;
        }

        return ""; // Won't get to here ever
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Another way of implementing it.

*/

/* Time  Beats: 75.56% */
/* Space Beats: 44.89% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    string destCity(vector<vector<string>>& paths)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        unordered_set<string> uset;

        for (auto& p : paths)
            uset.insert(p[0]);

        for (auto& p : paths)
        {
            if (uset.find(p[1]) == uset.end()) // Doesn't exist in the Set
                return p[1];
        }

        return ""; // Won't get to here ever
    }
};
