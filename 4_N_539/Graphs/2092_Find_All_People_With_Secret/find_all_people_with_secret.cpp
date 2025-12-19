/*
    ============
    === HARD ===
    ============

    =================================
    2092) Find All People With Secret
    =================================

    ============
    Description:
    ============

    You are given an integer n indicating there are n people numbered from 0 to
    n - 1. You are also given a 0-indexed 2D integer array meetings where
    meetings[i] = [xi, yi, timei] indicates that person xi and person yi have a
    meeting at timei. A person may attend multiple meetings at the same time.
    Finally, you are given an integer firstPerson.

    Person 0 has a secret and initially shares the secret with a person
    firstPerson at time 0. This secret is then shared every time a meeting
    takes place with a person that has the secret. More formally, for every
    meeting, if a person xi has the secret at timei, then they will share the
    secret with person yi, and vice versa.

    The secrets are shared instantaneously. That is, a person may receive the
    secret and share it with people in other meetings within the same time
    frame.

    Return a list of all the people that have the secret after all the meetings
    have taken place. You may return the answer in any order.

    ===========================================================================================
    FUNCTION: vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson);
    ===========================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 6, meetings = [[1,2,5],[2,3,8],[1,5,10]], firstPerson = 1
    Output: [0,1,2,3,5]
    Explanation:
    At time 0, person 0 shares the secret with person 1.
    At time 5, person 1 shares the secret with person 2.
    At time 8, person 2 shares the secret with person 3.
    At time 10, person 1 shares the secret with person 5.
    Thus, people 0, 1, 2, 3, and 5 know the secret after all the meetings.


    --- Example 2 ---
    Input: n = 4, meetings = [[3,1,3],[1,2,2],[0,3,3]], firstPerson = 3
    Output: [0,1,3]
    Explanation:
    At time 0, person 0 shares the secret with person 3.
    At time 2, neither person 1 nor person 2 know the secret.
    At time 3, person 3 shares the secret with person 0 and person 1.
    Thus, people 0, 1, and 3 know the secret after all the meetings.


    --- Example 3 ---
    Input: n = 5, meetings = [[3,4,2],[1,2,1],[2,3,1]], firstPerson = 1
    Output: [0,1,2,3,4]
    Explanation:
    At time 0, person 0 shares the secret with person 1.
    At time 1, person 1 shares the secret with person 2, and person 2 shares the secret with person 3.
    Note that person 2 can share the secret at the same time as receiving it.
    At time 2, person 3 shares the secret with person 4.
    Thus, people 0, 1, 2, 3, and 4 know the secret after all the meetings.



    *** Constraints ***
    2 <= n <= 10^5
    1 <= meetings.length <= 10^5
    meetings[i].length == 3
    0 <= xi, yi <= n - 1
    xi != yi
    1 <= timei <= 10^5
    1 <= firstPerson <= n - 1

*/

#include <climits>
#include <numeric>
#include <queue>
#include <vector>

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (Classic BFS)

*/

/* Time  Beats: 76.35% */
/* Space Beats: 80.64% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_BFS {
public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson)
    {
        vector<pair<int, int>> adj_list[n];
        meetings.push_back({0, firstPerson, 0});

        for (int i = 0; i < meetings.size(); i++)
        {
            adj_list[meetings[i][0]].push_back({meetings[i][1], meetings[i][2]});
            adj_list[meetings[i][1]].push_back({meetings[i][0], meetings[i][2]});
        }

        vector<int> min_shared_time(n, INT_MAX);
        min_shared_time[0] = 0;

        queue<pair<int, int>> queue;
        queue.push({0, 0});

        while( ! queue.empty())
        {
            int size = queue.size();
            for (int i = 0; i < size; i++)
            {
                auto [u, uTime] = queue.front();
                queue.pop();

                for (auto [v, w]: adj_list[u])
                {
                    if (uTime <= w && min_shared_time[v] > w)
                    {
                        queue.push({v, w});
                        min_shared_time[v] = w;
                    }
                }
            }
        }

        vector<int> result;

        for (int i = 0; i < n; i++)
        {
            if (min_shared_time[i] != INT_MAX)
                result.push_back(i);
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 82.16% */
/* Space Beats: 75.22% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_DFS {
public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson)
    {
        vector<pair<int, int>> adj_list[n];
        meetings.push_back({0, firstPerson, 0});

        for (int i = 0; i < meetings.size(); i++)
        {
            adj_list[meetings[i][0]].push_back({meetings[i][1], meetings[i][2]});
            adj_list[meetings[i][1]].push_back({meetings[i][0], meetings[i][2]});
        }

        vector<int> min_shared_time(n, INT_MAX);
        min_shared_time[0] = 0;

        dfs(0, 0, adj_list, min_shared_time);

        vector<int> ans;
        for (int i = 0; i < n; i++)
        {
            if(min_shared_time[i] != INT_MAX)
                ans.push_back(i);
        }

        return ans;
    }

private:
    void dfs (int u, int uTime, vector<pair<int, int>> adj_list[], vector<int>& min_shared_time)
    {
        for (auto [v, w]: adj_list[u])
        {
            if (uTime <= w && min_shared_time[v] > w)
            {
                min_shared_time[v] = w;
                dfs(v, w, adj_list, min_shared_time);
            }
        }
    }
};

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (Dijkstra)

*/

