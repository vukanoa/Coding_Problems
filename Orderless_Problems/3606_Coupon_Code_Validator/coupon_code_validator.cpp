/*
    ============
    === EASY ===
    ============

    ===========================
    3606) Coupon Code Validator
    ===========================

    ============
    Description:
    ============

    You are given three arrays of length n that describe the properties of n
    coupons: code, businessLine, and isActive. The ith coupon has:

        + code[i]: a string representing the coupon identifier.

        + businessLine[i]: a string denoting the business category of the
          coupon.

        + isActive[i]: a boolean indicating whether the coupon is currently
          active.

    A coupon is considered valid if all of the following conditions hold:

        1. code[i] is non-empty and consists only of alphanumeric characters
           (a-z, A-Z, 0-9) and underscores (_).

        2. businessLine[i] is one of the following four categories:
           "electronics", "grocery", "pharmacy", "restaurant".

        3. isActive[i] is true.

    Return an array of the codes of all valid coupons, sorted first by their
    businessLine in the order: "electronics", "grocery", "pharmacy",
    "restaurant", and then by code in lexicographical (ascending) order within
    each category.

    =====================================================================================================================
    FUNCTION: vector<string> validateCoupons(vector<string>& code, vector<string>& businessLine, vector<bool>& isActive);
    =====================================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: code = ["SAVE20","","PHARMA5","SAVE@20"], businessLine = ["restaurant","grocery","pharmacy","restaurant"], isActive = [true,true,true,true]
    Output: ["PHARMA5","SAVE20"]
    Explanation:
        First coupon is valid.
        Second coupon has empty code (invalid).
        Third coupon is valid.
        Fourth coupon has special character @ (invalid).


    --- Example 2 ---
    Input: code = ["GROCERY15","ELECTRONICS_50","DISCOUNT10"], businessLine = ["grocery","electronics","invalid"], isActive = [false,true,true]
    Output: ["ELECTRONICS_50"]
    Explanation:
        First coupon is inactive (invalid).
        Second coupon is valid.
        Third coupon has invalid business line (invalid).


    *** Constraints ***
    n == code.length == businessLine.length == isActive.length
    1 <= n <= 100
    0 <= code[i].length, businessLine[i].length <= 100
    code[i] and businessLine[i] consist of printable ASCII characters.
    isActive[i] is either true or false.

*/

#include <algorithm>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Simulation problem, nothing to think about. Just code it up.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  42.86% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    vector<string> validateCoupons(vector<string>& code, vector<string>& businessLine, vector<bool>& isActive)
    {
        const int N = code.size();

        vector<pair<char, string>> res;
        vector<string> result;

        unordered_set<string> uset = {"electronics", "grocery", "pharmacy", "restaurant"};

        for (int i = 0; i < N; i++)
        {
            bool okay = true;
            for (const char& chr : code[i])
            {
                if ( ! is_okay(chr))
                {
                    okay = false;
                    break;
                }
            }

            if ( ! okay || code[i].empty())
                continue;


            if (uset.find(businessLine[i]) == uset.end())
                continue;

            if ( ! isActive[i])
                continue;

            switch (businessLine[i][0])
            {
                case 'e':
                    res.push_back({'a', code[i]});
                    break;

                case  'g':
                    res.push_back({'b', code[i]} );
                    break;

                case  'p':
                    res.push_back({'c', code[i]} );
                    break;

                case  'r':
                    res.push_back({'d', code[i]} );
                    break;
            }
        }

        sort(res.begin(), res.end());

        for (const auto& entry : res)
        {
            result.push_back(entry.second);
        }

        return result;
    }

private:
    bool is_okay(char chr)
    {
        return (chr >= 'a' && chr <= 'z') ||
               (chr >= 'A' && chr <= 'Z') ||
               (chr >= '0' && chr <= '9') ||
               chr == '_';
    }
};
