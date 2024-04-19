#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ==============================
    151) Reverse Words In A String
    ==============================

    ============
    Description:
    ============

    Given an input string s, reverse the order of the words.

    A word is defined as a sequence of non-space characters. The words in s
    will be separated by at least one space.

    Return a string of the words in reverse order concatenated by a single
    space.

    Note that s may contain leading or trailing spaces or multiple spaces
    between two words. The returned string should only have a single space
    separating the words. Do not include any extra spaces.


    Follow-up: If the string data type is mutable in your language, can you
               solve it in-place with O(1) extra space?

    ==================================================
    FUNCTION: std::string reverseWords(std::string s);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "the sky is blue"
    Output: "blue is sky the"

    --- Example 2 ---
    Input: s = "  hello world  "
    Output: "world hello"
    Explanation: Your reversed string should not contain leading or trailing
                 spaces.

    --- Example 3 ---
    Input: s = "a good   example"
    Output: "example good a"
    Explanation: You need to reduce multiple spaces between two words to a
                 single space in the reversed string.


    *** Constraints ***
    1 <= s.length <= 10^4
    s contains English letters (upper-case and lower-case), digits, and spaces
    ' '.
    There is at least one word in s.

*/

/*
    ------------
    --- IDEA ---
    ------------

    In each "iteration" in the first while loop, first skip all the leading
    spaces, then append all the non-space characters to "std::ostringstream",
    and at the very end check if std::ostringstream is non-empty, if it is then
    stringify it and push it to vector "words".

    In the very last "iteration", we will be checking only the trailing spaces
    thus we have:

        if (out.tellp() == 0)

    which helps us check if there were any non-space characters, i.e. words
    found in this "iteration". If there were not, then just don't push anything
    to vector "words"


    After we're done processing all the characters, simply process word-by-word
    vector "words", but in a reverse order. We are going to achieve that by
    taking words.back() and then popping back words from vector "words" with
    words.pop_back().

    Then we'll append the current word to a new std::ostringstream and we will
    also append a single blank character.

    Once we finish that we cannot immediately return out.str() because there is
    a single trailing <Space> character.

    We must get rid of that.
    We'll first stringify out and put it int std::string "result" with:

        result = out.str();

    And after that we'll just pop_back() the very last character and return
    string "result".

*/

/* Time  Beats: 59.07% */
/* Space Beats: 45.40% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::string reverseWords(std::string s)
    {
        std::string result;
        std::vector<std::string> words;

        int i = 0;
        while (i < s.length())
        {
            while (i < s.length() && s[i] == ' ')
                i++;

            std::ostringstream out;
            while (i < s.length() && s[i] != ' ')
                out << s[i++];

            if (out.tellp() != 0)
                words.push_back(out.str());
        }

        std::ostringstream out;
        while ( ! words.empty())
        {
            std::string word = words.back();
            words.pop_back();

            out << word;
            out << ' ';
        }

        result = out.str();
        result.pop_back(); // Last <Space> character

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  90.56% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Efficient {
public:
    std::string reverseWords(std::string s)
    {
        std::reverse(s.begin(), s.end());

        int left    = 0;
        int current = 0;

        int i = 0;
        while (i < s.length())
        {
            while (i < s.length() && s[i] == ' ')
                i++;

            current = i;
            while (i < s.length() && s[i] != ' ')
                i++;

            std::reverse(s.begin()+current, s.begin()+i);

            while (current < i)
                s[left++] = s[current++];

            if (i < s.length())
                s[left++] = ' ';

            i++;
        }

        i = s.length();
        while (left < i--)
            s.pop_back();

        while (s.back() == ' ')
            s.pop_back();

        return s;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    + Reverse the entire string
    + Reverse individual words while handling the extra spaces
    + Remove extra spaces and return


    Input: s = "__Bob__Alice__"

    Initialize left, right and current to 0.

    Step 1: [Reverse the entire string]

        std::reverse(s.begin(), s.end());



    Step 2: [Skip Leading Spaces]

        while (i < s.length() && s[i] == ' ')
            i++;

                current
                   |
                   |
                   v
            s = "__eciliA__boB__"



    Step 3: [Copy characters of a word to the correct position]

        while (i < s.length() && s[i] != ' ')
            s[right++] = s[i++];


                current
                   |
                   |
                   v
            s = "__eciliA__boB__"

            s = "ecilAA__boB__"
                     ^
                     |
                     |
                   right

    Step 4: [Reverse Individual words]

        std::reverse(s.begin()+left, s.begin()+right);

        from:
            s = "ecilAA__boB__"
                 ^   ^
              ___|   |___
              |         |
             left      right


        to:
            s = "AliceA__boB__"


    Step 5: [Add Space between words]

        s[right++] = ' ';
        left = right;

        from:
            s = "AliceA__boB__"


                     right
                       |
        to:            v
            s = "Alice___boB__"
                       ^
                       |
                     left


    Repeat the steps for all the words.

    Finally, it resizes the string to remove any extra space.
        s.resize(right-1);

            s = "Alice_Bob_ob___"
                          ^    ^
                       ___|    |___
                       |          |
                     left        current


    Output: s = "Alice_Bob"

*/

/* Time  Beats: 100.00% */
/* Space Beats:  95.82% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Efficient_2 {
public:
    std::string reverseWords(std::string s)
    {
        std::reverse(s.begin(), s.end());

        int left  = 0;
        int right = 0;

        int i = 0;
        while(i < s.length())
        {
            while(i < s.length() && s[i] == ' ')
                i++;

            if(i == s.length())
                break; // To stop index going out of bounds

            while(i < s.length() && s[i] != ' ')
                s[right++] = s[i++];

            std::reverse(s.begin()+left, s.begin()+right);
            s[right++] = ' ';

            left = right;
            i++;
        }

        s.resize(right-1);
        return s;
    }
};
