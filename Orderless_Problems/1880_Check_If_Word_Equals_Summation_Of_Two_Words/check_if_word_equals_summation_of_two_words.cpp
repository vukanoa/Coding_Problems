/*
    ============
    === EASY ===
    ============

    =================================================
    1880) Check if Word Equals Summation of Two Words
    =================================================

    ============
    Description:
    ============

    The letter value of a letter is its position in the alphabet starting from
    0 (i.e. 'a' -> 0, 'b' -> 1, 'c' -> 2, etc.).

    The numerical value of some string of lowercase English letters s is the
    concatenation of the letter values of each letter in s, which is then
    converted into an integer.

    For example, if s = "acb", we concatenate each letter's letter value,
    resulting in "021". After converting it, we get 21.

    You are given three strings firstWord, secondWord, and targetWord, each
    consisting of lowercase English letters 'a' through 'j' inclusive.

    Return true if the summation of the numerical values of firstWord and
    secondWord equals the numerical value of targetWord, or false otherwise.

    ==================================================================================
    FUNCTION: bool isSumEqual(string firstWord, string secondWord, string targetWord);
    ==================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: firstWord = "acb", secondWord = "cba", targetWord = "cdb"
    Output: true
    Explanation:
    The numerical value of firstWord is "acb" -> "021" -> 21.
    The numerical value of secondWord is "cba" -> "210" -> 210.
    The numerical value of targetWord is "cdb" -> "231" -> 231.
    We return true because 21 + 210 == 231.

    --- Example 2 ---
    Input: firstWord = "aaa", secondWord = "a", targetWord = "aab"
    Output: false
    Explanation: 
    The numerical value of firstWord is "aaa" -> "000" -> 0.
    The numerical value of secondWord is "a" -> "0" -> 0.
    The numerical value of targetWord is "aab" -> "001" -> 1.
    We return false because 0 + 0 != 1.

    --- Example 3 ---
    Input: firstWord = "aaa", secondWord = "a", targetWord = "aaaa"
    Output: true
    Explanation: 
    The numerical value of firstWord is "aaa" -> "000" -> 0.
    The numerical value of secondWord is "a" -> "0" -> 0.
    The numerical value of targetWord is "aaaa" -> "0000" -> 0.
    We return true because 0 + 0 == 0.


    *** Constraints ***
    1 <= firstWord.length, secondWord.length, targetWord.length <= 8
    firstWord, secondWord, and targetWord consist of lowercase English letters
    from 'a' to 'j' inclusive.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:   5.01% */

/* Time  Complexity: O(N + M + K) */
/* Space Complexity: O(N + M + K) */
class Solution {
public:
    bool isSumEqual(string firstWord, string secondWord, string targetWord)
    {
        const int N = firstWord.size();
        const int M = secondWord.size();
        const int K = secondWord.size();

        string one;
        string two;
        string target;

        one.reserve(2*N);
        two.reserve(2*M);
        target.reserve(2*K);

        for (const char& chr : firstWord)
            one += to_string(static_cast<int>(chr - 'a'));

        for (const char& chr : secondWord)
            two += to_string(static_cast<int>(chr - 'a'));

        for (const char& chr : targetWord)
            target += to_string(static_cast<int>(chr - 'a'));

        return (stoi(one) + stoi(two)) == stoi(target);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Cleaner way of implementing it.

*/

/* Time  Beats:  3.90% */
/* Space Beats: 89.14% */

/* Time  Complexity: O(N + M + K) */
/* Space Complexity: O(1)         */
class Solution_2 {
public:
    bool isSumEqual(string firstWord, string secondWord, string targetWord)
    {
        const int N = firstWord.size();
        const int M = secondWord.size();
        const int K = targetWord.size();

        int first  = 0;
        int second = 0;
        int target = 0;

        for (int i = 0; i < N; i++)
            first = first * 10 + (firstWord[i] - 'a');

        for (int i = 0; i < M; i++)
            second = second * 10 + (secondWord[i] - 'a');

        for (int i = 0; i < K; i++)
            target = target * 10 + (targetWord[i] - 'a');

        return (first + second) == target;
    }
};
