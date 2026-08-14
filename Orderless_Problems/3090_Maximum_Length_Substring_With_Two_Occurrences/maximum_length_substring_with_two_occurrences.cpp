/*
    ============
    === EASY ===
    ============

    ===================================================
    3090) Maximum Length Substring With Two Occurrences
    ===================================================

    ============
    Description:
    ============

    Given a string s, return the maximum length of a  such that it contains at
    most two occurrences of each character.

    ===============================================
    FUNCTION: int maximumLengthSubstring(string s);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "bcbbbcba"
    Output: 4
    Explanation: The following substring has a length of 4 and contains at most
                 two occurrences of each character: "bcbbbcba".

    --- Example 2 ---
    Input: s = "aaaa"
    Output: 2
    Explanation: The following substring has a length of 2 and contains at most
                 two occurrences of each character: "aaaa".


    *** Constraints ***
    2 <= s.length <= 100
    s consists only of lowercase English letters.

*/

#include <cstdint>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explantory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  77.33% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maximumLengthSubstring(string s)
    {
        const int N = s.size();
        int result = 0;

        int freq[26] = {0}; // On the Stack

        int L = 0;
        int R = 0;
        while (R < N)
        {
            ++freq[s[R] - 'a'];

            while (freq[s[R] - 'a'] > 2)
            {
                --freq[s[L] - 'a'];

                // Increment
                ++L;
            }

            result = max(result, R - L + 1);

            // Incrment
            ++R;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is a small "trick" with indexing both lowercase and upperase English
    letters.



    Both 'a' = 97 and 'A' = 65 will result in 1 when we BITIWSE AND with 31.
    Then we just subtract by 1 and voila, we get 0-based indexing.

    ---------------------
    --- lowercase 'a' ---
    ---------------------

        97 = 0110 0001
        31 = 0001 1111  & (Bitwise AND)
       ---------------
         1 = 0000 0001
         1 = 0000 0001  - (Minus)
       ---------------
         0 = 0000 0000  <-- Final index of of: 'a' = 97


    ---------------------
    --- uppercase 'A' ---
    ---------------------

        64 = 0100 0001
        31 = 0001 1111  & (Bitwise AND)
       ---------------
         1 = 0000 0001
         1 = 0000 0001  - (Minus)
       ---------------
         0 = 0000 0000  <-- Final index of of: 'A' = 65



    Now:
        + both 'A' and 'a' will be indexed at 0.
        + both 'B' and 'b' will be indexed at 1.
        + ...
        + both 'Y' and 'y' will be indexed at 24
        + both 'Z' and 'z' will be indexed at 25.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  77.33% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Bit_Trick {
public:
    int maximumLengthSubstring(string s)
    {
        const int N = s.size();
        int result = 0;

        int freq[26] = {0}; // On the Stack

        int L = 0;
        int R = 0;
        while (R < N)
        {
            ++freq[(s[R] & 31) - 1];

            while (freq[(s[R] & 31) - 1] > 2)
            {
                --freq[(s[L] & 31) - 1];

                // Increment
                ++L;
            }

            result = max(result, R - L + 1);

            // Incrment
            ++R;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Since each character appears at most twice, only 2 bits are needed to store
    the frequency of one character.

    For all 26 lowercase letters, then 26 * 2 = 52 bits are enough.

    Therefore, the entire frequency table can be stored inside a single 64-bit
    integer.

    Each character is assigned 2-bits:

        letter     starting bit     two-bit slot

        a              0             [1][0]
        b              2             [3][2]
        c              4             [5][4]
        d              6             [7][6]
        ...
        z             50            [51][50]



            50th LSB      6th   3rd LSB (Least Significant Bit)
               |           |     |
               |           |     |
               v           v     v
        00 .. 00 00 00 .. 00 00 00 00
               z  y  x     d  c  b  a


    But why two bits?
    Because we're storing the count of each character:

        00  -->  0
        01  -->  1
        10  -->  2
        11  -->  3


    Therefore, we first determine the bit_pos of the current character and then
    we do:

        mask += 1ULL << bit_pos;

    which effectivelly does:

        ++freq[character];

    However, instead of having (int freq[26] = {0}), we're uinsg a uint64_t.

    So when we do:

        mask += 1ULL << bit_pos;

    It's adding a 1 to the corresponding bit position.

        01
        01 + (Plus)
        --
        10


    Then if we want to check whether at position (2 bits) for that character,
    i.e. the FREQUENCY of this character is 3, we have to right SHIFT by
    bit_pos and then simply BITIWSE AND with 3(i.e. with 0x11).

    If both bits for that character are SET, then that means this character
    appears 3 times, which is forbidden.

    THerefore we're inside this while loop until it comes back down to freq of
    2.


    Subtracting this does the reverse:

        mask -= 1ULL << (((s[L] & 31) - 1) << 1);

    It's as if we wrote:

        --freq[character];

*/

/* Time  Beats: 100.00% */
/* Space Beats:  87.78% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Bit_Manipulation {
public:
    int maximumLengthSubstring(string s)
    {
        const int N = s.size();
        int result = 0;

        uint64_t mask = 0;
        
        int L = 0;
        int R = 0;
        while (R < N)
        {
            int bit_pos = ((s[R] & 31) - 1) << 1;
            mask += 1ULL << bit_pos;
            
            while (((mask >> bit_pos) & 3) == 3) // (...  &  0x11)  ==  0x11
            {
                mask -= 1ULL << (((s[L] & 31) - 1) << 1);

                // Increment
                ++L;
            }
                
            result = max(result, R - L + 1);

            // Increment
            ++R;
        }
        
        return result;
    }
};
