/*
    ============
    === EASY ===
    ============

    ==================================================
    2273) Find Resultant Array After Removing Anagrams
    ==================================================

    ============
    Description:
    ============

    You are given a 0-indexed string array words, where words[i] consists of
    lowercase English letters.

    In one operation, select any index i such that 0 < i < words.length and
    words[i - 1] and words[i] are anagrams, and delete words[i] from words.
    Keep performing this operation as long as you can select an index that
    satisfies the conditions.

    Return words after performing all operations. It can be shown that
    selecting the indices for each operation in any arbitrary order will lead
    to the same result.

    An Anagram is a word or phrase formed by rearranging the letters of a
    different word or phrase using all the original letters exactly once. For
    example, "dacb" is an anagram of "abdc".

    ===============================================================
    FUNCTION: vector<string> removeAnagrams(vector<string>& words);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: words = ["abba","baba","bbaa","cd","cd"]
    Output: ["abba","cd"]
    Explanation:
    One of the ways we can obtain the resultant array is by using the following operations:
    - Since words[2] = "bbaa" and words[1] = "baba" are anagrams, we choose index 2 and delete words[2].
      Now words = ["abba","baba","cd","cd"].
    - Since words[1] = "baba" and words[0] = "abba" are anagrams, we choose index 1 and delete words[1].
      Now words = ["abba","cd","cd"].
    - Since words[2] = "cd" and words[1] = "cd" are anagrams, we choose index 2 and delete words[2].
      Now words = ["abba","cd"].
    We can no longer perform any operations, so ["abba","cd"] is the final answer.


    --- Example 2 ---
    Input: words = ["a","b","c","d","e"]
    Output: ["a","b","c","d","e"]
    Explanation:
    No two adjacent strings in words are anagrams of each other, so no operations are performed.


    *** Constraints ***
    1 <= words.length <= 100
    1 <= words[i].length <= 10
    words[i] consists of lowercase English letters.

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 12.74% */
/* Space Beats: 28.80% */

/* Time  Complexity: O(N * M) */
/* Space Complexity: O(N)     */
class Solution {
public:
    vector<string> removeAnagrams(vector<string>& words)
    {
       const int N = words.size();
       vector<string> result;
       result.push_back(words[0]);

       for (int i = 1; i < N; i++)
       {
           if (count_sort(words[i]) != count_sort(words[i-1]))
               result.push_back(words[i]);
       }

       return result;
    }

private:
  string count_sort(string s)
  {
        int freq[26] = {0};
        for (const char& chr : s)
            freq[chr - 'a']++;

        string str;
        for (int i = 0; i < 26; i++)
            str += string(freq[i], i + 'a');

        return str;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This looks like a small improvement, but it's crucial. Instead of
    calculating the frequency map for the previous anagram EACH TIME, we count
    it once.

    For these Constraints it's not a problem, however were the Constraints
    worse, we'd have a problem and this would make a difference.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  19.31% */

/* Time  Complexity: O(N * M) */
/* Space Complexity: O(1)     */
class Solution_2 {
public:
    vector<string> removeAnagrams(vector<string>& words)
    {
        const int N = words.size();

        vector<string> result;

        string prev_string = words[0];
        vector<int> prev_anagram(26, 0); // Frequency map
        for (const char& chr : words[0])
            prev_anagram[chr - 'a']++;

        for (int i = 1; i < N; i++)
        {
            string curr_string = words[i];
            vector<int> curr_anagram(26, 0);
            for (const char& chr : words[i])
                curr_anagram[chr - 'a']++;
            
            if (prev_anagram != curr_anagram)
            {
                result.push_back(prev_string);

                prev_string  = curr_string;
                prev_anagram = curr_anagram;
            }
        }
        result.push_back(prev_string);

        return result;
    }
};
