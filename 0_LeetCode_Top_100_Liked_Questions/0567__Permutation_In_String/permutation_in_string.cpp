#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    567) Permutation In String
    ===========================

    ============
    Description:
    ============

    Given two strings s1 and s1, return true if s2 contains a permutation of
    s1, or false otherwise.

    In other words, return true if one of s1's premutations is the substring of
    s2.

    ====================================================
    FUNCTION: bool checkInclusion(string s1, string s2);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  s1 = "ab", s2 = "eidbaooo"
    Output: true
    Explanation: s2 contains one permutation of s1 ("ba").

    --- Example 2 ---
    Input:  s1 = "ab", s2 = "eidboaoo"
    Output: false

    *** Constraints ***
    1 <= s1.length, s2.length <= 10^4
    s1 and s2 consist of lowercase English letters

*/

/*
    ------------
    --- IDEA ---
    ------------

    Idea is **Absolutely Equivalent** to:
        LeetCode Problem 438 "Find All Anagrams In A String"

    The only thing that differs is the return type.

    In the 438-th Problem we needed to count all the anagrams, while in this
    one we only have to tell if there is a permutation of s1 in s2.

    So it's even easier.

*/

/* Time  Beats: 92.60% */
/* Space Beats: 91.21% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Sliding_Window {
public:
    bool checkInclusion(std::string s1, std::string s2)
    {
        if (s1.length() > s2.length())
            return false;

        std::vector<int> s1_map(26, 0);
        std::vector<int> s2_map(26, 0);

        /* First window */
        for (int i = 0; i < s1.length(); i++)
        {
            s1_map[s1[i] - 'a']++;
            s2_map[s2[i] - 'a']++;
        }

        if (s1_map == s2_map)
            return true;

        int left  = 0;
        int right = s1.length();

        /* Sliding Window */
        while (right < s2.length())
        {
            s2_map[s2[left] - 'a']--;
            left++;

            s2_map[s2[right] - 'a']++;
            right++;

            if (s1_map == s2_map)
                return true;
        }

        return false;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above, implemented in another way.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  35.38% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Another_Implementation {
public:
    bool checkInclusion(string s1, string s2)
    {
        vector<int> letters_one(26, 0);
        vector<int> letters_two(26, 0);

        for (const char& chr : s1)
            letters_one[chr - 'a']++;

        int left  = 0;
        int right = 0;
        while (right < s2.length())
        {
            letters_two[s2[right] - 'a']++;

            // Increment
            right++;

            if (right < s1.length())
                continue;

            if (letters_one == letters_two)
                return true;

            letters_two[s2[left] - 'a']--;
            left++; // Shrink left-bound, i.e. "Slide Window"
        }

        return false;
    }
};


int
main()
{
    Solution_Sliding_Window sol_win;


    /* Example 1 */
    // std::string s1 = "ab";
    // std::string s2 = "eidbaooo";

    /* Example 2 */
    // std::string s1 = "ab";
    // std::string s2 = "eidboaoo";

    /* Example 3 */
    std::string s1 = "abc";
    std::string s2 = "bbbca";

    std::cout << "\n\t=============================";
    std::cout << "\n\t=== PERMUTATION IN STRING ===";
    std::cout << "\n\t=============================\n";


    /* Write Input */
    std::cout << "\n\ts1 = \"" << s1 << "\"";
    std::cout << "\n\ts2 = \"" << s2 << "\"\n";


    /* Solution */
    bool b = sol_win.checkInclusion(s1, s2);


    /* Write Output */
    if (b)
        std::cout << "\n\tOutput: True\n\n";
    else
        std::cout << "\n\tOutput: False\n\n";


    return 0;
}
