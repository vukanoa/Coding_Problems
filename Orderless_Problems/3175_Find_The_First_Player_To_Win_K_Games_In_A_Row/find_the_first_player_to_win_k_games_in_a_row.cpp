/*
    ==============
    === MEDIUM ===
    ==============

    ===================================================
    3175) Find The First Player to win K Games in a Row
    ===================================================

    ============
    Description:
    ============

    A competition consists of n players numbered from 0 to n - 1.

    You are given an integer array skills of size n and a positive integer k,
    where skills[i] is the skill level of player i. All integers in skills are
    unique.

    All players are standing in a queue in order from player 0 to player n - 1.

    The competition process is as follows:

    The first two players in the queue play a game, and the player with the
    higher skill level wins. After the game, the winner stays at the beginning
    of the queue, and the loser goes to the end of it.

    The winner of the competition is the first player who wins k games in a row

    Return the initial index of the winning player.

    ============================================================
    FUNCTION: int findWinningPlayer(vector<int>& skills, int k);
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: skills = [4,2,6,3,9], k = 2
    Output: 2
    Explanation: Initially, the queue of players is [0,1,2,3,4]. The following
    process happens:

    Players 0 and 1 play a game, since the skill of player 0 is higher than
    that of player 1, player 0 wins. The resulting queue is [0,2,3,4,1].

    Players 0 and 2 play a game, since the skill of player 2 is higher than
    that of player 0, player 2 wins. The resulting queue is [2,3,4,1,0].

    Players 2 and 3 play a game, since the skill of player 2 is higher than
    that of player 3, player 2 wins. The resulting queue is [2,4,1,0,3].

    Player 2 won k = 2 games in a row, so the winner is player 2.


    --- Example 2 ---
    Input: skills = [2,5,4], k = 3
    Output: 1
    Explanation:
    Initially, the queue of players is [0,1,2]. The following process happens:
        Players 0 and 1 play a game, since the skill of player 1 is higher than
        that of player 0, player 1 wins. The resulting queue is [1,2,0].

        Players 1 and 2 play a game, since the skill of player 1 is higher than
        that of player 2, player 1 wins. The resulting queue is [1,0,2].

        Players 1 and 0 play a game, since the skill of player 1 is higher than
        that of player 0, player 1 wins. The resulting queue is [1,2,0].

    Player 1 won k = 3 games in a row, so the winner is player 1.


    *** Constraints ***
    n == skills.length
    2 <= n <= 10^5
    1 <= k <= 10^9
    1 <= skills[i] <= 10^6
    All integers in skills are unique.

*/

#include <algorithm>
#include <deque>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory. Go through the code and through one example and you'll
    get it.

*/

/* Time  Beats: 23.00% */
/* Space Beats: 18.47% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int findWinningPlayer(vector<int>& skills, int k)
    {
        const int N = skills.size();
        int result = 0;


        int max_elem = *max_element(skills.begin(), skills.end());

        deque<pair<int,int>> deque;
        for (int i = 0; i < N; i++)
            deque.push_back( {skills[i], i} );

        int winning_streak = 0;

        int left_player = deque.front().first;
        int left_idx    = deque.front().second;
        deque.pop_front();

        if (left_player == max_elem)
            return left_idx;

        for(;;)
        {
            int right_player = deque.front().first;
            int right_idx    = deque.front().second;
            deque.pop_front();

            if (max_elem == right_player)
                return right_idx;

            if (left_player > right_player)
            {
                winning_streak++;
                deque.push_back( {right_player, right_idx} );
            }
            else
            {
                winning_streak = 1;
                deque.push_back( {left_player, left_idx} );

                left_player = right_player;
                left_idx    = right_idx;
            }

            if (winning_streak == k)
                break;
        }

        return left_idx;
    }
};
