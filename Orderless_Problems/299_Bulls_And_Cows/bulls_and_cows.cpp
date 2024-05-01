#include <iostream>
#include <unordered_set>
#include <unordered_map>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    299) Bulls and Cows
    ===========================

    ============
    Description:
    ============

    You are playing the Bulls and Cows game with your friend.

    You write down a secret number and ask your friend to guess what the number
    is. When your friend makes a guess, you provide a hint with the following
    info:

        + The number of "bulls", which are digits in the guess that are in the
          correct position.

        + The number of "cows", which are digits in the guess that are in your
          secret number but are located in the wrong position. Specifically,
          the non-bull digits in the guess that could be rearranged such that
          they become bulls.

    Given the secret number secret and your friend's guess guess, return the
    hint for your friend's guess.

    The hint should be formatted as "xAyB", where x is the number of bulls and
    y is the number of cows. Note that both secret and guess may contain
    duplicate digits.

    =====================================================================
    FUNCTION: std::string getHint(std::string secret, std::string guess);
    =====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: secret = "1807", guess = "7810"
    Output: "1A3B"
    Explanation: Bulls are connected with a '|' and cows are underlined:
    "1807"
      |
    "7810"


    --- Example 2 ---
    Input: secret = "1123", guess = "0111"
    Output: "1A1B"
    Explanation: Bulls are connected with a '|' and cows are underlined:
    "1123"        "1123"
      |      or     |
    "0111"        "0111"

    Note that only one of the two unmatched 1s is counted as a cow since the
    non-bull digits can only be rearranged to allow one 1 to be a bull.




    *** Constraints ***
    1 <= secret.length, guess.length <= 1000
    secret.length == guess.length
    secret and guess consist of digits only.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 54.39% */
/* Space Beats:  5.31% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::string getHint(std::string secret, std::string guess)
    {
        std::unordered_set<int> bull_indices;
        std::unordered_map<char, int> potential_cows;

        for (int i = 0; i < guess.length(); i++)
        {
            if (secret[i] == guess[i])
                bull_indices.insert(i);
            else
                potential_cows[guess[i]]++;
        }

        int cows = 0;
        for (int i = 0; i < secret.length(); i++)
        {
            if (bull_indices.find(i) != bull_indices.end()) // If i exists in the Set
                continue;

            if(potential_cows[secret[i]] > 0)
            {
                potential_cows[secret[i]]--;
                cows++;
            }
        }

        std::ostringstream out;

        out << bull_indices.size();
        out << "A";
        out << cows;
        out << "B";

        return out.str();
    }
};
