/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================
    1807) Evaluate a Bracket Pairs of a String
    ==========================================

    ============
    Description:
    ============

    You are given a string s that contains some bracket pairs, with each pair
    containing a non-empty key.

        + For example, in the string "(name)is(age)yearsold", there are two
          bracket pairs that contain the keys "name" and "age".

    You know the values of a wide range of keys. This is represented by a 2D
    string array knowledge where each knowledge[i] = [keyi, valuei] indicates
    that key keyi has a value of valuei.

    You are tasked to evaluate all of the bracket pairs. When you evaluate a
    bracket pair that contains some key keyi, you will:

        + Replace keyi and the bracket pair with the key's corresponding
          valuei.

        + If you do not know the value of the key, you will replace keyi and
          the bracket pair with a question mark "?" (without the quotation
          marks).

    Each key will appear at most once in your knowledge. There will not be any
    nested brackets in s.

    Return the resulting string after evaluating all of the bracket pairs.

    =======================================================================
    FUNCTION: string evaluate(string s, vector<vector<string>>& knowledge);
    =======================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "(name)is(age)yearsold", knowledge = [["name","bob"],["age","two"]]
    Output: "bobistwoyearsold"
    Explanation:
    The key "name" has a value of "bob", so replace "(name)" with "bob".
    The key "age" has a value of "two", so replace "(age)" with "two".

    --- Example 2 ---
    Input: s = "hi(name)", knowledge = [["a","b"]]
    Output: "hi?"
    Explanation: As you do not know the value of the key "name", replace
                 "(name)" with "?".

    --- Example 3 ---
    Input: s = "(a)(a)(a)aaa", knowledge = [["a","yes"]]
    Output: "yesyesyesaaa"
    Explanation: The same key can appear multiple times.
    The key "a" has a value of "yes", so replace all occurrences of "(a)" with
    "yes". Notice that the "a"s not in a bracket pair are not evaluated.


    *** Constraints ***
    1 <= s.length <= 10^5
    0 <= knowledge.length <= 10^5
    knowledge[i].length == 2
    1 <= keyi.length, valuei.length <= 10
    s consists of lowercase English letters and round brackets '(' and ')'.
    Every open bracket '(' in s will have a corresponding close bracket ')'.
    The key in each bracket pair of s will be non-empty.
    There will not be any nested bracket pairs in s.
    keyi and valuei consist of lowercase English letters.
    Each keyi in knowledge is unique.

*/

#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 72.27% */
/* Space Beats: 80.69% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge)
    {
        const int N = s.size();
        string result;
        result.reserve(N); // To prevent repeated reapllocations

        unordered_map<string, string> umap;
        for (const auto& entry : knowledge)
        {
            const string& key = entry[0];
            const string& val = entry[1];

            umap[key] = val;
        }

        int i = 0;
        while (i < N)
        {
            if (s[i] == '(')
            {
                int close_parenthesis_idx = s.find(")", i + 1);

                int key_len = (close_parenthesis_idx - 1) - (i + 1) + 1;
                string key  = s.substr(i + 1, key_len);

                if (umap.find(key) == umap.end()) // does NOT exist in HashMap
                    result += '?';
                else
                    result += umap[key];

                // Increment
                i = close_parenthesis_idx + 1;
            }
            else
            {
                result += s[i];

                // Increment
                ++i;
            }
        }


        return result;
    }
};
