/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    916) Word Subsets
    ===========================

    ============
    Description:
    ============

    You are given two string arrays words1 and words2.

    A string b is a subset of string a if every letter in b occurs in a
    including multiplicity.

    For example, "wrr" is a subset of "warrior" but is not a subset of "world".

    A string a from words1 is universal if for every string b in words2, b is a
    subset of a.

    Return an array of all the universal strings in words1. You may return the
    answer in any order.

    =====================================================================================
    FUNCTION: vector<string> wordSubsets(vector<string>& words1, vector<string>& words2);
    =====================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: words1 = ["amazon","apple","facebook","google","leetcode"], words2 = ["e","o"]
    Output: ["facebook","google","leetcode"]

    --- Example 2 ---
    Input: words1 = ["amazon","apple","facebook","google","leetcode"], words2 = ["l","e"]
    Output: ["apple","google","leetcode"]


    *** Constraints ***
    1 <= words1.length, words2.length <= 10^4
    1 <= words1[i].length, words2[i].length <= 10
    words1[i] and words2[i] consist only of lowercase English letters.
    All the strings of words1 are unique.

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Since each and EVERY string 'b'(its letters, even multiple letters) need
    to be present in some word from words1, then it is also true that maximum
    frequency of each character, among all of the words from words2, need to
    be present in at least that amount.

    Let's represents this with an Example:

        words1 = ["papleyuio"],     words2 = ["apple", "appp", "a", "yi", "uo"]

    That means that the word "papleyuio" needs to have:

        1) Because of "apple": 1 * a, 2 * p, 1 * l, 1 * e
        2) Because of "appp":  1 * a, 3 * p
        3) Because of "a":     1 * a
        4) Becayse of "yi":    1 * y, 1 * i
        5) Becayse of "uo":    1 * u, 1 * o


        That means that the MINIMUM amount of letter 'a' needed to cover all
        of the words from words2 is the maximum frequency among all of them,
        which, in this example, is: 1

        However, for letter 'p', that number is 3.
        Why?

        For "apple" we need 2, for "a" we need only 1, however for "appp" we
        need 3 letter 'p'.

        Therefore, if we didn't have 3 letter 'p' within current word in words1
        then we wouldn't be able to say that absolutely every word from words2
        is a subset in terms of letters, from this current word from words1.

        Therefore, we would NOT include it as a "universal" word in result.

    That is the reason we must take the maximum frequency of each letter among
    all of the words in words2.

    Once we do that, then we only need to iterate through words in words1 and
    in O(26), i.e. O(1), check if it is true that all of the letters from words
    in words2, with the right amount of frequency, is present in the current
    word from words1.

    If that is the case, we include current word from words1 in our "result".

    This makes the overall Time Complexity: O(N + M) which is very efficient
    for this problem.

*/

/* Time  Beats: 57.08% */
/* Space Beats: 33.79% */

/* Time  Complexity: O(N + M) */
/* Space Complexity: O(1)     */ // "Result" is NOT counted as additional
class Solution {
public:
    vector<string> wordSubsets(vector<string>& words1, vector<string>& words2)
    {
        vector<string> result;

        vector<int> max_freq_of_letter(26, 0);
        for (const string& b : words2)
        {
            vector<int> b_count = count(b);

            for (int i = 0; i < 26; ++i)
                max_freq_of_letter[i] = max(max_freq_of_letter[i], b_count[i]);
        }

        for (const string& a : words1)
        {
            vector<int> a_count = count(a);

            bool universal = true;
            for (int i = 0; i < 26; i++)
            {
                if (a_count[i] < max_freq_of_letter[i])
                {
                    universal = false;
                    break;
                }
            }

            if (universal)
                result.push_back(a);
        }

        return result;
    }

private:
    vector<int> count(const string& word)
    {
        vector<int> counter(26, 0);

        for (const char& chr : word)
            counter[chr - 'a']++;

        return counter;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, but written in another way. It's good to be able to compare.

*/

/* Time  Beats: 37.50% */
/* Space Beats: 39.97% */

/* Time  Complexity: O(N + M) */
/* Space Complexity: O(1)     */ // "Result" is NOT counted as additional
class Solution_Neater {
public:
    vector<string> wordSubsets(vector<string>& words1, vector<string>& words2)
    {
        vector<string> result;

        vector<int> words2_counter(26, 0);

        for (const string& b : words2)
        {
            vector<int> curr_counter(26, 0);
            for (const char& chr : b)
                curr_counter[chr - 'a']++;

            for (int i = 0; i < 26; i++)
                words2_counter[i] = max(words2_counter[i], curr_counter[i]);
        }

        for (const string& a : words1)
        {
            vector<int> curr_counter(26, 0);
            for (const char& chr : a)
                curr_counter[chr - 'a']++;

            bool universal = true;
            for (int i = 0; i < 26; i++)
            {
                if (curr_counter[i] < words2_counter[i])
                {
                    universal = false;
                    break;
                }
            }

            if (universal)
                result.push_back(a);
        }

        return result;
    }
};
