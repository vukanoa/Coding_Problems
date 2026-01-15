/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    881) Boats To Save People
    ===========================

    ============
    Description:
    ============

    You are given an array people where people[i] is the weight of the ith
    person, and an infinite number of boats where each boat can carry a maximum
    weight of limit. Each boat carries at most two people at the same time,
    provided the sum of the weight of those people is at most limit.

    Return the minimum number of boats to carry every given person.

    =============================================================
    FUNCTION: int numRescueBoats(vector<int>& people, int limit);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: people = [1,2], limit = 3
    Output: 1
    Explanation: 1 boat (1, 2)


    --- Example 2 ---
    Input: people = [3,2,2,1], limit = 3
    Output: 3
    Explanation: 3 boats (1, 2), (2) and (3)


    --- Example 3 ---
    Input: people = [3,5,3,4], limit = 5
    Output: 4
    Explanation: 4 boats (3), (3), (4), (5)


    *** Constraints ***
    1 <= people.length <= 5 * 10^4
    1 <= people[i] <= limit <= 3 * 10^4

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Read carefully: "AT MOST two people".

    Simply put the heaviest one immediately and then see if you can fit the
    lightest one that is not in any boat yet.

    In order to make "picking" heavieast and lightest first, we must sort the
    input vector.

*/

/* Time  Beats: 95.17% */
/* Space Beats: 15.56% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(logN)     */ // C++'s Intro Sort
class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit)
    {
        const int N = people.size();
        int boats = 0;

        /* Sort */
        sort(people.begin(), people.end());

        int L = 0;
        int R = N-1;
        while (L <= R)
        {
            if (people[L] + people[R] <= limit)
                L++;

            R--; // This is ALWAYS done since: people[i] <= limit
            boats++;
        }

        return boats;
    }
};