/* Time  Beats: 77.24% */
/* Space Beats: 32.79% */

/* Time  Complexity: O((N + M) * log(N + M)) */
/* Space Complexity: O(N + M)                */
class Solution_Dijkstra {
public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) 
    {
        // Person to Meetings
        vector<vector<pair<int,int>>> adj_list(n);

        for (const auto& meeting : meetings) 
        {
            int person_a     = meeting[0];
            int person_b     = meeting[1];
            int meeting_time = meeting[2];

            adj_list[person_a].emplace_back(meeting_time, person_b);
            adj_list[person_b].emplace_back(meeting_time, person_a);
        }

        vector<int> known_time(n, INT_MAX);
        vector<int> people_who_know_secret;
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> min_heap;

        min_heap.emplace(0, 0);
        min_heap.emplace(0, firstPerson);

        while ( ! min_heap.empty()) 
        {
            auto [current_time, current_person] = min_heap.top();
            min_heap.pop();

            if (known_time[current_person] != INT_MAX) 
                continue;

            known_time[current_person] = current_time;
            people_who_know_secret.push_back(current_person);

            for (auto& [meeting_time, other_person] : adj_list[current_person]) 
            {
                if (known_time[other_person] != INT_MAX || meeting_time < current_time) 
                    continue;

                min_heap.emplace(meeting_time, other_person);
            }
        }

        return people_who_know_secret;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO
    DSU

*/

/* Time  Beats: 91.87% */
/* Space Beats: 44.99% */

/* Time  Complexity: O(N + M) */
/* Space Complexity: O(N + M) */
class DSU {
public:
    vector<int> rank;
    vector<int> parent;

    DSU(int n)
    {
        rank.assign(n, 1);

        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
        // iota(parent.begin(), parent.end(), 1);
    }

    int find_root_node(int node)
    {
        // Get root parent
        while (node != parent[node])
        {
            // Huge Optimization (From O(n) to Amortized O(1) Time Complexity)
            // If there is no grandparent, nothing will happen
            parent[node] = parent[parent[node]];

            node = parent[node];
        }

        return node;
    }

    bool union_components(int node1, int node2)
    {
        int root1 = find_root_node(node1);
        int root2 = find_root_node(node2);

        if (root1 == root2)
            return false;

        if (rank[root1] < rank[root2])
            swap(root1, root2);

        // Make sure that to merge TOWARDS the smaller node, i.e. root1
        parent[root2] = root1;
        rank[root1] += rank[root2];

        return true;
    }
};

class Solution_DSU {
public:
    using PersonPair = pair<int, int>;

    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) 
    {
        // Maximum meeting time is 10^5, so we can use counting sort
        vector<PersonPair> meetings_by_time[100001]; // meetings_by_time[t] = {(x, y) have meeting at t}
        int max_meeting_time = -1;

        for (const auto& meeting : meetings) 
        {
            int person_a     = meeting[0];
            int person_b     = meeting[1];
            int meeting_time = meeting[2];

            meetings_by_time[meeting_time].emplace_back(person_a, person_b);
            max_meeting_time = max(max_meeting_time, meeting_time);
        }


        DSU dsu(n);

        dsu.union_components(0, firstPerson);

        for (int current_time = 0; current_time <= max_meeting_time; current_time++) 
        {
            for (auto& [person_a, person_b] : meetings_by_time[current_time]) 
                dsu.union_components(person_a, person_b);

            for (auto& [person_a, person_b] : meetings_by_time[current_time]) 
            {
                if (dsu.find_root_node(person_a) != dsu.find_root_node(0)) 
                {
                    dsu.parent[person_a] = person_a;
                    dsu.rank[person_a]   = 1;

                    dsu.parent[person_b] = person_b;
                    dsu.rank[person_b]   = 1;
                }
            }
        }

        vector<int> people_who_know_secret = {0};
        for (int person_id = 1; person_id < n; person_id++) 
        {
            if (dsu.find_root_node(person_id) == dsu.find_root_node(0)) 
                people_who_know_secret.push_back(person_id);
        }

        return people_who_know_secret;
    }
};
