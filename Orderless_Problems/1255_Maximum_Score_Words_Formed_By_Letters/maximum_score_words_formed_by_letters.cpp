/*
    ============
    === HARD ===
    ============

    ===========================================
    1255) Maximum Score Words Formed by Letters
    ===========================================

    ============
    Description:
    ============

    Given a list of words, list of  single letters (might be repeating) and
    score of every character.

    Return the maximum score of any valid set of words formed by using the
    given letters (words[i] cannot be used two or more times).

    It is not necessary to use all characters in letters and each letter can
    only be used once. Score of letters 'a', 'b', 'c', ... ,'z' is given by
    score[0], score[1], ... , score[25] respectively.

    ==============================================================================================
    FUNCTION: int maxScoreWords(vector<string>& words, vector<char>& letters, vector<int>& score);
    ==============================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: words = ["dog","cat","dad","good"],
           letters = ["a","a","c","d","d","d","g","o","o"],
           score = [1,0,9,5,0,0,3,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0]
    Output: 23
    Explanation:
    Score  a=1, c=9, d=5, g=3, o=2
    Given letters, we can form the words "dad" (5+1+5) and "good" (3+2+2+5)
    with a score of 23.  Words "dad" and "dog" only get a score of 21.


    --- Example 2 ---
    Input: words = ["xxxz","ax","bx","cx"],
           letters = ["z","a","b","c","x","x","x"],
           score = [4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,10]
    Output: 27
    Explanation:
    Score  a=4, b=4, c=4, x=5, z=10
    Given letters, we can form the words "ax" (4+5), "bx" (4+5) and "cx" (4+5)
    with a score of 27.  Word "xxxz" only get a score of 25.


    --- Example 3 ---
    Input: words = ["leetcode"],
           letters = ["l","e","t","c","o","d"],
           score = [0,0,1,1,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,0,0]
    Output: 0
    Explanation:
    Letter "e" can only be used once.


    *** Constraints ***
    1 <= words.length <= 14
    1 <= words[i].length <= 15
    1 <= letters.length <= 100
    letters[i].length == 1
    score.length == 26
    0 <= score[i] <= 10
    words[i], letters[i] contains only lower case English letters.

*/

#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Intuition

    To solve this problem, the key is to explore all possible combinations of
    the given words and calculate the scores for each combination while
    ensuring the letter constraints are satisfied. We will use a backtracking
    approach to systematically explore and evaluate each subset of words.

    Approach:

    1. Initialization:
           We initialize a variable maxScore to store the maximum score
           encountered during the evaluation of subsets of words.

    2. Helper Function:
           We define a helper function findMaxScore which will be used to
           explore subsets of words recursively.  The helper function takes the
           current index of words being considered, the current state of the
           letter count, and the current cumulative score.

    3. Base Case:
           If the current index equals the number of words, we compare the
           current cumulative score with maxScore and update maxScore if the
           current score is higher.

    4. Recursive Exploration:
           For each word, we have two choices: either include the word in the
           current subset or exclude it.  We first explore the case where the
           current word is excluded by making a recursive call to findMaxScore
           with the next index.  Then, we calculate the score for the current
           word using the calculateScore function, which checks if the word can
           be formed with the remaining letters. If the word can be formed, we
           explore the case where the current word is included by making a
           recursive call to findMaxScore with the updated letter count and
           cumulative score.

    5. Score Calculation:
           The calculateScore function takes a word, the current state of the
           letter count, and the letter scores. It calculates the score for the
           word if it can be formed with the remaining letters. If the word
           cannot be formed, it returns a score of 0.

    6. Main Function:
           The main function maxScoreWords initializes the letter count from
           the given list of letters and calls the findMaxScore helper function
           starting from the first word with an initial score of 0.

*/

/* Time  Beats: 88.93% */
/* Space Beats: 57.09% */

/*
    Time  Complexity: O(2^W * W * L)

    where W is the number of words and m is the average length of words.
*/
/*
    Space Complexity: O(W)

    where W is the number of words and k is the number of unique characters
    which is 26 for lowercase words
*/
class Solution {
public:
    int maxScoreWords(vector<string>& words, vector<char>& letters, vector<int>& score)
    {
        int max_score = 0;

        vector<int> letter_count(26, 0);
        for (const char& chr : letters)
            letter_count[chr - 'a']++;

        find_max_score(0, words, score, letter_count, 0, max_score);

        return max_score;
    }

private:
    int calculate_score(string& word, vector<int>& letter_count, vector<int>& score)
    {
        int current_score = 0;

        for (const char& chr : word)
        {
            if (letter_count[chr - 'a'] > 0)
            {
                current_score += score[chr - 'a'];
                letter_count[chr - 'a']--;
            }
            else
                return 0;
        }

        return current_score;
    }

    void find_max_score(int index,
                      vector<string>& words,
                      vector<int>& score,
                      vector<int>  letter_count,
                      int  current_val,
                      int& max_score)
    {
        if (index == words.size())
        {
            max_score = max(max_score, current_val);
            return;
        }

        find_max_score(index + 1, words, score, letter_count, current_val, max_score);

        int word_score = calculate_score(words[index], letter_count, score);

        if (word_score > 0)
            find_max_score(index + 1, words, score, letter_count, current_val + word_score, max_score);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 43.39% */
/* Space Beats: 89.24% */

/*
    Time  Complexity: O(2^W * W * L)

    where W is the number of words and m is the average length of words.
*/
/*
    Space Complexity: O(1)
*/
class Solution_Bitmask {
public:
    int maxScoreWords(vector<string>& words, vector<char>& letters, vector<int>& score)
    {
        int word_count = words.size();

        vector<int> letter_count(26, 0);
        for (const char& chr : letters)
            letter_count[chr - 'a']++;

        int max_score = 0;
        vector<int> subset_count(26, 0);

        for (int mask = 0; mask < (1 << word_count); mask++)
        {
            fill(subset_count.begin(), subset_count.end(), 0);

            for (int i = 0; i < word_count; i++)
            {
                if (mask & (1 << i))
                {
                    for (const char& chr : words[i])
                        subset_count[chr - 'a']++;
                }
            }

            max_score = max(max_score, calculate_subset_score(subset_count, score, letter_count));
        }

        return max_score;
    }

private:
    int calculate_subset_score(vector<int>& subset_count,
                               vector<int>& score,
                               vector<int>& letter_count)
    {
        int total_score = 0;

        for (int i = 0; i < 26; i++)
        {
            if (subset_count[i] > letter_count[i])
                return 0;

            total_score += subset_count[i] * score[i];
        }

        return total_score;
    }
};
