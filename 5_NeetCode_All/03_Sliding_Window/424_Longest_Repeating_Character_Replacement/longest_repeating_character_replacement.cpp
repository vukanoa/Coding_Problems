/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    424) Longest Repeating Character Replacement
    ============================================

    ============
    Description:
    ============

    You are given a string s and an integer k. You can choose any character of
    the string and change it to any other uppercase English character. You can
    perform this operation at most k times.

    Return the length of the longest substring containing the same letter you
    can get after performing the above operations.

    ====================================================
    FUNCTION: int characterReplacement(string s, int k);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "ABAB", k = 2
    Output: 4
    Explanation: Replace the two 'A's with two 'B's or vice versa.


    --- Example 2 ---
    Input: s = "AABABBA", k = 1
    Output: 4
    Explanation: Replace the one 'A' in the middle with 'B' and form "AABBBBA".
    The substring "BBBB" has the longest repeating letters, which is 4.
    There may exists other ways to achive this answer too.


    *** Constraints ***
    1 <= s.length <= 10^5
    s consists of only uppercase English letters.
    0 <= k <= s.length

*/

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Let's consider this example:

    Input: s = "ABABBA", k = 2

    What is the Brute Force way to solve it? Check every substring and return
    the longest one. However, that wouldn't be efficient, since to consider
    every single substring, it would take us O(n^2) time, which is inefficient.

    But even if we're doing that, what exactly are we looking for?

    Let's pick consider this example:
        Input: s = "ABABBA", k = 2

    Let's say that, currently, we're checking this substring:
        s = "ABABBA"
              ^^^^

        i.e. substring = "BABB"

    If we are looking at a particular substring - How do we know if that
    substring is valid?

    "BABB", k = 2

    'k' denotes that we're allowed to replace at max 2 characters in a window,
    i.e substing.

    So, which character(s) do we want to replace here?

    Do we want to replace B's in order to match the A?
    Or do we want to replace the A in order to match other, surrounding, Bs?

    Of course, we want to replace the character that occurs less frequently,
    because the number of replacements we have is limited by a variable 'k'.

    So, we conclude that we always want to replace the character(s) that are
    less frequent than **THE MOST FREQUENT CHARACTER IN THE CURRENT WINDOW**.

    We could've had something like this:
        substring = "CCBCABCBCCA", k = 5

        The most frequent character here is character 'C'(occurs 6 times),
        whereas all the other characters occurr either the same amount or less
        than character 'C'.(In this case, all characters, individually, occur
        less than character 'C', i.e. less than 6 times)

    Since we don't actually have to replace the characters, then it doesn't
    matter which character's count we "pick"(as long as they both share the 1st
    spot, i.e. they both have the most frequent occurrence in the given window,
    if there are more than 1 such characters)

    So in order to check if a given window(substring) is valid, we have to
    subtract the most frequent element count from the total length of a current
    window(substring) and check if that element is less than or equal to k.

    Since they say, in the description of a problem, that:
        "s consists of only uppercase English letters."

    Then instead of using a HashMap, we can use a basic vector of size 26.
    Also, vectors in C++, are a bit more optimized than unordered_map, so no
    reason not to use a vector here.

    Let's get through our previous example substring:
        "BABB", k = 2

    We can call the HashMap(or vector, rather) "letters" or "count".
    I'll call it "letters", but the value for each letter is going to represent
    a count.

    letters = [1, 3, 0, 0, 0, 0, ...,  0]
               0  1  2  3  4  5       25

    Index 0 represents the occurrence of letter 'A'.
    Index 1 represents the occurrence of letter 'B', etc.

    You get the point.

    So, as we've said - To determine if a current substring is valid, we must,
    from the total length of a current window(substring), subtract the
    occurrence of the most frequent element in a current substring and see if
    that number is less than or equal to k(which is the limit).

    In other words:
        substring.length - max_frequent_value ==> Number of remaining elements
                                                  we must replace in order to
                                                  get a window consisted of a
                                                  same letter.

    *** This is the fundamental thing of a Sliding Window technique ***

    if ((substring.length - max_frequent) <= k)
        // The window is INDEED valid
    else
        // The window is NOT valid

    However, since we don't want to check for a positive, i.e. if a window is
    valid, but the opposite - if the window is NOT valid, then we have to write
    it like this:

    if ((substring.length - max_frequent) > k)
        // The window is NOT valid

    It goes without saying, at this point, that we're going to use a Sliding
    Window technique.

    We're going to have "left" and "right" pointers that both start at index 0
    at the beginning.

    "right" pointer will be shifted by one in every iteration, whereas the left
    is going to be shifted only conditionally, if a current window ISN'T valid.

    Also, since we are iterating through this string one-by-one, if we find out
    that the window is NOT valid, then we don't have to shrink the window in a
    "while loop", we can only do it once, in an if statement, since if it is
    NOT valid, it's because of the current element, therefore whichever element
    we get to shrink on the left side, we're sure that our window is, again,
    destined to be valid.

    One more thing I didn't mention is that in order to find "max_frequent"
    element we have to iterate through the entire vector. That seems to be the
    O(n), but it is not.

    Since we're told we only have 26 uppercase letters, we have to check only
    26 elements each time which is O(1).

    Anyway, if the window is NOT valid, i.e. this condition is true:

    if ((substring.length - max_frequent) > k) // The window is NOT valid
    {
        letters[s[left] - 'A']--;
        left++;
    }

    We decrement the occurrence of a leftmost letter in a current window and
    we shrink window to the right by one, i.e. move the left boundary to the
    right, by one.

    Now, as we've said, our window is certainly valid and thus we can check
    if this current window length is the longest so far.

    We do that by:

        // current_window_length = right - left + 1
        longest = std::max(longest, right - left + 1);

    Once our "right" pointer reaches the end, we break the "for loop" and we
    return "longest".



    ************************************************************************
    *************************** Simulation *********************************
    ************************************************************************

    s = "ABABBA", k = 2

    1.
        s = "A B A B B A"
             0 1 2 3 4 5
             l
             r

            Before: letters = [0, 0, 0, 0, ..,  0]
                               0  1  2  3      25
                               |
            letters[right]++;  |
                               v
            After:  letters = [1, 0, 0, 0, ..,  0]
                               0  1  2  3      25

            window_len = r - l + 1 => window_len = 0 - 0 + 1 = 1
            max_freq = 1 // 'A' at index 0 is the most frequent

            if (window_len - max_freq > k) ==> (1 - 1 > 2) ==> (0 > 2) NOT true

            Since it is NOT true, that means that the current window is VALID.

            longest = max(longest, window_len) = max(0, 1) = 1

    2.
        s = "A B A B B A"
             0 1 2 3 4 5
             l r

            Before: letters = [1, 0, 0, 0, ..,  0]
                               0  1  2  3      25
                                  |
            letters[right]++;     |
                                  v
            After:  letters = [1, 1, 0, 0, ..,  0]
                               0  1  2  3      25

            window_len = r - l + 1 => window_len = 1 - 0 + 1 = 2
            max_freq = 1 // 'A' at index 0 is the most frequent(or 'B')

            if (window_len - max_freq > k) ==> (2 - 1 > 2) ==> (1 > 2) NOT true

            Since it is NOT true, that means that the current window is VALID.

            longest = max(longest, window_len) = max(1, 2) = 2

    3.
        s = "A B A B B A"
             0 1 2 3 4 5
             l   r

            Before: letters = [1, 1, 0, 0, ..,  0]
                               0  1  2  3      25
                               |
            letters[right]++;  |
                               v
            After:  letters = [2, 1, 0, 0, ..,  0]
                               0  1  2  3      25

            window_len = r - l + 1 => window_len = 2 - 0 + 1 = 3
            max_freq = 2 // 'A' at index 0 is the most frequent

            if (window_len - max_freq > k) ==> (3 - 2 > 2) ==> (1 > 2) NOT true

            Since it is NOT true, that means that the current window is VALID.

            longest = max(longest, window_len) = max(2, 3) = 3


    4.
        s = "A B A B B A"
             0 1 2 3 4 5
             l     r

            Before: letters = [2, 1, 0, 0, ..,  0]
                               0  1  2  3      25
                                  |
            letters[right]++;     |
                                  v
            After:  letters = [2, 2, 0, 0, ..,  0]
                               0  1  2  3      25

            window_len = r - l + 1 => window_len = 3 - 0 + 1 = 4
            max_freq = 2 // 'A' at index 0 is the most frequent(or 'B')

            if (window_len - max_freq > k) ==> (4 - 2 > 2) ==> (2 > 2) NOT true

            Since it is NOT true, that means that the current window is VALID.

            longest = max(longest, window_len) = max(3, 4) = 4


    5.
        s = "A B A B B A"
             0 1 2 3 4 5
             l       r

            Before: letters = [2, 2, 0, 0, ..,  0]
                               0  1  2  3      25
                                  |
            letters[right]++;     |
                                  v
            After:  letters = [2, 3, 0, 0, ..,  0]
                               0  1  2  3      25

            window_len = r - l + 1 => window_len = 4 - 0 + 1 = 5
            max_freq = 3 // 'B' at index 0 is the most frequent

            if (window_len - max_freq > k) ==> (5 - 3 > 2) ==> (2 > 2) NOT true

            Since it is NOT true, that means that the current window is VALID.

            longest = max(longest, window_len) = max(4, 5) = 5



    6.
        s = "A B A B B A"
             0 1 2 3 4 5
             l         r

            Before: letters = [2, 3, 0, 0, ..,  0]
                               0  1  2  3      25
                               |
            letters[right]++;  |
                               v
            After:  letters = [3, 3, 0, 0, ..,  0]
                               0  1  2  3      25

            window_len = r - l + 1 => window_len = 5 - 0 + 1 = 6
            max_freq = 3 // 'A' at index 0 is the most frequent(or 'B')

            if (window_len - max_freq > k) ==> (6 - 3 > 2) ==> (3 > 2) // TRUE
            {
                // decrement the count of the leftmost letter in this current
                // window
                letters[s[left] - 'A']--;

                // Shrink the window to the right by one
                left++
            }

            window_len = r - l + 1 => window_len = 5 - 1 + 1 = 6
                                                       ^
                                                      _|
                                                     |
            // Remember that in this (5th step) our left pointer incremented

            Now the window is VALID AGAIN, thus we can also do:
                longest = max(longest, window_len) = max(5, 5) = 5

            (You can see that we do this nonetheless, since if the window was
             NOT valid, it is going to become after the if statement, and if it
             already was, then we can do it anyway)

