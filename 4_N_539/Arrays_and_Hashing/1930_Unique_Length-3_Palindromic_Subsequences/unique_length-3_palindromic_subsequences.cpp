#include <iostream>
#include <vector>
#include <unordered_set>

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


/*
    ------------
    --- IDEA ---
    ------------

    We are kind of "Sliding the Window". We can notice that we only need to
    check if some <letter> exists both left and right from the current
    character.

    First we push only the very first(index 0) element to the left "map" and
    we push the rest to the right.

    Then we start iterating from the 1st index since we can't form a 3-letter
    palindrome when starting on the first and last index.

    Therefore, we iterate from i = 1; i < n-1;

    At the beginning of each iteration we have to remove the current element
    from the right "map"(vector really since only lowercase English characters
    are allowed).

    So we remove the current one(which is the middle of the palindrome) and
    we try to iterate through all 26 characters and check if there are some
    characters that are both present in the left and in the right "map".

    If that is the case, increment "unique" and insert that string into a Set
    so that we don't have duplicates since that is also required.

    After we finish checking all 26, now we have to push current element into
    the left "map" since that will be used in our next iteration.

    This repeats until we do all n characters in the string s and at the very
    end we return "unique".

*/

/* Time  Complexity: O(26 * n) */
/* Space Complexity: O(1) */
class Solution_Passes_Tests_But_TLE_1 {
public:
    int countPalindromicSubsequence(string s)
    {
        std::vector<int> left (26, 0);
        std::vector<int> right(26, 0);

        left[s[0] - 'a']++;

        for (int i = 1; i < s.length(); i++)
            right[s[i] - 'a']++;

        std::unordered_set<std::string> uset;

        int unique = 0;
        for (int i = 1; i < s.length() - 1; i++)
        {
            right[s[i] - 'a']--;

            for (int x = 0; x < 26; x++)
            {
                std::ostringstream out;
                if (left[x] > 0 && right[x] > 0)
                {
                    char chr = 'a' + x;
                    out << chr;
                    out << s[i];
                    out << chr;

                    if (uset.find(out.str()) == uset.end()) // Doesn't exist
                    {
                        unique++;
                        uset.insert(out.str());
                    }
                }
            }

            left[s[i] - 'a']++;

        }

        return unique;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This IDEA is almost equivalent to the one above, however we can notice that
    we don't need to iterate through all of the 26 characters for each letter
    in string s.

    We only have to iterate through the set of characters on one side, let's
    say it's the left side, and check if those characters are present on the
    right side, or rather in the right Set.

    However it's important to notice that we cannot only have Sets since it's
    possible that we have two or more letters on one side, so when we are
    removing the current letter from the "map" we must keep an additional
    vector to check if by removing the current letter from the right portion,
    the right portion becomes 0. Only if that's the case, we are allowed to
    remove that letters from the right Set.

    This is an optimization of the first one, but it still does give us a TLE.
    Though it is noted that we passed all tests.

*/

/* Time  Complexity: O(26 * n) */ // But this one is better than the one above
/* Space Complexity: O(1)      */
class Solution_Passes_Tests_But_TLE_2 {
public:
    int countPalindromicSubsequence(string s)
    {
        std::vector<int> right(26, 0);
        for (int i = 1; i < s.length(); i++)
            right[s[i] - 'a']++;

        std::unordered_set<char> left_uset;
        std::unordered_set<char> right_uset;

        left_uset.insert(s[0]);
        for (int i = 1; i < s.length(); i++)
            right_uset.insert(s[i]);

        std::unordered_set<std::string> result_uset;
        int unique = 0;
        for (int mid = 1; mid < s.length() - 1; mid++)
        {
            right[s[mid] - 'a']--;
            if (right[s[mid] - 'a'] == 0)
                right_uset.erase(s[mid]);

            for (const char& l : left_uset)
            {
                if (right_uset.find(l) != right_uset.end())
                {
                    std::ostringstream out;

                    out << l;
                    out << s[mid];
                    out << l;

                    result_uset.insert(out.str());
                }
            }

            left_uset.insert(s[mid]);
        }

        return result_uset.size();
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
class Solution_Efficient_1 {
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
class Solution {
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

            std::unordered_set<char> result_uset;
            for(int i = left+1; i < right; i++)
                result_uset.insert(s[i]);

            unique += result_uset.size();
        }

        return unique;
    }
};
