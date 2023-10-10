#include <iostream>
#include <vector>

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

    we bulld a Hash Map:

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

    We just do a basic DFS where we memorize the path in set called "cycle" and
    if we find the cycle, immately return false and return an empty vector.

    Upon fully finishing a certain course, i.e. doing a successfull DFS on it,
    mark it as visited in set "visit" so that we don't have to check it
    anymore.

    That's it.

*/

using namespace std;

/* Time  Beats: 98.67% */
/* Space Beats: 47.32% */

/*
    Time  Complexity: O(E + V)
    where 'E' are Edges, and V are Vecrtices, i.e. Nodes.

    'E' are prerequisites and 'V' are numCourses.
*/
/* Space Complexity: O(V) */
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites)
    {
        std::vector<std::vector<int>> map(numCourses, std::vector<int>());
        std::vector<bool>            cycle (numCourses, 0);
        std::vector<bool>            visit (numCourses, 0);

        std::vector<int> result;

        // Fill the Hash map
        for (int i = 0; i < prerequisites.size(); i++)
            map[prerequisites[i][0]].push_back(prerequisites[i][1]);

        for (int i = 0; i < numCourses; i++)
        {
            if (!dfs(map, cycle, visit, result, i))
                return {};
        }

        return result;
    }

private:
    bool dfs(vector<vector<int>>& map, vector<bool>& cycle, vector<bool>& visit, vector<int>& result, int course)
    {
        if (cycle[course])
            return false;

        if (visit[course])
            return true;

        cycle[course] = true;
        for (const auto& c : map[course])
        {
            if (!dfs(map, cycle, visit, result, c))
                return false;
        }
        cycle[course] = false;
        visit[course] = true;

        result.push_back(course);

        return true;
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
    std::vector<int> findOrder(int numCourses, std::vector<std::vector<int>>& prerequisites)
    {
        std::vector<int> results;

        std::unordered_set<int> done;
        std::vector<bool> path(numCourses, false);
        std::vector<std::vector<int>> adj_list(numCourses);

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
    bool topological_sort(std::vector<std::vector<int>>& adj_list,
                     int curr,
                     std::vector<bool>& path,
                     std::unordered_set<int>& done,
                     std::vector<int>& results)
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
