#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cstring>

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


/*

    **************************************************************************
    ***************************** IMPORTANT NOTE *****************************
    **************************************************************************

    Theoretical Time Complexity is better in 2nd Solution, however due to many
    optimizations of C++, in practice, 1st code runs faster on Leetcode.

    There are various factors for that. One thing is that when we're using a
    small to mid sized array, it's better to use vector.

    Also, sort() is highly highly optimized, and thus, for these small examples
    it works faster than going each time(i.e. for each string) through 26
    characters and incrementing values of correct letters.

    But, overall, Time Complexity of 2nd Solution is indeed better.
*/

/*
    ------------
    --- IDEA ---
    ------------

    Two strings are anagrams if and only if their sorted strings are equal.

    We have a Hash Map with lexicographically sorted string as a "key" and
    original strings(in a vector) as "values"
*/

/* Time  Beats: 86.53% */
/* Space Beats: 82.3% */

/* Time  Complexity: O(n * k * logk)
   Where 'n' is the length of "strs", and 'k' is the maximum length of a string
   in "strs". The outer loop has complexity O(n) as we iterate through each
   string. Then, we sort each string in O(k * logk) time.
*/
/* Space Complexity: O(n * k) */
class Solution_Verbose {
public:
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs)
    {
        std::unordered_map<std::string, std::vector<std::string>> umap;

        for (int i = 0; i < strs.size(); i++)
        {
            std::string original_str = strs[i];
            std::string sorted_str   = strs[i]; // We'll sort this one

            std::sort(sorted_str.begin(), sorted_str.end());

            umap[sorted_str].push_back(original_str);
        }

        std::vector<std::vector<std::string>> results;
        for (auto& entry : umap)
            results.push_back(entry.second);

        return results;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Two strings are anagrams if and only if their character counts(respective
    number of occurrences of each character) are the same.

    We have an array "counter" which counts number of occurrences of each
    letter in a current string.

    Once we've done that, we transform that array into a string and we use it
    as a key for our Hash Map.
    As for "values" we keep a vector of original strings.

    At the end we iterate through Hash Map's keys and add each "value"(entire
    vector) to our vector of vector "results" and we return that.

*/

/* Time  Beats: 60.19% */
/* Space Beats: 24.28% */

/* Time  Complexity: O(n * k)
   Where 'n' is the length of "strs", and 'k' is the maximum length of a string
   in "strs". Counting each string is linear in the size of the string, and we
   count every string.
*/
/* Space Complexity: O(n * k) */
class Solution_improved{
public:
    std::vector<std::vector<std::string>>
    groupAnagrams(std::vector<std::string>& strs)
    {
        std::vector<std::vector<std::string>> results;
        std::unordered_map<std::string, std::vector<std::string>> umap;

        int counter[26];

        for (const std::string& str : strs)
        {
            memset(counter, 0, sizeof(counter)); // sizeof(int) * 26

            for (const char& chr : str)
                counter[chr - 'a']++;

            std::string key;
            for (int i = 0; i < 26; i++)
                key += counter[i];

            umap[key].push_back(str);
        }

        for (const auto& m : umap)
            results.push_back(m.second);

        return results;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Similar to first solution(Solution_Verbose), just in one pass.

*/

/* Time  Beats: 98.72% */
/* Space Beats: 96.71% */

/* Time  Complexity: O(k * n * logn) */
/* Space Complexity: O(k * n)     */
class Solution_Efficient {
public:
    std::vector<std::vector<std::string>>
    groupAnagrams(std::vector<std::string>& strs)
    {
        std::unordered_map<std::string, int> umap;
        std::vector<std::vector<std::string>> results;

        for (const std::string& str: strs)
        {
            std::string key = str;
            std::sort(key.begin(), key.end());

            if (umap.find(key) == umap.end()) // New Anagram
            {
                umap[key] = results.size();
                results.push_back({});
            }

            results[umap[key]].push_back(str);
        }

        return results;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Equivalent to the one above, however it is implemented a bit differently.
    Some people may find this approach easier to read than the above one.

    Even though, for some reason, above Solution runs faster on LeetCode.
    Probably because "Wall Time Clock" is lower than here.

*/

/* Time  Beats: 78.56% */
/* Space Beats: 59.88% */

/* Time  Complexity: O(k * n * logn) */
/* Space Complexity: O(k * n)     */
class Solution_Efficient_2 {
public:
    std::vector<std::vector<std::string>>
    groupAnagrams(std::vector<std::string>& strs)
    {
        std::vector<std::vector<std::string>> results;

        std::unordered_map<std::string, std::vector<std::string>> umap;
        for (const std::string& str : strs)
        {
            std::string sorted_str = str;
            std::sort(sorted_str.begin(), sorted_str.end());

            umap[sorted_str].push_back(str);
        }

        for (const auto& entry : umap)
        {
            std::vector<std::string> group;
            for (const std::string& str : entry.second)
                group.push_back(str);

            results.push_back(group);
        }

        return results;
    }
};


int
main()
{
    // Solution_Verbose  sol_verbose;
    // Solution_improved sol_improved;
    Solution_Efficient   sol_eff;
    Solution_Efficient_2 sol_eff_2;

    /* Example 1 */
    std::vector<std::string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};

    /* Example 2 */
    // std::vector<std::string> strs = {""};

    /* Example 3 */
    // std::vector<std::string> strs = {"a"};

    /* Example 4 */
    // std::vector<std::string> strs = {"", "b"};

    /* Example 5 */
    // std::vector<std::string> strs = {"", ""};

    /* Example 6 */
    // std::vector<std::string> strs = {"hhhhu","tttti","tttit","hhhuh","hhuhh","tittt"};

    /* Example 7 */
    // std::vector<std::string> strs = {"ddddddddddg","dgggggggggg"};

    std::cout << "\n\t======================";
    std::cout << "\n\t=== GROUP ANAGRAMS ===";
    std::cout << "\n\t======================\n";


    /* Write Input */
    bool first = true;
    std::cout << "\n\tCandidates: [";
    for (auto x: strs)
    {
        if (!first)
            std::cout << ", ";

        std::cout << "\"" << x << "\"";
        first = false;
    }
    std::cout << "]\n";


    /* Solution */
    // std::vector<std::vector<std::string>> results = sol_verbose.groupAnagrams(strs);
    // std::vector<std::vector<std::string>> results = sol_improved.groupAnagrams(strs);
    std::vector<std::vector<std::string>> results = sol_eff.groupAnagrams(strs);
    // std::vector<std::vector<std::string>> results = sol_eff_2.groupAnagrams(strs);


    /* Write Output */
    first = true;
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
