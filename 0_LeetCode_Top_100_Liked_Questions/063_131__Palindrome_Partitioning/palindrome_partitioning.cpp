#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    =============================
    131) Palindrome Partitioning
    =============================

    ============
    Description:
    ============

    Given a string 's', partition 's' such that every substring of the
    partition is a palindrome. Return all possible palindrome partitioning of
    's'.

    =====================================================
    FUNCTION: vector<vector<string>> partition(string s);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  Input s = "aab"
    Output: [["a", "a", "b"], ["aa", "b"]]

    --- Example 2 ---
    Input:  s = "a"
    Output: [["a"]]

    *** Constraints ***
    1 <= s.length <= 16
    's' containts only lowercase English letters

*/


/*
    ------------
    --- IDEA ---
    ------------

    For the first partition we have 3 choices:
        1) "a" by itself if we took just the first character of the string.
        2) "aa", if we took first two characters.
        3) "aab", if we took the entire string as our first partition.

                        *** Backtracking ***

                          _____"aab"_____
                         /       |       \
                       "a"      "aa"      "aab"

        1) "a" is indeed a palindrome, so we continue down that path with
           remaining characters, which are "ab" in this case.

                        *** Backtracking ***

                          _____"aab"_____
                         /       |       \
                       "a"      "aa"      "aab"
                       / \
                     "a" "ab"

    Now we have two options:
        1) "a" by itself, if we took just the first character of the
           remaining string "ab".

        2) "ab", if we took the entire remaining string.


        Since 1) "a", is indeed a palindrome, we coninue down that path.

                        *** Backtracking ***

                          _____"aab"_____
                         /
                       "a"
                       / \
                     "a" "ab"
                     /
                   "b"
                  (end)

        "b" was the only remaining character and it is a palindrome by itself
        so we push it in current_vec.

        Now we go dfs(i + 1) but that is out of bounds, so we push the entire
        current_vec, which at this point is ["a", "a", "b"] to vector "results"
        and we Backtrack.

        We pop "b" and Backtrack again since that is the last character.
        We pop "a" and go dfs(i + 1) and now we're checking the "ab"


                        *** Backtracking ***

                          _____"aab"_____
                         /
                       "a"
                       / \
                     "a" "ab"
                     /    ^^
                   "b"
                  (end)

        We can clearly see that it's not a palindrome and thus Backtrack.

        At the very end the Backtracking Tree look like this:


                        *** Backtracking ***

                          _____"aab"_____
                         /       |       \
                       "a"      "aa"      "aab"
                       / \       |         ^^^
                     "a" "ab"   "b"
                     /    ^^   (end)
                   "b"
                  (end)

    Legend:
          ^^^ => Backtrack since it is NOT a Palindrome. Do not store it.

        (end) => No more characters to go "down", push the current_vec.
*/

/* Time  Beats: 82.73% */
/* Space Beats: 96.39% */

/* Time  Complexity: O(2^n) */
/* Space Complexity: O(n^2) */
class Solution {
private:
    // O(2^n)
    void backtracking_dfs(std::string& s, int start, std::vector<std::string>& current_vec, std::vector<std::vector<std::string>>& results)
    {
        if (start == s.length())
            results.push_back(current_vec);
        else
        {
            for (int i = start; i < s.length(); i++)
            {
                if (palindrome(s, start, i))
                {
                    current_vec.push_back(s.substr(start, i - start + 1));
                    backtracking_dfs(s, i + 1, current_vec, results);
                    current_vec.pop_back();
                }
            }
        }
    }

    // O(n)
    bool palindrome(std::string& str, int left, int right)
    {
        while (left < right)
        {
            if (str[left++] != str[right--])
                return false;
        }

        return true;
    }

public:
    std::vector<std::vector<std::string>> partition(std::string s)
    {
        std::vector<std::vector<std::string>> results;
        std::vector<std::string> current_vec;

        backtracking_dfs(s, 0, current_vec, results);

        return results;
    }
};


int
main()
{
    Solution sol;

    /* Example 1 */
    // std::string s = "aab";

    /* Example 2 */
    // std::string s = "a";

    /* Example 3 */
    // std::string s = "";

    /* Example 4 */
    // std::string s = "abcba";

    /* Example 5 */
    // std::string s = "baab";

    /* Example 6 */
    // std::string s = "bab";

    /* Example 7 */
    std::string s = "abcdcba";

    /* Example 8 */
    // std::string s = "aaa";


    std::cout << "\n\t===============================";
    std::cout << "\n\t=== PALINDROME PARTITIONING ===";
    std::cout << "\n\t===============================\n\n";


    /* Write Input */
    std::cout << "\tString: \"";
    for (const auto& x: s)
        std::cout << x;
    std::cout << "\"\n";


    /* Solution */
    std::vector<std::vector<std::string>> results = sol.partition(s);


    /* Write Output */
    bool first = true;
    std::cout << "\n\tResults: [";
    for (auto x: results)
    {
        if (!first)
            std::cout << ", ";

        bool first_first = true;
        std::cout << "[";
        for (const auto& xx : x)
        {
            if (!first_first)
                std::cout << ", ";

            std::cout << "\"" << xx << "\"";
            first_first = false;
        }
        std::cout << "]";

        first = false;
    }
    std::cout << "]\n\n";


    return 0;
}
