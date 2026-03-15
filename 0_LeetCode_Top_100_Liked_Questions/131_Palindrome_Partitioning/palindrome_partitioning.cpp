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

#include <string>
#include <vector>
using namespace std;

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
public:
    vector<vector<string>> partition(string s)
    {
        const int N = s.size();
        vector<vector<string>> results;

        vector<string> curr_partition = {};
        backtracking(0, {}, s, results);

        return results;
    }

private:
    void backtracking(int start, vector<string> curr_partition, string& s, vector<vector<string>>& results)
    {
        const int N = s.size();

        if (start == N)
        {
            results.push_back(curr_partition);
            return;
        }

        for (int i = start; i < N; i++)
        {
            int len = i - start + 1;
            string substr = s.substr(start, len);

            if (is_palindrome(substr))
            {
                curr_partition.push_back(substr);
                backtracking(i + 1, curr_partition, s, results);
                curr_partition.pop_back();
            }
        }
    }

    bool is_palindrome(const string& str)
    {
        const int N = str.size();

        int L = 0;
        int R = N - 1;

        while (L < R)
        {
            if (str[L] != str[R])
                return false;

            L++;
            R--;
        }

        return true;
    }

};
