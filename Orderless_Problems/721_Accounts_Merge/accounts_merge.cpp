#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <numeric>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    721) Accounts Merge
    ===========================

    ============
    Description:
    ============

    Given a list of accounts where each element accounts[i] is a list of
    strings, where the first element accounts[i][0] is a name, and the rest of
    the elements are emails representing emails of the account.

    Now, we would like to merge these accounts. Two accounts definitely belong
    to the same person if there is some common email to both accounts. Note
    that even if two accounts have the same name, they may belong to different
    people as people could have the same name. A person can have any number of
    accounts initially, but all of their accounts definitely have the same
    name.

    After merging the accounts, return the accounts in the following format:
    the first element of each account is the name, and the rest of the elements
    are emails in sorted order. The accounts themselves can be returned in any
    order.

    =====================================================================================================
    FUNCTION: std::vector<std::vector<string>> accountsMerge(std::vector<std::vector<string>>& accounts);
    =====================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: accounts = [["John","johnsmith@mail.com","john_newyork@mail.com"],["John","johnsmith@mail.com","john00@mail.com"],["Mary","mary@mail.com"],["John","johnnybravo@mail.com"]]
    Output: [["John","john00@mail.com","john_newyork@mail.com","johnsmith@mail.com"],["Mary","mary@mail.com"],["John","johnnybravo@mail.com"]]
    Explanation:
    The first and second John's are the same person as they have the common email "johnsmith@mail.com".
    The third John and Mary are different people as none of their email addresses are used by other accounts.
    We could return these lists in any order, for example the answer [['Mary', 'mary@mail.com'], ['John', 'johnnybravo@mail.com'],
    ['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com']] would still be accepted.


    --- Example 2 ---
    Input: accounts =
    [["Gabe","Gabe0@m.co","Gabe3@m.co","Gabe1@m.co"],["Kevin","Kevin3@m.co","Kevin5@m.co","Kevin0@m.co"],["Ethan","Ethan5@m.co","Ethan4@m.co","Ethan0@m.co"],["Hanzo","Hanzo3@m.co","Hanzo1@m.co","Hanzo0@m.co"],["Fern","Fern5@m.co","Fern1@m.co","Fern0@m.co"]]
    Output:
    [["Ethan","Ethan0@m.co","Ethan4@m.co","Ethan5@m.co"],["Gabe","Gabe0@m.co","Gabe1@m.co","Gabe3@m.co"],["Hanzo","Hanzo0@m.co","Hanzo1@m.co","Hanzo3@m.co"],["Kevin","Kevin0@m.co","Kevin3@m.co","Kevin5@m.co"],["Fern","Fern0@m.co","Fern1@m.co","Fern5@m.co"]]


    *** Constraints ***
    1 <= accounts.length <= 1000
    2 <= accounts[i].length <= 10
    1 <= accounts[i][j].length <= 30
    accounts[i][0] consists of English letters.
    accounts[i][j] (for j > 0) is a valid email.

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

    Similar Union and Find problems:

        547.  Number of Provinces
        952.  Largest Component Size by Common Factor
        947.  Most Stones Removed with Same Row or Column
        1319. Number of Operations to Make Network Connected
        684.  Redundant Connection
        990.  Satisfiability of Equality Equations
        1202. Smallest String With Swaps
        2421. Number of Good Paths

*/

/* Time  Beats: 53.72% */
/* Space Beats: 81.18% */

/* Time  Complexity: O(N * α(N) + M * log(M)) */
/* Space Complexity: O(N + M) */
class UF {
public:
    // Constructor: initialize the parent list where each node is its own parent
    UF(int N) : parents(N) {
        iota(parents.begin(), parents.end(), 0); // Fill with 0, 1, ..., N-1
    }

    // Find the root of the set containing 'x', with path compression
    int find(int x) {
        if (x != parents[x]) {
            parents[x] = find(parents[x]); // Path compression
        }
        return parents[x];
    }

    // Union the sets containing 'child' and 'parent'
    void unionSets(int child, int parent) {
        parents[find(child)] = find(parent); // Attach the root of child to the root of parent
    }

private:
    vector<int> parents;
};

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts)
    {
        int n = accounts.size();
        UF uf(n); // Create a union-find structure

        // Map to track which email belongs to which account index
        unordered_map<string, int> ownership;

        // Create unions between indexes based on shared emails
        for (int i = 0; i < n; ++i)
        {
            for (int j = 1; j < accounts[i].size(); ++j)
            {
                const string& email = accounts[i][j];
                if (ownership.count(email))
                    uf.unionSets(i, ownership[email]);

                ownership[email] = i;
            }
        }

        // Group emails by root account
        unordered_map<int, unordered_set<string>> mergedAccounts;
        for (const auto& [email, owner] : ownership)
        {
            int rootOwner = uf.find(owner);
            mergedAccounts[rootOwner].insert(email);
        }

        // Prepare the result
        vector<vector<string>> result;
        for (const auto& [owner, emails] : mergedAccounts)
        {
            vector<string> mergedAccount(emails.begin(), emails.end());

            sort(mergedAccount.begin(), mergedAccount.end());

            mergedAccount.insert(mergedAccount.begin(), accounts[owner][0]); // Add the name at the start
            result.push_back(mergedAccount);
        }

        return result;
    }
};
