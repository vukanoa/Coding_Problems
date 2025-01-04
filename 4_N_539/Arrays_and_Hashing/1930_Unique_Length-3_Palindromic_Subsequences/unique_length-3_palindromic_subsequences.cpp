/*
    ==============
    === MEDIUM ===
    ==============

    ==============================================
    1930) Unique Length-3 Palindromic Subsequences
    ==============================================

    ============
    Description:
    ============

    Given a string s, return the number of unique palindromes of length three
    that are a subsequence of s.

    Note that even if there are multiple ways to obtain the same subsequence,
    it is still only counted once.

    A palindrome is a string that reads the same forwards and backwards.

    A subsequence of a string is a new string generated from the original
    string with some characters (can be none) deleted without changing the
    relative order of the remaining characters.

        For example, "ace" is a subsequence of "abcde".

    ====================================================
    FUNCTION: int countPalindromicSubsequence(string s);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "aabca"
    Output: 3
    Explanation: The 3 palindromic subsequences of length 3 are:
    - "aba" (subsequence of "aabca")
    - "aaa" (subsequence of "aabca")
    - "aca" (subsequence of "aabca")


    --- Example 2 ---
    Input: s = "adc"
    Output: 0
    Explanation: There are no palindromic subsequences of length 3 in "adc".


    --- Example 3 ---
    Input: s = "bbcbaba"
    Output: 4
    Explanation: The 4 palindromic subsequences of length 3 are:
    - "bbb" (subsequence of "bbcbaba")
    - "bcb" (subsequence of "bbcbaba")
    - "bab" (subsequence of "bbcbaba")
    - "aba" (subsequence of "bbcbaba")


    *** Constraints ***
    3 <= s.length <= 105
    s consists of only lowercase English letters.

*/

#include <climits>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Remember the lefmost occurence of every character.
    Iterate thorugh stinrg s from the back and do each letter only once.

    count number of unique letter between left_most occurence of current letter
    and 'i'(which is the current inx of current letter)

*/

/* Time  Beats: 77.00% */
/* Space Beats: 56.14% */

/* Time  Complexity: O(n^2)   */
/* Space Complexity: O(n + u) */ // 'u' is the number of unique substrings
class Solution {
public:
    int countPalindromicSubsequence(std::string s)
    {
        const int N = s.length();
        int result = 0;


        vector<int> letter_left_idx(26, -1);
        for (int i = 0; i < N; i++)
        {
            if (letter_left_idx[s[i] - 'a'] == -1)
                letter_left_idx[s[i] - 'a'] = i; // leftmost idx of this letter
        }

        vector<bool> done(26, false);
        for (int i = N-1; i >= 2; i--)
        {
            if (done[s[i] - 'a'])
                continue;
            else
                done[s[i] - 'a'] = true;
            
            if (letter_left_idx[s[i] - 'a'] == i)
                continue;
            
            int idx = letter_left_idx[s[i] - 'a'];
            
            unordered_set<char> uset_unique;
            for (int x = idx + 1; x < i; x++)
                uset_unique.insert(s[x]);

            result += uset_unique.size();
        }

        return result;
    }
};



/*
    ------------
    --- IDEA ---
    ------------

    Idea is the same as the one below.

    Make a HashMap, or rather a vector, of 26 characters where the key is an
    integer, range [0, 25], and key is a pair of first and last occurrence of
    that letter in string s.

    After we fill the HashMap with values, we will go through all 26 characters
    and check if that letter occurs twice or more and if it does then start
    iterating from first occurrence+1's position until the last occurrence and
    count how many different character have you seen.

    What is the purpose of this?
    Consider this example:

        "bbcbaba"

    Let's try letter 'b'. Its first occurence is at position: 0 and its last
    occurrence is at position 5.

    Therefore, we iterate from [1, 4], inclusive, i.e. i = first+1; i < second;

    Since we are searching for unique 3 letters palindromes and we have fixed
    two on the side, we only need to check for unique characters between those
    two fixed on the sides.

    However, you might think that we would, somehow, count some element twice
    since, you think, we don't check which letters are fixed, but that's not
    true.

    We are resetting the Set for each letter.
    Why?

    Since we are going to fix two elements(same elements) for each letter, we
    only care about the middle one.

    If we had a global Set, then we would have that problem. But we are
    resetting the Set since we are certain that it's a different unique string
    each time since we have fixed different characters on two ends.

*/

/* Time  Beats: 69.69% */
/* Space Beats: 60.44% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    int countPalindromicSubsequence(std::string s)
    {
        // HashMap of <letter>'s first and last occurrence in string s
        std::vector<std::pair<int, int> > letter(26, {-1, -1});

        for (int i = 0 ; i < s.length(); i++ )
        {
            if (letter[s[i] - 'a'].first == -1)
                letter[s[i] - 'a'].first = i;  // Character appered for the first time
            else
                letter[s[i] - 'a'].second = i; // Last occurrence will be stored at last
        }

        int unique = 0 ;
        for (int i = 0 ; i < 26; i++ )
        {
            if (letter[i].second != -1) // Only if alphabet occured second time
            {
                // Using set to keep only unique elements between the range.
                std::unordered_set<char> uset;
                for (int x = letter[i].first + 1; x < letter[i].second ; x++)
                    uset.insert(s[x]);

                unique += uset.size(); // Add number of unique elements
            }
        }

        return unique;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, but implemented a bit differently. This one gives better
    results on LeetCode.

*/

/* Time  Beats: 81.67% */
/* Space Beats: 69.87% */
/* Time  Complexity: O(n) */

/* Space Complexity: O(n) */
class Solution_3 {
public:
    int countPalindromicSubsequence(std::string s)
    {
        // HashMap of <letter>'s first and last occurrence in string s
        vector<std::pair<int, int>> letters(26, std::pair<int, int>({INT_MAX, INT_MIN}));

        for(int i = 0; i < s.length(); i++)
        {
            letters[s[i] - 'a'].first  = std::min(letters[s[i] - 'a'].first,  i);
            letters[s[i] - 'a'].second = std::max(letters[s[i] - 'a'].second, i);
        }

        int unique = 0;
        for(const auto& entry : letters)
        {
            int left  = entry.first;
            int right = entry.second;

            if(left == INT_MAX)
                continue;

            std::unordered_set<char> uset_unique_letters_between;
            for(int i = left+1; i < right; i++)
                uset_unique_letters_between.insert(s[i]);

            unique += uset_unique_letters_between.size();
        }

        return unique;
    }
};
