/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    3076) Shortest Uncommon Substring in an Array
    =============================================

    ============
    Description:
    ============

    You are given an array arr of size n consisting of non-empty strings.

    Find a string array answer of size n such that:

        answer[i] is the shortest substring  of arr[i] that does not occur as a
        substring in any other string in arr. If multiple such substrings
        exist, answer[i] should be the lexicographically smallest. And if no
        such substring exists, answer[i] should be an empty string.

    Return the array answer.

    =================================================================
    FUNCTION: vector<string> shortestSubstrings(vector<string>& arr);
    =================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = ["cab","ad","bad","c"]
    Output: ["ab","","ba",""]
    Explanation: We have the following:

    - For the string "cab", the shortest substring that does not occur in any
      other string is either "ca" or "ab", we choose the lexicographically
      smaller substring, which is "ab".

    - For the string "ad", there is no substring that does not occur in any
      other string.

    - For the string "bad", the shortest substring that does not occur in any
      other string is "ba".

    - For the string "c", there is no substring that does not occur in any
      other string.



    --- Example 2 ---
    Input: arr = ["abc","bcd","abcd"]
    Output: ["","","abcd"]
    Explanation: We have the following:
    - For the string "abc", there is no substring that does not occur in any
      other string.

    - For the string "bcd", there is no substring that does not occur in any
      other string.

    - For the string "abcd", the shortest substring that does not occur in any
      other string is "abcd".


    *** Constraints ***
    n == arr.length
    2 <= n <= 100
    1 <= arr[i].length <= 20
    arr[i] consists only of lowercase English letters.

*/

#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Look at the Constraints!

    You can just Brute-Force it. It's that simple. That's why you should ALWAYS
    look at the Constraints as soon as you're finished reading the problem.

*/

/* Time  Beats: 35.69% */
/* Space Beats: 10.60% */

/* Time  Complexity: O(N * L^3) */
/* Space Complexity: O(N * L^2) */
class Solution {
private:
    static bool shorter_first(const string& a, const string& b)
    {
        if (a.size() != b.size())
            return a.size() < b.size();

        return a < b; // lexicographical tie-break
    }

public:
    vector<string> shortestSubstrings(vector<string>& arr)
    {
        const int N = arr.size();
        unordered_map<string, unordered_set<int>> umap;

        for (int i = 0; i < N; i++)
        {
            generate_all_substrings(arr[i], umap, i);
        }

        vector<vector<string>> vec(N);

        for (const auto& [str, uset] : umap)
        {
            for (const int& idx : uset)
            {
                vec[idx].push_back(str);
            }
        }

        for (int i = 0; i < N; i++)
            sort(vec[i].begin(), vec[i].end(), shorter_first);


        vector<string> answer(N);

        for (int i = 0; i < N; i++)
        {
            for (const auto& str : vec[i])
            {
                if (umap[str].size() == 1)
                {
                    answer[i] = str;
                    break;
                }
            }
        }

        return answer;
    }

private:
    void generate_all_substrings(string& str, unordered_map<string, unordered_set<int>>& umap, int idx)
    {
        const int LEN = str.length();

        for (int size = 1; size <= LEN; size++)
        {
            for (int start = 0; start + size <= LEN; start++)
            {
                string sub = str.substr(start, size);
                umap[sub].insert(idx);
            }
        }
    }
};
