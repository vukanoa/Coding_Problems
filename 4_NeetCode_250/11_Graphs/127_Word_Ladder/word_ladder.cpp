/*
    ============
    === HARD ===
    ============

    ===========================
    127) Word Ladder
    ===========================

    ============
    Description:
    ============

    A transformation sequence from word beginWord to word endWord using a
    dictionary wordList is a sequence of words:
    beginWord -> s1 -> s2 -> ... -> sk such that:

        - Every adjacent pair of words differs by a single letter.
        - Every si for 1 <= i <= k is in wordList. Note that beginWord does not
          need to be in wordList.
        - sk == endWord

    Given two words, beginWord and endWord, and a dictionary wordList, return
    the number of words in the shortest transformation sequence from beginWord
    to endWord, or 0 if no such sequence exists.

    =======================================================================================
    FUNCTION: int ladderLength(string beginWord, string endWord, vector<string>& wordList);  
    =======================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: beginWord = "hit"
           endWord = "cog"
           wordList = ["hot","dot","dog","lot","log","cog"]
    Output: 5
    Explanation: One shortest transformation sequence is:
    "hit" -> "hot" -> "dot" -> "dog" -> cog", which is 5 words long.

    --- Example 2 ---
    Input: beginWord = "hit"
           endWord = "cog"
           wordList = ["hot","dot","dog","lot","log"]
    Output: 0
    Explanation: The endWord "cog" is not in wordList, therefore there is no
                 valid transformation sequence.

    *** Constraints ***
    1 <= beginWord.length <= 10
    endWord.length == beginWord.length
    1 <= wordList.length <= 5000
    wordList[i].length == beginWord.length
    beginWord, endWord, and wordList[i] consist of lowercase English letters.
    beginWord != endWord
    All the words in wordList are unique.

*/

#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    We create an Adjacency List in an inefficient way, then it's just a simple
    and standard BFS

*/

/* Time  Beats: 5.00% */
/* Space Beats: 5.05% */

/* Time  Complexity: O(M^2 * WORD_SIZE) */
/* Space Complexity: O(M^2 * WORD_SIZE) */
class Solution_Brute_Force {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList)
    {
        const int WORD_SIZE = beginWord.size();
        const int M         = wordList.size();
        int result = 1;

        /* O(M * WORD_SIZE) (entire block) */
        unordered_map<string, vector<string>> adj_list;
        for (const string& curr_word : wordList) // O(M)
        {
            adj_list[beginWord].push_back(beginWord); // WORD_SIZE because of Hashing
            adj_list[curr_word].push_back(curr_word); // WORD_SIZE because of Hashing
        }

        /* O(M^2 * WORD_SIZE) (entire block) */
        for (const string& curr_word : wordList) // O(M)
        {
            for (const auto& entry : adj_list) // O(M)
            {
                const string& other_word = entry.first;

                if (differ_by_one_letter(curr_word, other_word)) // O(WORD_SIZE)
                {
                    adj_list[curr_word].push_back (other_word);
                    adj_list[other_word].push_back(curr_word);
                }
            }
        }

        unordered_set<string> visited;
        visited.insert(beginWord); // O(1)

        queue<string> queue;
        queue.push(beginWord); // O(1)

        /* BFS */
        /* O(WORD_SIZE + M) (entire block) */
        while ( ! queue.empty())
        {
            int size = queue.size();

            while (size > 0)
            {
                string node = queue.front(); // O(1)
                queue.pop();                 // O(1)


                /*
                    Accessing adj_list[word] involves Hashing that takes O(WORD_SIZE)
                    And there can be at most M "neighbor_word"s within the list
                    
                    Therefore: O(WORD_SIZE + M) (entire block)
                */
                for (const string& neighbor: adj_list[node]) // O(WORD_SIZE + M)
                {
                    if (visited.count(neighbor)) // O(1)
                        continue;

                    if (neighbor == endWord)
                        return result + 1;

                    visited.insert(neighbor); // O(1)
                    queue.push(neighbor);     // O(1)
                }

                // Decrement
                size--;
            }

            result++;
        }

        return 0;
    }

private:
    bool differ_by_one_letter(const string& word_1, const string& word_2)
    {
        const int N = word_1.size();

        int diff = 0;
        for (int i = 0; i < N; i++)
        {
            if (word_1[i] != word_2[i])
                diff++;
        }

        return diff == 1;
    }
};
