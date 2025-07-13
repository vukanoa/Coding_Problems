/*
    ==============
    === MEDIUM ===
    ==============

    ===============================================
    2410) Maximum Matching of Players With Trainers
    ===============================================

    ============
    Description:
    ============

    You are given a 0-indexed integer array players, where players[i]
    represents the ability of the ith player. You are also given a 0-indexed
    integer array trainers, where trainers[j] represents the training capacity
    of the jth trainer.

    The ith player can match with the jth trainer if the player's ability is
    less than or equal to the trainer's training capacity. Additionally, the
    ith player can be matched with at most one trainer, and the jth trainer can
    be matched with at most one player.

    Return the maximum number of matchings between players and trainers that
    satisfy these conditions.

    ===================================================================================
    FUNCTION: int matchPlayersAndTrainers(vector<int>& players, vector<int>& trainers);
    ===================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: players = [4,7,9], trainers = [8,2,5,8]
    Output: 2
    Explanation:
    One of the ways we can form two matchings is as follows:
    - players[0] can be matched with trainers[0] since 4 <= 8.
    - players[1] can be matched with trainers[3] since 7 <= 8.
    It can be proven that 2 is the maximum number of matchings that can be formed.

    --- Example 2 ---
    Input: players = [1,1,1], trainers = [10]
    Output: 1
    Explanation:
    The trainer can be matched with any of the 3 players.
    Each player can only be matched with one trainer, so the maximum answer is 1.


    *** Constraints ***
    1 <= players.length, trainers.length <= 10^5
    1 <= players[i], trainers[j] <= 10^9

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Pretty straightforward "Sorting + Two Pointers + Greedy" Problem.

*/

/* Time  Beats: 48.79% */
/* Space Beats: 24.52% */

/* Time  Complexity: O(N * logN + M * logM) */
/* Space Complexity: O(logN + logM)         */ // C++'s sort Space Complexity
class Solution {
public:
    int matchPlayersAndTrainers(vector<int>& players, vector<int>& trainers)
    {
        int PLAYERS_SIZE = players.size();
        int TRAINERS_SIZE = trainers.size();
        int result = 0;

        /* Sort */
        sort(players.begin(), players.end());
        sort(trainers.begin(), trainers.end());

        for (int i = 0, j = 0; i < PLAYERS_SIZE && j < TRAINERS_SIZE; i++, j++)
        {
            while (j < TRAINERS_SIZE && players[i] > trainers[j])
                j++;

            if (j < TRAINERS_SIZE)
                result++;
        }

        return result;
    }
};
