/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    49) Group Anagrams
    ===========================

    ============
    Description:
    ============

    Given an array of strings 'strs', group the anagrams together. You can
    return the answer in any order.

    An Anagram is a word or phrase formed by rearranging the letters of a
    different word or phrase, typically using all the original letters exactly
    once.

    =====================================================================
    FUNCTION: vector<vector<string>> groupAnagrams(vector<string>& strs);
    =====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
    Output: [["bat"], ["nat", "tan"], ["ate", "eat", "tea"]]

    --- Example 2 ---
    Input:  strs = [""]
    Output: [[""]]

    --- Example 3 ---
    Input:  strs = ["a"]
    Output: [["a"]]

    *** Constraints ***
    1 <= strs.length <= 10^4
    0 <= strs[i].length <= 100
    strs[i] consists of lowercase English letters

*/

#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Naive Solution, but good for beginners.

    Two strings are anagrams if and only if their sorted strings are equal.

    We have a Hash Map with lexicographically sorted string as a "key" and
    original strings(in a vector) as "values"
*/

/* Time  Beats: 86.53% */
/* Space Beats: 82.3% */

/* Time  Complexity: O(N * M * logM) */ // M is the longest string in strs
/* Space Complexity: O(N * M)        */
class Solution_Naive {
public:
    vector<vector<string>>groupAnagrams(vector<string>& strs)
    {
        const int N = strs.size();
        vector<vector<string>> result;

        unordered_map<string, vector<string>> groups;

        // O(N * M * logM) (entire block)
        for (const string& orig_str : strs) // O(N)
        {
            string sorted_str = orig_str;
            sort(sorted_str.begin(), sorted_str.end()); // O(M * log(M))

            // O(M) for hashing sorted_str and O(1) Amortized for "push_back"
            groups[sorted_str].push_back(orig_str);
        }

        // O(N) (entire block)
        for (const auto& entry : groups) // O(N)
            result.push_back(entry.second);

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Instead of sorting each string, we can use frequencies of each of the 26
    characaters(since there will only be lowercase English characters) to
    recreate a sorted string in O(M) instead of O(M * logM).

    That way we've reduced Time Complexity by an order of O(logM).

    Note:
    This one is Optimal in terms of Overall Time and Space Compleixty, however
    the one BELOW this Solution is an OPTIMAL(named "Solution_Optimal") way to
    implement this.

*/

/* Time  Complexity: O(N * M) */ // M is the longest string in strs
/* Space Complexity: O(N * M) */
class Solution_Verbose {
public:
    vector<vector<string>>groupAnagrams(vector<string>& strs)
    {
        const int N = strs.size();
        vector<vector<string>> result;

        unordered_map<string, vector<string>> groups;

        // O(N * M)
        for (int i = 0; i < N; i++) // O(N)
        {
            int letters[26] = {0}; // O(1)
            for (const char& chr : strs[i]) // O(M)
                letters[chr - 'a']++;

            string sorted_str;
            sorted_str.reserve(static_cast<int>(strs[i].size())); // O(1) Amortized

            // O(M)
            for (int letter_idx = 0; letter_idx < 26; letter_idx++) // O(1)
            {
                for (int j = 0; j < letters[letter_idx]; j++)
                    sorted_str += static_cast<char>(letter_idx + 'a'); // O(1)
            }

            // O(M) for hashing sorted_str and O(1) Amortized for "push_back"
            groups[sorted_str].push_back(strs[i]);
        }

        // O(N) (entire block)
        for (const auto& entry : groups)
            result.push_back(entry.second);

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    The better way is NOT to recreate a sorted_str from each string and then
    use THAT as a hash, instead it's better to hash only frequencies of each
    of 26 characters:

    Example:
        "2#0#...0#3#"

    Would mean: "aazzz" when sorted, which is what we want.

*/

/* Time  Complexity: O(N * M) */ // M is the longest string in strs
/* Space Complexity: O(N * M) */
class Solution_Optimal {
public:
    vector<vector<string>>groupAnagrams(vector<string>& strs)
    {
        const int N = strs.size();
        vector<vector<string>> result;

        unordered_map<string, vector<string>> groups;

        // O(N * M) (entire block)
        for (int i = 0; i < N; i++) // O(N)
        {
            int letters[26] = {0}; // O(1)
            for (const char& chr : strs[i]) // O(M)
                letters[chr - 'a']++;

            string key;
            // O(1) (entire block)
            for (const int& freq : letters) // O(1)
                key += to_string(freq) + "#"; // O(1) Amortized

            // O(M) for hashing sorted_str and O(1) Amortized for "push_back"
            groups[key].push_back(strs[i]);
        }

        // O(N) (entire block)
        for (const auto& entry : groups)
            result.push_back(entry.second);

        return result;
    }
};
