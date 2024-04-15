#include <iostream>
#include <vector>
#include <unordered_map>

/*
    ==============
    === MEDIUM ===
    ==============

    ==================================
    438) Find All Anagrams in a String
    ==================================

    ============
    Description:
    ============

    Given two string 's' and 'p', return an array of all the start indices of
    p's anagrams in s. You may return the answer in any order.

    An Anagram is a word or phrase formed by rearranging the letters of a
    different word or phrase, typically using all the original letters exactly
    once.

    ======================================================
    FUNCTION: vector<int> findAnagrams(string s, string p);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  s = "cbaebabacd", p = "abc"
    Output: [0, 6]

    --- Example 2 ---
    Input:  s = "abab", p = "ab"
    Output: [0, 1, 2]

    *** Constraints ***
    1 <= s.length, p.length <= 3 * 10^4
    s and p consist of lowercase English letters

*/


/*
    ------------
    --- IDEA ---
    ------------

    Make a Hash Map out of the content in string 'p'.

    In the process of filling the Hash Map of 'p' with frequencies, we do the
    same for first 'p' letters in string 's'.

    Thus we covered the "first window". We immediately check if the two Hash
    Maps are the same. If they are, then push 0 as the starting index.

    Afterwards, do these steps:
        1. Always remove the leftmost in a window by decrementing the frequency
           of that letter by one in the Hash map.

        2. Always add the right, new one, in a window by incrementing the
           frequencies of that letter by one in the Hash Map.

        3. Check if both Hash Maps, i.e. "freq_p" and "window" and if they are
           push the "left" index in vector "ret" which we're returning at the
           end.


    *** OPTIMIZATION ***

    Instead of a Hash Map, we use a vector, since we are told that both 's' and
    'p' are consisted of only lowercase English letters.

    This way, we're optimized the code hugely:
        Using real Unordered Hash Map gives us: Time Beats 21%

        Using vector as a Hash Map gives us   : Time Beats 94%

    So it's a huge optimization. Also using a vector can be considered O(1)
    Space since we're told that we only have lowercase English letters, meaning
    it does not depend on the input, meaning it's constant, hence O(1) Space.
*/

/* Time  Beats: 92.64% */
/* Space Beats: 44.01% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    std::vector<int> findAnagrams(std::string s, std::string p)
    {
        if (p.length() > s.length())
            return {};

        std::vector<int> results;

        std::vector<int> p_vec(26, 0);
        std::vector<int> s_vec(26, 0);

        for (int i = 0; i < p.length(); i++)
        {
            p_vec[p[i] - 'a']++;
            s_vec[s[i] - 'a']++;
        }

        if (p_vec == s_vec)
            results.push_back(0);

        int i = p.length();
        for (int i = p.length(); i < s.length(); i++)
        {
            s_vec[ s[i - p.length()] - 'a' ]--;
            s_vec[ s[i] - 'a' ]++;

            if (s_vec == p_vec)
                results.push_back(i - p.length() + 1);
        }

        return results;
    }
};


int
main()
{
    Solution sol;

    /* Example 1 */
    // std::string s = "cbaebabacd";
    // std::string p = "abc";

    /* Example 2 */
    // std::string s = "abab";
    // std::string p = "ab";

    /* Example 3 */
    // std::string s = "baa";
    // std::string p = "aa";

    /* Example 4 */
    std::string s = "rzzbarryrrrabis";
    std::string p = "rbra";


    std::cout << "\n\t=====================================";
    std::cout << "\n\t=== FIND ALL ANAGRAMS IN A STRING ===";
    std::cout << "\n\t=====================================\n";


    /* Write Input */
    std::cout << "\n\ts = \"" << s << "\"";
    std::cout << "\n\tp = \"" << p << "\"\n";


    /* Solution */
    std::vector<int> ret = sol.findAnagrams(s, p);


    /* Write Output */
    bool first = true;
    std::cout << "\n\tIndexes: [";
    for (auto x: ret)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n\n";


    return 0;
}
