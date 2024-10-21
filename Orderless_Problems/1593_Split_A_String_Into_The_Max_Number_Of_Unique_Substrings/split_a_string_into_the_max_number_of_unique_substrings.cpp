#include <iostream>
#include <vector>
#include <unordered_set>

/*
    ==============
    === MEDIUM ===
    ==============

    =============================================================
    1593) Split a String Into the Max Number of Unique Substrings
    =============================================================

    ============
    Description:
    ============

    Given a string s, return the maximum number of unique substrings that the
    given string can be split into.

    You can split string s into any list of non-empty substrings, where the
    concatenation of the substrings forms the original string. However, you
    must split the substrings such that all of them are unique.

    A substring is a contiguous sequence of characters within a string.

    =======================================
    FUNCTION: int maxUniqueSplit(string s);
    =======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "ababccc"
    Output: 5
    Explanation: One way to split maximally is ['a', 'b', 'ab', 'c', 'cc'].
                 Splitting like ['a', 'b', 'a', 'b', 'c', 'cc'] is not valid as
                 you have 'a' and 'b' multiple times.


    --- Example 2 ---
    Input: s = "aba"
    Output: 2
    Explanation: One way to split maximally is ['a', 'ba'].


    --- Example 3 ---
    Input: s = "aa"
    Output: 1
    Explanation: It is impossible to split the string any further.


    *** Constraints ***
    1 <= s.length <= 16
    s contains only lower case English letters.

*/

/*
    ------------
    --- IDEA ---
    ------------

    If we try a "Brute Force Intuitive way" of solving this problem, we'll
    quickly realize what is the problem.

    Look at the "Example 2": "aba"

    The "Brute Force Intuitive way" would be to iterate through the Input and
    for every letter, try to see if we've already put it in HashSet and if we
    didn't, put that single letter and continue iterating.

    If this current SINGLE letter is NOT in the HashSet:
        put that single letter and continue iterating
    else
        try appending the next letter to this one and see if that STRING is
        non-existant in HashSet

        If it DOESN'T exist in HashSet:
            put that substring in HashSet and continue iterating from the
            letter that comes immediately after this substring.
        else
            append the next letter and see if THAT substring is in the HashSet


    We'll quickly realize that this approach wouldn't work for Input "aba".
    Why?

    + We put 'a' in Hashset.

    + We put 'b' in HashSet.

    + Now we're at 'a', but 'a' already exists and we CANNOT extend this
      substring anymore, therefore we cannot say that the count is 2, since we
      didn't succeed in splitting the whole string s.

      Therefore, we have to remove the previous 'b' from the HashSet and then
      try to append this current 'a' to it and see if that is in the HashSet.

      Now in our HashSet, there's only 'a'. Now we append our current 'a'(at
      index 2) to the previous 'b' substring and we get "ba". We check if that
      substring is present in the HashSet and since it is NOT, we can insert it
      and then we're done. We've split the entire string s.

      The answer is 2.


    But there is a problem with this approach. Let's consider a slightly
    complicated example:

        Example: "abcabab"

    + We put 'a' in Hashset.
    + We put 'b' in Hashset.
    + We put 'c' in Hashset.
    + We put 'ab' in Hashset.
    + Now we cannot put 'a' and we cannot pu "ab", so we have to go all the way
      back. Now we remove 'c' from HashSet, but then do we pair "ca" or "cab"?

      It seems better to use smaller substrings so that we can maximize the
      number substring in which we're able to split this string. But if we do
      that, then we're left with a final 'b' and 'b' is already in the HashSet.

      Now we have to go even more back.

      ...

      At this point you should realize that there are SO MANY possibilities
      that can happen that we're not even able to think of. If that goes
      thorugh our minds, it is a STRONG indicator that we should be using
      Backtracking technqiue.

      There are SO MANY combinations, therefore we probably MUST check each and
      every possible one to be able to figure out if it is the most optimal
      result.

      After this, you're free to try and think of a non-Backtracking Solution,
      but the problem is, as we've concluded - You'll realize that you cannot
      even think of many edge cases, and since that is the case, it is almost
      certainly a "Backtracking problem".

      Once we know that it is a "Backtracking problem", it is very easy to come
      up with a Solution.

      If you're not familiar with Backtraking, check some basic ones and then
      come back. It is a fundamental use of Backtracking.

      The hard part is figuring out that we should be using Backtracking.

*/

/* Time  Beats: 36.26% */
/* Space Beats: 50.88% */

/* Time  Complexity: O(n * 2^n) */
/* Space Complexity: O(n)       */
class Solution {
public:
    int maxUniqueSplit(string s)
    {
        int result = 0;
        unordered_set<string> uset;

        backtracking(s, uset, 0, 0, result);

        return result;
    }

private:
    void backtracking(string s, unordered_set<string>& uset, int start, int curr_res, int& result)
    {
        if (start == s.length())
        {
            result = max(result, curr_res);
            return;
        }

        for (int i = start; i < s.length(); i++)
        {
            string substr = s.substr(start, i - start + 1);

            if (uset.find(substr) == uset.end())
            {
                curr_res++;
                uset.insert(substr);

                backtracking(s, uset, i+1, curr_res, result);

                uset.erase(substr);
                curr_res--;
            }
        }
    }
};
