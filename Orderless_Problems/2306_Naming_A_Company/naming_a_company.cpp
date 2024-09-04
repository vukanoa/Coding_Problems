#include <iostream>
#include <vector>
#include <unordered_set>

/*
    ============
    === HARD ===
    ============

    ===========================
    2306) Naming a Company
    ===========================

    ============
    Description:
    ============

    You are given an array of strings ideas that represents a list of names to
    be used in the process of naming a company. The process of naming a company
    is as follows:

        1. Choose 2 distinct names from ideas, call them ideaA and ideaB.

        2. Swap the first letters of ideaA and ideaB with each other.

        3. If both of the new names are not found in the original ideas, then
           the name ideaA ideaB (the concatenation of ideaA and ideaB,
           separated by a space) is a valid company name.  Otherwise, it is not
           a valid name.

    Return the number of distinct valid names for the company.

    =========================================================
    FUNCTION: long long distinctNames(vector<string>& ideas);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: ideas = ["coffee","donuts","time","toffee"]
    Output: 6
    Explanation: The following selections are valid:
    - ("coffee", "donuts"): The company name created is "doffee conuts".
    - ("donuts", "coffee"): The company name created is "conuts doffee".
    - ("donuts", "time"): The company name created is "tonuts dime".
    - ("donuts", "toffee"): The company name created is "tonuts doffee".
    - ("time", "donuts"): The company name created is "dime tonuts".
    - ("toffee", "donuts"): The company name created is "doffee tonuts".
    Therefore, there are a total of 6 distinct company names.

    The following are some examples of invalid selections:
    - ("coffee", "time"): The name "toffee" formed after swapping already
                          exists in the original array.

    - ("time", "toffee"): Both names are still the same after swapping and
                          exist in the original array.

    - ("coffee", "toffee"): Both names formed after swapping already exist in
                            the original array.


    --- Example 2 ---
    Input: ideas = ["lack","back"]
    Output: 0
    Explanation: There are no valid selections. Therefore, 0 is returned.



    *** Constraints ***
    2 <= ideas.length <= 5 * 10^4
    1 <= ideas[i].length <= 10
    ideas[i] consists of lowercase English letters.
    All the strings in ideas are unique.

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 18.40% */
/* Space Beats: 11.32% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    long long distinctNames(vector<string>& ideas)
    {
        unordered_map<int, unordered_set<string>> first_letter_to_substrings;

        for (string idea : ideas)
        {
            int first_letter = idea[0] - 'a';

            string substring = idea.substr(1);
            first_letter_to_substrings[first_letter].insert(substring);
        }

        long long result = 0;

        for (int i = 0; i < 26; i++)
        {
            for (int j = i + 1; j < 26; j++)
            {
                unordered_set<string> substrings_starting_with_i = first_letter_to_substrings[i];
                unordered_set<string> substrings_starting_with_j = first_letter_to_substrings[j];
                int duplicate = 0;

                for (string substring : substrings_starting_with_i)
                {
                    if (substrings_starting_with_j.count(substring) > 0)
                        duplicate++;
                }

                result += (substrings_starting_with_i.size() - duplicate) * (substrings_starting_with_j.size() - duplicate);
            }
        }

        return result * 2;
    }
};
