/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    210) Course Schedule II
    ===========================

    ============
    Description:
    ============

    There are a total of numCourses courses you have to take, labeled from 0
    to numCourses - 1. You are given an array prerequisites where
    prerequisites[i] = [ai, bi] indicates that you must take course bi first
    if you want to take course ai.

    For example, the pair [0, 1], indicates that to take course 0 you have to
    first take course 1.

    Return the ordering of courses you should take to finish all courses. If
    there are many valid answers, return any of them. If it is impossible to
    finish all courses, return an empty array.

    ====================================================================================
    FUNCTION: vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites);
    ====================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: numCourses = 2, prerequisites = [[1,0]]
    Output: [0,1]
    Explanation: There are a total of 2 courses to take. To take course 1 you
    should have finished course 0. So the correct course order is [0,1].

    --- Example 2 ---
    Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
    Output: [0,2,1,3]
    Explanation: There are a total of 4 courses to take. To take course 3 you
    should have finished both courses 1 and 2. Both courses 1 and 2 should be
    taken after you finished course 0.
    So one correct course order is [0,1,2,3]. Another correct ordering is
    [0,2,1,3].

    --- Example 3 ---
    Input: numCourses = 1, prerequisites = []
    Output: [0]

    *** Constraints ***
    1 <= numCourses <= 2000
    0 <= prerequisites.length <= numCourses * (numCourses - 1)
    prerequisites[i].length == 2
    0 <= ai, bi < numCourses
    ai != bi
    All the pairs [ai, bi] are distinct.

*/

#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Basic Topological Sort using DFS.

    Consider this Example:
    (Outer Edges represent Dependencies. i.e 1 depends on 3)


                5 ----     ----> 1 -----> 3
                      \   /               |
                       v /                |
                4 ---> 0 ---------> 2 <----


    we bulld an Adjacency List:

                  Course : [list of courses that MUST be done BEFORE this one]
                  Course : Dependencies
                +--------+--------------+
                |   0    |   1,2        |
                +--------+--------------+
                |   1    |   3          |
                +--------+--------------+
                |   2    |              |
                +--------+--------------+
                |   3    |   2          |
                +--------+--------------+
                |   4    |   0          |
                +--------+--------------+
                |   5    |   0          |
                +--------+--------------+

    Do a simple DFS. If we every stumble on some cycle, mark it and return an
    empty list.

    Otherwise, push all of the vertices(i.e. courses) we've successfully
    completed.

*/

/* Time  Beats: 76.50% */
/* Space Beats: 52.03% */

/* Time  Complexity: O(V + E) */
/* Space Complexity: O(V + E) */
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites)
    {
        const int V = numCourses;
        const int E = prerequisites.size();

        /* "I 'src' depend on 'dst' course" */
        vector<vector<int>> adj_list(V); // Space: O(V + E)

        vector<bool> completed(V, false); // Space: O(V)
        vector<bool> path(V, false);      // Space: O(V)

        vector<int> result;
        result.reserve(V);

        /* Create an Adjacency List */
        for (const auto& edge : prerequisites)
        {
            const int& src = edge[0];
            const int& dst = edge[1]; // This one needs to be completed FIRST

            adj_list[src].push_back(dst);
        }

        /* DFS with cycle detection */
        for (int course = 0; course < V; course++)
        {
            if ( ! completed[course])
            {
                if (dfs_is_cyclic(course, completed, path, result, adj_list))
                    return {};
            }
        }

        return result;
    }

private:
    bool dfs_is_cyclic(int course, vector<bool>& completed, vector<bool>& path, vector<int>& result, vector<vector<int>>& adj_list)
    {
        if (path[course]) // Present in the current path---Cycle!
            return true;

        if (completed[course])
            return false;

        path[course] = true;  // Mark
        for (const int& neighbor : adj_list[course])
        {
            if (dfs_is_cyclic(neighbor, completed, path, result, adj_list))
                return true;
        }
        path[course] = false; // Unmark

        completed[course] = true;
        result.push_back(course);

        return false;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    It's the equivalent IDEA, however this one is much more reminiscent of the
    original problem "Course Schedule".

    For some reason, I prefer implementing it this way.

*/

/* Time  Beats: 86.19% */
/* Space Beats: 18.45% */

/*
    Time  Complexity: O(E + V)
    where 'E' are Edges, and V are Vecrtices, i.e. Nodes.

    'E' are prerequisites and 'V' are numCourses.
*/
/* Space Complexity: O(V) */
class Solution_Topological {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites)
    {
        vector<int> results;

        unordered_set<int> done;
        vector<bool> path(numCourses, false);
        vector<vector<int>> adj_list(numCourses);

        // Make an Adjacency List
        for (auto& edge : prerequisites)
            adj_list[edge[0]].push_back(edge[1]);

        for (int i = 0; i < numCourses; i++)
        {
            if (!topological_sort(adj_list, i, path, done, results))
                return {};
        }

        if (done.size() < numCourses)
            return {};

        return results;
    }

private:
    bool topological_sort(vector<vector<int>>& adj_list,
                     int curr,
                     vector<bool>& path,
                     unordered_set<int>& done,
                     vector<int>& results)
    {
        if (done.find(curr) != done.end()) // Already finished
            return true;

        path[curr] = true;
        for (int i = 0; i < adj_list[curr].size(); i++)
        {
            if (path[adj_list[curr][i]] == true) // Cycle detected
                return false;

            if (!topological_sort(adj_list, adj_list[curr][i], path, done, results))
                return false;
        }
        path[curr] = false;

        done.insert(curr);
        results.push_back(curr);

        return true;
    }
};
