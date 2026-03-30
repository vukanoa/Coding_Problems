/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    207) Course Schedule
    ===========================

    ============
    Description:
    ============

    There are a total of "numCourses" courses you have to take, labeled from 0
    to "numCourses - 1". You are given an array "prerequisites where
    prerequisites[i] = [ai, bi] indicates that you must take course bi first
    if you want to take course ai.

    For example, the pair [0, 1], indicates that to take course 0 you have to
    first take course 1.

    Return "true" if you can finish all courses. Otherwise, return "false".

    =============================================================================
    FUNCTION: bool canFinish(int numCourses, vector<vector<int>>& prerequisites);
    =============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  numCourses = 2, prerequisites = [[1, 0]]
    Output: true
    Explanation: There are a total of 2 courses to take. To take course 1 you
    should have finished course 0. So it is possible.

    --- Example 2 ---
    Input:  numCourses = 2, prerequisites = [[1, 0], [0, 1]]
    Output: false
    Explanation: There are a total of 2 courses to take. To take course 1 you
    should also have finished course 1. So it is impossible.

    *** Constraints ***
    1 <= numCourses <= 2000
    0 <= prerequisites.length <= 5000
    prerequisites[i].length = 2
    0 <= ai, bi < numCourses
    All the pairs prerequisites[i] are unique.

*/

#include <vector>
#include <queue>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Consider this example:
        [[0, 1], [1, 2], [2, 3]]

    We would interpret the example as:
    In order to take Course 0, you need to take Course 1.
    In order to take Course 1, you need to take Course 2.
    In order to take Course 2, you need to take Course 3.

    If we represent this as a Graph, it looks like this:

                   1 -> 2
                   ^     \
                  /       v
                 0         3

    So if we're able to take this Course 3 without any prerequisite, then
    we would be eligible to take Course 2.
    And if you take Course 2 then you would be eligible to take Course 1.
    And if you take Course 1 then you would be eligible to take Course 0.
    And if you take Course 0, you're done. It is possible to take all the
    courses.

    Now let's assume that there was another Course:
        [[0, 1], [1, 2], [2, 3], [3, 1]]

    Now the Graph would look like this:

                 --> 1 ----> 2
                 |   ^       |
                 |    \      |
                 |     \     |
                 0      3 <---

    Now there's no starting point. Let's say we start from Course 3:
    In order to take Course 3 you need to take Course 1.
    In order to take Course 1 you need to take Course 2.
    In order to take Course 2 you need to take Course 3.

    Therefore, there's a cycle and we return "false".

    This is a similar problem to Dead Lock Detection in a Single Resource
    Instance Distributed System.

    (If we have a cycle in the Graph then we will have Deadlock)
    Note: This has nothing to do with the concept of Deadlock considering
    multiple Threads)

    So we just need to find out if there's a cycle in our Directed Graph.

    This Problem can be solved using:
        Cycle Detection: Graph Coloring

    We will have a "visited" array with possible values:
    0: Unused
    1: Processed
    2: Processing

    Consider this Example:

                    3
                     \
                      -> 2
                          \
                           -> 0
                               \
                                -> 1

    So if we start from Node 2, then step by step, this will look like this:
    [0, 0, 0, 0]
    [2, 0, 0, 0]
    [2, 2, 0, 0]
    [2, 1, 0, 0]
    [1, 1, 0, 0]

    Now let's say we want to process Node 2:
    [1, 1, 0, 0]
    [1, 1, 2, 0]
    [1, 1, 1, 0]

    Now we're left only with Node 3:
    [1, 1, 1, 0]
    [1, 1, 1, 2]
    [1, 1, 1, 1] => Return "true"


*/

/* Time  Beats: 66.10% */
/* Space Beats: 90.15% */

