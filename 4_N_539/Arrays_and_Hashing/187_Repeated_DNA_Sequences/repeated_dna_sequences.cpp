#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    187) Repeated DNA Sequences
    ===========================

    ============
    Description:
    ============

    The DNA sequence is composed of a series of nucleotides abbreviated as 'A',
    'C', 'G', and 'T'.

        For example, "ACGAATTCCG" is a DNA sequence.

    When studying DNA, it is useful to identify repeated sequences within the
    DNA.

    Given a string s that represents a DNA sequence, return all the
    10-letter-long sequences (substrings) that occur more than once in a DNA
    molecule. You may return the answer in any order.

    ============================================================
    FUNCTION: vector<string> findRepeatedDnaSequences(string s);
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
    Output: ["AAAAACCCCC","CCCCCAAAAA"]

    --- Example 2 ---
    Input: s = "AAAAAAAAAAAAA"
    Output: ["AAAAAAAAAA"]


    *** Constraints ***
    1 <= s.length <= 105
    s[i] is either 'A', 'C', 'G', or 'T'.

*/


/*
    ------------
    --- IDEA ---
    ------------

    Self-Explanatory.

*/

/* Time  Beats: 69.01% */
/* Space Beats: 31.25% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s)
    {
        if (s.length() < 11) // If it's impossible to make any 10-letter-long OR if it's possible to
            return {};       // Only make a single one, in those cases - return an empty vector.

        std::unordered_map<std::string, int> DNAs;

        DNAs.insert({s.substr(0, 10), 1});

        for (int i = 10; i < s.length(); i++)
        {
            std::string str = s.substr(i-10+1, 10);

            if (DNAs.find(str) == DNAs.end())
                DNAs.insert({str, 1});
            else
                DNAs[str]++;
        }

        std::vector<std::string> results;
        for (auto& entry : DNAs)
        {
            if (entry.second > 1)
                results.push_back(entry.first);
        }

        return results;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Virtually the same as above, but a bit more efficient way of implementing.

*/

/* Time  Beats: 85.03% */
/* Space Beats: 81.08% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s)
    {
        if (s.length() < 11) // If it's impossible to make any 10-letter-long OR if it's possible to
            return {};       // Only make a single one, in those cases - return an empty vector.

        std::vector<std::string> results;

        std::unordered_set<std::string> in_results;
        std::unordered_set<std::string> DNAs;

        for (int i = 0; i < s.length()-9; i++)
        {
            std::string str = s.substr(i, 10);

            if (DNAs.count(str) != 0 && in_results.count(str) == 0)
            {
                results.push_back(str);
                in_results.insert(str);
            }

            DNAs.insert(str);
        }

        return results;
    }
};
