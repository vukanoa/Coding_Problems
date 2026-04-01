/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    752) Open The Lock
    ===========================

    ============
    Description:
    ============

    You have a lock in front of you with 4 circular wheels. Each wheel has 10
    slots: '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'. The wheels can
    rotate freely and wrap around: for example we can turn '9' to be '0', or
    '0' to be '9'. Each move consists of turning one wheel one slot.

    The lock initially starts at '0000', a string representing the state of the
    4 wheels.

    You are given a list of deadends dead ends, meaning if the lock displays
    any of these codes, the wheels of the lock will stop turning and you will
    be unable to open it.

    Given a target representing the value of the wheels that will unlock the
    lock, return the minimum total number of turns required to open the lock,
    or -1 if it is impossible.

    ================================================================
    FUNCTION: int openLock(vector<string>& deadends, string target);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: deadends = ["0201","0101","0102","1212","2002"], target = "0202"
    Output: 6
    Explanation:
    A sequence of valid moves would be "0000" -> "1000" -> "1100" -> "1200" ->
    "1201" -> "1202" -> "0202".  Note that a sequence like "0000" -> "0001" ->
    "0002" -> "0102" -> "0202" would be invalid, because the wheels of the lock
    become stuck after the display becomes the dead end "0102".


    --- Example 2 ---
    Input: deadends = ["8888"], target = "0009"
    Output: 1
    Explanation: We can turn the last wheel in reverse to move from "0000" ->
    "0009"


    --- Example 3 ---
    Input: deadends =
    ["8887","8889","8878","8898","8788","8988","7888","9888"], target = "8888"
    Output: -1
    Explanation: We cannot reach the target without getting stuck.



    *** Constraints ***
    1 <= deadends.length <= 500
    deadends[i].length == 4
    target.length == 4
    target will not be in the list deadends.
    target and deadends[i] consist of digits only.

*/

#include <string>
#include <vector>
#include <unordered_set>
#include <queue>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 45.77% */
/* Space Beats: 19.59% */

/* Time  Complexity: O(d^WHEELS + DEADENDS_SIZE * WHEELS) */
/* Space Complexity: O(d^WHEELS)                          */
class Solution {
public:
    int openLock(vector<string>& deadends, string target)
    {
        if (target == "0000")
            return 0;

        // O(DEADENDS_SIZE * WHEELS), because of the hashing of size WHEELS */
        unordered_set<string> visited(deadends.begin(), deadends.end());

        if (visited.count("0000")) // Starting combination is a deadend itself
            return -1;

        queue<pair<string,int>> queue; // {combination_str, number_of_turns};
        queue.push( {"0000", 0} );
        visited.insert("0000");

        while ( ! queue.empty())
        {
            auto [combination_str, number_of_turns] = queue.front();
            queue.pop();

            vector<string> new_states = generate_new_states(combination_str);

            for (const string& state : new_states)
            {
                if (state == target)
                    return number_of_turns + 1;

                if (visited.count(state))
                    continue;

                visited.insert(state);
                queue.push( {state, number_of_turns+1} );
            }
        }

        return -1;
    }

    vector<string> generate_new_states(string combination_str)
    {
        const int WHEELS = 4;
        const int MOD    = 10; // WHEEL_VALUES

        vector<string> new_states;
        new_states.reserve(WHEELS * 2);

        for (int i = 0; i < WHEELS; i++)
        {
            string prev_state = combination_str;
            string next_state = combination_str;

            prev_state[i] = (((prev_state[i] - '0') - 1 + MOD) % MOD) + '0';
            next_state[i] = (((next_state[i] - '0') + 1 + MOD) % MOD) + '0';

            new_states.push_back(prev_state);
            new_states.push_back(next_state);
        }

        return new_states;
    }
};