/* Time  Complexity: O(V + E) */
/* Space Complexity: O(V + E) */
class Solution_DFS {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites)
    {
        vector<vector<int>> adj_list(numCourses);

        /* Create an Adjacency List(DAG) */
        for (const auto& edge : prerequisites)
        {
            const auto& a = edge[0]; // To complete course 'a'
            const auto& b = edge[1]; // you MUST FIRST complete 'b'

            adj_list[a].push_back(b);
        }

        vector<int> visited(numCourses, 0);
        for (int course_idx = 0; course_idx < numCourses; course_idx++)
        {
            if ( ! possible(course_idx, visited, adj_list))
                return false;
        }

        return true;
    }

private:
    bool possible(int course_idx, vector<int>& visited, vector<vector<int>>& adj_list)
    {
        if (visited[course_idx] == 2) // Cycle detected
            return false;

        if (visited[course_idx] == 1) // Already completed
            return true;

        visited[course_idx] = 2; // Mark as currently in PATH

        for (const int& neighbor : adj_list[course_idx])
        {
            if (visited[neighbor] == 1)
                continue;

            if ( ! possible(neighbor, visited, adj_list))
                return false;
        }

        visited[course_idx] = 1; // Mark as successfully completed

        return true;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Consider this Graph represented:

    Adjacency List:
    [[5, 3], [5, 1], [7, 3], [7, 0], [6, 3], [6, 4], [3, 0], [3, 2], [4, 1]]


                               2    0    1
                               |   /|   /|
                               |  / |  / |
                               | /  | /  |
                               v    |/   v
                            ---3    /    4
                            |  | \ /|    |
                            |  |  \ |    |
                            |  | / \|    |
                            |  v    v    v
                            |  5    7    6
                            |            ^
                            |____________|


    Valid Topological Orders for this Graph would be:
        1)
            2, 0, 1, 3, 4, 5, 7, 6 (Visual left to right, top to bottom)

        2)
            0, 1, 2, 3, 4, 5, 6, 7 (smallest-numbered available vertex first)

        3)
            2, 0, 1, 4, 3, 5, 7, 6 (fewest edges first)

        4)
            2, 0, 3, 7, 1, 5, 4, 6 (largest-numbered available vertex first)

        5)
            2, 0, 3, 1, 5, 7, 4, 6 (arbitrary)

    Topological Sort is also known as a "Kahn's Algorithm".

*/

/* Time  Beats: 99.18% */
/* Space Beats: 90.15% */

/* Time  Complexity: O(V + E) */
/* Space Complexity: O(V + E) */
class Solution_Topological {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites)
    {
        vector<vector<int>> adj_list(numCourses);
        vector<int> indegree(numCourses, 0);

        /* Populate an Adjacency List & Indegree vector */
        for (const auto& edge : prerequisites)
        {
            const auto& a = edge[0]; // To complete course 'a'
            const auto& b = edge[1]; // you MUST FIRST complete 'b'

            /*
               In Topological Sort algorithm, the Adjacency List MUST be in an
               UNINTUITIVE way(at least it's unintuitive to me)

               This Adjacency List(i.e. Graph) can be interpreted as:

                   MY(b) dependents: [..., a, ...]


               This is required because we need to decrement the "indegree" of
               dependents as soon as we finish the current course.

               That's why it needs to be in this UNINTUITIVE way.
            */
            adj_list[b].push_back(a);

            indegree[a]++; // Number of INCOMING edges
        }

        queue<int> queue;

        /* Populate Queue with courses that have NO prerequisites */
        for (int course = 0; course < numCourses; course++)
        {
            if (indegree[course] == 0)
                queue.push(course);
        }

        /* Multi-source BFS from the immediately completable courses */
        int finished_courses = 0;
        while ( ! queue.empty())
        {
            int course = queue.front();
            queue.pop();

            finished_courses++;

            for (int& neighbor : adj_list[course])
            {
                indegree[neighbor]--;

                if (indegree[neighbor] == 0)
                    queue.push(neighbor);
            }
        }

        return finished_courses == numCourses;
    }
};
