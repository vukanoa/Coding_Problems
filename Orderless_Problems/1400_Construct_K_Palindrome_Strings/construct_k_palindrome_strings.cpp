/*
    ==============
    === MEDIUM ===
    ==============

    ====================================
    1400) Construct K Palindrome Strings
    ====================================

    ============
    Description:
    ============

    Given a string s and an integer k, return true if you can use all the
    characters in s to construct k palindrome strings or false otherwise.

    =============================================
    FUNCTION: bool canConstruct(string s, int k);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "annabelle", k = 2
    Output: true
    Explanation: You can construct two palindromes using all characters in s.
    Some possible constructions "anna" + "elble", "anbna" + "elle", "anellena" + "b"

    --- Example 2 ---
    Input: s = "leetcode", k = 3
    Output: false
    Explanation: It is impossible to construct 3 palindromes using all the characters of s.

    --- Example 3 ---
    Input: s = "true", k = 4
    Output: true
    Explanation: The only possible solution is to put each character in a separate string.


    *** Constraints ***
    1 <= s.length <= 10^5
    s consists of lowercase English letters.
    1 <= k <= 10^5

*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Before we begin explaining anything about this Solution, let's first
    refresh our knowledge about what is a "palindrome".

    Palindrome is a string of one or more characters that reads the same both
    forward and backward.

    A few examples of palindromes:

        1. "abba"       // All characters appear EVEN number of times ('a','b')
        2. "ababa"      // Only ONE character appears ODD number of times ('a')
        3. "abcba"      // Only ONE character appears ODD number of times ('c')
        4. "aba"        // Only ONE character appears ODD number of times ('b')
        5. "aaa"        // Only ONE character appears ODD number of times ('a')
        6. "a"          // Single character

    It's very important to note that a SINGLE character is also a palindrome.
    That is crucial for this problem.

    Next it is also important to notice that it is IMPOSSIBLE to create a
    palindrome using two letters that occurr ODD number of times.

        Example:

            'a': 3
            'c': 1

            caaa  // NOT a palindrome
            acaa  // NOT a palindrome
            aaca  // NOT a palindrome
            aaac  // NOT a palindrome

    To form a palindrome you EITHER need:
        1. ANY number of characters(except 0) that occur EVEN number of times
           and ZERO characters that occur ODD number of times.

           (in other words: ALL characters must occurr EVEN number of times)

               example: "abba", "abccba", ...
                          a:2     a:2
                          b:2     b:2
                                  c:2


        2. ANY number of characters(INCLUDING 0) that occur EVEN number of
           times and a exactly ONE character that occurs ODD number of times.

           (in other words: a maximum of ONE character can occur ODD number of
            times)

               example: "a", "aba", "abcba", ...
                        a:1   a:2     a:2
                              b:1     2:2
                                      c:1


    Now that we know that one thing is easy to be oversee.
    If some character occurrs ODD number of times, let's say:

        str = "aaa"

    At first sight you might think:"We can either make 3 palindromes by using
    each letter once, or we can create 1 palindrome by using all 3 characters
    to create a single palindrome"

    But that would be mistaken. We can create 2 palindromes as well:

        str = "aaa"

            1. "aa"
            2. "a"

    In ODD occurrences, if we REMOVE one letter, now we have EVEN number of
    occurrences. That is imortant to consciously realize.


    Now let's explain how to solve this:

    1.
    First, if the TOTAL amount of characters in s, i.e. the length of string s
    is LESS than 'k', then we immediately return false.

    Why?
    Because if we take the extreme case where each letter is one palindrome,
    we still wouldn't be able to create 'k' palindromes.



    2.
    However, if the TOTAL amount of characters in s, i.e. the length of string
    s is EXACTLY k, then we immediately return true.

    Why?
    Because if we consider each character in s as a palindrome, then we would
    indeed be able to make 'k' palindromes.



    We have to make a vector "counter" which will have 26 cells, each
    representing the occurrence of each character in the alphabet.

    Now here comes the crux of the Solution: We want to go through this vector
    "counter" of 26 elements and count how many ODD and EVEN characters are
    there.
    However, that is NOT enough.

    If we were to only count the number of EVEN and ODD characters, we wouldn't
    be able to correctly solve problems like this:

        Example:

            s = "aaabb",   k = 3

            counter: a b c d e f g h i j k l m n o p q r s t u v w x z y
                     1 1

        We wouldn't be able to know if we can create k=3 palindromes if we
        only obtained information about the number of ODD and EVEN characters.

        In this case, we'd know we have one ODD and one EVEN character.
        But we don't know if there is 1 occurences of that 1 ODD character or
        if that ODD occurrence is 7. Or 9. Or 91, etc.

        Same is true with the EVEN characters. We'd only know there is a single
        character, 'b' in this case, that occurrs EVEN number of times.
        But we don't know the ACTUAL number that it occurrs.
        It could be: 2, or 4 od 16 or 22 or 84. We just don't know.


    Okay, but besides this example, why are the ACTUAL occurences important?
    I'm glad you asked!

    Make sure you get this:

        If we have two characters that occurr ODD number of times, only one of
        each character will be "odd".

        This seems weird, let me repeat that another way.

            "aaa", "bbbbb"
               ^        ^
               |        |
               |________|
                   |
            Only THESE two are ODD. All of the other could be treated as EVEN.

        So, we must know if the number of these ODD characters (one per
        characters that occurr ODD number of times) is GREATER than k.

        If it is, then we must return FALSE.
        Why?

        Because we cannot put these "single" character together. Each of them
        must go into a separate palindrome. So if there are more characters
        like this than 'k', then we cannot createa 'k' palindromes since we
        will have a left-over of characters. The ones we didn't use.



    Once you understand the above explanation, you'll realize that this is the
    only  way that prevents us to create exactly 'k' palindromes, i.e. having
    more than 'k' characters that occur ODD number of times(not the ACTUAL
    occurrences).

    We do NOT care about the number of EVEN occurring characters.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  66.78% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool canConstruct(string s, int k)
    {
        const int N = s.length();

        if (N < k)  return false;
        if (N == k) return true;

        vector<int> counter(26, 0);
        for (const char& chr : s)
            counter[chr - 'a']++;

        int even = 0;
        int odd  = 0;

        for (int i = 0; i < 26; i++)
        {
            if (counter[i] != 0)
            {
                if (counter[i] & 1) // Odd
                    odd++;
            }
        }

        if (odd > k)
            return false;

        return true;
    }
};





/*
    ------------
    --- IDEA ---
    ------------

    Same as above, however this one is implemented using Bit-Manipulation.

    These two lines are the crux of this Implementation:

        for (const char& chr : s)
            odd_counter ^= 1 << (chr - 'a');

    Since an integer is 32-bits or 4B, on 64-bit architectures, we can use
    those as a "counter" of 26.

    However, since we don't care about the ACTUAL number of occurrences of each
    letter, but ONLY about the number of letters that occurr ODD number of
    times, we can use XOR operation to flip the bit at each "index". At the
    end, we can use this GCC built-in function:

        __builtin_popcount(odd_counter)

    To obtain the number of set-bits, i.e. 1s, in this integer odd_counter.


    Let's simulate:

        int odd_counter = 0;

        0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
       31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
                          z  y  x  w  v  u  t  s  r  q  p  o  n  m  l  k  j  i  h  g  f  e  d  c  b  a

    Now let's explain these two crucial lines:

        for (const char& chr : s)
            odd_counter ^= 1 << (chr - 'a');

    We are iterating through each character in string s.

    While we're doing that we're going to flip the corresponding bit in our
    variable odd_counter.

    How does that work?

        chr is the ASCII value of some lowercase english alphabet character.

        chr is [97, 122], inclusivelly.

        chr - 'a' will give us an integer from [0, 25], also inclusivelly,
        where each number reprenents one character from the alphabet.

        0  represents 'a'
        1  represents 'b'
        2  represents 'c'
        ...
        25 represents 'z'


        Now this part:    1 << (chr - 'a')

        means that the set-bit will be shifted to the LEFT the exact number of
        times that the current character represents.

        if it's a character 'c', it will be:

            1 << (99 - 'a')

            1 << (99 - 97)

            1 << (2)

            000..00001 << 2

            000..00100
                   ^
                   |____________
                               |
                               |
                               |
            0  0  0  ..  0  0  1  0  0
            31 30 29 ..  4  3  2  1  0
                         e  d  c  b  a


    This means that character 'c' occurrs ODD number of times. However, if we
    were to stumble upon anoher 'c', we would flip this bit at index 2 again
    and it would be turned to 0, which would mean:"Character 'c' occurrs EVEN
    number of times".


    Since we ONLY care about the number of characters that occurr ODD number of
    times, we ONLY care about the set-bits after we've iterated through entire
    string s.

    That's where out __builtin_popcount() functions comes in. It's is a GCC
    built-in function that returns the total number of set-bits in any given
    number.

    For example:

        __builtin_popcount(5) would return 2.

        Why?
        Let's represents 5 in binary: 0000.000101

        As we can see it only have two 1s, i.e. two set-bits. That's why it is
        returning 2.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  51.75% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_BitManipulation{
public:
    bool canConstruct(string s, int k)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        const int N = s.length();

        if (N < k)  return false;
        if (N == k) return true;

        int odd_counter  = 0;

        for (const char& chr : s)
            odd_counter ^= 1 << (chr - 'a');

        int odd = __builtin_popcount(odd_counter); // How many occurr ODD times

        return odd <= k;
    }
};
