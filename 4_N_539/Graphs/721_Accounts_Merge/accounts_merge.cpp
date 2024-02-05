#include <iostream>

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

    =================================================================================
    FUNCTION: vector<vector<string>> accountsMerge(vector<vector<string>>& accounts);
    =================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: accounts = [
                       ["John", "johnsmith@mail.com", "john_newyork@mail.com"],
                       ["John", "johnsmith@mail.com", "john00@mail.com"],
                       ["Mary", "mary@mail.com"],
                       ["John", "johnnybravo@mail.com"]
                      ]

    Output: [
             ["John","john00@mail.com", "john_newyork@mail.com", "johnsmith@mail.com"],
             ["Mary","mary@mail.com"],
             ["John","johnnybravo@mail.com"]
            ]

    Explanation: The first and second John's are the same person as they have
    the common email "johnsmith@mail.com".  The third John and Mary are
    different people as none of their email addresses are used by other
    accounts.  We could return these lists in any order, for example the answer

    [
     ['Mary', 'mary@mail.com'],
     ['John', 'johnnybravo@mail.com'],
     ['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com']
    ]

    would still be accepted.



    --- Example 2 ---
    Input: accounts = [
                       ["Gabe", "Gabe0@m.co", "Gabe3@m.co", "Gabe1@m.co"],
                       ["Kevin", "Kevin3@m.co", "Kevin5@m.co", "Kevin0@m.co"],
                       ["Ethan", "Ethan5@m.co", "Ethan4@m.co", "Ethan0@m.co"],
                       ["Hanzo", "Hanzo3@m.co", "Hanzo1@m.co", "Hanzo0@m.co"],
                       ["Fern", "Fern5@m.co", "Fern1@m.co", "Fern0@m.co"]
                      ]
    Output: [
             ["Ethan", "Ethan0@m.co", "Ethan4@m.co", "Ethan5@m.co"],
             ["Gabe", "Gabe0@m.co", "Gabe1@m.co", "Gabe3@m.co"],
             ["Hanzo", "Hanzo0@m.co", "Hanzo1@m.co", "Hanzo3@m.co"],
             ["Kevin", "Kevin0@m.co", "Kevin3@m.co", "Kevin5@m.co"],
             ["Fern", "Fern0@m.co", "Fern1@m.co", "Fern5@m.co"]
            ]



    *** Constraints ***
    1 <= accounts.length <= 1000
    2 <= accounts[i].length <= 10
    1 <= accounts[i][j].length <= 30
    accounts[i][0] consists of English letters.
    accounts[i][j] (for j > 0) is a valid email.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 92.37% */
/* Space Beats: 40.34% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::vector<std::vector<string>> accountsMerge(std::vector<std::vector<string>>& accounts)
    {
        int n = accounts.size();

        std::vector<int> ranks(n, 1);
        std::vector<int> parents(n);
        std::iota(parents.begin(), parents.end(), 0);

        std::unordered_map<std::string, int> emails;
        for (int i = 0; i < n; i++)
        {
            for (int j = 1; j < accounts[i].size(); j++)
            {
                if (emails.find(accounts[i][j]) == emails.end())
                    emails[accounts[i][j]] = i;
                else
                {
                    std::pair<int, int> edge = {emails[accounts[i][j]], i};
                    Union(edge, parents, ranks);
                }
            }
        }

        std::vector<std::set<std::string>> merge(n);
        for (auto email : emails)
            merge[Find(email.second, parents)].insert(email.first);

        std::vector<std::vector<std::string>> result;
        for (int i = 0; i < n; i++)
        {
            if (!merge[i].size())
                continue;

            std::vector<std::string> tmp;
            tmp.push_back(accounts[i][0]);

            for(std::string str : merge[i])
                tmp.push_back(str);

            result.push_back(tmp);
        }

        return result;
    }

private:
    int Find(int node, std::vector<int>& parents)
    {
        // Get root parent
        while (node != parents[node])
        {
            // Huge Optimization (From O(n) to Amortized O(1) Time Complexity)
            // If there is no grandparent, nothing will happen
            parents[node] = parents[parents[node]];

            node = parents[node];
        }

        return node;
    }

    int Union(std::pair<int, int>& edge, std::vector<int>& parents, std::vector<int>& ranks)
    {
        // Parent 1 & Parent 2
        int p1 = Find(edge.first,  parents);
        int p2 = Find(edge.second, parents);

        if (p1 == p2)
            return false;

        if (ranks[p2] > ranks[p1])
        {
            parents[p1] = p2;
            ranks[p2] += ranks[p1];
        }
        else // ranks[p1] > ranks[p2]
        {
            parents[p2] = p1;
            ranks[p1] += ranks[p2];
        }

        return true;
    }
};
