#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    =========================================================
    1963) Minimum Number of Swaps to Make the String Balanced
    =========================================================

    ============
    Description:
    ============

    You are given a 0-indexed string s of even length n. The string consists of
    exactly n / 2 opening brackets '[' and n / 2 closing brackets ']'.

    A string is called balanced if and only if:

        It is the empty string, or
        It can be written as AB, where both A and B are balanced strings, or
        It can be written as [C], where C is a balanced string.

    You may swap the brackets at any two indices any number of times.

    Return the minimum number of swaps to make s balanced.

    =================================
    FUNCTION: int minSwaps(string s);
    =================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "][]["
    Output: 1
    Explanation: You can make the string balanced by swapping index 0 with
    index 3.  The resulting string is "[[]]".


    --- Example 2 ---
    Input: s = "]]][[["
    Output: 2
    Explanation: You can do the following to make the string balanced:
    - Swap index 0 with index 4. s = "[]][][".
    - Swap index 1 with index 5. s = "[[][]]".
    The resulting string is "[[][]]".


    --- Example 3 ---
    Input: s = "[]"
    Output: 0
    Explanation: The string is already balanced.



    *** Constraints ***
    n == s.length
    2 <= n <= 106
    n is even.
    s[i] is either '[' or ']'.
    The number of opening brackets '[' equals n / 2, and the number of closing
    brackets ']' equals n / 2.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Count how many of the opened brackets are not closed. At the end all we
    have to do is std::ceil(open / 2.0);

    But why does that work?
    It's not very intuitive, but if you try to "invent" 10 or more examples, it
    becomes kind of obivous how many time and which brackets you have to swap.

    Consider these: (I'm going to use angle brackets. Easier to distinguish)
    > > > > > < < < < <
    0 1 2 3 4 5 6 7 8 9

    If you wanted to manually swap these to make them valid, what is the least
    amount of swaps?
    Try different approaches and ask yourself what does that work.

    One maybe thinks that we should just swap going from outer, so:
    0-th with 9-th
    1-st with 8-th
    ...

    However, that would take a total of 5 swaps, whih is definitely NOT the
    most optimal.

    But, what IS the most optimal way?
    The most optimal number of swaps is 3.

    Swap 4-th with 5-th
    Swap 2-nd with 7-th
    Swap 0-th with 9-th

    Do you see the pattern?

    Let's check an easier, but similar, example:
    > > > < < <
    0 1 2 3 4 5

    Are 3 swaps the most optimal number of swaps? No.
    We can achieve validity of this string with only 2 swaps.

    Swap 2-nd with 3-rd
    Swap 0-th with 5-th

    Do you see it now?

    Let's try again.

    < > > > < > < <
    0 1 2 3 4 5 6 7

    Since 0-th and 1-st form a valid string and 4-th and 5-th as well, it's
    as if we had this:
    > > < <
    0 1 2 3

    What is the most optimal amount of swaps?
    It's 2. we cannot do better.

    Okay, if you haven't figured it out, don't feel bad, let me explain:

    Whenever we have odd number of invalid opened/closed brackets, we don't
    have to have that same odd number of swaps, but rather ceil(odd / 2) swaps.

    However, if we had an even number of invalid brackets, then we only need:
    even / 2 swaps.

    As you could see:

    > > < <            2 invalid opened brackets, hence: 2/2 swaps.
    0 1 2 3

    or

    > > > > < < < <
    0 1 2 3 4 5 6 7    4 invalid opened brackets, hence: 4/2 swaps.



    However, if we had an odd number of invalid opened/closed brackets:

    > <                  1 invalid opened bracket, hence:  ceil(1 / 2.0) swaps
    0 1

    or

    > > > < < <          3 invalid opened brackets, hence: ceil(3 / 2.0) swaps
    0 1 2 3 4 5

    or

    > > > > > < < < < <  5 invalid opened brackets, hence: ceil(5 / 2.0) swaps
    0 1 2 3 4 5 6 7 8 9

*/


/* Time  Beats: 95.14% */
/* Space Beats: 41.04% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Open_Counting {
public:
    int minSwaps(std::string s)
    {
        int open = 0;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == ']')
            {
                if (open > 0)
                    open--;
            }
            else
                open++;
        }

        return (int) std::ceil(open / 2.0);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Virtualy the same IDEA, however if we want to count extra closed brackets,
    then we have to remember maximum amount of invalid, closed brackets at
    any point.

    It's a different implementation, but some people might find this one easier
    to read and grasp.

    I prefer this one.

*/

/* Time  Beats: 96.23% */
/* Space Beats: 45.39% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Extra_Close {
public:
    int minSwaps(std::string s)
    {
        int extra_close = 0;
        int max = 0; // Maximum at any given point

        for (char& chr : s)
        {
            if (chr == ']')
                extra_close++;
            else
                extra_close--;

            max = std::max(max, extra_close);
        }

        return static_cast<int>((max + 1) / 2.0);
    }
};
