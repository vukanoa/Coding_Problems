/*
    ============
    === EASY ===
    ============

    ===============================
    717) 1-bit and 2-bit characters
    ===============================

    ============
    Description:
    ============

    We have two special characters:

        + The first character can be represented by one bit 0.
        + The second character can be represented by two bits (10 or 11).

    Given a binary array bits that ends with 0, return true if the last
    character must be a one-bit character.

    ====================================================
    FUNCTION: bool isOneBitCharacter(vector<int>& bits);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: bits = [1,0,0]
    Output: true
    Explanation: The only way to decode it is two-bit character and one-bit
                 character. So the last character is one-bit character.

    --- Example 2 ---
    Input: bits = [1,1,1,0]
    Output: false
    Explanation: The only way to decode it is two-bit character and two-bit
                 character. So the last character is not one-bit character.


    *** Constraints ***
    1 <= bits.length <= 1000
    bits[i] is either 0 or 1.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  39.33% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    bool isOneBitCharacter(vector<int>& bits)
    {
        const int N = bits.size();

        vector<bool> dp(N+1, false);
        dp[N-1] = true;

        for (int i = N-2; i >= 0; i--)
        {
            if (bits[i] == 1)
                dp[i] = dp[i+2];
            else
                dp[i] = dp[i+1];
        }

        return dp[0];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  70.38% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    bool isOneBitCharacter(vector<int>& bits)
    {
        const int N = bits.size();

        bool nextnext = false;
        bool next     = true;

        for (int i = N-2; i >= 0; i--)
        {
            bool curr = false;
            if (bits[i] == 1)
                curr = nextnext;
            else
                curr = next;

            nextnext = next;
            next     = curr;
        }

        return next;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  39.33% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_3 {
public:
    bool isOneBitCharacter(vector<int>& bits)
    {
        const int N = bits.size();

        int i = N - 2;
        while (i >= 0 && bits[i] > 0)
            i--;

        return (N - i) % 2 == 0;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  70.38% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_4 {
public:
    bool isOneBitCharacter(vector<int>& bits)
    {
        const int N = bits.size();

        int ones = 0;

        for (int i = N-2; i >= 0 && bits[i] != 0 ; i--)
            ones++;

        return ones % 2 == 0;
    }
};
