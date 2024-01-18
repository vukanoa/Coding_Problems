#include <iostream>
#include <unordered_set>

/*
    ==============
    === MEDIUM ===
    ==============

    =============================================================
    1456) Maximum Number of Vowels in a Substring of Given Length
    =============================================================

    ============
    Description:
    ============

    Given a string s and an integer k, return the maximum number of vowel
    letters in any substring of s with length k.

    Vowel letters in English are 'a', 'e', 'i', 'o', and 'u'.

    =========================================
    FUNCTION: int maxVowels(string s, int k);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abciiidef", k = 3
    Output: 3
    Explanation: The substring "iii" contains 3 vowel letters.

    --- Example 2 ---
    Input: s = "aeiou", k = 2
    Output: 2
    Explanation: Any substring of length 2 contains 2 vowels.

    --- Example 3 ---
    Input: s = "leetcode", k = 3
    Output: 2
    Explanation: "lee", "eet" and "ode" contain 2 vowels.


    *** Constraints ***
    1 <= s.length <= 10^5
    s consists of lowercase English letters.
    1 <= k <= s.length

*/

/*
    ------------
    --- IDEA ---
    ------------

    This is the simplest Sliding Window problem there is. The window is fixed
    once it gets to the point of being of that, fixed given, size.

    Let's consider an example:

        Input: s = "abciiidef", k = 3

    We'll assign "L"(left) and "R"(right) pointers to point at index 0,
    initially.

        s = "abciiidef", k = 3
             L
             R

    If s[R] is the vowel, increment variable "vowels".

    However, we are asked to find:
        "maximum number of vowel letters in any substring of s with length k."

    It's important to emphasize - OF SIZE K.

    That means we DON'T consider windows which are less than size k. That will
    be the case only until the first window gets to size k. Afterwards we move
    both "L" and "R" by one each iteration.

    In other words, we move "R" by one EACH iteration, however we don't start
    moving "L" by one each iteration until "right - left + 1"(aka window_len)
    gets bigger than k.

    Once it's bigger, we'll decrements "vowels" if s[L] was a vowel and we'll
    move "L" by one to the right, since window_len is greater than the limit k.

    Now our window_len is equal k and then we check if this new number of
    vowels in the current window is the new maximum number of vowels we've had
    so far.

    At the end of each iteration we increment "R".

*******************************************************************************
********************************** SIMULATION *********************************
*******************************************************************************

                            Input: s = "abciiidef", k = 3

                            result = 0;
                            vowels = 0;

===============================================================================

    1. R = 0

             0 1 2 3 4 5 6 7 8
        s = "a b c i i i d e f",         k = 3
             L
             R

        if (s[R] is vowel) // It is, 'a' is INDEED a vowel.
            vowels++;

        vowels = 1;
        window_len = R - L + 1 ==> 0 - 0 + 1 ==> 1

        if (window_len > k) // It is not
        if (1 > 3)          // It is not

        result = max(result, vowels) ==> max(0, 1) ==> 1 // New max

===============================================================================

    2. R = 1;

             0 1 2 3 4 5 6 7 8
        s = "a b c i i i d e f",         k = 3
             L R

        if (s[R] is vowel) // It is NOT, 'b' is NOT a vowel.

        vowels = 1; // Remains 1
        window_len = R - L + 1 ==> 1 - 0 + 1 ==> 2

        if (window_len > k) // It is not
        if (2 > 3)          // It is not

        result = max(result, vowels) ==> max(1, 1) ==> 1 // Remains 1

===============================================================================

    3. R = 2;

             0 1 2 3 4 5 6 7 8
        s = "a b c i i i d e f",         k = 3
             L   R

        if (s[R] is vowel) // It is NOT, 'c' is NOT a vowel.

        vowels = 1; // Remains 1
        window_len = R - L + 1 ==> 2 - 0 + 1 ==> 3

        if (window_len > k) // It is not
        if (3 > 3)          // It is not

        result = max(result, vowels) ==> max(1, 1) ==> 1 // Remains 1

===============================================================================

    4. R = 3;

             0 1 2 3 4 5 6 7 8
        s = "a b c i i i d e f",         k = 3
               L   R

        if (s[R] is vowel) // It is, 'i' is INDEED a vowel.
            vowels++;

        vowels = 2; // Updated(Incremented)
        window_len = R - L + 1 ==> 3 - 0 + 1 ==> 4

        if (window_len > k) // It is
        if (4 > 3)          // It is
        {
            if (s[L] is vowel) // It is, 'a' is INDEED a vowel.
                vowels--;

            L++;
        }

             0 1 2 3 4 5 6 7 8
        s = "a b c i i i d e f",         k = 3
               L     R

        vowels = 1; // Updated(Decremented)

        result = max(result, vowels) ==> max(1, 1) ==> 1 // Remains 1

===============================================================================

    5. R = 4;

             0 1 2 3 4 5 6 7 8
        s = "a b c i i i d e f",         k = 3
               L     R

        if (s[R] is vowel) // It is, 'i' is INDEED a vowel.
            vowels++;

        vowels = 2; // Updated(Incremented)
        window_len = R - L + 1 ==> 4 - 1 + 1 ==> 4

        if (window_len > k) // It is
        if (4 > 3)          // It is
        {
            if (s[L] is vowel) // It is NOT, 'b' is NOT a vowel.

            L++;
        }

             0 1 2 3 4 5 6 7 8
        s = "a b c i i i d e f",         k = 3
                 L   R

        vowels = 2

        result = max(result, vowels) ==> max(1, 2) ==> 2 // New max

===============================================================================

    6. R = 5

             0 1 2 3 4 5 6 7 8
        s = "a b c i i i d e f",         k = 3
                 L     R

        if (s[R] is vowel) // It is, 'i' is INDEED a vowel.
            vowels++;

        vowels = 3; // Updated(Incremented)
        window_len = R - L + 1 ==> 5 - 2 + 1 ==> 4

        if (window_len > k) // It is
        if (4 > 3)          // It is
        {
            if (s[L] is vowel) // It is NOT, 'c' is NOT a vowel.

            L++;
        }

             0 1 2 3 4 5 6 7 8
        s = "a b c i i i d e f",         k = 3
                   L   R

        vowels = 3 // Remains 3

        result = max(result, vowels) ==> max(2, 3) ==> 3 // New Max

===============================================================================

    7. R = 6

             0 1 2 3 4 5 6 7 8
        s = "a b c i i i d e f",         k = 3
                   L     R

        if (s[R] is vowel) // It is NOT , 'd' is NOT a vowel.

        vowels = 3; // Remains 1
        window_len = R - L + 1 ==> 6 - 3 + 1==> 4

        if (window_len > k) // It is
        if (4 > 3)          // It is
        {
            if (s[L] is vowel) // It is INDEED, 'i' is INDEED a vowel.
                vowels--;

            L++;
        }

             0 1 2 3 4 5 6 7 8
        s = "a b c i i i d e f",         k = 3
                     L   R

        vowels = 2 // Updated(Decremented)

        result = max(result, vowels) ==> max(3, 2) ==> 3 // Remains 3

===============================================================================

    8. R = 7

             0 1 2 3 4 5 6 7 8
        s = "a b c i i i d e f",         k = 3
                     L     R

        if (s[R] is vowel) // It is INDEED , 'e' is INDEED a vowel.

        vowels = 3; // Updated(Incremented)
        window_len = R - L + 1 ==> 7 - 4 + 1 ==> 4

        if (window_len > k) // It is
        if (4 > 3)          // It is
        {
            if (s[L] is vowel) // It is INDEED, 'i' is INDEED a vowel.
                vowels--;

            L++;
        }

             0 1 2 3 4 5 6 7 8
        s = "a b c i i i d e f",         k = 3
                       L   R

        vowels = 2 // Updated(Decremented)

        result = max(result, vowels) ==> max(3, 2) ==> 3 // Remains 3

===============================================================================
    8. R = 8

             0 1 2 3 4 5 6 7 8
        s = "a b c i i i d e f",         k = 3
                       L     R

        if (s[R] is vowel) // It is NOT , 'f' is NOT a vowel.

        vowels = 2; // Remains 2
        window_len = R - L + 1 ==> 8 - 5 + 1 ==> 4


        if (window_len > k) // It is
        if (4 > 3)          // It is
        {
            if (s[L] is vowel) // It is INDEED, 'i' is INDEED a vowel.
                vowels--;

            L++;
        }

        vowels = 1 // Updated(Decremented)

        result = max(result, vowels) ==> max(3, 1) ==> 3 // Remains 3

===============================================================================

    At the end, just return "result" variable.

*/

