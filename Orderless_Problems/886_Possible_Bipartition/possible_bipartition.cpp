/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    886) Possible Bipartition
    ===========================

    ============
    Description:
    ============

    We want to split a group of n people (labeled from 1 to n) into two groups
    of any size. Each person may dislike some other people, and they should not
    go into the same group.

    Given the integer n and the array dislikes where dislikes[i] = [ai, bi]
    indicates that the person labeled ai does not like the person labeled bi,
    return true if it is possible to split everyone into two groups in this way

    =========================================================================
    FUNCTION: bool possibleBipartition(int n, vector<vector<int>>& dislikes);
    =========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 4, dislikes = [[1,2],[1,3],[2,4]]
    Output: true
    Explanation: The first group has [1,4], and the second group has [2,3].

    --- Example 2 ---
    Input: n = 3, dislikes = [[1,2],[1,3],[2,3]]
    Output: false
    Explanation: We need at least 3 groups to divide them. We cannot put them
                 in two groups.


    *** Constraints ***
    1 <= n <= 2000
    0 <= dislikes.length <= 10^4
    dislikes[i].length == 2
    1 <= ai < bi <= n
    All the pairs of dislikes are unique.

*/

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

/* Time  Beats: 46.99% */
/* Space Beats: 44.06% */

/* Time  Complexity: O(V + E) */
/* Space Complexity: O(V + E) */
class Solution {
private:
    enum COLOR_CONSTANT {
        GREEN = -1,  // -1
        NOT_COLORED, // 0
        BLUE         // 1
    };

public:
    bool possibleBipartition(int n, vector<vector<int>>& dislikes)
    {

        if (n == 1 || dislikes.size() == 0) // Edge case
        {
            return true;
        }

        // Each person maintains a list of people he/she dislikes
        unordered_map<int, vector<int>> adj_list;

        // Construct an Adjacency List, notice that we're create UNDIRECTED
        // graph becase if person1 doesn't like person2, then they need to be
        // separated anyway, therefore construct an UNDIRECTED edge
        for (const auto& entry : dislikes)
        {
            adj_list[entry[0]].push_back(entry[1]);
            adj_list[entry[1]].push_back(entry[0]);
        }

        // key:   person_id
        // value: color_of_person
        unordered_map<int, int> color_table; // {person_id, color_of_person}

        for (int person_id = 1; person_id <= n; person_id++)
        {
            if (color_table[person_id] == NOT_COLORED && !dfs_helper(person_id, BLUE, adj_list, color_table))
                return false;
        }

        return true;
    }

private:
    bool dfs_helper(int person_id, int color, unordered_map<int, vector<int>>& adj_list, unordered_map<int, int>& color_table)
    {
        color_table[person_id] = color;

        for (const int& other_person : adj_list[person_id]) // adj_list <==> "dislike table"
        {
            // If other_person is colored the same as person_id --> return false immediately
            if (color_table[other_person] == color)
                return false;

            // If other_person is NOT_COLORED, then try to color it with an opposite color of person_id and try recursively
            if (color_table[other_person] == NOT_COLORED && !dfs_helper(other_person, -color, adj_list, color_table))
                return false;
        }

        return true;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 25.35% */
/* Space Beats: 43.96% */

/* Time  Complexity: O(V + E) */
/* Space Complexity: O(V + E) */
class Solution_BFS {
private:
    enum COLOR_CONSTANT {
        GREEN = -1,  // -1
        NOT_COLORED, // 0
        BLUE         // 1
    };

public:
    bool possibleBipartition(int n, vector<vector<int>>& dislikes)
    {
        if (n == 1 || dislikes.size() == 0) // Edge case
            return true;

        // Each person maintains a list of people he/she dislikes
        unordered_map<int, vector<int>> adj_list;

        // Build an undirected graph
        for (const auto& entry : dislikes)
        {
            adj_list[entry[0]].push_back(entry[1]);
            adj_list[entry[1]].push_back(entry[0]);
        }

        // key:   person_id
        // value: color_of_person
        unordered_map<int, int> color_table; // {person_id, color_of_person}

        for (int person_id = 1; person_id <= n; person_id++)
        {
            // Skip if this person has already been colored
            if (color_table[person_id] != NOT_COLORED)
                continue;

            // Start BFS from this person with BLUE color
            queue<pair<int, int>> queue;
            queue.push({person_id, BLUE});

            color_table[person_id] = BLUE;

            while ( ! queue.empty())
            {
                int curr_person = queue.front().first;
                int curr_color  = queue.front().second;
                queue.pop();

                for (const int& other_person : adj_list[curr_person])
                {
                    if (color_table[other_person] == NOT_COLORED)
                    {
                        color_table[other_person] = -curr_color;
                        queue.push({other_person, color_table[other_person]});
                    }
                    else if (color_table[other_person] == curr_color)
                    {
                        return false;
                    }
                }
            }
        }

        return true;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 37.04% */
/* Space Beats: 53.44% */

/* Time  Complexity: O(V + E * alfa(V)) */ // Wheres the alfa(V) inverse
                                           // Ackermann function, nearly
                                           // constant in practice
/* Space Complexity: O(V + E)           */
class Solution_Union_and_Find {
private:
    vector<int> parent;
public:
    bool possibleBipartition(int n, vector<vector<int>>& dislikes)
    {
        parent.resize(n + 1);
        for (int i = 0; i <= n; i++) // Can be done using std::iota
            parent[i] = i;

        unordered_map<int, vector<int>> adj_list;
        for (const auto& entry : dislikes)
        {
            adj_list[entry[0]].push_back(entry[1]);
            adj_list[entry[1]].push_back(entry[0]);
        }

        for (int person_id = 1; person_id <= n; person_id++)
        {
            if (adj_list[person_id].empty())
                continue;

            for (const int& enemy : adj_list[person_id])
            {
                // If person and enemy are in same group, it's impossible
                if (find_parent(person_id) == find_parent(enemy))
                    return false;

                // Union all enemies into the same group
                union_groups(adj_list[person_id][0], enemy);
            }
        }

        return true;
    }

private:
    int find_parent(int person)
    {
        if (parent[person] != person)
            parent[person] = find_parent(parent[person]);

        return parent[person];
    }

    void union_groups(int person_one, int person_two)
    {
        int root_one = find_parent(person_one);
        int root_two = find_parent(person_two);

        parent[root_one] = root_two;
    }

};
