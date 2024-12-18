#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    =========================================================
    2981) Find Longest Special Substring that Occurs Thrice I
    =========================================================

    ============
    Description:
    ============

    You are given a string s that consists of lowercase English letters.

    A string is called special if it is made up of only a single character. For
    example, the string "abc" is not special, whereas the strings "ddd", "zz",
    and "f" are special.

    Return the length of the longest special substring of s which occurs at
    least thrice, or -1 if no special substring occurs at least thrice.

    A substring is a contiguous non-empty sequence of characters within a
    string.

    ======================================
    FUNCTION: int maximumLength(string s);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "aaaa"
    Output: 2
    Explanation: The longest special substring which occurs thrice is "aa":
                 substrings "aaaa", "aaaa", and "aaaa". It can be shown that
                 the maximum length achievable is 2.

    --- Example 2 ---
    Input: s = "abcdef"
    Output: -1
    Explanation: There exists no special substring which occurs at least
                 thrice. Hence return -1.


    --- Example 3 ---
    Input: s = "abcaba"
    Output: 1
    Explanation: The longest special substring which occurs thrice is "a":
                 substrings "abcaba", "abcaba", and "abcaba". It can be shown
                 that the maximum length achievable is 1.


    *** Constraints ***
    3 <= s.length <= 50
    s consists of only lowercase English letters.

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Minimal possible length to occur is always 1. However, maximal possible
    length is the length of the longest subsequence of same characters in s.

    For example:
        s = "aaabbcaabbbaad"

    Longest subsequence of same characters is 3. Either "aaa" or "bbb".
    Thus, we know the result is in that range --> [1..3]

    Now, instead of manually trying to find THRICE occurring special substrings
    of length: 3, 2 and then 1

    We can, instead, optimize this linear part. We can use a Binary Search.
    This way, instead of linearly going through the range of possible results,
    we are doing a Binary Search and thus reducing Time Complexity from O(n)
    to O(logn). (This is NOT an overall Time Complexity. It's ONLY for this
    part).


    But even if we did a Linear scan, how can we know if there are, at least,
    three occurrences of same special substring that amount of times?

    In other words, if we pick a subsequence of length 2 - How can we know if
    there are at least three(i.e. "occurrs thrice") special subsequences of
    same character.

    We cann't find "aa", "bb" and "aa". That does NOT count as THREE special
    occurrences even if, indepdently, every single one of this substrings is
    indeed special.

    Instead, we need to find either: "aa", "aa", "aa", or "bb", "bb", "bb" etc.
    All special substrings must be of same "substance".

    How are we going to do that?
    Let's try a Brute-Force. How would that even look like: Let's use same
    example as above:

        s = "aaabbcaabbbaad"

    Well, we could... Try with every 'i' in string s and check nex 2-1
    characters and if they match, we can mark in some HashMap, that special
    substring of "substance" 'a' of length 2, occurs once, so far.

    Then increment 'i' by 1 and do it again.
    But... That would mean that for every 'i' we are doing "upper_bound" of
    original range (upon we wish to do a Binary Search on).

    That means we would have a Complexity(only for this part) of O(N) *
    O(upper_bound).

    Note that "upper_bound" can be N in the worst case.
    Why?

    Consider this:
        
        s = "ccccc"   N = 5
             01234

    What would be the range for this example upon which we wish to do a Binary
    Search?

    It's [1..5] because 5 is the maximal length of any substring with same
    characters.

    That further means, the above Solution would be O(N) * O(N). And on top of
    that we would need to multiply all of that by the Time Complexity of our
    Binary Search which is O(logN).

    Which in total would be O(N^2 * logN).

    That is waaay too inefficient for large Inputs. (In this problem, it
    wouldn't be much of a problem since the Constraints say s.length can be
    at maximum only 50).

    But in general case, it would be VERY inefficient.

    Thus, how can we Optimize this BruteForce approach?

    Well, we must, at least go through every position of 'i' that is for sure,
    thus we can't reduce it to O(1) or O(logN) that is for sure.

    But can we reduce it from O(N^2) to O(N)?
    We can, here is how is that going to work.

    Instead of trying to go, "to the right", to check if next X-1 characters
    are the same as the character at s[i], we can precompute this part.

        s = "aaabbcaabbbaad"
             012345679...

        Let's call it "dp", but it's "subsequence_length" in the code.

        We start at the last element and if current element and adjacent
        element to the right are the same, then we say - Starting at this index
        'i' there is a substring of length X. 

        What is this X?
        X will be consecutive elements from the position 'i+1' plus one(the
        current one)
        
        Consider this small part at the end:

                "..b  b  a  a  d"
                  10 11 12 13 14

                [..0, 0, 0, 0, 1]
                (it's important to note that the LAST element's length of
                 consecutive substring is ALWAYS 1, because there are no other
                 elements ot its right)


        Now let's simulate the rest:

                "..b  b  a  a  d"
                  10 11 12 13 14
                [..0, 0, 0, 0, 1]
                            i

        if (s[i] == s[i+1]) // Which it ISN'T
            dp[i] = 1 + dp[i+1]
        else
            dp[i] = 1; // But we are not going to have this "else" part
                       // Because we'll initialize our dp to have all 1s.


        i = 13)
                "..b  b  a  a  d"
                  10 11 12 13 14
                [..1, 1, 1, 1, 1]
                            i

            if (s[i] == s[i+1]) // Which it ISN'T, 'a' != 'd'



        i = 12)
                "..b  b  a  a  d"
                  10 11 12 13 14
                [..1, 1, 1, 1, 1]
                         i

            if (s[i] == s[i+1]) // Which it is, 'a' == 'a'
                dp[i] = 1 + 1 = 2



        i = 11)
                "..b  b  a  a  d"
                  10 11 12 13 14
                [..1, 1, 2, 1, 1]
                      i

            if (s[i] == s[i+1]) // Which it ISN'T, 'b' != 'a'



        i = 10)
                "..b  b  a  a  d"
                  10 11 12 13 14
                [..1, 1, 2, 1, 1]
                   i

            if (s[i] == s[i+1]) // Which it is, 'b' == 'b'
                dp[i] = 1 + dp[i+1] = 1 + 1 = 2

        i = 9) 
                "..b  b  a  a  d"
                  10 11 12 13 14
                [..2, 1, 2, 1, 1]
                i

                ... etc.


        This way, by pre-computing, we can simply do a Linear scan through s
        and find out if at any given position 'i' there are at least X-1 same
        consecutive characters to the right.

        (Why X-1? Because if we are looking for length 3, we only care about
         the next 2, since the current one is also counted)


    This way our Overall Time Complexity becomes: O(N) * O(logN) => O(N * logN)
    Our Space Complexity is O(N) because we've used vector "dp" to precompute.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  92.09% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n)        */
class Solution {
public:
    int maximumLength(string s)
    {
        const int N = s.length();
        const int THRICE = 3;

        int result = -1;

        vector<int> subarray_length(N, 1);

        int upper_bound = 1;
        for (int i = N-2; i >= 0; i--)
        {
            if (s[i] == s[i+1])
                subarray_length[i] = 1 + subarray_length[i+1];

            upper_bound = max(upper_bound, subarray_length[i]);
        }

        int left  = 1;
        int right = upper_bound;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            int max_occurr = 0;
            vector<int> counter(26, 0);
            for (int i = 0; i < N; i++)
            {
                if (subarray_length[i] >= mid)
                {
                    counter[s[i] - 'a']++;
                    max_occurr = max(max_occurr, counter[s[i] - 'a']);
                }
            }

            if (max_occurr >= THRICE)
            {
                result = max(result, mid);
                left = mid + 1;
            }
            else
                right = mid-1;
        }

        return result;
    }
};
