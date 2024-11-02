#include <iostream>
#include <vector>
#include <sstream>

/*
    ============
    === EASY ===
    ============

    ===========================
    2490) Circular Sentence
    ===========================

    ============
    Description:
    ============

    A sentence is a list of words that are separated by a single space with no
    leading or trailing spaces.

        For example, "Hello World", "HELLO", "hello world hello world" are all
        sentences.

    Words consist of only uppercase and lowercase English letters. Uppercase
    and lowercase English letters are considered different.

    A sentence is circular if:

        + The last character of a word is equal to the first character of the
          next word.

        + The last character of the last word is equal to the first character
          of the first word.

    For example, "leetcode exercises sound delightful", "eetcode", "leetcode
    eats soul" are all circular sentences. However, "Leetcode is cool", "happy
    Leetcode", "Leetcode" and "I like Leetcode" are not circular sentences.

    Given a string sentence, return true if it is circular. Otherwise, return
    false.

    ===================================================
    FUNCTION: bool isCircularSentence(string sentence);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: sentence = "leetcode exercises sound delightful"
    Output: true
    Explanation: The words in sentence are
                 ["leetcode", "exercises", "sound", "delightful"].
    - leetcode's last character is equal to exercises's first character.
    - exercises's last character is equal to sound's first character.
    - sound's last character is equal to delightful's first character.
    - delightful's last character is equal to leetcode's first character.
    The sentence is circular.


    --- Example 2 ---
    Input: sentence = "eetcode"
    Output: true
    Explanation: The words in sentence are ["eetcode"].
    - eetcode's last character is equal to eetcode's first character.
    The sentence is circular.


    --- Example 3 ---
    Input: sentence = "Leetcode is cool"
    Output: false
    Explanation: The words in sentence are ["Leetcode", "is", "cool"].
    - Leetcode's last character is not equal to is's first character.
    The sentence is not circular.


    *** Constraints ***
    1 <= sentence.length <= 500
    sentence consist of only lowercase and uppercase English letters and spaces.
    The words in sentence are separated by a single space.
    There are no leading or trailing spaces.

*/

/*
    ------------
    --- IDEA ---
    ------------

    If you're not familiar with "istringstream" in CPP, please read about it.
    Once you know about it, the problem becomes trivial.

    Use "istringstream" to parse each word and push it into vector "words".
    After that begin at index=1 and every time check if the previous word's
    last character is the same as current word's first(i.e. 0th idx) character.

    If at any points we find disparaty - Return false.

    Otherwise we're done with the for-loop and we must do the last check:

        Is the last word's last character the same as the first word's 0th chr.

    We're doing that by returning the result of that condition as a final
    result. If they ARE equal then the whole sentence is INDEED circular,
    otherwise it's not.

*/

/* Time  Beats: 100.00% */
/* Space Beats:   6.09% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    bool isCircularSentence(string sentence)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        if (sentence.length() == 1)
            return true;

        std::istringstream iss(sentence); // Create input string stream

        std::string word;
        std::vector<std::string> words;

        while (iss >> word) // Read words separated by whitespace
            words.push_back(word);

        for (int i = 1; i < words.size(); i++)
        {
            if (words[i-1].back() != words[i][0])
                return false;
        }

        string first_word = words[0];
        string last_word  = words[words.size() - 1];

        return last_word.back() == first_word[0];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one is even more simple than the above Solution.
    Since last word's last character needs to be equal to the first word's
    first character, that literally means that the very last character of the
    Input needs to be equal to the very first character of the Input sentence.

    If they are equal indeed, then we proceed to check other ones. We're told
    that each words is separated by EXACTLY one space character. We can use
    that information to that advantage.

    Anytime we stumble upon a whitespace character, we are CERTAIN that exactly
    one character BEFORE that whitespace character is a previous word's LAST
    character. Similarly, we are CERTAIN that exactly one character AFTER that
    whitespace character is a next word's FIRST character. They MUST much in
    order to call this Input sentence a "Circular sentence".

    If at any point we find that they do NOT match - Return false.

    Once we're done with the for-loop and since we haven't returned false, we
    can simply return true since we are sure that this is INDEED a circular
    sentence.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  59.78% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Efficient {
public:
    bool isCircularSentence(string sentence)
    {
        const int n = sentence.size();

        if (sentence[0] != sentence[n-1])
            return false;

        for (int i = 1; i < n-1; i++)
        {
            if (sentence[i] == ' ')
            {
                if (sentence[i-1] != sentence[i+1])
                    return false;
            }
        }

        return true;
    }
};
