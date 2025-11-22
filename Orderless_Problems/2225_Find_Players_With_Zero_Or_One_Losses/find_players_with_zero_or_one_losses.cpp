/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================
    2225) Find Players with Zero or One Losses
    ==========================================

    ============
    Description:
    ============

    You are given an integer array matches where matches[i] = [winneri, loseri]
    indicates that the player winneri defeated player loseri in a match.

    Return a list answer of size 2 where:

        + answer[0] is a list of all players that have not lost any matches.

        + answer[1] is a list of all players that have lost exactly one match.


    The values in the two lists should be returned in increasing order.

    Note:

        + You should only consider the players that have played at least one
          match.

        + The testcases will be generated such that no two matches will have
          the same outcome.

    ========================================================================
    FUNCTION: vector<vector<int>> findWinners(vector<vector<int>>& matches);
    ========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: matches = [[1,3],[2,3],[3,6],[5,6],[5,7],[4,5],[4,8],[4,9],[10,4],[10,9]]
    Output: [[1,2,10],[4,5,7,8]]
    Explanation:
    Players 1, 2, and 10 have not lost any matches.
    Players 4, 5, 7, and 8 each have lost one match.
    Players 3, 6, and 9 each have lost two matches.
    Thus, answer[0] = [1,2,10] and answer[1] = [4,5,7,8].

    --- Example 2 ---
    Input: matches = [[2,3],[1,3],[5,4],[6,4]]
    Output: [[1,2,5,6],[]]
    Explanation:
    Players 1, 2, 5, and 6 have not lost any matches.
    Players 3 and 4 each have lost two matches.
    Thus, answer[0] = [1,2,5,6] and answer[1] = [].


    *** Constraints ***
    1 <= matches.length <= 10^5
    matches[i].length == 2
    1 <= winneri, loseri <= 10^5
    winneri != loseri
    All matches[i] are unique.

*/

#include <algorithm>
#include <map>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 46.97% */
/* Space Beats: 42.45% */

/* Time  Complexity: O(N * logN) */ // Because of the final two sorts
/* Space Complexity: O(N)        */
class Solution {
public:
    vector<vector<int>> findWinners(vector<vector<int>>& matches)
    {
        const int N = matches.size();

        unordered_map<int, int> player;
        for (const auto& entry : matches)
        {
            const int& winner = entry[0];
            const int& loser  = entry[1];

            player.insert( {winner, 0} );
            player.insert( {loser,  0} );
        }

        for (const auto& entry: matches)
        {
            const int& winner = entry[0];
            const int& loser  = entry[1];

            player[loser]++;
        }

        vector<vector<int>> answer(2, vector<int>());
        for (const auto& entry : player)
        {
            const int& player_id = entry.first;
            const int& frequency = entry.second;

            if (frequency == 0)
                answer[0].push_back(player_id);

            if (frequency == 1)
                answer[1].push_back(player_id);
        }

        /* Sort */
        sort(answer[0].begin(), answer[0].end());
        sort(answer[1].begin(), answer[1].end());

        return answer;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, thought it's less explicit.

*/

/* Time  Beats: 31.45% */
/* Space Beats: 51.83% */

/* Time  Complexity: O(N * logN) */ // Because of the final two sorts
/* Space Complexity: O(N)        */
class Solution_Concise {
public:
    vector<vector<int>> findWinners(vector<vector<int>>& matches)
    {
        map<int,int> losses_player;

        for (const auto& entry : matches)
        {
            const int& winner = entry[0];
            const int& loser  = entry[1];

            if ( ! losses_player.count(entry[0]))
                losses_player[winner] = 0;

            losses_player[loser]++;
        }

        vector<int> zero;
        vector<int> ones;
        for (const auto& [player_id, frequency] : losses_player)
        {
            if (frequency == 0) zero.push_back(player_id);
            if (frequency == 1) ones.push_back(player_id);
        }

        return {zero, ones};
    }
};
