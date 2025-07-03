/*
    ============
    === EASY ===
    ============

    ==============================================
    3304) Find The K-th Character in String Game I
    ==============================================

    ============
    Description:
    ============

    Alice and Bob are playing a game. Initially, Alice has a string word = "a".

    You are given a positive integer k.

    Now Bob will ask Alice to perform the following operation forever:

        Generate a new string by changing each character in word to its next
        character in the English alphabet, and append it to the original word.

    For example, performing the operation on "c" generates "cd" and performing
    the operation on "zb" generates "zbac".

    Return the value of the kth character in word, after enough operations have
    been done for word to have at least k characters.

    =====
    Note: that the character 'z' can be changed to 'a' in the operation.
    =====

    ===================================
    FUNCTION: char kthCharacter(int k);
    ===================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: k = 5
    Output: "b"
    Explanation:
    Initially, word = "a". We need to do the operation three times:
        Generated string is "b", word becomes "ab".
        Generated string is "bc", word becomes "abbc".
        Generated string is "bccd", word becomes "abbcbccd".


    --- Example 2 ---
    Input: k = 10
    Output: "c"


    *** Constraints ***
    1 <= k <= 500

*/

#include <sstream>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    There isn't anything to know here, just code what you're told. However, be
    careful with this line:

        out << static_cast<char>(((chr - 'a' + 1) % 26) + 'a');

    Make sure you understand it well.

    first we subtract 'a' from our "chr", that way we get a number from [0, 25]
    inclusively. Now we need the next character in the alphabet, however if it
    is letter 'z' then we need to wrap around. We do that by using MODULO 26,
    becase there are 26 letters in the English alphabet.

    Then once we're done with that we have the number from [0, 25] of this new
    character, and now we need to add 'a'(i.e. 97 because of ASCII) to it and
    convert it back to "char" type.

    Once we've done that, push that to "out". Do this for all current letters
    in "word" and append those at the end.

    Once we have a word of size greater than or equal to k, we return word[k-1]
    because indexing starts with 0.

*/

/* Time  Beats: 56.73% */
/* Space Beats:  6.49% */

/* Time  Complexity: O(k) */
/* Space Complexity: O(k)   */
class Solution {
public:
    char kthCharacter(int k)
    {
        if (k == 1)
            return 'a';

        string str = "a";
        while (str.length() < k)
        {
            ostringstream out;

            for (const char& chr : str)
                out << static_cast<char>(((chr - 'a' + 1) % 26) + 'a');

            str += out.str();
        }

        return str[k-1];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    __lg is a GCC/Clang built-in function that computes the base-2 logarithm of
    an integer, returning the largest integer x such that 2^x <= n.

    __lg(1) = 0     // 2^0 = 1
    __lg(2) = 1     // 2^1 = 2
    __lg(3) = 1     // 2^1 = 2 (largest power of 2 ≤ 3)
    __lg(4) = 2     // 2^2 = 4
    __lg(5) = 2     // 2^2 = 4
    __lg(8) = 3     // 2^3 = 8
    ...


    It's EQUIVALENT to:
        int log_value = static_cast<int>(log2(n));

    but __lg is faster and doesn't use floating-point math.


    It is undefined for n = 0 — just like log(0) is undefined.

    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    !!! This is compiler-specific but works in both GCC and Clang !!!
    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


    A portable alternative would be:

        int floor_log2(int n)
        {
            int result = 0;
            while (n >>= 1)
                result++;

            return result;
        }

*/

/* Time  Complexity: O(logK) */
/* Space Complexity: O(1)    */
class Solution_Optimized {
public:
    char kthCharacter(int k)
    {
        int character_shift_count = 0;
        int highest_power_of_two_exponent;

        while (k != 1)
        {
            highest_power_of_two_exponent = __lg(k);

            if ((1 << highest_power_of_two_exponent) == k)
            {
                highest_power_of_two_exponent--;
            }

            k = k - (1 << highest_power_of_two_exponent);
            character_shift_count++;
        }

        return 'a' + character_shift_count;
    }
};