/* Time  Beats: 53.84% */
/* Space Beats: 27.15% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Sliding_Window_1 {
public:
    int maxVowels(string s, int k)
    {
        std::unordered_set<char> uset_vowels = {'a', 'e', 'i', 'o', 'u'};

        int result = 0;
        int vowels = 0;

        int left  = 0;
        int right = 0;

        while (right < s.length())
        {
            if (uset_vowels.count(s[right]))
                vowels++;

            if (right - left + 1 > k)
            {
                if (uset_vowels.count(s[left]))
                    vowels--;

                left++;
            }

            result = std::max(result, vowels);

            right++;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 65.85% */
/* Space Beats: 97.69% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Sliding_Window_2 {
public:
    int max_vowelsVowels(std::string s, int k)
    {
        int max_vowels = 0;
        int vowels = 0;

        int left  = 0;
        int right = 0;

        while (right < s.length())
        {
            if (is_vowel(s[right]))
                vowels++;

            if (right - left + 1 == k)
            {
                max_vowels = std::max_vowels(max_vowels, vowels);

                if (is_vowel(s[left]))
                    vowels--;

                left++;
            }

            right++;
        }

        return max_vowels;
    };

private:
    bool is_vowel(char& c)
    {
        return (c == 'a' ||
                c == 'e' ||
                c == 'i' ||
                c == 'o' ||
                c == 'u');
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Self-Explanatory

*/

/* Time  Beats: 27.51% */
/* Space Beats: 20.93% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maxVowels(std::string s, int k)
    {
        std::unordered_set<char> uset = {'a', 'e', 'i', 'o', 'u'};

        int max_vowels = 0;
        int vowels = 0;
        for (int i = 0; i < s.size(); ++i)
        {
            vowels += uset.find(s[i]) != uset.end() ? 1 : 0;

            if (i - k >= 0)
                vowels -= uset.find(s[i - k]) != uset.end() ? 1 : 0;

            max_vowels = max(max_vowels, vowels);
        }

        return max_vowels;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

    (Same approach, but this uses Bit Mask instead of a Hash Set)

    Computers are much better at performing bitwise operations.

*/

/* Time  Beats: 98.58% */
/* Space Beats: 72.36% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maxVowels(std::string s, int k)
    {
        auto is_vowel = [](char c)
        {
            static const uint32_t b1 = 0x208222;
            static const uint8_t  b2 = 0x1f;
            static const uint8_t  b3 = 0x1;

            return (b1 >> (c & b2)) & b3;
        };

        int max_vowels = 0;
        int vowels = 0;
        for(int i = 0, j = i - k; i < s.size(); ++i, ++j)
        {
            vowels += is_vowel(s[i]);
            if (i >= k)
                vowels -= is_vowel(s[j]);

            max_vowels = max(max_vowels, vowels);
        }

        return max_vowels;
    };
};
