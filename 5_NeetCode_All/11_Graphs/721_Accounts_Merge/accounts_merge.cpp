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

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

    Similar Disjoint-Set Union(aka Union and Find) problems:

        547.  Number of Provinces
        952.  Largest Component Size by Common Factor
        947.  Most Stones Removed with Same Row or Column
        1319. Number of Operations to Make Network Connected
        684.  Redundant Connection
        990.  Satisfiability of Equality Equations
        1202. Smallest String With Swaps
        2421. Number of Good Paths

*/

/* Time  Beats: 84.00% */
/* Space Beats: 92.25% */

/* Time  Complexity: O(N * M        * LEN_OF_LONGEST_EMAIL + N * M        * alpha(N) + N * M        * log(N * M))        */
/* Time  Complexity: O(TOTAL_EMAILS * LEN_OF_LONGEST_EMAIL + TOTAL_EMAILS * alpha(N) + TOTAL_EMAILS * log(TOTAL_EMAILS)) */
/* Space Complexity: O(N + TOTAL_EMAILS * LEN_OF_LONGEST_EMAIL)                                                          */
class DSU {
private:
    vector<int> rank;
    vector<int> parent;

public:
    DSU (int n)
    {
        rank.resize(n);
        parent.resize(n);

        for (int i = 0; i < n; i++)
        {
            rank[i]   = 1;
            parent[i] = i;
        }
    }

    int find_root(int node)
    {
        while (node != parent[node])
        {
            /* Reverse Ackerman function, <= 5 for all practical purposes */
            parent[node] = parent[parent[node]];

            node = parent[node];
        }

        return node;
    }

    bool union_components(int node_1, int node_2)
    {
        int root_1 = find_root(node_1);
        int root_2 = find_root(node_2);

        if (root_1 == root_2)
            return false;

        if (rank[root_1] < rank[root_2])
            swap(root_1, root_2);

        parent[root_2] = root_1;
        rank[root_1]  += rank[root_2];

        return true;
    }
};

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts)
    {
        const int N = accounts.size();

        DSU dsu(N);

        // O(N * M * LEN_OF_LONGEST_EMAIL) <==> O(TOTAL_EMAILS * LEN_OF_LONGEST_EMAIL)
        unordered_map<string, int> email__to__account_idx;
        for (int account_idx = 0; account_idx < N; account_idx++) // O(N)
        {
            // Skip i=0, as that is the NAME of the account, not an email
            for (unsigned i = 1; i < accounts[account_idx].size(); i++) // O(M)
            {
                string& email = accounts[account_idx][i];

                if (email__to__account_idx.count(email)) // O(LEN_OF_LONGEST_EMAIL)
                {
                    int& other_acount_idx = email__to__account_idx[email];

                    // O(alpha(N)) <==> O(1) for all practical purposes,
                    // O(1) because we go directly from email to account_idx
                    // and not from some deep account_idx upwards.
                    dsu.union_components(account_idx, other_acount_idx);
                }
                else
                {
                    // O(LEN_OF_LONGEST_EMAIL) because of Hashing
                    email__to__account_idx.insert( {email, account_idx} );
                }
            }
        }

        unordered_map<int, vector<string>> email_groups;

        // O(N * M * alpha(N)) <==> O(TOTAL_EMAILS * alpha(N))  (entire block)
        for (const auto& [email, account_idx] : email__to__account_idx)
        {
            int root_account_idx = dsu.find_root(account_idx); // O(alpha(N)) <==> O(1)

            email_groups[root_account_idx].push_back(email);
        }

        /*

            We have two options:
                1) email_groups is of same size as initial accounts, i.e. no
                   accounts merged

                2) email_groups is of size 1, i.e. all the accounts merged.

            ~~~~~~~~~~
            ~~~ 1) ~~~
            ~~~~~~~~~~
            If 1), then for each of N acounts(i.e. accounts.size()), we copy
            emails from the emails_groups to results in O(M), where M is the
            upper_bound of emails per account. Tht makes it O(N * M) so far.

            Then we sort this "final_account" of size(M + 1), but we only sort
            last M slots, which makes it: O(M * logM) Therefore in 1), it
            should be:
                O(N * M + N * M * logM)

            ~~~~~~~~~~
            ~~~ 2) ~~~
            ~~~~~~~~~~
            However, if it's 2), then we only have a single account in
            email_groups, but that means we have a total of N * M emails within
            that single account, i.e. TOTAL_EMAILS. First we copy all of those
            emails to results in O(TOTAL_EMAILS) time. Then we sort it in:
                O(TOTAL_EMAIL * log(TOTAL_EMAILS))

            So how do we know if we should specify:

                1) O(N * M + N * M * logM)

                    or

                2) O(TOTAL_EMAIL * log(TOTAL_EMAILS))


            Let's think logically. If it's 1), then we would have N accounts of
            1 distinct email each. Therefore it would take a total of:

                O(N * 1   +  N * 1 * log1) --> O(N + N) --> O(2N) --> O(N)

            But that's not THE WORST scenario.

            Scenario in 2) would be WORSE. If it's 2), then we have a SINGLE
            account with ALL of the emails, i.e. all (N * M) emails,

            TOTAL_EMAILS = N * M

            In that case we'd have:

                O(1 * TOTAL_EMAILS  +  TOTAL_EMAIL * logTOTAL_EMAILS)

            Which is:

                O(TOTAL_EMAILS * logTOTAL_EMAILS)

            And since that is WORSE than O(N) from 1), we conclude that this is
            the correct Time Complexity for this given block.

        */
        vector<vector<string>> results;
        for (const auto& [root_account_idx, emails] : email_groups)
        {
            string& name = accounts[root_account_idx][0];

            vector<string> final_account;
            final_account.push_back(name);
            final_account.insert(final_account.end(), emails.begin(), emails.end()); // O(M)

            /* Sort only emails */
            sort(final_account.begin() + 1, final_account.end()); // O(M * logM)

            results.push_back(final_account);
        }

        return results;
    }
};
