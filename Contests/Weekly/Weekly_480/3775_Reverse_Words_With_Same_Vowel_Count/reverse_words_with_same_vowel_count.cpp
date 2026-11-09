/*
    ==============
    === MEDIUM ===
    ==============

    =========================================
    3775) Reverse Words with Same Vowel Count
    =========================================

    ============
    Description:
    ============

    You are given a string s consisting of lowercase English words, each
    separated by a single space.

    Determine how many vowels appear in the first word. Then, reverse each
    following word that has the same vowel count. Leave all remaining words
    unchanged.

    Return the resulting string.

    Vowels are 'a', 'e', 'i', 'o', and 'u'.

    ========================================
    FUNCTION: string reverseWords(string s);
    ========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "cat and mice"
    Output: "cat dna mice"
    Explanation:
        The first word "cat" has 1 vowel.
        "and" has 1 vowel, so it is reversed to form "dna".
        "mice" has 2 vowels, so it remains unchanged.
        Thus, the resulting string is "cat dna mice".


    --- Example 2 ---
    Input: s = "book is nice"
    Output: "book is ecin"
    Explanation:
        The first word "book" has 2 vowels.
        "is" has 1 vowel, so it remains unchanged.
        "nice" has 2 vowels, so it is reversed to form "ecin".
        Thus, the resulting string is "book is ecin".


    --- Example 3 ---
    Input: s = "banana healthy"
    Output: "banana healthy"
    Explanation:
        The first word "banana" has 3 vowels.
        "healthy" has 2 vowels, so it remains unchanged.
        Thus, the resulting string is "banana healthy".


    *** Constraints ***
    1 <= s.length <= 10^5
    s consists of lowercase English letters and spaces.
    Words in s are separated by a single space.
    s does not contain leading or trailing spaces.

*/

#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:  9.23% */
/* Space Beats: 11.03% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution2{
private:
   static constexpr unsigned vowel_mask = (1 << ('a' - 'a')) |
                                          (1 << ('e' - 'a')) |
                                          (1 << ('i' - 'a')) |
                                          (1 << ('o' - 'a')) |
                                          (1 << ('u' - 'a'));

public:
    string reverseWords(string s)
    {
        const int N = s.size();

        vector<pair<int, string>> vec; // {vowel_count, str}

        istringstream iss(s);
        string word;
        while (getline(iss, word, ' '))
        {
            int count = count_vowels(word);
            vec.push_back( {count, word} );
        }

        s.clear();
        s.reserve(N);

        s += vec[0].second;

        const int WORDS = vec.size();
        for (int i = 1; i < WORDS; i++)
        {
            if (vec[0].first == vec[i].first)
                reverse(vec[i].second.begin(), vec[i].second.end());

            s += " ";
            s += vec[i].second;
        }

        return s;
    }

private:
    int count_vowels(const string& word)
    {
        int vowels = 0;
        for (const char& chr : word)
        {
            if (vowel_mask & (1 << (chr - 'a')))
                ++vowels;
        }

        return vowels;
    }
};
