/*
    ==============
    === MEDIUM ===
    ==============

    ===============================
    825) Friend of Appropriate Ages
    ===============================

    ============
    Description:
    ============

    There are n persons on a social media website. You are given an integer
    array ages where ages[i] is the age of the ith person.

    A Person x will not send a friend request to a person y (x != y) if any of
    the following conditions is true:

        age[y] <= 0.5 * age[x] + 7
        age[y] > age[x]
        age[y] > 100 && age[x] < 100

    Otherwise, x will send a friend request to y.

    Note that if x sends a request to y, y will not necessarily send a request
    to x. Also, a person will not send a friend request to themself.

    Return the total number of friend requests made.

    ===================================================
    FUNCTION: int numFriendRequests(vector<int>& ages);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: ages = [16,16]
    Output: 2
    Explanation: 2 people friend request each other.

    --- Example 2 ---
    Input: ages = [16,17,18]
    Output: 2
    Explanation: Friend requests are made 17 -> 16, 18 -> 17.

    --- Example 3 ---
    Input: ages = [20,30,100,110,120]
    Output: 3
    Explanation: Friend requests are made 110 -> 100, 120 -> 110, 120 -> 100.


    *** Constraints ***
    n == ages.length
    1 <= n <= 2 * 10^4
    1 <= ages[i] <= 120

*/

#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 55.61% */
/* Space Beats: 14.97% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N)   */
class Solution {
public:
    int numFriendRequests(vector<int>& ages)
    {
        int result = 0;
        unordered_map<int, int> freq;

        for (const int& age : ages)
            freq[age]++;

        for (const auto& x : freq)
        {
            for (const auto& y : freq)
            {
                if (request(x.first, y.first))
                    result += x.second * (y.second - (x.first == y.first ? 1 : 0));
            }
        }

        return result;
    }

    bool request(int x, int y)
    {
        return ! (y <= 0.5 * x + 7 || y > x || (y > 100 && x < 100));
    }
};
