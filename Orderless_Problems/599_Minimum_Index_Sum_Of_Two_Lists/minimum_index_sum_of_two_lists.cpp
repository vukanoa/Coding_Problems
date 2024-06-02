#include <iostream>
#include <vector>
#include <unordered_map>

/*
    ============
    === EASY ===
    ============

    ===================================
    599) Minimum Index Sum of Two Lists
    ===================================

    ============
    Description:
    ============

    Given two arrays of strings list1 and list2, find the common strings with
    the least index sum.

    A common string is a string that appeared in both list1 and list2.

    A common string with the least index sum is a common string such that if it
    appeared at list1[i] and list2[j] then i + j should be the minimum value
    among all the other common strings.

    Return all the common strings with the least index sum. Return the answer
    in any order.

    ======================================================================================
    FUNCTION: vector<string> findRestaurant(vector<string>& list1, vector<string>& list2);
    ======================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: list1 = ["Shogun","Tapioca Express","Burger King","KFC"], list2 =
    ["Piatti","The Grill at Torrey Pines","Hungry Hunter Steakhouse","Shogun"]
    Output: ["Shogun"]
    Explanation: The only common string is "Shogun".


    --- Example 2 ---
    Input: list1 = ["Shogun","Tapioca Express","Burger King","KFC"], list2 =
    ["KFC","Shogun","Burger King"]
    Output: ["Shogun"]
    Explanation: The common string with the least index sum is "Shogun" with
    index sum = (0 + 1) = 1.


    --- Example 3 ---
    Input: list1 = ["happy","sad","good"], list2 = ["sad","happy","good"]
    Output: ["sad","happy"]
    Explanation: There are three common strings:
    "happy" with index sum = (0 + 1) = 1.
    "sad" with index sum = (1 + 0) = 1.
    "good" with index sum = (2 + 2) = 4.
    The strings with the least index sum are "sad" and "happy".


    *** Constraints ***
    1 <= list1.length, list2.length <= 1000
    1 <= list1[i].length, list2[i].length <= 30
    list1[i] and list2[i] consist of spaces ' ' and English letters.
    All the strings of list1 are unique.
    All the strings of list2 are unique.
    There is at least a common string between list1 and list2.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 66.44% */
/* Space Beats: 26.48% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::vector<std::string> findRestaurant(std::vector<std::string>& list1, std::vector<std::string>& list2)
    {
        std::unordered_map<std::string, int> umap;
        const int n1 = list1.size();
        const int n2 = list2.size();

        for(int i = 0; i < n2; i++)
            umap[list2[i]] = i;

        int min_index_sum = n1 + n2;
        std::vector<std::string> result;

        for(int i = 0; i < n1; i++)
        {
            std::string s = list1[i];

            if(umap.count(s))
            {
                int indexSum = i + umap[s];

                if(min_index_sum > indexSum)
                {
                    result.clear();
                    min_index_sum = indexSum;
                    result.push_back(s);
                }
                else if (min_index_sum == indexSum)
                    result.push_back(s);
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Another way of implemenitng it.

*/

/* Time  Beats: 66.44% */
/* Space Beats: 55.87% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_2 {
public:
    std::vector<std::string> findRestaurant(std::vector<std::string>& list1, std::vector<std::string>& list2)
    {
        std::vector<std::string> result;

        std::unordered_map<std::string,int> umap;
        int min = INT_MAX;

        for (int i = 0; i < list1.size(); i++)
            umap[list1[i]] = i;

        for (int i = 0; i < list2.size(); i++)
        {
            if (umap.count(list2[i]) != 0)
            {
                if (umap[list2[i]] + i < min)
                    min = umap[list2[i]] + i, result.clear(), result.push_back(list2[i]);
                else if (umap[list2[i]] + i == min)
                    result.push_back(list2[i]);
            }
        }

        return result;
    }
};
