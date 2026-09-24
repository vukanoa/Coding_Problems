/*
    ==============
    === MEDIUM ===
    ==============

    =============================
    3926) Count Valid Occurrences
    =============================

    ============
    Description:
    ============

    You are given an array of strings chunks. Concatenate all strings in chunks
    in order to form a string s.

    You are also given an array of strings queries.

    A joiner hyphen is a hyphen character '-' in s whose previous and next
    characters both exist and are lowercase English letters.

    A word is a maximal of s consisting only of lowercase English letters and
    joiner hyphens.

    All other characters, including spaces and hyphens that are not joiner
    hyphens, are treated as separators.

    Return an integer array ans, where ans[i] is the number of times queries[i]
    appears as a word in s.

    ============================================================================================
    FUNCTION: vector<int> countWordOccurrences(vector<string>& chunks, vector<string>& queries);
    ============================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: chunks = ["hello wor","ld hello"], queries = ["hello","world","wor"]
    Output: [2,1,0]
    Explanation:
        After concatenating all strings in chunks, s = "hello world hello".
        The words are "hello", "world", and "hello".
        The substring "wor" appears inside "world", but it is not a full word.

    --- Example 2 ---
    Input: chunks = ["a-b a--b ","a-","b"], queries = ["a-b","a","b"]
    Output: [2,1,1]
    Explanation:
        After concatenating all strings in chunks, s = "a-b a--b a-b".
        In "a-b", the hyphen is a joiner hyphen because it is between two lowercase English letters, so "a-b" is one word.
        In "a--b", neither hyphen is a joiner hyphen, so it is split into the words "a" and "b".
        Therefore, the words are "a-b", "a", "b", and "a-b".

    --- Example 3 ---
    Input: chunks = ["-cat dog- mouse"], queries = ["cat","dog","mouse","cat-dog"]
    Output: [1,1,1,0]
    Explanation:
        After concatenating all strings in chunks, s = "-cat dog- mouse".
        The leading hyphen before "cat" and the trailing hyphen after "dog" are not joiner hyphens, so they are separators.
        The words are "cat", "dog", and "mouse".


    *** Constraints ***
    1 <= chunks.length <= 10^5
    1 <= chunks[i].length <= 10^5
    The total length of all strings in chunks does not exceed 105.
    chunks[i] consists only of lowercase English letters, spaces, and '-'.
    1 <= queries.length <= 10^5
    1 <= queries[i].length <= 10^5
    The total length of all strings in queries does not exceed 105.
    queries[i] consists only of lowercase English letters and '-'.
    queries[i] is a valid word: it does not start or end with '-', and it does not contain two consecutive hyphens.

*/

#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    Memory-refresher on "Input Stream Stream" in C++:


            string str = "dog car fish lion";
            vector<string> words;

            istringstream iss(str);                // InputStringStream

            string word;
            while (iss >> word)
                words.push_back(word);

            // Before:  str = "dog car fish lion";
            // After: words = ["dog", "car", "fish", "lion"]

*/

/* Time  Beats: 6.56% */
/* Space Beats: 5.05% */

/* Time  Complexity: O(N + Q) */
/* Space Complexity: O(N)     */
class Solution {
public:
    vector<int> countWordOccurrences(vector<string>& chunks, vector<string>& queries)
    {
        const int N = chunks.size();
        const int Q = queries.size();
        vector<int> result(Q, 0);

        string s;
        s.reserve(1e5 + 1); // To prevent repeated reallocations

        for (const string& chunk : chunks)
            s += chunk;


        vector<string> words;
        istringstream iss(s);

        string word;
        while (iss >> word)
            words.push_back(word);

        unordered_map<string, int> umap_word_freq;
        for (const string& w : words)
        {
            const int SIZE = w.size();

            int i = 0;
            int j = SIZE-1;

            while (i < SIZE && w[i] == '-') // NON-joiner hyphen
                i++;

            while (j > i && w[j] == '-')
                j--;

            if (i <= j)
            {
                string new_word = w.substr(i, j-i+1);
                int len = new_word.size();

                for (int idx = 1; idx < len-1; idx++)
                {
                    if (new_word[idx] != '-')
                        continue;

                    if (  ! (islower(new_word[idx-1]) && islower(new_word[idx+1]))  )
                        new_word[idx] = ' ';

                }
            
                istringstream iss2(new_word);

                vector<string> vec_words;
                string word2;
                while (iss2 >> word2)
                    vec_words.push_back(word2);

                for (const string wrd : vec_words)
                    umap_word_freq[wrd]++;
            }
        }


        for (int i = 0; i < Q; i++)
        {
            string query_word = queries[i];

            if (umap_word_freq.find(query_word) != umap_word_freq.end())
                result[i] = umap_word_freq[query_word];
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

/* Time  Beats: 71.86% */
/* Space Beats:  9.25% */

/* Time  Complexity: O(N + Q) */
/* Space Complexity: O(Q)     */
class Solution_Elegant {
public:
    vector<int> countWordOccurrences(vector<string>& chunks, vector<string>& queries)
    {
        unordered_map<string, int> umap;

        string s;
        s.reserve(1e5 + 1); // To prevent repeated reallocations
        for (const string& chunk : chunks)
            s += chunk;

        string curr_str;
        const int TOTAL_SIZE = s.size();

        for (int i = 0; i < TOTAL_SIZE; i++)
        {
            if (islower(s[i]))
            {
                curr_str += s[i];
            }
            else if (s[i] == '-')
            {
                if (i > 0              &&
                    i + 1 < TOTAL_SIZE &&
                    islower(s[i - 1])  &&
                    islower(s[i + 1]))
                {
                    curr_str += '-';
                }
                else if ( ! curr_str.empty())
                {
                    umap[curr_str]++;
                    curr_str.clear();
                }
            }
            else if ( ! curr_str.empty())
            {
                umap[curr_str]++;
                curr_str.clear();
            }
        }

        // One additional at the end
        if ( ! curr_str.empty())
            umap[curr_str]++;

        const int Q = queries.size();
        vector<int> result;
        result.reserve(Q);

        for (const string& query : queries)
            result.push_back(umap[query]);

        return result;
    }
};
