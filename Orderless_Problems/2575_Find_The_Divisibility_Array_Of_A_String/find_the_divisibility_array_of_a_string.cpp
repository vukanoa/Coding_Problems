/*
    ==============
    === MEDIUM ===
    ==============

    ==============================================
    2575) Find the Divisibility String of a String
    ==============================================

    ============
    Description:
    ============

    You are given a 0-indexed string word of length n consisting of digits,
    and a positive integer m.

    The divisibility array div of word is an integer array of length n such
    that:

        + div[i] = 1 if the numeric value of word[0,...,i] is divisible by m,

              or

        + div[i] = 0 otherwise.

    Return the divisibility array of word.

    ============================================================
    FUNCTION: vector<int> divisibilityArray(string word, int m);
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: word = "998244353", m = 3
    Output: [1,1,0,0,0,1,1,0,0]
    Explanation: There are only 4 prefixes that are divisible by 3:
                 "9", "99", "998244", and "9982443".

    --- Example 2 ---
    Input: word = "1010", m = 10
    Output: [0,1,0,1]
    Explanation: There are only 2 prefixes that are divisible by 10: "10",
                 and "1010".


    *** Constraints ***
    1 <= n <= 10^5
    word.length == n
    word consists of digits from 0 to 9
    1 <= m <= 10^9

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The crux of this Solution is to realize that you CANNOT keep multiplying
    by 10 and adding every new digit and then if it's divisible by 'm', then
    you put a 1 in "answer".

    You must understand why you can't do that.
    You can't do that because of the given Constraints.

        word.length() is up to 10^5

    which means that it can be a number that has up to 10^5 DIGITS. That is
    waaaay past any data type.

    For reference, GCC and Clang have a way of delcaring a 128 bit number.
    For exmaple:

        unsigned __int128 = ...;

    But even 2^256 has only 78 digits!

    So how in the world are you going to work with such big numbers?



    The answer is -- You can't
    However, the Solution is to realize that you don't have to.

    since we're ALWAYS only and I mean ONLY interested in checking if the given
    number is divisible by 'm', it's really totally equivalent whether you
    try to check with:
        1. some huge number or
        2. with that huge numbers's mod m.

    For example:

        8244 is divisible by 3

    However, we don't have to add 4 digits in order to know that. We can simply
    mod by 3 each time we add a number number.

    That way instead of trying to check 8244, we check 0.


    Each time we add a digit, we mod because mod won't mess up with our
    calculations.

    Once you notice -- It's game over, you've won.

*/

/* Time  Beats: 19.62% */
/* Space Beats: 30.70% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */ // or O(1) since "result" is not "extra space".
class Solution {
public:
    vector<int> divisibilityArray(string word, int m)
    {
        const int N = word.length();
        vector<int> result;

        long long value = 0LL;
        for (int i = 0; i < N; i++)
        {
            char digit = word[i];

            value *= 10LL;
            value %= m;
            value += digit - '0';
            value %= m;

            if (value % m == 0)
                result.push_back(1);
            else
                result.push_back(0);

            value %= m;
        }

        return result;
    }
};
