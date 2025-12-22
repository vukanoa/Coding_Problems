/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    2514) Count Anagrams
    ===========================

    ============
    Description:
    ============

    You are given a string s containing one or more words. Every consecutive
    pair of words is separated by a single space ' '.

    A string t is an anagram of string s if the ith word of t is a permutation
    of the ith word of s.

    For example, "acb dfe" is an anagram of "abc def", but "def cab" and "adc
    bef" are not.

    Return the number of distinct anagrams of s. Since the answer may be very
    large, return it modulo 10^9 + 7.

    ======================================
    FUNCTION: int countAnagrams(string s);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "too hot"
    Output: 18
    Explanation: Some of the anagrams of the given string are "too hot", "oot
                 hot", "oto toh", "too toh", and "too oht".

    --- Example 2 ---
    Input: s = "aa"
    Output: 1
    Explanation: There is only one anagram possible for the given string.


    *** Constraints ***
    1 <= s.length <= 10^5
    s consists of lowercase English letters and spaces ' '.
    There is single space between consecutive words.

*/

#include <sstream>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 68.15% */
/* Space Beats: 91.08% */

/* Time  Complexity: O(N + L) */
/* Space Complexity: O(N)     */
class Solution {
public:
    const int MODULO = 1e9 + 7;
    int factorial[100002];

    int countAnagrams(string s)
    {
        compute_factorials();

        istringstream input_stream(s);
        string curr_word;

        int total_anagram_count = 1;
        while (input_stream >> curr_word)
            total_anagram_count = modular_multiply(total_anagram_count, count_distinct_anagrams_for_word(curr_word));

        return total_anagram_count;
    }

private:
    int modular_multiply(int lhs, int rhs)
    {
        return (static_cast<long long>(lhs) * rhs) % MODULO;
    }

    int binary_exponentiation(int base, int exponent)
    {
        if ( ! exponent)
            return 1;

        int half_power = binary_exponentiation(base, exponent / 2);

        if (exponent & 1)
            return modular_multiply(base, modular_multiply(half_power, half_power));

        return modular_multiply(half_power, half_power);
    }

    int modular_multiplicative_inverse(int value)
    {
        return binary_exponentiation(value, MODULO - 2);
    }

    void compute_factorials()
    {
        factorial[0] = 1;

        for (int i = 1; i <= 100001; i++)
        {
            factorial[i] = modular_multiply(factorial[i - 1], i);
        }
    }

    int count_distinct_anagrams_for_word(string word)
    {
        const int N = word.size();

        int character_frequency[26] = {0};

        for (int i = 0; i < N; i++)
            character_frequency[word[i] - 'a']++;

        int total_permutations = factorial[N];

        int duplicate_factorial_product = 1;
        for (int i = 0; i < 26; i++)
        {
            duplicate_factorial_product = modular_multiply(duplicate_factorial_product, factorial[character_frequency[i]]);
        }

        return modular_multiply(total_permutations, modular_multiplicative_inverse(duplicate_factorial_product)
        );
    }

};
