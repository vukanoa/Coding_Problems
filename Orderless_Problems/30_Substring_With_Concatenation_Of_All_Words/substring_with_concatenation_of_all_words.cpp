#include <iostream>
#include <vector>
#include <unordered_map>

/*
    ============
    === HARD ===
    ============

    =============================================
    30) Substring with Concatenation of All Words
    =============================================

    ============
    Description:
    ============

    You are given a string s and an array of strings words. All the strings of
    words are of the same length.

    A concatenated string is a string that exactly contains all the strings of
    any permutation of words concatenated.

        + For example, if words = ["ab","cd","ef"], then "abcdef", "abefcd",
          "cdabef", "cdefab", "efabcd", and "efcdab" are all concatenated
          strings. "acdbef" is not a concatenated string because it is not the
          concatenation of any permutation of words.

    Return an array of the starting indices of all the concatenated substrings
    in s. You can return the answer in any order.

    ==========================================================================
    FUNCTION: std::vector<int> findSubstring(string s, vector<string>& words);
    ==========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "barfoothefoobarman", words = ["foo","bar"]
    Output: [0,9]
    Explanation:
    The substring starting at 0 is "barfoo". It is the concatenation of
    ["bar","foo"] which is a permutation of words.

    The substring starting at 9 is "foobar". It is the concatenation of
    ["foo","bar"] which is a permutation of words



    --- Example 2 ---
    Input: s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]
    Output: []
    Explanation:
    There is no concatenated substring.


    --- Example 3 ---
    Input: s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]
    Output: [6,9,12]
    Explanation:
    The substring starting at 6 is "foobarthe". It is the concatenation of
    ["foo","bar","the"].
    The substring starting at 9 is "barthefoo". It is the concatenation of
    ["bar","the","foo"].
    The substring starting at 12 is "thefoobar". It is the concatenation of
    ["the","foo","bar"].


    *** Constraints ***
    1 <= s.length <= 10^4
    1 <= words.length <= 5000
    1 <= words[i].length <= 30
    s and words[i] consist of lowercase English letters.

*/

/*
    ===========================
    === THIS CODE GIVES TLE ===
    ===========================

    But I wanted to include it in this file anyway. It's nice to see the Brute
    force Solution and an Optimized one afterwards.

    This is WAAAAAAAAAY to inefficient, but it is composed of different parts
    that are or could be useful for other problems, that's why I chose to
    indlude it in this file.

*/

/* Time  Complexity: O(n * n!) */
/* Space Complexity: O(n!) */
class Solution_TLE {
public:
    vector<int> findSubstring(string s, vector<string>& words)
    {
        const int WORD_LENGTH = words[0].length();
        const int WORDS = words.size();
        const int ONE_PERMUTATION_LENGTH = WORDS * WORD_LENGTH;

        if (s.length() < ONE_PERMUTATION_LENGTH)
            return {};

        std::vector<int> results;

        std::vector<int> words_indices(WORDS);
        std::iota(words_indices.begin(), words_indices.end(), 0); // words_indices = [0, 1, 2, 3, 4]

        std::vector<std::vector<int>> permutations = permute(words_indices);
        std::unordered_set<std::string> uset_string_permutations;

        std::vector<int> vec = {1,3,2,0};
        for (int i = 0; i < permutations.size(); i++)
        {
            std::ostringstream curr_string_permutation;
            for (int j = 0; j < permutations[0].size(); j++)
            {
                curr_string_permutation << words[permutations[i][j]];
            }

            uset_string_permutations.insert(curr_string_permutation.str());
        }

        for (int i = 0; i <= s.length()-ONE_PERMUTATION_LENGTH; i++)
        {
            std::string substr = s.substr(i, ONE_PERMUTATION_LENGTH);

            if (uset_string_permutations.find(substr) != uset_string_permutations.end())
                results.push_back(i);
        }

        return results;
    }

private:
    std::vector<std::vector<int>> permute(std::vector<int>& nums)
    {
        std::vector<std::vector<int>> results;
        std::unordered_set<int> uset_permutations; // Unordered set of permutations

        backtracking(nums, {}, uset_permutations, results);

        return results;
    }

