#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    68) Text Justification
    ===========================

    ============
    Description:
    ============

    Given an array of strings words and a width maxWidth, format the text such
    that each line has exactly maxWidth characters and is fully (left and
    right) justified.

    You should pack your words in a greedy approach; that is, pack as many
    words as you can in each line. Pad extra spaces ' ' when necessary so that
    each line has exactly maxWidth characters.

    Extra spaces between words should be distributed as evenly as possible. If
    the number of spaces on a line does not divide evenly between words, the
    empty slots on the left will be assigned more spaces than the slots on the
    right.

    For the last line of text, it should be left-justified, and no extra space
    is inserted between words.

    =====
    Note:  A word is defined as a character sequence consisting of non-space
    =====  characters only.

           Each word's length is guaranteed to be greater than 0 and not
           exceed maxWidth.

           The input array words contains at least one word.



    ==========================================================================
    FUNCTION: vector<string> fullJustify(vector<string>& words, int maxWidth);
    ==========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: words = ["This", "is", "an", "example", "of", "text",
                    "justification."], maxWidth = 16
    Output:
    [
       "This    is    an",
       "example  of text",
       "justification.  "
    ]


    --- Example 2 ---
    Input: words = ["What","must","be","acknowledgment","shall","be"],
           maxWidth = 16
    Output:
    [
      "What   must   be",
      "acknowledgment  ",
      "shall be        "
    ]
    Explanation: Note that the last line is "shall be    " instead of "shall
    be", because the last line must be left-justified instead of
    fully-justified.  Note that the second line is also left-justified because
    it contains only one word.


    --- Example 3 ---
    Input: words =
    ["Science", "is", "what", "we", "understand", "well", "enough", "to",
     "explain", "to", "a", "computer.", "Art", "is", "everything", "else", "we",
     "do"],
    maxWidth = 20
    Output:
    [
      "Science  is  what we",
      "understand      well",
      "enough to explain to",
      "a  computer.  Art is",
      "everything  else  we",
      "do                  "
    ]


    *** Constraints ***
    1 <= words.length <= 300
    1 <= words[i].length <= 20
    words[i] consists of only English letters and symbols.
    1 <= maxWidth <= 100
    words[i].length <= maxWidth

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  5.49% */

/* Time  Complexity: O(???) */
/* Space Complexity: O(???) */
class Solution_Messy {
public:
    std::vector<std::string> fullJustify(std::vector<std::string>& words, int maxWidth)
    {
        int n = words.size();

        std::vector<std::pair<std::vector<int>, int>> wIdx(1);
        int curr = 0;
        int len  = 0;

        for (int i = 0; i < n; i++)
        {
            // wlen = sum of length of words w/o space in 1 line
            int wlen = words[i].size();
            len += wlen;

            if (len > maxWidth)
            {
                w_idx.push_back({{i}, wlen});
                curr++;
                len = wlen;
            }
            else
            {
                w_idx[curr].first.push_back(i);
                wIidx[curr].second += wlen;
            }

            len++; // At least 1 whitespace between words
        }

        return print_w_idx(words, w_idx, maxWidth);
    }

private:
    std::vector<std::string> result;

    std::string space(int c)
    {
        return std::string(c, ' ');
    }

    std::vector<std::string>
    print_wIdx(
               std::vector<std::string>& words,
               std::vector<std::pair<std::vector<int>, int>>& wIdx,
               int maxWidth
              )
    {
        for (int i = 0; i < wIdx.size(); i++)
        {
            int num_words = wIdx[i].first.size();
            int total_len = wIdx[i].second;
            int total_spaces = maxWidth - total_len;
            int num_gaps = num_words - 1;
            int num_spaces = 1;
            int remaining_spaces = 0;

            if (num_gaps > 0)
            {
                num_spaces = total_spaces / num_gaps;
                remaining_spaces = total_spaces % num_gaps;
            }

            // Start with the first word
            std::string line = words[wIdx[i].first[0]];
            for (int j = 1; j < num_words; j++)
            {
                if (i == wIdx.size() - 1)
                    line += space(1); // Last line, left justify
                else
                {
                    line+= space(num_spaces+(remaining_spaces>0?1:0));
                    remaining_spaces--;
                }

                line += words[wIdx[i].first[j]];
            }

            if (line.size() < maxWidth)
                line+= space(maxWidth-line.size());

            result.push_back(line);
        }

        return result;
    }
};
