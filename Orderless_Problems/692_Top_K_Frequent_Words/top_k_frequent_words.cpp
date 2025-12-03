/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    693) Top K Frequent Words
    ===========================

    ============
    Description:
    ============

    Given an array of strings words and an integer k, return the k most
    frequent strings.

    Return the answer sorted by the frequency from highest to lowest. Sort the
    words with the same frequency by their lexicographical order.

    ---------------
    -- Follow Up --
    ---------------

        Could you solve it in O(n log(k)) time and O(n) extra space?


    ====================================================================
    FUNCTION: vector<string> topKFrequent(vector<string>& words, int k);
    ====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: words = ["i","love","leetcode","i","love","coding"], k = 2
    Output: ["i","love"]
    Explanation: "i" and "love" are the two most frequent words. Note that "i"
                 comes before "love" due to a lower alphabetical order.

    --- Example 2 ---
    Input: words = ["the","day","is","sunny","the","the","the","sunny","is","is"], k = 4
    Output: ["the","is","sunny","day"]
    Explanation: "the", "is", "sunny" and "day" are the four most frequent
                 words, with the number of occurrence being 4, 3, 2 and 1
                 respectively.


    *** Constraints ***
    1 <= words.length <= 500
    1 <= words[i].length <= 10
    words[i] consists of lowercase English letters.
    k is in the range [1, The number of unique words[i]]

*/

#include <algorithm>
#include <map>
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

/* Time  Beats: 64.41% */
/* Space Beats: 88.39% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k)
    {
        unordered_map<string, int> freq;

        for (const string& word : words)
            freq[word]++;

        vector<pair<string, int>> entries;
        entries.reserve(freq.size());

        for (const auto& entry : freq)
            entries.push_back(entry);

        // Custom comparator: higher frequency first;
        //                    if equal, lexicographically smaller first
        auto comparator = [](const pair<string, int>& a, const pair<string, int>& b)
        {
            if (a.second != b.second)
                return a.second > b.second; // Higher frequency first

            return a.first < b.first; // Lexicographically smaller first
        };

        sort(entries.begin(), entries.end(), comparator);

        vector<string> result;
        result.reserve(k);

        for (int i = 0; i < k; i++)
            result.push_back(entries[i].first);

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution_Max_Heap {
public:
    vector<string> topKFrequent(vector<string>& words, int k)
    {
        vector<string> result;
        result.reserve(k);

        unordered_map<string, int> freq;
        for (const string& word : words)
            freq[word]++;

        vector<pair<string, int>> max_heap;

        // custom comparator for heap
        auto cmp = [](const pair<string, int>& a, const pair<string, int>& b)
        {
            if (a.second != b.second)
                return a.second < b.second; // Larger freq should be "greater"

            return a.first > b.first; // Lexicographically smaller should be "greater"
        };

        // Build heap
        for (const auto& entry : freq)
            max_heap.push_back(entry);

        make_heap(max_heap.begin(), max_heap.end(), cmp);


        for (int i = 0; i < k; i++)
        {
            pop_heap(max_heap.begin(), max_heap.end(), cmp);
            result.push_back(max_heap.back().first);
            max_heap.pop_back();
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO
    Trie + BucketSort

*/

/* Time  Beats: 44.60% */
/* Space Beats:  5.53% */

/* Time  Complexity: O(N * L) */ // 'L' is the maximum len of any single word
/* Space Complexity: O(N * L) */ // 'L' is the maximum len of any single word
class TrieNode {
public:
    TrieNode* children[26];
    string word;

    TrieNode()
    {
        for (int i = 0; i < 26; i++)
            children[i] = nullptr;

        word = "";
    }
};

class Trie {
public:
    TrieNode* root;

    Trie()
    {
        root = new TrieNode();
    }

    void add_word(const string& word)
    {
        TrieNode* curr = root;

        for (const char& chr : word)
        {
            int idx = chr - 'a';

            if (curr->children[idx] == nullptr)
                curr->children[idx] = new TrieNode();

            curr = curr->children[idx];
        }

        curr->word = word;
    }

    void get_words(TrieNode* node, vector<string>& result)
    {
        if(node == nullptr)
            return;

        if ( ! node->word.empty())
            result.push_back(node->word);

        for (int i = 0; i < 26; i++)
        {
            if (node->children[i] != nullptr)
                get_words(node->children[i], result);
        }
    }
};

class Solution_Trie_plus_Bucket_Sort {
public:
    vector<string> topKFrequent(vector<string>& words, int k)
    {
        const int N = words.size();
        vector<string> result;

        unordered_map<string,int> freq;
        for (const string& word : words)
            freq[word]++;

        vector<Trie*> buckets(N + 1, nullptr);

        for (const auto& entry : freq)
        {
            const string& word = entry.first;
            int freq = entry.second;

            if (buckets[freq] == nullptr)
                buckets[freq] = new Trie();

            buckets[freq]->add_word(word);
        }

        for (int i = N-1; i >= 0; i--)
        {
            if (buckets[i] != nullptr)
            {
                vector<string> tmp;
                buckets[i]->get_words(buckets[i]->root, tmp);

                if (static_cast<int>(tmp.size()) < k)
                {
                    result.insert(result.end(), tmp.begin(), tmp.end());
                    k -= tmp.size();
                }
                else
                {
                    for (int j = 0; j < k; j++)
                        result.push_back(tmp[j]);

                    break;
                }
            }
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

/* Time  Beats: 77.01% */
/* Space Beats: 54.15% */

/* Time  Complexity: O(N * L + N * logN) */
/* Space Complexity: O(N * L)            */
class Solution3 {
public:
    vector<string> topKFrequent(vector<string>& words, int k)
    {
        const int N = words.size();
        vector<string> result;

        unordered_map<string,int> freq;
        for (const string& word : words)
            freq[word]++;

        vector<map<string,int>> buckets(N + 1);

        for (const auto& entry : freq)
        {
            const string& word = entry.first;
            int freq = entry.second;

            buckets[freq].insert({word, freq});
        }


        for (int i = N; i >= 0; i--)
        {
            if ( ! buckets[i].empty())
            {
                auto& curr_bucket = buckets[i];

                if (static_cast<int>(curr_bucket.size()) < k)
                {
                    k -= curr_bucket.size();

                    while ( ! curr_bucket.empty())
                    {
                        auto it = curr_bucket.begin();
                        result.push_back(it->first);
                        curr_bucket.erase(it);
                    }
                }
                else
                {
                    while (k > 0)
                    {
                        auto it = curr_bucket.begin();
                        result.push_back(it->first);
                        curr_bucket.erase(it);
                        k--;
                    }

                    break;
                }
            }
        }

        return result;
    }
};