*/

/* Time  Beats: 83.15% */
/* Space Beats: 70.87% */

/*
    Time  Complexity: O(n)
    It's O(26 * n) --> O(1 * n) --> O(n)
*/
/*
    Space Complexity: O(1)
*/
class Solution {
public:
    int characterReplacement(string s, int k)
    {
        const int N = s.size();
        int letters[26] = {0}; // Frequency counter

        int left  = 0;
        int right = 0;

        int result = 0;
        while (right < N)
        {
            letters[s[right] - 'A']++;

            // O(26) -> constant -> O(1)
            int max_freq = *max_element(begin(letters), end(letters));

            // current_window_length = right - left + 1
            if ((right - left + 1) - max_freq > k)
            {
                letters[s[left] - 'A']--;
                left++;
            }

            // current_window_length = right - left + 1
            result = max(result, right - left + 1);

            // Increment
            right++;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    It is going to be very similar to the above Solution, however the Time
    Complexity is not going to be: O(n * 26) -> O(n), but flat O(n * 1) -> O(n)

    What makes the above Soltuion have this constant of 26?

    The fact that, possibly at each iteration, we have to find max_freq value
    from the vector(Hash Map) "letters".


    Here, instead of doing that, we're going to maintain a global "max_freq"
    variable that is going to denote a maximum frequent character at any given
    point in time.

    For example, if we had this situation:

        letters = [3, 2, 0, 0, 0, 0, ...,  0]
                   0  1  2  3  4  5  ...  25
                   A  B  C  D  E  F  ...   Z

        max_freq = 3

    The most frequent character at this time is 'A' which occurs 3 times,
    therefore variable "max_freq" is going to be 3.


    Now, let's say we moved 2 characters to the right and that we have this
    situation:

        letters = [3, 4, 0, 0, 0, 0, ...,  0]
                   0  1  2  3  4  5  ...  25
                   A  B  C  D  E  F  ...   Z

        max_freq = 4

    Now, "max_freq" becomes 4, in other words - We always want "max_freq" to be
    the most frequent character in any already considered window(substring).

    (And we consider windows, i.e. substrings one-by-one by using the Sliding
     Window technique)

    One problem is, if we're trying to maintain the most frequent character,
    what happens when we take our "left" pointer and shift it?

    If we do that, let's say this happens:

        ************************
        ***** Before Shift *****
        ************************

        letters = [3, 4, 0, 0, 0, 0, ...,  0]
                   0  1  2  3  4  5  ...  25
                   A  B  C  D  E  F  ...   Z

        max_freq = 4

        ***********************
        ***** After Shift *****
        ***********************

        letters = [3, 2, 0, 0, 0, 0, ...,  0]
                   0  1  2  3  4  5  ...  25
                   A  B  C  D  E  F  ...   Z

        max_freq = 3

    Then we'd have to "rescan" this entire HashMap(or vector in this case) and
    find the current most frequent one for this window.

    Now:
        max_freq = 3

    However, that defeats the purpose of this whole approach. We would, again,
    have O(n * 26) and not O(n * 1) which isn't an optimization at all.

   ____________________________________________________________________________
   |                                                                          |
   |But, and here is the crux of this Solution, it's technically true that you|
   |DON'T HAVE TO DECREMENT max_freq once the window is shinked and it becomes|
   |true that there is no longer any character,in a current window(substring),|
   |that occurs 4 times.                                                      |
   |__________________________________________________________________________|

    Take the time to read this above paragraph multiple times if you don't get
    it.

    The main idea is this - The result(variable "longest") is ONLY going to be
    maximized as we find new maximum frequent character in some window, i.e.
    substring.

    Remember what we were doing, we would do this:

        window_len - max_freq

    and we wanted to minimize this(since the valid number this can be is
    bounded by variable 'k').

    We want "window_len" to be maximized, because that's what our result(i.e.
    variable "longest") is going to be set to, so therefore we also want our
    "max_freq" variable to be maximized because we want to ensure that this:

        window_len - max_freq

    is MINIMIZED, i.e. less than or equal to 'k'.

    Let's say that our "max_freq" was 4, but then got downgraded to 3.

    I'd still want "max_freq" to be 4 because it is NOT going to change our
    result.

    For example:

        window_len - max_freq  <= k

               6   -   4       <= 2 (let's say that 'k' is 2)

    if we LEAVE max_freq to be a 4, even if the most frequent element in a
    current window(substring) is, say, 3, then we're OVERESTIMATING what the
    max_freq is, but we know that at least at one given point in time, max_freq
    was indeed 4 and were, therefore, able to take window_len(6) and set it
    as our result(i.e. "longest").

    So, now let's say that our result is:
        longest = 6

    If we were ever going to INCREASE from 6 to another greater number such as:
    7, 8, 9, etc.

    then we would REQUIRE our max_freq to INCREASE.

    If it stays the same or if decreases, our result(i.e. "longest") is NEVER
    going to change.

    WE ONLY CHANGE OUR RESULT(i.e. "longest") WHEN WE INCREASE max_freq,
    BECAUSE THAT IS THE ONLY WAY THIS CONDITION:

        window_len - max_freq  <= k

    IS GOING TO BE TRUE.


    So, if the maximum frequency character in a given window(substring) becomes
    less than the current "max_freq" value, we don't have to update it. We
    don't have to look in the entire HashMap(vector) and find a new max.

    But, if we do increase our maximum frequency character in a given window,
    then we do want to update our max_frequency and increase it and as a result
    we'll get a new "longest" value and we can do that in O(1) since we don't
    have to "scan" through the entire HashMap(vector).

    ************************
    ***** TO SUMMARIZE *****
    ************************

    We can notice that if we don't decrease max_freq, once maximum frequency
    chracter count in a current window becomes less than max_freq, then the
    Solution will still work since we're Overestimating.

    If and only if we find a max_freq that is greater than the previous value,
    only then can we increase the size of the longest substring, thus we don't
    have to keep finding the max_freq for each current window.

*/

/* Time  Beats: 98.55% */
/* Space Beats: 70.87% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Flat_O_of_n {
public:
    int characterReplacement(string s, int k)
    {
        const int N = s.size();
        int result = 0;

        int letters[26] = {0}; // Frequency counter

        int left  = 0;
        int right = 0;
        int max_freq = 0;
        while (right < N)
        {
            letters[s[right] - 'A']++;

            // This is the optimization.
            max_freq = max(max_freq, letters[s[right] - 'A']);

            // current_window_length = right - left + 1
            if ((right - left + 1) - max_freq > k)
            {
                letters[s[left] - 'A']--;
                left++;
            }

            // current_window_length = right - left + 1
            result = max(result, right - left + 1);

            // Increment
            right++;
        }

        return result;
    }
};
