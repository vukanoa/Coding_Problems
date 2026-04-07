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

#include <queue>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

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
class Solution_Cycle_Detection {
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

    The IDEA is reversed here. Instead of having an Adjacency List where each
    course(i.e. node) points to all the courses it is dependent on, here we do
    the exact opposite---We create an Adjacency List where each dependency
    points to the courses that depend on it.

    This is done so that we can immediately tell which courses can be
    immediately completed.

    Such courses have an initial indegree(i.e. the number of nodes that are
    incoming into it) equal to 0.

    Iniially we push all of those nodes in a Queue and then we simply perform
    a Multi-Source BFS Solution.

*/

/* Time  Beats: 56.11% */
/* Space Beats: 57.18% */

/* Time  Complexity: O(V + E) */
/* Space Complexity: O(V + E) */
class Solution_Topological_Sort_BFS { // Standard way of writing Topological
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites)
    {
        const int V = numCourses;
        const int E = prerequisites.size();

        vector<vector<int>> adj_list(numCourses); // Space: O(V + E)
        vector<int> indegree(numCourses);         // Space: O(V)

        vector<int> result;
        result.reserve(numCourses); // This prevent potential reallocations

        /* Create an Adjacency List and populate indegree */
        // Time: O(E) (entire block)
        for (const auto& edge : prerequisites)
        {
            const int& dst = edge[0];
            const int& src = edge[1];

            adj_list[src].push_back(dst);
            indegree[dst]++;
        }

        /* Mark already completed courses, i.e. ones with NO prerequisites */
        vector<bool> completed(numCourses, false); // Space: O(V)
        queue<int> queue;                          // Space: O(V)

        // Time: O(V) (entire block)
        for (int course = 0; course < numCourses; course++)
        {
            if (indegree[course] == 0)
            {
                queue.push(course);
                completed[course] = true;

                result.push_back(course);
            }
        }

        /* Multi-source BFS */
        // Time: O(V + E) (entire block)
        while ( ! queue.empty())
        {
            int course = queue.front();
            queue.pop();

            for (const int& neighbor : adj_list[course])
            {
                if (completed[neighbor])
                    continue;

                indegree[neighbor]--;

                if (indegree[neighbor] == 0)
                {
                    queue.push(neighbor);
                    completed[neighbor] = true;

                    result.push_back(neighbor);
                }
            }
        }

        if (result.size() == numCourses) 
            return result;

        return {};
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Basic Topological Sort using DFS, however it's important to note that
    writing a "Topological Sort" is an UNUSUAUL way.

    Much more natural for Topological Sort is to use a Multi-Source BFS.
    That solution, i.e. "Multi-Source BFS" is the 2nd one in this file(above).

*/

/* Time  Beats: 100.00% */
/* Space Beats:  52.03% */

/* Time  Complexity: O(V + E) */
/* Space Complexity: O(V + E) */
class Solution_Topological_Sort_DFS { // Unusual way of writing Topological
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites)
    {
        const int V = numCourses;
        const int E = prerequisites.size();

        vector<vector<int>> adj_list(V);   // Space: O(V + E)
        vector<int> indegree(V, 0);        // Space: O(V)
        vector<bool> completed(V, false);  // Space: O(V)

        vector<int> result;
        result.reserve(V);

        /* Create an Adjacency List and populate indegree */
        for (const auto& edge : prerequisites)
        {
            const int& dst = edge[0];
            const int& src = edge[1];

            adj_list[src].push_back(dst);
            indegree[dst]++;
        }

        /* Start DFS from all zero-indegree nodes */
        for (int course = 0; course < numCourses; course++)
        {
            if (indegree[course] == 0 && ! completed[course])
                dfs(course, adj_list, indegree, completed, result);
        }

        if (result.size() != numCourses)
            return {};

        return result;
    }

private:
    void dfs(int course, vector<vector<int>>& adj_list, vector<int>& indegree, vector<bool>& completed, vector<int>& result)
    {
        result.push_back(course);
        completed[course] = true;

        for (const int& neighbor : adj_list[course])
        {
            indegree[neighbor]--;

            if (indegree[neighbor] == 0 && !completed[neighbor])
                dfs(neighbor, adj_list, indegree, completed, result);
        }
    }
};
