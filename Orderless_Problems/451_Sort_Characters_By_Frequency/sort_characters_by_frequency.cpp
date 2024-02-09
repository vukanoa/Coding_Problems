#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    451) Sort Characters By Frequency
    =================================

    ============
    Description:
    ============

    Given a string s, sort it in decreasing order based on the frequency of the
    characters. The frequency of a character is the number of times it appears
    in the string.

    Return the sorted string. If there are multiple answers, return any of
    them.

    =========================================
    FUNCTION: string frequencySort(string s);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "tree"
    Output: "eert"
    Explanation: 'e' appears twice while 'r' and 't' both appear once.
    So 'e' must appear before both 'r' and 't'. Therefore "eetr" is also a
    valid answer.


    --- Example 2 ---
    Input: s = "cccaaa"
    Output: "aaaccc"
    Explanation: Both 'c' and 'a' appear three times, so both "cccaaa" and
    "aaaccc" are valid answers.  Note that "cacaca" is incorrect, as the same
    characters must be together.


    --- Example 3 ---
    Input: s = "Aabb"
    Output: "bbAa"
    Explanation: "bbaA" is also a valid answer, but "Aabb" is incorrect.
    Note that 'A' and 'a' are treated as two different characters.


    *** Constraints ***
    1 <= s.length <= 5 * 10^5
    s consists of uppercase and lowercase English letters and digits.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 42.13% */
/* Space Beats: 57.25% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::string frequencySort(std::string s)
    {
        auto cmp = [](const pair<char, int>& a, const pair<char, int>& b)
        {
            return a.second < b.second;
        };

        std::priority_queue<std::pair<char, int>,
                            std::vector<std::pair<char, int>>,
                            decltype(cmp)> heap(cmp);

        std::unordered_map<char, int> umap;

        for (char& chr : s)
            umap[chr]++;

        for (const auto& entry : umap)
            heap.push(std::make_pair(entry.first, entry.second));

        std::string result = "";
        while (!heap.empty())
        {
            std::pair<char, int> pair = heap.top();
            heap.pop();

            result.append(pair.second, pair.first);
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 89.80% */
/* Space Beats: 42.80% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class Solution_2 {
public:
    std::string frequencySort(std::string s)
    {
        std::vector<std::pair<int, char>> bucket;
        std::unordered_map<char, int> umap;

        std::string result = "";

        // Count character frequency
        for(auto ch: s)
            umap[ch]++;

        // Push from umap to bucket
        for(auto i: umap)
            bucket.push_back({i.second, i.first});

        // Sort "bucket" in decreasing order
        sort(bucket.begin(), bucket.end(), std::greater<std::pair<int, char>>());

        // Add to final result string
        for(auto& i : bucket)
        {
            while(i.first--)
                result += i.second;
        }

        return result;
    }
};
