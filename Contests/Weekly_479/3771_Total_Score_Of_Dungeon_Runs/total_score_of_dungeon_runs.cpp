/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    3771) Total Score of Dungeon Runs
    =================================

    ============
    Description:
    ============

    You are given a positive integer hp and two positive 1-indexed integer
    arrays damage and requirement.

    There is a dungeon with n trap rooms numbered from 1 to n. Entering room i
    reduces your health points by damage[i]. After that reduction, if your
    remaining health points are at least requirement[i], you earn 1 point for
    that room.

    Let score(j) be the number of points you get if you start with hp health
    points and enter the rooms j, j + 1, ..., n in this order.

    Return the integer score(1) + score(2) + ... + score(n), the sum of scores
    over all starting rooms.

    =====
    Note: You cannot skip rooms. You can finish your journey even if your
          health points become non-positive. 
    =====

    ======================================================================================
    FUNCTION: long long totalScore(int hp, vector<int>& damage, vector<int>& requirement);
    ======================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: hp = 11, damage = [3,6,7], requirement = [4,2,5]
    Output: 3
    Explanation:
    score(1) = 2, score(2) = 1, score(3) = 0. The total score is 2 + 1 + 0 = 3.
    As an example, score(1) = 2 because you get 2 points if you start from room 1.
        You start with 11 health points.
        Enter room 1. Your health points are now 11 - 3 = 8. You get 1 point because 8 >= 4.
        Enter room 2. Your health points are now 8 - 6 = 2. You get 1 point because 2 >= 2.
        Enter room 3. Your health points are now 2 - 7 = -5. You do not get any points because -5 < 5.


    --- Example 2 ---
    Input: hp = 2, damage = [10000,1], requirement = [1,1]
    Output: 1
    Explanation:
    score(1) = 0, score(2) = 1. The total score is 0 + 1 = 1.
    score(1) = 0 because you do not get any points if you start from room 1.
        You start with 2 health points.
        Enter room 1. Your health points are now 2 - 10000 = -9998. You do not get any points because -9998 < 1.
        Enter room 2. Your health points are now -9998 - 1 = -9999. You do not get any points because -9999 < 1.
    score(2) = 1 because you get 1 point if you start from room 2.
        You start with 2 health points.
        Enter room 2. Your health points are now 2 - 1 = 1. You get 1 point because 1 >= 1.



    *** Constraints ***
    1 <= hp <= 10^9
    1 <= n == damage.length == requirement.length <= 10^5
    1 <= damage[i], requirement[i] <= 10^4

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 48.15% */
/* Space Beats: 83.33% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    long long totalScore(int hp, vector<int>& damage, vector<int>& requirement)
    {
        const int N = damage.size();
        long long result = 0LL;

        vector<long long> prefix_sum_damage(N+1, 0);
        for (int i = 1; i <= N; i++)
            prefix_sum_damage[i] = prefix_sum_damage[i-1] + damage[i-1];


        for (int curr_room = 1; curr_room <= N; curr_room++)
        {
            // health = hp - (prefix_sum_damage[curr_room      ] - 
            //                prefix_sum_damage[start_room - 1]);
            //
            // "health" needs to be >= requirement[curr_room]      // (however curr_room needs to be (curr_room-1) because of 0-index for requirement)
            //
            //                                                                    health  >= requirement[curr_room]
            // (hp - (prefix_sum_damaage[curr_room] - prefix_sum_damage[start_room - 1])) >= requirement[curr_room]
            //
            // if we're going to get a point for "curr_room" by starting at start_room, then we're going to get a point by starting at ANY
            // other SUBSEQUENT start_room, i.e. [start_room+1, start_room+2, ... curr_room]]
            //
            // because starting at a LATER start_room makes us get LESS damage.
            // so if we're able to get a point for some later room with MORE
            // damage, then we'll CERTAINLY be able to get it getting LESS damage.
            //
            // so we're trying to find the LEFTMOST start_room with which we'll get a point for curr_room
            // and then we add +1 for each of the scores in which it'll get us a point
            //
            //
            // For example:
            //
            // since we need score(1) + score(2) + score(3) + score(4)
            // we'll be trying to to get a point for each of these:
            //
            // score 1: room_1 + room_2 + room_3 + room_4
            // score 2:          room_2 + room_3 + room_4
            // score 3:                   room_3 + room_4
            // score 4:                            room_4
            //
            // As you can see room_4 is included in ALL of the scores. However, maybe we will NOT get a point for it if we start at room_1 or room_2
            // but we WILL if we start at room_3 and room_4.
            //
            // So for each room_X we are trying to find the EARLIEST(i.e. lefmost) score_X in which we'll get a point for it.
            //
            // And that speeds this Solution form O(N^2) down to O(N * logN) beacuse of the BinarySearch, i.e. "lower_bound"(first that is EQUAL or GREATER)
            long long required_prefix = prefix_sum_damage[curr_room] + requirement[curr_room-1] - hp;

            auto rightmost_INVALID_it = lower_bound(prefix_sum_damage.begin(),
                                                    prefix_sum_damage.begin() + curr_room, // w/o including prefix_sum_damage[room]
                                                    required_prefix);

            int rightmost_INVALID_start_room = rightmost_INVALID_it - prefix_sum_damage.begin();


            // now (curr_room - rightmost_INVALID_start_room) will get us the
            // number of scores for which curr_room will get us a point
            //
            // Therefore we add +1 for each score in which curr_rom gets us a
            // point
            //
            // and there are exactly (curr_room - rightmost_INVALID_start_room)
            // such scores
            result += curr_room - rightmost_INVALID_start_room;
        }

        return result;
    }
};
