/*
    ==============
    === MEDIUM ===
    ==============

    ==================================================
    2127) Maximum Employees to be Invited to a Meeting
    ==================================================

    ============
    Description:
    ============

    A company is organizing a meeting and has a list of n employees, waiting to
    be invited. They have arranged for a large circular table, capable of
    seating any number of employees.

    The employees are numbered from 0 to n - 1. Each employee has a favorite
    person and they will attend the meeting only if they can sit next to their
    favorite person at the table. The favorite person of an employee is not
    themself.

    Given a 0-indexed integer array favorite, where favorite[i] denotes the
    favorite person of the ith employee, return the maximum number of employees
    that can be invited to the meeting.

    ========================================================
    FUNCTION: int maximumInvitations(vector<int>& favorite);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: favorite = [2,2,1,2]
    Output: 3
    Explanation:
    The above figure shows how the company can invite employees 0, 1, and 2,
    and seat them at the round table. All employees cannot be invited because
    employee 2 cannot sit beside employees 0, 1, and 3, simultaneously. Note
    that the company can also invite employees 1, 2, and 3, and give them their
    desired seats. The maximum number of employees that can be invited to the
    meeting is 3.

    --- Example 2 ---
    Input: favorite = [1,2,0]
    Output: 3
    Explanation:
    Each employee is the favorite person of at least one other employee, and
    the only way the company can invite them is if they invite every employee.
    The seating arrangement will be the same as that in the figure given in
    example 1:
    - Employee 0 will sit between employees 2 and 1.
    - Employee 1 will sit between employees 0 and 2.
    - Employee 2 will sit between employees 1 and 0.
    The maximum number of employees that can be invited to the meeting is 3.

    --- Example 3 ---
    Input: favorite = [3,0,1,4,1]
    Output: 4
    Explanation:
    The above figure shows how the company will invite employees 0, 1, 3, and
    4, and seat them at the round table.
    Employee 2 cannot be invited because the two spots next to their favorite
    employee 1 are taken.
    So the company leaves them out of the meeting.
    The maximum number of employees that can be invited to the meeting is 4.


    *** Constraints ***
    n == favorite.length
    2 <= n <= 10^5
    0 <= favorite[i] <= n - 1
    favorite[i] != i

*/

#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (Cycle Detection with Extended Paths)

*/

/* Time  Beats: 23.77% */
/* Space Beats: 10.66% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int maximumInvitations(vector<int>& favorite)
    {
        const int N = favorite.size();
        vector<vector<int>> reversed_graph(N);

        for (int person = 0; person < N; person++)
            reversed_graph[favorite[person]].push_back(person);

        int longest_cycle = 0;
        int two_cycle_invitations = 0;

        vector<bool> path(N, false);

        // Find all cycles
        for (int person = 0; person < N; ++person)
        {
            if ( ! path[person])
            {
                unordered_map<int, int> visited_people;
                int curr_person = person;
                int distance = 0;

                while (true)
                {
                    if (path[curr_person])
                        break;

                    path[curr_person] = true;

                    visited_people[curr_person] = distance++;
                    int next_person = favorite[curr_person];

                    if (visited_people.count(next_person)) // Cycle detected
                    {
                        int cycle_len = distance - visited_people[next_person];
                        longest_cycle = max(longest_cycle, cycle_len);

                        if (cycle_len == 2)
                        {
                            unordered_set<int> visited_nodes = {curr_person, next_person};

                            two_cycle_invitations += 2 + bfs(reversed_graph, next_person, visited_nodes)
                                                       + bfs(reversed_graph, curr_person, visited_nodes);
                        }

                        break;
                    }

                    curr_person = next_person;
                }
            }
        }

        return max(longest_cycle, two_cycle_invitations);
    }

private:
    int bfs(vector<vector<int>>& reversed_graph, int startNode, unordered_set<int>& visited_nodes)
    {
        queue<pair<int, int>> queue;
        queue.push( {startNode, 0} );

        int max_distance = 0;

        while ( ! queue.empty())
        {
            auto [curr_node, curr_distance] = queue.front();
            queue.pop();

            for (int neighbor : reversed_graph[curr_node])
            {
                if (visited_nodes.count(neighbor))
                    continue;

                visited_nodes.insert(neighbor);
                queue.push({neighbor, curr_distance + 1});
                max_distance = max(max_distance, curr_distance + 1);
            }
        }

        return max_distance;
    }
};
