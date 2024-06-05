#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ============================
    1002) Find Common Characters
    ============================

    ============
    Description:
    ============

    Given a string array words, return an array of all characters that show up
    in all strings within the words (including duplicates). You may return the
    answer in any order.

    ============================================================
    FUNCTION: vector<string> commonChars(vector<string>& words);
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: words = ["bella","label","roller"]
    Output: ["e","l","l"]

    --- Example 2 ---
    Input: words = ["cool","lock","cook"]
    Output: ["c","o"]


    *** Constraints ***
    1 <= words.length <= 100
    1 <= words[i].length <= 100
    words[i] consists of lowercase English letters.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Construct N vectors of of 26 zeros which represents frequencies of each
    letter for that word.

    N is the number of different words given in input "words".

    For example: word "bella" will be represents in a vector like this:


    [1,    --> a   // One a
     1,    --> b   // One b
     0,    --> c
     0,    --> d
     1,    --> e   // One e
     0,    --> f
     0,    --> g
     0,    --> h
     0,    --> i
     0,    --> j
     0,    --> k
     2,    --> l   // Two l's
     0,    --> m
     0,    --> n
     0,    --> o
     0,    --> p
     0,    --> q
     0,    --> r
     0,    --> s
     0,    --> t
     0,    --> u
     0,    --> v
     0,    --> w
     0,    --> x
     0,    --> y
     0]    --> z


     We make N of such vectors, one for each words, and then then we take the
     minimum out of every 'a', every 'b', etc.

     Once we have that, we simply output it to our result vector.

*/

/* Time  Beats: 70.90% */
/* Space Beats: 51.34% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::vector<std::string> commonChars(std::vector<std::string>& words)
    {
        const int N = words.size();

        std::vector<std::vector<int>> vec_letters_freq(N, std::vector<int>(26, 0));

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < words[i].size(); j++)
            {
                vec_letters_freq[i][words[i][j] - 'a']++;
            }
        }


        std::vector<std::string> result;
        for (int letter_idx = 0; letter_idx < 26; letter_idx++)
        {
            int repeats = INT_MAX;

            for (int i = 0; i < N; i++)
            {
                repeats = std::min(repeats, vec_letters_freq[i][letter_idx]);
            }

            while (repeats-- > 0)
            {
                char chr = static_cast<char>(letter_idx + 'a');
                std::string str(1, chr);

                result.push_back(str);
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, though we use a different way of converting char's to string

*/

/* Time  Beats: 96.29% */
/* Space Beats: 51.34% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_2 {
public:
    std::vector<std::string> commonChars(std::vector<std::string>& words)
    {
        const int N = words.size();

        std::vector<std::vector<int>> vec_letters_freq(N, std::vector<int>(26, 0));

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < words[i].size(); j++)
            {
                vec_letters_freq[i][words[i][j] - 'a']++;
            }
        }


        std::vector<std::string> result;
        for (int letter_idx = 0; letter_idx < 26; letter_idx++)
        {
            int repeats = INT_MAX;

            for (int i = 0; i < N; i++)
            {
                repeats = std::min(repeats, vec_letters_freq[i][letter_idx]);
            }

            /*
                Another way of constructing a character out from an integer and
                a string out of a character
            */
            while (repeats-- > 0)
            {
                char chr = static_cast<char>(letter_idx + 'a');

                std::ostringstream out;
                out << chr;

                result.push_back(out.str());
            }
        }

        return result;
    }
};
