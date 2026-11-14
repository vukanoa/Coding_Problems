/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    841) Keys and Rooms
    ===========================

    ============
    Description:
    ============

    There are n rooms labeled from 0 to n - 1 and all the rooms are locked
    except for room 0. Your goal is to visit all the rooms. However, you cannot
    enter a locked room without having its key.

    When you visit a room, you may find a set of distinct keys in it. Each key
    has a number on it, denoting which room it unlocks, and you can take all of
    them with you to unlock the other rooms.

    Given an array rooms where rooms[i] is the set of keys that you can obtain
    if you visited room i, return true if you can visit all the rooms, or false
    otherwise.

    ============================================================
    FUNCTION: bool canVisitAllRooms(vector<vector<int>>& rooms);
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: rooms = [[1],[2],[3],[]]
    Output: true
    Explanation: 
    We visit room 0 and pick up key 1.
    We then visit room 1 and pick up key 2.
    We then visit room 2 and pick up key 3.
    We then visit room 3.
    Since we were able to visit every room, we return true.

    --- Example 2 ---
    Input: rooms = [[1,3],[3,0,1],[2],[0]]
    Output: false
    Explanation: We can not enter room number 2 since the only key that unlocks
                 it is in that room.


    *** Constraints ***
    n == rooms.length
    2 <= n <= 1000
    0 <= rooms[i].length <= 1000
    1 <= sum(rooms[i].length) <= 3000
    0 <= rooms[i][j] < n
    All the values of rooms[i] are unique.

*/

#include <queue>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  13.07% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_BFS {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms)
    {
        const int N = rooms.size();

        unordered_set<int> seen;
        seen.insert(0);

        /* BFS */
        queue<int> queue;
        queue.push(0);

        while ( ! queue.empty())
        {
            int node = queue.front();
            queue.pop();

            for (const int& neighbor : rooms[node])
            {
                if (seen.count(neighbor))
                    continue;
                
                seen.insert(neighbor);
                queue.push(neighbor);
            }
        }

        return seen.size() == N;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  10.24% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_DFS {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms)
    {
        const int N = rooms.size();

        unordered_set<int> seen;
        seen.insert(0);

        /* DFS */
        dfs(0, seen, rooms);

        return seen.size() == N;
    }

private:
    void dfs(int node, unordered_set<int>& seen, vector<vector<int>>& rooms)
    {
        for (const int& neighbor : rooms[node])
        {
            if (seen.count(neighbor))
                continue;

            seen.insert(neighbor);
            dfs(neighbor, seen, rooms);
        }
    }
};
