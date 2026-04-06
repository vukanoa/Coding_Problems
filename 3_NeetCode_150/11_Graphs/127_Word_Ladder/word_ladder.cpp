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



/*
    ------------
    --- IDEA ---
    ------------

    Instead of creating an Adjacency list between every two pairs, we can
    instead build an Adjancency List from every pattern to list of words.

    What is a pattern?

    Since we can "jump" from one word to another if they differ by exactly one
    letter, then we can generate each of the WORD_SIZE patterns for each word.

    A pattern for, say word "hit" is:

        1)  * i t
        2)  h * t
        3)  h i *

    Therefore, for all 3 of these patterns we're going to append the word to it
    and that way we'll a vector of words that can jump between each other
    because they all differ on the character were the '*' is.

    This is MUCH more optimal given the Constraints.

    WORD_SIZE is said to be: [1, 10], wheereas
    M         is said to be: [1, 5000]

    Therefore, we've reduced the Time Complexity from:

        O(M^2 * WORD_SIZE) ----> O(M * WORD_SIZE)

*/

/* Time  Beats: 41.81% */
/* Space Beats:  6.42% */

/* Time  Complexity: O(M * WORD_SIZE^2) */
/* Space Complexity: O(M * WORD_SIZE^2) */
class Solution_Optimal {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList)
    {
        const int WORD_SIZE = beginWord.size();
        const int M         = wordList.size();
        int result = 1; // Shortest sequence length, including beginWord itself

        wordList.push_back(beginWord); // Add starting word

        /* O(M * WORD_SIZE^2) (entire block) */
        unordered_map<string, vector<string>> adj_list;
        for (const string& word : wordList) // O(M)
        {
            string pattern;

            /* O(WORD_SIZE^2) (entire block) */
            for (int i = 0; i < WORD_SIZE; i++) // O(WORD_SIZE)
            {
                pattern = word; // O(WORD_SIZE)
                pattern[i] = '*';

                adj_list[pattern].push_back(word);
            }
        }

        unordered_set<string> visited;
        visited.insert(beginWord);

        queue<string> queue;
        queue.push(beginWord);

        /*******/
        /* BFS */
        /*******/
        /* O(WORD_SIZE^2 + M * WORD_SIZE) (entire block)*/
        while ( ! queue.empty())
        {
            int size = queue.size();

            while (size > 0)
            {
                string word = queue.front(); // O(1)
                queue.pop();                 // O(1)

                string pattern;

                /* O(WORD_SIZE^2 + M * WORD_SIZE) */
                for (int i = 0; i < WORD_SIZE; i++) // O(WORD_SIZE)
                {
                    pattern = word;   // O(WORD_SIZE)
                    pattern[i] = '*';


                    /*
                        Accessing adj_list[patternn] involves Hashing that takes O(WORD_SIZE)
                        And there can be at most M "neighbor_word"s within the list
                        
                        Therefore: O(WORD_SIZE + M) (entire block)
                    */
                    for (const string& neighbor_word : adj_list[pattern]) // O(WORD_SIZE + M)
                    {
                        if (visited.count(neighbor_word)) // O(1)
                            continue;

                        if (neighbor_word == endWord)
                            return result + 1;

                        visited.insert(neighbor_word); // O(1)
                        queue.push(neighbor_word);     // O(1)
                    }
                }

                // Decrement
                size--;
            }

            result++;
        }

        return 0;
    }
};
