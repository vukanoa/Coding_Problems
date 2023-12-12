#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <queue>

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

/*
    ------------
    --- IDEA ---
    ------------

    If we tried to do a DFS for every "u" in queries, we may traverse the
    graph mutliple times. To avoid that we'll make sure to save visited nodes
    and its prerequisites.

    We'll save it in a Hash Map of Sets named prereq_umap;

    That way we'll only visit each node once and at the end we can just check
    if "u" exists in prereq_umap[v] and store that in answer for a given query.

*/

/* Time  Beats: 27.78% */
/* Space Beats: 5.65%  */

/* 
    Time  Complexity:
        O(N * (E + N) + Q) -> O(N * (N^2) + Q) -> O(N^3 + Q) -> O(N^3)

    E is number of edges
    N is number of nodes
    Q is number of queries
*/
/* Space Complexity: O(N) */
class Solution {
public:
    std::vector<bool> checkIfPrerequisite(
                                          int numCourses,
                                          std::vector<std::vector<int>>& prerequisites,
                                          std::vector<std::vector<int>>& queries
                                         )
    {
        std::vector<bool> answer(queries.size(), false);

        if (prerequisites.size() == 0)
            return answer;

        std::vector<std::vector<int>> adj(numCourses);

        // Make adjacency matrix(Directed Graph) in the opposite way of what's
        // on the picture
        for (int i = 0; i < prerequisites.size(); i++)
            adj[prerequisites[i][1]].push_back(prerequisites[i][0]);

        // Traverse the graph and fill Sets
        std::unordered_map<int, std::unordered_set<int>> prereq_umap;
        for (int course = 0; course < numCourses; course++)
            dfs(adj, course, prereq_umap);

        // Fill answer vector
        for (int i = 0; i < queries.size(); i++)
        {
            int u = queries[i][0];
            int v = queries[i][1];

            answer[i] = prereq_umap[v].find(u) != prereq_umap[v].end();
        }

        return answer;
    }

private:
    std::unordered_set<int> dfs(
                                std::vector<std::vector<int>>& adj,
                                int course,
                                std::unordered_map<int, std::unordered_set<int>> &prereq_umap
                               )
    {
        if (prereq_umap.find(course) != prereq_umap.end())
            return prereq_umap[course];

        prereq_umap[course] = std::unordered_set<int>(); // Insert empty set
        for (auto& prereq : adj[course])
        {
            auto uset = dfs(adj, prereq, prereq_umap);

            prereq_umap[course].insert(uset.begin(), uset.end());
        }
        prereq_umap[course].insert(course); // Insert the course itself

        return prereq_umap[course];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 19.54% */
/* Space Beats: 98.55% */

/* Time  Complexity: O(N^3) */
/* Space Complexity: O(N^2) */
class Solution_Floyd_warshall {
public:
    std::vector<bool> checkIfPrerequisite(
                                          int numCourses,
                                          std::vector<std::vector<int>>& prerequisites,
                                          std::vector<std::vector<int>>& queries
                                         )
    {
        std::vector<std::vector<bool>> connected = std::vector(numCourses, std::vector<bool>(numCourses, false));

        for (auto& prereq : prerequisites)
            connected[prereq[0]][prereq[1]] = true;

        for (int k = 0; k < numCourses; k++)
        {
            for (int i = 0; i < numCourses; i++)
            {
                for (int j = 0; j < numCourses; j++)
                    connected[i][j] = connected[i][j] || connected[i][k] && connected[k][j];
            }
        }

        std::vector<bool> answer;
        for (auto& q : queries)
            answer.push_back(connected[q[0]][q[1]]);

        return answer;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This problem is a direct application of kahn's algorithm with addition to
    that, we need to maintain a matrix "connected"  which represents if two
    courses are prerequisites of one another.

    Push all the vertices with indegree 0 to the queue.

    For all such vertices, decrease their adjacent vertex's indegree by 1 since
    we are removing current vertex from the queue.

    For connected[i][j] such that i is prerequsite of j, make it true for
    current vertex & it's adjacent nodes.

    And also if current vertex had a prerequisite, that will apply to current
    vertex's neighbour as well.

    for(int i = 0; i < n; i++)
    {
        if(connected[i][curr])
            table[i][prereq] = true;
    }

*/

/* Time  Beats: 79.32% */
/* Space Beats: 88.04% */

/* Time  Complexity: O(N^3) */
/* Space Complexity: O(N^2) */
class Solution_Kahn {
public:
    std::vector<bool> checkIfPrerequisite(
                                          int numCourses,
                                          std::vector<std::vector<int>>& prerequisites,
                                          std::vector<std::vector<int>>& queries
                                         )
    {
        std::vector<bool> answer;

        std::vector<std::vector<int>> adj_list(numCourses);   
        std::vector<int> indegree(numCourses, 0);
        
        // Make adj_listacency & Indegree List
        for(int i = 0; i < prerequisites.size(); i++)
        {
            adj_list[prerequisites[i][0]].push_back(prerequisites[i][1]);
            indegree[prerequisites[i][1]]++;
        }

        std::vector<std::vector<bool>> connected(numCourses, std::vector<bool>(numCourses, false));

        std::queue<int> queue;
        for(int i = 0; i < numCourses; i++)
        {
            if(indegree[i] == 0)
                queue.push(i);
        }

        while(!queue.empty())
        {
            int curr_course = queue.front();
            queue.pop();

            for(auto &prereq : adj_list[curr_course])
            {
                connected[curr_course][prereq] = true;

                for(int i = 0; i < numCourses; i++)
                {
                    if(connected[i][curr_course])
                        connected[i][prereq] = true;
                }
                indegree[prereq]--;

                if(indegree[prereq] == 0)
                    queue.push(prereq);
            }
        }

        for(int i = 0; i < queries.size(); i++)
            answer.push_back(connected[queries[i][0]][queries[i][1]]);

        return answer;
    }
};
