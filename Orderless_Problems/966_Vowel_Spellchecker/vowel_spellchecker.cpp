/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    966) Vowel Spellchecker
    ===========================

    ============
    Description:
    ============

    Given a wordlist, we want to implement a spellchecker that converts a query
    word into a correct word.

    For a given query word, the spell checker handles two categories of
    spelling mistakes:

        Capitalization: If the query matches a word in the wordlist
        (case-insensitive), then the query word is returned with the same case
        as the case in the wordlist.
            Example: wordlist = ["yellow"], query = "YellOw": correct = "yellow"
            Example: wordlist = ["Yellow"], query = "yellow": correct = "Yellow"
            Example: wordlist = ["yellow"], query = "yellow": correct = "yellow"


        Vowel Errors: If after replacing the vowels ('a', 'e', 'i', 'o', 'u')
        of the query word with any vowel individually, it matches a word in the
        wordlist (case-insensitive), then the query word is returned with the
        same case as the match in the wordlist.
            Example: wordlist = ["YellOw"], query = "yollow": correct = "YellOw"
            Example: wordlist = ["YellOw"], query = "yeellow": correct = "" (no match)
            Example: wordlist = ["YellOw"], query = "yllw": correct = "" (no match)

    In addition, the spell checker operates under the following precedence rules:

        + When the query exactly matches a word in the wordlist
          (case-sensitive), you should return the same word back.

        + When the query matches a word up to capitlization, you should return
          the first such match in the wordlist.

        + When the query matches a word up to vowel errors, you should return
          the first such match in the wordlist.

        + If the query has no matches in the wordlist, you should return the
          empty string.

    Given some queries, return a list of words answer, where answer[i] is the
    correct word for query = queries[i].


    =========================================================================================
    FUNCTION: vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries);
    =========================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: wordlist = ["KiTe","kite","hare","Hare"],
           queries = ["kite","Kite","KiTe","Hare","HARE","Hear","hear","keti","keet","keto"]
    Output: ["kite","KiTe","KiTe","Hare","hare","","","KiTe","","KiTe"]


    --- Example 2 ---
    Input: wordlist = ["yellow"],
           queries = ["YellOw"]
    Output: ["yellow"]


    *** Constraints ***
    1 <= wordlist.length, queries.length <= 5000
    1 <= wordlist[i].length, queries[i].length <= 7
    wordlist[i] and queries[i] consist only of only English letters.

*/

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 93.04% */
/* Space Beats: 78.48% */

/* Time  Complexity: O(N * L + Q * L) */ // Where 'L' <==> average word length
/* Space Complexity: O(N * L)         */
class Solution {
private:
    unordered_set<string> words_original;
    unordered_map<string, string> words_lowercase;
    unordered_map<string, string> words_devoweled;

public:
    vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries)
    {
        for (const string& word : wordlist)
        {
            words_original.insert(word);

            string word_lowercase = word;
            for (char& chr : word_lowercase)
                chr = tolower(chr);

            if (words_lowercase.find(word_lowercase) == words_lowercase.end())
                words_lowercase[word_lowercase] = word;

            string devoweled_word = devowel(word_lowercase);
            if (words_devoweled.find(devoweled_word) == words_devoweled.end())
                words_devoweled[devoweled_word] = word;
        }

        vector<string> result;
        result.reserve(queries.size());
        for (const string& query : queries)
            result.push_back(solve(query));

        return result;
    }

private:
    string solve(const string& query)
    {
        if (words_original.find(query) != words_original.end())
            return query;

        string query_lower = query;
        for (char& chr : query_lower)
            chr = tolower(chr);

        if (words_lowercase.find(query_lower) != words_lowercase.end())
            return words_lowercase[query_lower];

        string devoweled_query = devowel(query_lower);
        if (words_devoweled.find(devoweled_query) != words_devoweled.end())
            return words_devoweled[devoweled_query];

        return "";
    }

    string devowel(const string &word)
    {
        const int N = word.length();
        string result;
        result.reserve(N);

        for (const char& chr : word)
        {
            if (is_vowel(chr))
                result.push_back('*');
            else
                result.push_back(chr);
        }

        return result;
    }

    bool is_vowel(char chr)
    {
        return (chr == 'a' || chr == 'e' ||
                chr == 'i' || chr == 'o' ||
                chr == 'u');
    }
};
