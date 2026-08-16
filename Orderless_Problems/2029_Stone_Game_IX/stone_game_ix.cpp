/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    2029) Stone Game IX
    ===========================

    ============
    Description:
    ============

    Alice and Bob continue their games with stones. There is a row of n stones,
    and each stone has an associated value. You are given an integer array
    stones, where stones[i] is the value of the ith stone.

    Alice and Bob take turns, with Alice starting first. On each turn, the
    player may remove any stone from stones. The player who removes a stone
    loses if the sum of the values of all removed stones is divisible by 3. Bob
    will win automatically if there are no remaining stones (even if it is
    Alice's turn).

    Assuming both players play optimally, return true if Alice wins and false
    if Bob wins.

    ================================================
    FUNCTION: bool stoneGameIX(vector<int>& stones);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: stones = [2,1]
    Output: true
    Explanation: The game will be played as follows:
    - Turn 1: Alice can remove either stone.
    - Turn 2: Bob removes the remaining stone. 
    The sum of the removed stones is 1 + 2 = 3 and is divisible by 3.
    Therefore, Bob loses and Alice wins the game.

    --- Example 2 ---
    Input: stones = [2]
    Output: false
    Explanation: Alice will remove the only stone, and the sum of the values on
    the removed stones is 2. Since all the stones are removed and the sum of
    values is not divisible by 3, Bob wins the game.

    --- Example 3 ---
    Input: stones = [5,1,2,4,3]
    Output: false
    Explanation: Bob will always win. One possible way for Bob to win is shown below:
    - Turn 1: Alice can remove the second stone with value 1. Sum of removed stones = 1.
    - Turn 2: Bob removes the fifth stone with value 3. Sum of removed stones = 1 + 3 = 4.
    - Turn 3: Alices removes the fourth stone with value 4. Sum of removed stones = 1 + 3 + 4 = 8.
    - Turn 4: Bob removes the third stone with value 2. Sum of removed stones = 1 + 3 + 4 + 2 = 10.
    - Turn 5: Alice removes the first stone with value 5. Sum of removed stones = 1 + 3 + 4 + 2 + 5 = 15.
    Alice loses the game because the sum of the removed stones (15) is divisible by 3. Bob wins the game.


    *** Constraints ***
    1 <= stones.length <= 10^5
    1 <= stones[i] <= 10^4

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Since the player's goal is to ensure that the total value of the removed
    stones is not a multiple of 3, what we can do is divide the stones into three
    categories based on their REMAINDERS when divided by 3: 0, 1, and 2.

    We'll use use 0, 1, and 2 to represent the three types, and let their
    respective counts count_0, count_1, count_2.

    We can notice that removing a stone of type 0 does NOT affect the remainder
    of the total sum. Therefore, stones of type 0 can be considered as a
    "switch of turns." For example, if it is Alice's turn and she finds that
    removing a stone of type 1 or 2 CANNOT lead to a win, then she can remove a
    stone of type 0 instead, passing the same situation to Bob. If there are
    still stones of type 0 remaining, Bob can similarly remove one to pass the
    situation back to Alice.

    By repeatedly applying this idea, we can draw the following conclusions:

        + If the number of stones of type 0 is EVEN, the winning or losing
          state is equivalent to the state without any stones of type 0.

        + If the number of stones of type 0 is ODD, the winning condition is
          equivalent to the winning condition with exactly ONE stone of type 0.
          However, this is not simply the opposite of the winning condition
          with no stones of type 0. This is because if all the stones are
          removed, the player who removes the last stone loses. Therefore, if
          Alice cannot win by removing a stone of type 1 or 2, and she chooses
          to remove a stone of type 0 instead, she may still lose if the reason
          she cannot win is that all the stones will eventually be removed.


    After considering the stones of type 0, we are left with stones of types 1
    and 2. To ensure that the sum of the removed stones is NOT a multiple of 3,
    the sequence of operations can only follow one of the following two
    patterns:

    If Alice removes a stone of type 1 first, then Bob can ONLY remove a stone
    of type 1(Becuase we've already covered type 1 and Bob CANNOT remove type 2
    since that would mean the sum would be divisible by 3, therefore he'd lose).
    After that, Alice can ONLY remove a stone of type 2, and Bob can ONLY
    remove a stone of type 1. Thus, the sequence of removal types is:

        1 1 2 1 2 1 2 1 2 1⋯

    If Alice removes a stone of type 2 first, the sequence is symmetric:

        2 2 1 2 1 2 1 2 1 2⋯

    As the first player, Alice can choose either sequence.

    Suppose Alice chooses the first sequence. In that case Bob MUST ALWAYS
    remove a stone of type 1, while Alice removes a stone of type 1 in the
    first step and then always removes a stone of type 2. Alice can win in the
    following situations:

        + If there is exactly 1 stone of type 1 and at least 1 stone of type 2,
          Alice wins when Bob completes the first step.

        + If there are at least 2 stones of type 1 and the number of type 1
          stones does not exceed the number of type 2 stones, Alice can also
          win.


    More specifically:

        + If there is exactly ONE MORE stone of type 1 than of type 2, then
          after Alice removes the last stone of type 2, all stones are removed,
          so Bob wins.

        + If there are exactly TWO MORE stones of type 1 than of type 2, then
          after Bob removes the last stone of type 1, all stones are removed,
          so Bob wins.

        + If there are MORE THAN TWO ADDITIONAL STONES of type 1, Alice
          eventually reaches a turn when there are no stones of type 2 left to
          remove, so Bob wins.

        + If the number of stones of type 2 is AT LEAST THE NUMBER OF STONES OF
          type 1, Bob eventually reaches a turn when there are no stones of
          type 1 left to remove, so Alice wins.


   Therefore, the conditions above can be summarized as follows:

       + Alice wins when there is at least one stone of type 1 and the number
         of type 1 stones is no greater than the number of type 2 stones.

   Similarly,

        + if Alice chooses the second sequence, she wins if and only if there
          is at least one stone of type 2 and the number of type 2 stones is no
          greater than the number of type 1 stones.


   Combining these two cases, when there are no stones of type 0, Alice wins if
   and only if there is at least one stone of each type, 1 and 2.

*/

/* Time  Beats: 75.38% */
/* Space Beats: 33.50% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool stoneGameIX(vector<int>& stones)
    {
        int count_0 = 0;
        int count_1 = 0;
        int count_2 = 0;

        for (const int& stone : stones)
        {
            int type = stone % 3;

            if (type == 0)
            {
                ++count_0;
            }
            else if (type == 1)
            {
                ++count_1;
            }
            else
            {
                ++count_2;
            }
        }

        if (count_0 % 2 == 0)
            return count_1 >= 1 && count_2 >= 1;

        return count_1 - count_2 > 2 || count_2 - count_1 > 2;
    }
};
