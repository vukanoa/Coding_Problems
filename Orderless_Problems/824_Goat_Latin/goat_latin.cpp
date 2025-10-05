/*
    ============
    === EASY ===
    ============

    ===========================
    824) Goat Latin
    ===========================

    ============
    Description:
    ============

    ou are given a string sentence that consist of words separated by spaces.
    Each word consists of lowercase and uppercase letters only.

    We would like to convert the sentence to "Goat Latin" (a made-up language
    similar to Pig Latin.) The rules of Goat Latin are as follows:

        + If a word begins with a vowel ('a', 'e', 'i', 'o', or 'u'), append "ma"
          to the end of the word.

            For example, the word "apple" becomes "applema".


        + If a word begins with a consonant (i.e., not a vowel), remove the
          first letter and append it to the end, then add "ma".

            For example, the word "goat" becomes "oatgma".



        + Add one letter 'a' to the end of each word per its word index in the
          sentence, starting with 1.

            For example, the first word gets "a" added to the end, the second
            word gets "aa" added to the end, and so on.


    Return the final sentence representing the conversion from sentence to Goat
    Latin.

    ==============================================
    FUNCTION: string toGoatLatin(string sentence);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: sentence = "I speak Goat Latin"
    Output: "Imaa peaksmaaa oatGmaaaa atinLmaaaaa"

    --- Example 2 ---
    Input: sentence = "The quick brown fox jumped over the lazy dog"
    Output: "heTmaa uickqmaaa rownbmaaaa oxfmaaaaa umpedjmaaaaaa overmaaaaaaa
            hetmaaaaaaaa azylmaaaaaaaaa ogdmaaaaaaaaaa"

    *** Constraints ***
    1 <= sentence.length <= 150
    sentence consists of English letters and spaces.
    sentence has no leading or trailing spaces.
    All the words in sentence are separated by a single space.

*/

#include <string>
#include <unordered_set>
#include <sstream>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  30.59% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    string toGoatLatin(string sentence)
    {
        const int N = sentence.size();
        string result = "";

        istringstream iss(sentence);

        unordered_set<char> uset = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};

        int amount = 1; // Amount of letter 'a'

        string word;
        while (iss >> word)
        {
            if (uset.count(word[0]))
            {
                result += word;
            }
            else
            {
                result += word.substr(1);
                result += word[0];
            }

            result += "ma";
            result += string(amount++, 'a');
            result += " ";
        }
        result.pop_back();

        return result;
    }
};
