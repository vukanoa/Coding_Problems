#include <iostream>

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

/*
	------------
	--- IDEA ---
	------------

	TODO
	
*/

/* Time  Beats: 98.92% */
/* Space Beats: 44.88% */

/* Time  Complexity: O(n^2 * m) */
/* Space Complexity: O(n * m) */
class Solution {
public:
    int ladderLength(std::string beginWord, std::string endWord, std::vector<std::string>& wordList)
	{
        unordered_set<std::string> dict(wordList.begin(), wordList.end());
		unordered_set<std::string> head;
		unordered_set<std::string> tail;
		unordered_set<std::string> *phead;
		unordered_set<std::string> *ptail;

        if (dict.find(endWord) == dict.end())
            return 0;

        head.insert(beginWord);
        tail.insert(endWord);

        int ladder = 2;
        while (!head.empty() && !tail.empty())
		{
            if (head.size() < tail.size())
			{
                phead = &head;
                ptail = &tail;
            }
			else
			{
                phead = &tail;
                ptail = &head;
            }

            unordered_set<std::string> temp;
            for (auto it = phead -> begin(); it != phead -> end(); it++)
			{    
                string word = *it;
                for (int i = 0; i < word.size(); i++)
				{
                    char t = word[i];
                    for (int j = 0; j < 26; j++)
					{
                        word[i] = 'a' + j;
                        if (ptail -> find(word) != ptail -> end())
						{
                            return ladder;
                        }
                        if (dict.find(word) != dict.end())
						{
                            temp.insert(word);
                            dict.erase(word);
                        }
                    }

                    word[i] = t;
                }
            }

            ladder++;
            phead -> swap(temp);
        }

        return 0;
    }
};