    void backtracking(std::vector<int>& nums,
                      std::vector<int> curr_permutation,
                      std::unordered_set<int>& uset_permutations,
                      std::vector<std::vector<int>>& results)
    {
        if (curr_permutation.size() == nums.size())
        {
            results.push_back(curr_permutation);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (uset_permutations.count(nums[i])) // If it exists in the Set
                continue;

            curr_permutation.push_back(nums[i]);
            uset_permutations.insert(nums[i]);

            backtracking(nums, curr_permutation, uset_permutations, results);

            uset_permutations.erase(nums[i]);
            curr_permutation.pop_back();
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Instead of generating every single permutation(That would take us O(n!)
    Time Complexity), what we can do instead is just count how many times does
    every word in "words" occurrs.

    Then, since we're told that:
    "A concatenated string is a string that exactly contains all the strings of
     any permutation of words concatenated."

    Which means that every "concatenated string" is OF THE SAME LENGTH! That
    length is always equals to WORD_LENGTH * words.size(), i.e. number of
    characters if all the strings in "words" are concatenated.

    Therefore, we can observe that this is an obvious FIXED Sliding Window
    problem.

    If we have:
        string s = "abcdef....slfjdslkj"

    And since we know that "concatenated string" is ALWAYS of the same length,
    then we can start at index 0 with a substr of length "concatenad string"
    and consider only that one substr at a time.

    Example:

        string s = "abcdefaxios"
        words = ["fa", "de", "bc", "de", "de"]

        // Helpers
        WINDOW_SIZE = 6
        word_count = {{"fa", 1},
                      {"de", 3},
                      {"bc", 1},


        1) string s = "abcdefadedexios"
                       |        |
                       |________|
                           ^
                   ________|
                   |
           This permutation cannot be assembled from "word_count"


        2) string s = "abcdefadedexios"
                        |        |
                        |________|
                            ^
                    ________|
                    |
           This permutation can INDEED be assembled from "word_count".

           1. One   "fa"
           2. Three "de"
           3. One   "bc"


        Therefore, we return true and thus we push the index 1(because we
        started this substring at index 1, at character "b".

        And we continue until index for starting a substring + WINDOW_SIZE
        becomes greater than STR_LENGTH.

        Once that happens we can no longer have a substring of of length
        WINDOW_SIZE, therefore, we're done.

        At the and return "results" vector with starting indexes from string s.

*/

/* Time  Beats: 30.76% */
/* Space Beats:  8.46% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::vector<int> findSubstring(std::string s, std::vector<std::string>& words)
    {
        const int WORD_LENGTH = words[0].size();
        const int STR_LENGTH  = s.size();
        const int WINDOW_SIZE = words.size() * WORD_LENGTH;

        std::vector<int> results;

        std::unordered_map<string, int> word_count;
        for(int i = 0; i < words.size(); i++)
            word_count[words[i]]++;

        for (int i = 0; i + WINDOW_SIZE <= STR_LENGTH; i++)
        {
            if (check_substring(word_count, s.substr(i, WINDOW_SIZE), WORD_LENGTH))
                results.push_back(i);
        }

        return results;
    }

private:
    bool check_substring(std::unordered_map<std::string, int> word_count,
                         std::string window_str,
                         const int& WORD_LENGTH)
    {
        for(int j = 0; j < window_str.length(); j += WORD_LENGTH)
        {
            std::string word = window_str.substr(j, WORD_LENGTH);
            if(word_count.find(word) != word_count.end())
            {
                if(word_count[word]-- == 0)
                    return false;
            }
            else
                return false;
        }

        return true;
    }
};
