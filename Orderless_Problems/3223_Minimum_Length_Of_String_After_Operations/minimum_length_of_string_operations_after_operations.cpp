/*
    ==============
    === MEDIUM ===
    ==============

    ================================================
    3223) Minimum Lengths of String After Operations
    ================================================

    ============
    Description:
    ============

    You are given a string s.

    You can perform the following process on s any number of times:

        + Choose an index i in the string such that there is at least one
          character to the left of index i that is equal to s[i], and at least
          one character to the right that is also equal to s[i].

        + Delete the closest character to the left of index i that is equal to
          s[i].

        + Delete the closest character to the right of index i that is equal to
          s[i].

    Return the minimum length of the final string s that you can achieve.

    ======================================
    FUNCTION: int minimumLength(string s);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abaacbcbb"
    Output: 5
    Explanation:
    We do the following operations:
        Choose index 2, then remove the characters at indices 0 and 3. The resulting string is s = "bacbcbb".
        Choose index 3, then remove the characters at indices 0 and 5. The resulting string is s = "acbcb".


    --- Example 2 ---
    Input: s = "aa"
    Output: 2
    Explanation:
    We cannot perform any operations, so we return the length of the original string.


    *** Constraints ***
    1 <= s.length <= 2 * 10^5
    s consists only of lowercase English letters.

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    When we are "removing" characters, we are NOT messing up any order that is
    currently there. That is VERY important to understand.

    However, there's one small caveat. We are not asked to pick three
    characters and then remove all three of them, that would be too easy.
    Instead, we are asked to picked three character, that is the middle one and
    two closest to it, and then remove ONLY those two closest.

    This makes it a little bit tricky, but it's not too bad.

    We don't want to do a "while loop" a keep cutting until number of that
    letters are greater than or equal to 3, instead we want to use mathematics,
    since it is much faster.

    But how are we going to do it?

    There is a simple "trick" that isn't too bad to come up with but it's not
    that obvious at a first glance.

    Since we have to pick THREE and only remove leftmost and rightmost
    characters, we can, first, decrease the count for that character by 3 and
    say that we've removed 2.

    Why are we doing this?

    As long as there are 3 or more elements, at least on of them CAN be a
    "middle" letter. It's not the same "mid" one since we need to remove the
    closest ones, but that doesn't make a problem.

    Consider this:

        "a..a..aa.aaa"

    It doesn't matter where we start, we can start:

        "a..a..aa.aaa"
            ^
            |
           mid


           or

        "a..a..aa.aaa"
               ^
               |
              mid


            or

        "a..a..aa.aaa"
                ^
                |
               mid

            or

        "a..a..aa.aaa"
                  ^
                  |
                 mid

            or

        "a..a..aa.aaa"
                   ^
                   |
                  mid


        (We only CANNOT say that a "mid" letter is the leftmost occurrence of
         that character or rightmost occurrence of that character)


        But after we remove closest left and closest right character from the
        standpoint of the current "mid", we will be, again, in a position to
        pick multiple characters as "mid". Therefore, this does NOT matter.

        Also, it's important to consciously understand that "removing"
        character does NOT(!!!!) mess up ANY other character. That's why it
        doesn't matter which way we do it.

        We can essentially look at a group of same characters as a Set of
        characters, even if they are not a substring but a subsequence of this
        string, and then perform removal counting on those completely
        independetly of the rest of the string.


        Example:

            s = "abbabba"

            We have 3 'a' characters
            We have 4 'b' characters

            Since we have 3 'a' characters, only ONE can be 'mid'. Once we've
            fixed the mid, we can remove(or count as removed) those other two
            'a' characters.

            Now let's look at 'b' characters. There are 4 'b' characters. Two
            characters can be "mid", but as we've seen, that is not important.
            Once we fix the first "mid", we'll remove two characters. Now we
            are left with 2 'b' characters in total. We cannot remove them any
            further because there are only 2, we cannot havea a "mid".

            At the end we can say we're left with 3 characters. One 'a' and two
            'b' characters.


        But is there some smart way we can count how many are we allow to
        remove or how many we can be left with?

        Yes, there is!

        Since "mid" can be shifted from cut-to-cut, it's not really important
        which one is it. It's only important that we have 3 or more occurrences
        of that character.

        That's why we can, at the outset, do this:

            1. Count the total occurrences of the current character. (We'll do
               that with our "counter" vector)

            2. Do: counter[i] -= 1;

                Why?
                Because that way we've removed ALL possible "mid" from counting
                as removed.

                We know that SOME character will be "mid" each time, but we do
                NOT care which one will actually be "mid". We only care about
                having a "mid".

                So, since we have ODD number of characters that is GREATER or
                EQUALS to 3, we first remove 1 character to make sure we are
                not counting any "mid" along the way as "removed". (unless it
                becomes non-mid in which way we can remove it)

            3. Count how many of the remaining ones can be removed:

                    a) If there are EVEN number of characters left, we can
                       remove ALL of them.

                    b) If there are ODD  number of characters left, we can
                       remove number-1 of them.

                We can make it a general case like this:

                    remove += (counter[i] / 2) * 2;

                Since this is an integer division, if it was an ODD frequency
                we'll end up with an EVEN frequency closest down.

                    (9 / 2) * 2 <==> (4) * 2 <==> 8
                    (8 / 2) * 2 <==> (4) * 2 <==> 8


        Therefore, by removing "mid" we made sure "mid" is NOT counted.

        It's not super-intuitive, but spend some time thinking about it and
        I promise it won't be that bad, you'll get it.

*/

/* Time  Beats: 60.48% */
/* Space Beats: 86.69% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minimumLength(string s)
    {
        const int N = s.length();
        int removed = 0;

        vector<int> counter(26, 0);
        for (const char& chr : s)
            counter[chr - 'a']++;

        for (int i = 0; i < 26; i++)
        {
            if (counter[i] < 3)
                continue;

            counter[i] -= 1; // "remove" mid. Don't count "mid"

            removed += (counter[i] / 2) * 2;
        }

        return N - removed;
    }
};
