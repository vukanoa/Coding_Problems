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
    once it gets to the point of being of that, fixed, given size k.

    Let's consider an example:

                    0 1 2 3 4 5 6 7 8
        Input: s = "a b c i i i d e f", k = 3

    We'll assign "L"(left) and "R"(right) pointers to point at index 0,
    initially.

             0 1 2 3 4 5 6 7 8
        s = "a b c i i i d e f", k = 3
             L
             R

    If s[R] is the vowel, increment variable "vowels".

    However, we are asked to find:
        "maximum number of vowel letters in any substring of with length k."

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

                            0 1 2 3 4 5 6 7 8
                       s = "a b c i i i d e f", k = 3

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

    The Idea is almost equivalent to the one above, but it's written in a bit
    different way.

    I wanted to have both imlementations here in case someone finds this one
    easier to grasp.

    Here we, at the beginning of each iteration, increment "vowels" if S[R] is
    a vowel, however, if we find out that the window_len is equal to k we
    immediately calculate if this number of vowels is the new maximum within a
    window of size k and we shrink the left boundary, decrementing if necessary
    of course.

    At the end of each iteration we move "right" pointer by one, always.

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

    Pretty much the same as both Solutions above. However this one doesn't use:
    1. if (window_len > k), nor
    2. if (window_len == k)

    It uses a third variation to check a similar thing.

    if the current character index minus the length k is still within the
    string s(i.e. it's NOT out of bounds), then it means that we've exceeded
    the size k of our window which further suggests that we should get right of
    the leftmost element within the current window.

    We decrement conditionally with this line:
        vowels -= uset.find(s[i - k]) != uset.end() ? 1 : 0;

    In other words: If a leftmost character within this window, of size k+1, is
    a vowel, decrement total number of vowels.

    At the end of each iteration, calculate if this number of vowels in the
    window is the new maximum.

    At the end, return varible "max_vowels".

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

    At first glance these numbers seem as "magic numbers".

    Where did they come from?
    Let's write down all 5 vowels in: Decimal, binary and hexadecimal

    ********************** ASCII values of vowels ****************************

        | Decimal  |  Binary   | Hexa |
        +----------+-----------+------+
    'a' |    97    | 0110 0001 |  61  |
        +----------+-----------+------+
    'e' |   101    | 0110 0101 |  65  |
        +----------+-----------+------+
    'i' |   105    | 0110 1001 |  69  |
        +----------+-----------+------+
    'o' |   111    | 0110 1111 |  6F  |
        +----------+-----------+------+
    'u' |   117    | 0111 0101 |  75  |
        +----------+-^^^-------+------+
                      |
                      ---------------------------------
                                                      |
    Now we can notice something. We can notice that these 3 bits(MSb - Most
    Significant bits) in each Byte(8 bits) are exactly the same. Since that is
    the case we can ignore them.

    Let's, again, write this table, but without those 3 bits.

        | Decimal  |  Binary   | Hexa |
        +----------+-----------+------+
    'a' |    97    |  0 0001   |   1  |
        +----------+-----------+------+
    'e' |   101    |  0 0101   |   5  |
        +----------+-----------+------+
    'i' |   105    |  0 1001   |   9  |
        +----------+-----------+------+
    'o' |   111    |  0 1111   |   F  |
        +----------+-----------+------+
    'u' |   117    |  1 0101   |  21  |
        +----------+-----------+------+

    Since we need only first 5 bits(5 LSb - Least Significant bits), we need to
    somehow "cut" 3 MSb(Most Significan bits).

    How are we going to do that?

    By using Bitwise operation called "AND". We're going to AND the original
    ASCII calues of these characters and "AND" it with 0x1F.

    Why with 0x1F?
    Let's write it down:

       Hexa      Binary
        1F   =  0001 1111

    So, if we take, say, letter 'e' and we "AND" it with 0x1F, we get this:

            0110 0101 // 0x65, aka 'e'
       AND  0001 1111 // 0x1F
       --------------
            0000 0101 // 0x05

       0000 0101 is equal to 5 in Decimal.

    Okay, now we have this:

        | Decimal  |  Binary   | Hexa |
        +----------+-----------+------+
    'a' |    97    |  0 0001   |   1  |
        +----------+-----------+------+
    'e' |   101    |  0 0101   |   5  |
        +----------+-----------+------+
    'i' |   105    |  0 1001   |   9  |
        +----------+-----------+------+
    'o' |   111    |  0 1111   |   F  |
        +----------+-----------+------+
    'u' |   117    |  1 0101   |  21  |
        +----------+-----------+------+

    How can this help us determine if some letters is a vowel or not?
    First, we need to "notice" that there are a total of 5 vowels.

    Let's say we want to check if a letter 'i' is a vowel or not.

    We'll take it's ASCII value and "AND" it with 0x1F, as we previously
    explained why.

            0110 1001 // 0x69, aka 'i'
       AND  0001 1111 // 0x1F
       --------------
            0000 1001 // 0x09

       0000 1001 is equal to 9 in Decimal.

    So now we are left with a value of 9. How can that help us to determine if
    it's a vowel or not?

    Let's mention again that we should keep in mind there are a total of 5
    vowels, but for now, let's just focus on vowel 'i'.

    We'll need a "mask" that we can SHIFT to the right by certain amount of
    time in order to confirm it's a letter 'i'.

    After AND-ing with 0x1F, Hexa value of 'i' is now 0x09.

    So we need a Mask that if we SHIFT 9 times to the right, we get an
    indicator that confirms it's an 'i' character.

    Let me show you successful and unsuccessful examples and it will be much
    more clear:

        Mask = 0010 0000 0000 // 1 is at 10-th LSb.

        ----------------------------------------------------------------------
        --------------------- SUCCESSFUL: (char c = 'i') ---------------------
        ----------------------------------------------------------------------

                                ASCII 'i' = 105

            orig_'i' = 0110 1001 // Original ASCII value of 'i' in Binary

            Now we "AND" 'i' with 0x1F and we get:

            new__'i' = 0000 1001 // We get 9 in Decimal


            We SHIFT our Mask to the right by new__'i'

                Mask >> (new__'i')

                0010 0000 0000 >> 9   ====>  0000 0000 0001


            In order to check if the character we passed is a vowel, we now
            just need to check if the LSb(Least Significant bit) is 1.

            How are we going to check if the LSb is 1?

            By "AND"-ing with 0x1

                0000 0000 0001 // Leftover of Mask >> new__'i'
            AND 0000 0000 0001 // 0x1
            ------------------
                0000 0000 0001 // 0x1

            Since the result of the last "AND" is 0x1, we know that passed
            character c was INDEED a character 'i'.


        ----------------------------------------------------------------------
        -------------------- UNSUCCESSFUL: (char c = 'g') --------------------
        ----------------------------------------------------------------------

                                ASCII 'g' = 103

            orig_'g' = 0110 0111 // Original ASCII value of 'g' in Binary

            Now we "AND" 'g' with 0x1F and we get:

            new__'g' = 0000 0111 // We get 7 in Decimal

                Mask >> (new__'g')

                0010 0000 0000 >> 7   ====>  0000 0000 0100


            In order to check if the character we passed is a vowel, we now
            just need to check if the LSb(Least Significant bit) is 1.

            How are we going to check if the LSb is 1?

            By "AND"-ing with 0x1

                0000 0000 0100 // Leftover of Mask >> new__'g'
            AND 0000 0000 0001 // 0x1
            ------------------
                0000 0000 0000 // 0x0

            Since the result of the last "AND" is NOT 0x1, we know that passed
            character c was NOT a character 'i'.



    The only different thing we do in this whole problem is - We don't only
    check if a passed character c is a character 'i', but we want to check if
    it is any of the vowels.

    Therefore, our Mask won't only be so that we can only check for letters 'i'
    but all 5 of the vowels.

    Howe are we going to do that?

    I don't know if you've notice, but in our example where we were checking if
    passed character c is a letter 'i', we've had a mask have a bit 1 at 10th
    LSb.

    Why exactly 10th?

    Because ASCII letter 'i' "AND"-ed with 0x1F gives us a 0x09

    Therefore, we need to put a bit 1 at "0x09 + 1"-th LSb position.

    Since we have our table:

        | Decimal  |  Binary   | Hexa |
        +----------+-----------+------+
    'a' |    97    |  0 0001   |   1  |  // 0x1  + 0x1 =  0x2  = 2nd LSb
        +----------+-----------+------+
    'e' |   101    |  0 0101   |   5  |  // 0x5  + 0x1 =  0x6  = 6th LSb
        +----------+-----------+------+
    'i' |   105    |  0 1001   |   9  |  // 0x9  + 0x1 =  0xA  = 10th LSb
        +----------+-----------+------+
    'o' |   111    |  0 1111   |   F  |  // 0xF  + 0x1 =  0x10 = 16th LSb
        +----------+-----------+------+
    'u' |   117    |  1 0101   |  15  |  // 0x15 + 0x1 =  0x16 = 22th LSb
        +----------+-----------+------+

    Our Mask will have 1 at bits(counting from LSb): 2, 6, 10, 16, 22

    MSb
     |
     |      0  1  0  0    0  0  0  1     0  0  0  0    0  1  0  0
     ----> 23 22 21 20   19 18 17 16    15 14 13 12   11 10  9  8

            0  6  0  0    0  2  0  0
            7  6  5  4    3  2  1  0 <------------------------
                                                             |
                                                             |
                                                            LSb

    Or written concisely:

    Mask = 0010 0000   1000 0010   0010 0010 // Binary
    Mask =  2    0       8   2      2    2

    Mask =   0x20         0x82        0x22

    Mask = 0x208222


    If passed character c is one of the vowels('a', 'e', 'i', 'o', 'u') then
    after SHIFTING we'll get 0x1, i.e. LSb will be 1.

    Otherwise, it won't.

    That's how we know if it is a vowel or not.

    Everything else is similar to other Solutions.
    Computers are much better at performing bitwise operations.

*/

/* Time  Beats: 98.58% */
/* Space Beats: 72.36% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution{
public:
    int maxVowels(std::string s, int k)
    {
        auto is_vowel = [](char ascii_character_value)
        {
            static const uint32_t mask     = 0x208222;
            static const uint8_t  five_LSb = 0x1f; // 5 Least Significant bits
            static const uint8_t  one      = 0x1;

            return (mask >> (ascii_character_value & five_LSb)) & one;
        };

        int result = 0;
        int vowels = 0;

        int right = 0;
        int left  = right - k; // Negative value initially, i.e. out of bounds

        while (right < s.length())
        {
            vowels += is_vowel(s[right]);

            if (right >= k)
                vowels -= is_vowel(s[left]);

            result = std::max(result, vowels);

            left++;
            right++;
        }

        return result;
    };
};
