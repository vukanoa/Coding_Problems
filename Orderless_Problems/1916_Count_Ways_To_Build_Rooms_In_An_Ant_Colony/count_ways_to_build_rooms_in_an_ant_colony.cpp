/*
    ============
    === HARD ===
    ============

    ================================================
    1916) Count Ways to Build Rooms in an Ant Colony
    ================================================

    ============
    Description:
    ============

    You are an ant tasked with adding n new rooms numbered 0 to n-1 to your
    colony. You are given the expansion plan as a 0-indexed integer array of
    length n, prevRoom, where prevRoom[i] indicates that you must build room
    prevRoom[i] before building room i, and these two rooms must be connected
    directly. Room 0 is already built, so prevRoom[0] = -1. The expansion plan
    is given such that once all the rooms are built, every room will be
    reachable from room 0.

    You can only build one room at a time, and you can travel freely between
    rooms you have already built only if they are connected. You can choose to
    build any room as long as its previous room is already built.

    Return the number of different orders you can build all the rooms in. Since
    the answer may be large, return it modulo 109 + 7.

    ======================================================
    FUNCTION: int waysToBuildRooms(vector<int>& prevRoom);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: prevRoom = [-1,0,1]
    Output: 1
    Explanation: There is only one way to build the additional rooms: 0 → 1 → 2

    --- Example 2 ---
    Input: prevRoom = [-1,0,0,1,2]
    Output: 6
    Explanation:
    The 6 ways are:
    0 → 1 → 3 → 2 → 4
    0 → 2 → 4 → 1 → 3
    0 → 1 → 2 → 3 → 4
    0 → 1 → 2 → 4 → 3
    0 → 2 → 1 → 3 → 4
    0 → 2 → 1 → 4 → 3


    *** Constraints ***
    n == prevRoom.length
    2 <= n <= 10^5
    prevRoom[0] == -1
    0 <= prevRoom[i] < n for all 1 <= i < n
    Every room is reachable from room 0 once all the rooms are built.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 96.81% */
/* Space Beats: 91.49% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
private:
    const int MOD = 1e9 + 7;

public:
    int waysToBuildRooms(vector<int>& prev_room)
    {
        int N = prev_room.size();

        // Build the dependency tree
        vector<vector<int>> dependency_tree(N);
        for (int room = 1; room < N; room++)
        {
            dependency_tree[prev_room[room]].push_back(room);
        }

        vector<int> subtree_size(N, 0);
        compute_subtree_size(dependency_tree, subtree_size, 0);

        // Compute n!
        long long factorial_n = 1;
        for (int i = 2; i <= N; i++)
            factorial_n = (factorial_n * i) % MOD;

        // Compute product of all subtree sizes
        long long denominator = 1;
        for (const int& size : subtree_size)
            denominator = (denominator * size) % MOD;

        // Modular division using modular inverse
        long long inverse_denominator = mod_inverse(denominator);

        return static_cast<int>((factorial_n * inverse_denominator) % MOD);
    }

private:
    // Computes subtree size rooted at curr_room
    int compute_subtree_size(
        vector<vector<int>>& dependency_tree,
        vector<int>& subtree_size,
        int curr_room)
    {
        int total_nodes = 1;

        for (const int& next_room : dependency_tree[curr_room])
        {
            total_nodes += compute_subtree_size(dependency_tree,
                                                subtree_size,
                                                next_room
                                               );
        }

        subtree_size[curr_room] = total_nodes;
        return total_nodes;
    }

    long long mod_inverse(long long value)
    {
        return fast_power(value, MOD - 2);
    }

    long long fast_power(long long base, long long exponent)
    {
        long long result = 1;
        base %= MOD;

        while(exponent > 0)
        {
            if(exponent & 1)
                result = (result * base) % MOD;

            base = (base * base) % MOD;
            exponent >>= 1;
        }

        return result;
    }
};
