/*

    There are several projects, and each is denoted by a one letter name.
    Each project may depend on one or more other projects (or none).

    For example, if project A depends on project B, then project A cannot complete
    before project B.

    You are given a list of dependences called "edges", of K such dependencies
    and also a list of delayed projects called "delayed", of J such projects.

    Output a list of all projects that will be delayed, in
    lexicographical(alphabetical) order.

    You can assume that a project, A, will be delayed if any project A depends
    on is delayed. The input is guaranteed to contain no circular dependencies.

    // Example 1
    Input:
        edges   = [['B','A'], ['C','B']]
        delayed = ['B']

    Output: ['B', 'C']




    // Example 2
    Input:
        edges = [['P','Q'], ['P','S'], ['Q','R'], ['R','T'], ['S','T']];
        delayed = ['Q','S']

    Output: ['P','Q','S']





    // Example 3
    Input:
        edges   = [['B','A'], ['C','B'], ['C','E'], ['D','C'], ['D','F'],
                   ['E','A'], ['F','E'], ['G','F']]
        delayed = ['B','F']

    Output: ['B','C','D','F','G']




    Constraints:
    1 <= K  <= 100
    1 <= 26 <= J
    Projects names are single uppercase letters, i.e {A-Z}

*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

/* Time  Complexity: O(K * logK) */
/* Space Complexity: O(K) */
class Solution {
public:
    std::vector<char> delayedProjects(std::vector<std::vector<char>>& edges,
                                      std::vector<char> delayed)
    {
        std::unordered_map<char, std::vector<char>> adj_list;

        // O(K)
        for (auto& entry : edges)
            adj_list[entry[0]].push_back(entry[1]);

        // O(J) -> O(26) -> O(1)
        std::vector<char> result;
        for (char& proj : delayed)
            result.push_back(proj);

        // O(K)
        for (auto& entry : adj_list)
        {
            // O(J) -> O(26) -> O(1)
            for (int i = 0; i < entry.second.size(); i++)
            {
                // O(J) -> O(26) -> O(1)
                for (int j = 0; j < delayed.size(); j++)
                {
                    if (delayed[j] == entry.second[i])
                    {
                        result.push_back(entry.first);

                        i = entry.second.size(); // So that it breaks outer too
                        break;
                    }
                }
            }
        }

        // O(K * logK)
        std::sort(result.begin(), result.end());

        return result;
    }
};


int
main()
{
    Solution sol;

    /* Example 1 */
    // std::vector<char> delayed = {'B'};
    // std::vector<std::vector<char>> edges = {{'B','A'}, {'C','B'}};


    /* Example 2 */
    // std::vector<char> delayed = {'Q','S'};
    // std::vector<std::vector<char>> edges = {{'P','Q'}, {'P','S'}, {'Q','R'},
    //                                        {'R','T'}, {'S','T'}};


    /* Example 3 */
    std::vector<char> delayed = {'B','F'};
    std::vector<std::vector<char>> edges = {{'B','A'}, {'C','B'}, {'C','E'}, {'D','C'},
                                            {'D','F'}, {'E','A'}, {'F','E'}, {'G','F'}};


    std::cout << "\n\t========================";
    std::cout << "\n\t=== DELAYED PROJECTS ===";
    std::cout << "\n\t========================\n";

    /* Write Input */

    /* Write Output */
    bool first = true;
    std::cout << "\n\tEdges: [";
    for (auto x: edges)
    {
        if (!first)
            std::cout << ", ";

        bool first_first = true;
        std::cout << "[";
        for (const auto& xx : x)
        {
            if (!first_first)
                std::cout << ", ";

            std::cout << xx;
            first_first = false;
        }
        std::cout << "]";

        first = false;
    }
    std::cout << "]";


    first = true;
    std::cout << "\n\tDelayed: [";
    for (auto x : delayed)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n";


    /* Solution */
    std::vector<char> result = sol.delayedProjects(edges, delayed);


    /* Write Output */
    first = true;
    std::cout << "\n\tResult: [";
    for (auto x: result)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n";

    std::cout << "\n\n";
    return 0;
}
