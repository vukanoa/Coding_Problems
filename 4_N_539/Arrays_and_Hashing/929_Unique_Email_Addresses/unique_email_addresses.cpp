#include <iostream>
#include <vector>
#include <unordered_set>

/*
    ============
    === EASY ===
    ============

    ===========================
    929) Unique Email Addresses
    ===========================

    ============
    Description:
    ============

    Every valid email consists of a local name and a domain name, separated by
    the '@' sign. Besides lowercase letters, the email may contain one or more
    '.' or '+'.

        For example, in "alice@leetcode.com", "alice" is the local name, and
        "leetcode.com" is the domain name.

    If you add periods '.' between some characters in the local name part of an
    email address, mail sent there will be forwarded to the same address
    without dots in the local name. Note that this rule does not apply to
    domain names.

        For example, "alice.z@leetcode.com" and "alicez@leetcode.com" forward
        to the same email address.

    If you add a plus '+' in the local name, everything after the first plus
    sign will be ignored. This allows certain emails to be filtered. Note that
    this rule does not apply to domain names.

        For example, "m.y+name@email.com" will be forwarded to "my@email.com".

    It is possible to use both of these rules at the same time.

    Given an array of strings emails where we send one email to each emails[i],
    return the number of different addresses that actually receive mails.

    ======================================================
    FUNCTION: int numUniqueEmails(vector<string>& emails);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: emails = ["test.email+alex@leetcode.com",
                     "test.e.mail+bob.cathy@leetcode.com",
                     "testemail+david@lee.tcode.com"]
    Output: 2
    Explanation: "testemail@leetcode.com" and "testemail@lee.tcode.com"
    actually receive mails.


    --- Example 2 ---
    Input: emails = ["a@leetcode.com","b@leetcode.com","c@leetcode.com"]
    Output: 3


    *** Constraints ***
    1 <= emails.length <= 100
    1 <= emails[i].length <= 100
    emails[i] consist of lowercase English letters, '+', '.' and '@'.
    Each emails[i] contains exactly one '@' character.
    All local and domain names are non-empty.
    Local names do not start with a '+' character.
    Domain names end with the ".com" suffix.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Since there aren't any pitfalls after the '@', we can just append from
    that point until the end of the string.

    However, it is important not to omit that part, since that can be the
    differing factor.

*/

/* Time  Beats: 49.68% */
/* Space Beats: 10.65% */

/* Time  Complexity: O(n * max_len(emails)) */
/* Space Complexity: O(n) */
class Solution {
public:
    int numUniqueEmails(vector<string>& emails)
    {
        std::unordered_set<std::string> uset;

        for (int i = 0; i < emails.size(); i++)
        {
            std::ostringstream out;
            bool plus_found = false;

            int j;
            for (j = 0; emails[i][j] != '@'; j++)
            {
                if (emails[i][j] == '.')
                    continue;
                else if (emails[i][j] == '+')
                    plus_found = true;

                if (!plus_found)
                    out << emails[i][j];
            }

            out << emails[i].substr(j, emails[i].length() - j + 1);

            uset.insert(out.str());
        }

        return uset.size();
    }
};
