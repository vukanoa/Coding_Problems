#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <climits>

/*

    You are given 2 arrays representing integer locations of stores and houses
    (each location in this problem is one-dementional). For each house, find
    the store closest to it.  Return an integer array result where result[i]
    should denote the location of the store closest to the i-th house. If many
    stores are equidistant from a particular house, choose the store with the
    smallest numerical location. Note that there may be multiple stores and
    houses at the same location.


    Example 1:
    Input: houses = [5, 10, 17], stores = [1, 5, 20, 11, 16]
    Output: [5, 11, 16]
    Explanation:
    The closest store to the house at location 5 is the store at the same
    location.
    The closest store to the house at location 10 is the store at
    the location 11.
    The closest store to the house at location 17 is the
    store at the location 16.


    Example 2:
    Input: houses = [2, 4, 2], stores = [5, 1, 2, 3]
    Output: [2, 3, 2]


    Example 3:
    Input: houses = [4, 8, 1, 1], stores = [5, 3, 1, 2, 6]
    Output: [3, 6, 1, 1]

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Complexity: O(N*logM + M*logM) */
/* Space Complexity: O(N + M)           */ // N for Sets and M is "std::sort" used extra M memory
class Solution_Upper_Bound {
public:
    std::vector<int> solution(std::vector<int>& houses, std::vector<int>& stores)
    {
        std::vector<int> results(houses.size());

        // O(M * logM)
        std::sort(stores.begin(), stores.end());

        // O(N)
        std::unordered_set<int> uniq_houses;
        for (int& house : houses)
            uniq_houses.insert(house);

        // Key: House     :      Value: Store
        std::unordered_map<int, int> store_for_house;

        // O(N * logM)
        for (const int& house : uniq_houses)
        {
            auto upper = std::upper_bound(stores.begin(), stores.end(), house);

            int diff_higher = INT_MAX;
            int diff_lower  = INT_MAX;

            if (upper != stores.end())
                diff_higher = *upper - house;

            auto lower = upper;
            if (upper != stores.begin())
            {
                lower = upper-1;
                diff_lower = house - *lower;
            }

            int closest_store = diff_lower <= diff_higher ? *lower : *upper;
            store_for_house.insert({house, closest_store});
        }

        for (int i = 0; i < houses.size(); i++)
            results[i] = store_for_house[houses[i]];

        return results;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Complexity: O(N*logM + M*logM) */
/* Space Complexity: O(M)               */ // M if "std::sort" uses extra M memory
class Solution_Lower_Bound {
public:
    std::vector<int> solution(std::vector<int>& houses, std::vector<int>& stores)
    {
        std::vector<int> results(houses.size());

        // O(M * logM)
        std::sort(begin(stores), end(stores));

        // O(N * logM)
        for (int i = 0 ; i < houses.size(); i++)
        {
            int index = std::lower_bound(stores.begin(),stores.end(), houses[i]) - stores.begin();

            if (index == 0)
                results[i] = stores[index];
            else if (index == stores.size())
                results[i] = stores[index - 1];
            else
            {
                int distance_left  = houses[i] - stores[index - 1];
                int distance_right = stores[index] - houses[i];

                if (distance_left <= distance_right)
                    results[i] = stores[index - 1];
                else
                    results[i] = stores[index];
            }
        }

        return results;
    }
};


int
main()
{
    Solution_Upper_Bound sol_upper;
    Solution_Lower_Bound sol_lower;

    /* Example 1 */
    std::vector<int> houses = {5, 10, 17};
    std::vector<int> stores = {1, 5, 20, 11, 16};

    /* Example 2 */
    // std::vector<int> houses = {2, 4, 2};
    // std::vector<int> stores = {5, 1, 2, 3};

    /* Example 3 */
    // std::vector<int> houses = {4, 8, 1, 1};
    // std::vector<int> stores = {5, 3, 1, 2, 6};


    std::cout << "\n\t=========================";
    std::cout << "\n\t=== STORES AND HOUSES ===";
    std::cout << "\n\t=========================\n";



    /* Write Input */
    bool first = true;
    std::cout << "\n\tHouses: [";
    for (auto x: houses)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]";

    first = true;
    std::cout << "\n\tStores: [";
    for (auto x: stores)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n";


    /* Solution */
    // std::vector<int> result = sol.solution(houses, stores);
    // std::vector<int> result = sol_upper.solution(houses, stores);
    std::vector<int> result = sol_lower.solution(houses, stores);


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
