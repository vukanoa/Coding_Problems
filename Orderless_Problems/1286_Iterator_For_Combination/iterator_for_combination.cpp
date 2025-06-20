/*
    ==============
    === MEDIUM ===
    ==============

    ==============================
    1286) Iterator for Combination
    ==============================

    ============
    Description:
    ============


    Design the CombinationIterator class:

        + CombinationIterator(string characters, int combinationLength)
          Initializes the object with a string characters of sorted distinct
          lowercase English letters and a number combinationLength as arguments

        + next() Returns the next combination of length combinationLength in
          lexicographical order.

        + hasNext() Returns true if and only if there exists a next combination.

    ===============================
    CLASS:
    class CombinationIterator {
    public:
        CombinationIterator(string characters, int combinationLength) {

        }

        string next() {

        }

        bool hasNext() {

        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input
    ["CombinationIterator", "next", "hasNext", "next", "hasNext", "next", "hasNext"]
    [["abc", 2], [], [], [], [], [], []]
    Output
    [null, "ab", true, "ac", true, "bc", false]

    Explanation
    CombinationIterator itr = new CombinationIterator("abc", 2);
    itr.next();    // return "ab"
    itr.hasNext(); // return True
    itr.next();    // return "ac"
    itr.hasNext(); // return True
    itr.next();    // return "bc"
    itr.hasNext(); // return False


    *** Constraints ***
    1 <= combinationLength <= characters.length <= 15
    All the characters of characters are unique.
    At most 104 calls will be made to next and hasNext.
    It is guaranteed that all calls of the function next are valid.

*/

#include <set>
#include <string>
#include <unordered_set>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 35.03% */
/* Space Beats:  7.91% */

/* Time  Complexity: O(2^s_len * s_len) */
/* Space Complexity: O(C(s_len, n) * n) */
class CombinationIterator {
private:
    string s;
    int n;
    int s_len;

    set<string> set_comb;
    set<string>::iterator curr_iter;

public:
    CombinationIterator(string& s, int n) : s(s), n(n), s_len(size(s))
    { generate(s, n); }

    string next() // Return increment to iterator next string
    {
        return *curr_iter++;
    }

    bool hasNext() // Check if all strings are iterated
    {
        return curr_iter != end(set_comb);
    }

private:
    void generate(string& s, int n)
    {
        for (int mask = 0; mask < 1 << s_len; mask++) // iterate mask from [0, 2^L)
        {
            if (__builtin_popcount(mask) != n)
                continue; // only mask with number of set bits = n must be considered

            string combination = "";
            for (int j = 0; j < s_len; j++) // traverse over bits of current mask
            {
                if (mask & 1 << j)       // if j-th bit is set, then
                    combination += s[j]; // push jth character of s
            }

            set_comb.insert(std::move(combination)); // insert the constructed string into set
        }

        curr_iter = begin(set_comb);
    }
};
