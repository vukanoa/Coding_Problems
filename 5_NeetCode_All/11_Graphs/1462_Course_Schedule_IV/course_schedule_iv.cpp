/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    1462) Course Schedule IV
    ===========================

    ============
    Description:
    ============

    There are a total of numCourses courses you have to take, labeled from 0 to
    numCourses - 1. You are given an array prerequisites where prerequisites[i]
    = [ai, bi] indicates that you must take course ai first if you want to take
    course bi.

        For example, the pair [0, 1] indicates that you have to take course 0
        before you can take course 1.

    Prerequisites can also be indirect. If course a is a prerequisite of course
    b, and course b is a prerequisite of course c, then course a is a
    prerequisite of course c.

    You are also given an array queries where queries[j] = [uj, vj]. For the
    jth query, you should answer whether course uj is a prerequisite of course
    vj or not.

    Return a boolean array answer, where answer[j] is the answer to the jth
    query.

    =============================================================================================================================
    FUNCTION: vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries);
    =============================================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: numCourses = 2, prerequisites = [[1,0]], queries = [[0,1],[1,0]]
    Output: [false,true]
    Explanation: The pair [1, 0] indicates that you have to take course 1
                 before you can take course 0.  Course 0 is not a prerequisite
                 of course 1, but the opposite is true.


    --- Example 2 ---
    Input: numCourses = 2, prerequisites = [], queries = [[1,0],[0,1]]
    Output: [false,false]
    Explanation: There are no prerequisites, and each course is independent.


    --- Example 3 ---
    Input: numCourses = 3,
           prerequisites = [[1,2],[1,0],[2,0]],
           queries = [[1,0],[1,2]]
    Output: [true,true]


    *** Constraints ***
    2 <= numCourses <= 100
    0 <= prerequisites.length <= (numCourses * (numCourses - 1) / 2)
    prerequisites[i].length == 2
    0 <= ai, bi <= n - 1
    ai != bi
    All the pairs [ai, bi] are unique.
    The prerequisites graph has no cycles.
    1 <= queries.length <= 10^4
    0 <= ui, vi <= n - 1
    ui != vi

*/

#include <queue>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Since this is a DAG (Directed Acyclic Graph), if course 'a' is a
    prerequisite of course 'b', then all of the descendants of 'b' are also
    indirect descendants of 'b'.

    We're going to use that in our advantange.

    We'll do a DFS starting from each course and we'll append ALL of the
    INDICRENT descendants of our DIRECT neighbor into our children[curr_course]
    and that way we'll be able to answer each query in O(1).

*/

/* Time  Beats: 44.83% */
/* Space Beats: 21.31% */

/* Time  Complexity: O(V^3  +  E  +  Q) */
/* Space Complexity: O(V^2  +  E  +  Q) */
class Solution {
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries)
    {
        const int V = numCourses;
        const int E = prerequisites.size();
        const int Q = queries.size();

        vector<bool> answer;
        answer.reserve(Q); // To prevent repeated reallocations

        /* Build an Adjacency List */
        vector<unordered_set<int>> adj_list(numCourses, unordered_set<int>());

        for (const vector<int>& edge : prerequisites)
        {
            const int& a = edge[0];
            const int& b = edge[1];

            adj_list[a].insert(b);
        }

        vector<unordered_set<int>> children(numCourses, unordered_set<int>());
        vector<bool> visited(numCourses, false);

        for (int course = 0; course < numCourses; course++)
            dfs_populate(course, children, adj_list, visited);

        for (const vector<int>& query : queries)
        {
            const int& u = query[0];
            const int& v = query[1];

            answer.push_back(children[u].count(v));
        }

        return answer;
    }

private:
    void dfs_populate(int course, vector<unordered_set<int>>& children, const vector<unordered_set<int>>& adj_list, vector<bool>& visited)
    {
        if (visited[course])
            return;

        visited[course] = true;

        for (const int& neighbor : adj_list[course])
        {
            dfs_populate(neighbor, children, adj_list, visited);

            children[course].insert(neighbor);
            children[course].insert(children[neighbor].begin(), children[neighbor].end());
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 10.90% */
/* Space Beats: 84.08% */

/* Time  Complexity: O(V^3) */
/* Space Complexity: O(V^2) */
class Solution_Floyd_warshall {
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries)
    {
        const int V = numCourses;
        const int E = prerequisites.size();
        const int Q = queries.size();

        vector<vector<bool>> connected = vector(numCourses, vector<bool>(numCourses, false));

        for (const vector<int>& edge : prerequisites)
        {
            const int& a = edge[0];
            const int& b = edge[1];

            connected[a][b] = true;
        }

        for (int k = 0; k < numCourses; k++)
        {
            for (int i = 0; i < numCourses; i++)
            {
                for (int j = 0; j < numCourses; j++)
                    connected[i][j] = connected[i][j] || connected[i][k] && connected[k][j];
            }
        }

        vector<bool> answer;
        answer.reserve(Q); // To prevent repeated reallocations
        for (const vector<int>& query : queries)
        {
            const int& u = query[0];
            const int& v = query[1];

            answer.push_back(connected[u][v]);
        }

        return answer;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This problem is a direct application of Topological Sort(i.e. "Kahn's
    algorithm") with addition to that, we need to maintain a matrix "connected"
    which represents if course 'i' is a prerequisite of course 'j'.

    Push all the vertices with indegree 0 to the queue, i.e. the ones with NO
    prerequisites.

    For all such vertices, decrease their neighbor's indegree by 1 since we are
    removing current course from the queue.

    For connected[i][j] such that i is prerequsite of j, make it true for
    current course & ALL of its neighbors.

    And also if current course had a prerequisite, that will apply to current
    course's neighbour as well.

    for(int i = 0; i < n; i++)
    {
        if(connected[i][curr_course])
            table[i][neighbor] = true;
    }

*/

/* Time  Beats: 71.20% */
/* Space Beats: 51.86% */

/* Time  Complexity: O(V^3) */
/* Space Complexity: O(V^2) */
class Solution_Topological_Sort__Kahn_Algo {
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries)
    {
        const int V = numCourses;
        const int E = prerequisites.size();
        const int Q = queries.size();

        /* Build an Adjacency List  &  Indegree List */
        vector<unordered_set<int>> adj_list (numCourses, unordered_set<int>());
        vector<int>                in_degree(numCourses, 0);

        for (const vector<int>& edge : prerequisites)
        {
            const int& a = edge[0];
            const int& b = edge[1];

            adj_list[a].insert(b);
            in_degree[b]++;
        }


        vector<vector<bool>> connected(numCourses, vector<bool>(numCourses, false));

        queue<int> queue;
        for (int i = 0; i < numCourses; i++)
        {
            if (in_degree[i] == 0)
                queue.push(i);
        }

        while ( ! queue.empty())
        {
            int curr_course = queue.front();
            queue.pop();

            for (const int& neighbor : adj_list[curr_course])
            {
                connected[curr_course][neighbor] = true;

                for (int i = 0; i < numCourses; i++)
                {
                    if (connected[i][curr_course]) // If 'i' is a prereq of ME
                        connected[i][neighbor] = true; // It's a prereq of NEI
                }
                in_degree[neighbor]--;

                if (in_degree[neighbor] == 0)
                    queue.push(neighbor);
            }
        }

        vector<bool> answer;
        answer.reserve(Q); // To prevent repeated reallocations
        for (const vector<int>& query : queries)
        {
            const int& u = query[0];
            const int& v = query[1];

            answer.push_back(connected[u][v]);
        }

        return answer;
    }
};
