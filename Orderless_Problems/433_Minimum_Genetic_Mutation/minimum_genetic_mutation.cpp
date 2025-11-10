/*
    ==============
    === MEDIUM ===
    ==============

    =============================
    433) Minimum Genetic Mutation
    =============================

    ============
    Description:
    ============

    A gene string can be represented by an 8-character long string, with
    choices from 'A', 'C', 'G', and 'T'.

    Suppose we need to investigate a mutation from a gene string startGene to a
    gene string endGene where one mutation is defined as one single character
    changed in the gene string.

    + For example, "AACCGGTT" --> "AACCGGTA" is one mutation.

    There is also a gene bank bank that records all the valid gene mutations. A
    gene must be in bank to make it a valid gene string.

    Given the two gene strings startGene and endGene and the gene bank bank,
    return the minimum number of mutations needed to mutate from startGene to
    endGene. If there is no such a mutation, return -1.

    =====
    Note: that the starting point is assumed to be valid, so it might not be
          included in the bank.
    =====

    ==================================================================================
    FUNCTION: int minMutation(string startGene, string endGene, vector<string>& bank);
    ==================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: startGene = "AACCGGTT", endGene = "AACCGGTA", bank = ["AACCGGTA"]
    Output: 1

    --- Example 2 ---
    Input: startGene = "AACCGGTT", endGene = "AAACGGTA", bank = ["AACCGGTA","AACCGCTA","AAACGGTA"]
    Output: 2


    *** Constraints ***
    0 <= bank.length <= 10
    startGene.length == endGene.length == bank[i].length == 8
    startGene, endGene, and bank[i] consist of only the characters ['A', 'C', 'G', 'T'].

*/

#include <queue>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  87.85% */

/* Time  Complexity: O(N * M) */
/* Space Complexity: O(N)     */
class Solution {
public:
    int minMutation(string start, string end, vector<string>& bank)
    {
        // Store all valid mutations
        unordered_set<string> valid_mutations(bank.begin(), bank.end());

        // If the end mutation is not in the list, return -1
        if ( ! valid_mutations.count(end))
            return -1;

        queue<string> queue;
        queue.push(start);

        int steps = 0;

        while ( ! queue.empty())
        {
            int level_size = queue.size();

            while (level_size-- > 0)
            {
                string curr_mutation = queue.front();
                queue.pop();

                // If we reached the end mutation
                if (curr_mutation == end)
                    return steps;

                // Remove the current mutation to avoid redundant checks
                valid_mutations.erase(curr_mutation);

                // Try all possible single-character mutations (A, C, G, T)
                for (int i = 0; i < 8; i++)
                {
                    string tmp = curr_mutation;

                    tmp[i] = 'A';
                    if (valid_mutations.count(tmp))
                        queue.push(tmp);

                    tmp[i] = 'C';
                    if (valid_mutations.count(tmp))
                        queue.push(tmp);

                    tmp[i] = 'G';
                    if (valid_mutations.count(tmp))
                        queue.push(tmp);

                    tmp[i] = 'T';
                    if (valid_mutations.count(tmp))
                        queue.push(tmp);
                }
            }

            steps++;
        }

        return -1;
    }
};
