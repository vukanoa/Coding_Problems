/*
    ============
    === EASY ===
    ============

    ================================
    953) Verifying Alien Dictionary
    ================================

    ============
    Description:
    ============

    In an alien language, surprisingly, they also use English lowercase
    letters, but possibly in a different order. The order of the alphabet is
    some permutation of lowercase letters.

    Given a sequence of words written in the alien language, and the order of
    the alphabet, return true if and only if the given words are sorted
    lexicographically in this alien language.

    ==================================================================
    FUNCTION: bool isAlienSorted(vector<string>& words, string order);
    ==================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: words = ["hello","leetcode"], order = "hlabcdefgijkmnopqrstuvwxyz"
    Output: true
    Explanation: As 'h' comes before 'l' in this language, then the sequence is
                 sorted.

    --- Example 2 ---
    Input: words = ["word","world","row"], order = "worldabcefghijkmnpqstuvxyz"
    Output: false
    Explanation: As 'd' comes after 'l' in this language, then words[0] >
                 words[1], hence the sequence is unsorted.

    --- Example 3 ---
    Input: words = ["apple","app"], order = "abcdefghijklmnopqrstuvwxyz"
    Output: false
    Explanation: The first three characters "app" match, and the second string
                 is shorter (in size.) According to lexicographical rules
                 "apple" > "app", because 'l' > '∅', where '∅' is defined as
                 the blank character which is less than any other character
                 (More info).


    *** Constraints ***
    1 <= words.length <= 100
    1 <= words[i].length <= 20
    order.length == 26
    All characters in words[i] and order are English lowercase letters.

*/

#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    First we have to put all the letters from string "order" in a Hash Map with
    its corresponding order value.

    Example:
    string order = "qet..."

         Hash Map
    |  Key  :  Value |
    +----------------|
    |  'q'  :    1   |
    +----------------|
    |  'e'  :    2   |
    +----------------|
    |  't'  :    3   |
    +----------------|
    |  ...  :   ...  |
    +----------------|

    How do we know if two words are sorted lexicographically?

    Well, in English, two words are sorted lexicographically if the first
    differing character of two words is in sorted order.

    In the English alphabet letter 'a' comes before letter 'c'.
    So if we have two words:
        1. sales
        2. scare

    We can say that they are indeed in a sorted order since the very first
    character 's' is the same in both strings, but the 2nd character(index 1)
    differs.

    The differing character of the first word is 'a' and the differing
    character of the second word is 'c'.

    Since we know that in the English alphabet 'a' does indeed comes before 'c'
    we can conclude that these two words are lexicographically sorted.

    However, here we do have a different permutation of the English alphabet.
    For example, as given in Example 1:

    words = ["hello","leetcode"]
    order = "hlabcdefgijkmnopqrstuvwxyz"

    Upon further examination, we can conclude that these two are sorted since
    the first differing character, which in this case is at the very first
    letter (index 0). Differing characters are 'h' and 'l', respectively.

    We now take a look at the string order and we can see that letter 'h' does
    indeed come before letter 'l', thus we conclude that those two words are
    sorted.

    There is one more, crucially important, thing to understand about the
    lexicographical ordering of the words:

        If one word is the prefix of the other word, prefix(i.e. shorter
          word) MUST come BEFORE the longer one.

        Example:
        words = ["he", "hello"] // This is correct

        words = ["hello", "he"] // This is INCORRECT


    This is the crux of this problem.

    So how can we check for that?
    We'll always check if there are any differing characters within the length
    of the "left", i.e word that comes before.

    Why?
    Consider this example:
        words = ["he", "hello"] // This is correct

    We're only going to check if 'h' and 'e' at the position of 0 and 1,
    respecively, in the Word 2.

    If we don't find any character that is different in Word 2, then that means
    one of two things:
        1. Two words are exactly the same(Which is lexicographically valid)
        2. First word is the prefix of the Second one, but Second one is longer

    However, we have seen that there can be a scenario where the second word
    is the prefix of the first word and the second word is the longer one:
        words = ["hello", "he"] // This is INCORRECT

*/

/* Time  Complexity: O(N * W) */ // W is the length of the longest word
/* Space Complexity: O(1)     */
class Solution {
public:
    bool isAlienSorted(vector<string>& words, string order)
    {
        const int N = words.size();
        const int LOWERCASE_ENGLISH_LETTERS = 26;
        unordered_map<char, int> idx_of_chr;

        for (int i = 0; i < LOWERCASE_ENGLISH_LETTERS; i++)
            idx_of_chr.insert( {order[i], i} );

        for (int left = 0; left < N-1; left++)
        {
            int right = left + 1;

            int i = 0;
            const int LEFT_WORD_SIZE  = words[left].size();
            const int RIGHT_WORD_SIZE = words[right].size();

            bool lexicographically_smaller = false;
            while (i < LEFT_WORD_SIZE && i < RIGHT_WORD_SIZE)
            {
                if (idx_of_chr[words[left][i]] > idx_of_chr[words[right][i]])
                    return false;

                if (idx_of_chr[words[left][i]] < idx_of_chr[words[right][i]])
                {
                    lexicographically_smaller = true;
                    break;
                }

                // Increment
                i++;
            }

            if ( ! lexicographically_smaller && LEFT_WORD_SIZE > RIGHT_WORD_SIZE)
                return false;
        }

        return true;
    }
};
