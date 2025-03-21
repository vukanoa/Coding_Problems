/*
    ==============
    === MEDIUM ===
    ==============

    ===================================================
    2115) Find All Possible Recipes from Given Supplies
    ===================================================

    ============
    Description:
    ============

    You have information about n different recipes. You are given a string
    array recipes and a 2D string array ingredients. The ith recipe has the
    name recipes[i], and you can create it if you have all the needed
    ingredients from ingredients[i]. A recipe can also be an ingredient for
    other recipes, i.e., ingredients[i] may contain a string that is in recipes

    You are also given a string array supplies containing all the ingredients
    that you initially have, and you have an infinite supply of all of them.

    Return a list of all the recipes that you can create. You may return the
    answer in any order.

    =====
    Note: that two recipes may contain each other in their ingredients.
    =====

    ===============================
    FUNCTION:  vector<string> findAllRecipes(vector<string>& recipes,
                                  vector<vector<string>>& ingredients,
                                  vector<string>& supplies);
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: recipes = ["bread"], ingredients = [["yeast","flour"]], supplies = ["yeast","flour","corn"]
    Output: ["bread"]
    Explanation:
    We can create "bread" since we have the ingredients "yeast" and "flour".

    --- Example 2 ---
    Input: recipes = ["bread","sandwich"], ingredients = [["yeast","flour"],["bread","meat"]], supplies = ["yeast","flour","meat"]
    Output: ["bread","sandwich"]
    Explanation:
    We can create "bread" since we have the ingredients "yeast" and "flour".
    We can create "sandwich" since we have the ingredient "meat" and can create the ingredient "bread".

    --- Example 3 ---
    Input: recipes = ["bread","sandwich","burger"], ingredients = [["yeast","flour"],["bread","meat"],["sandwich","meat","bread"]], supplies = ["yeast","flour","meat"]
    Output: ["bread","sandwich","burger"]
    Explanation:
    We can create "bread" since we have the ingredients "yeast" and "flour".
    We can create "sandwich" since we have the ingredient "meat" and can create the ingredient "bread".
    We can create "burger" since we have the ingredient "meat" and can create the ingredients "bread" and "sandwich".


    *** Constraints ***
    n == recipes.length == ingredients.length
    1 <= n <= 100
    1 <= ingredients[i].length, supplies.length <= 100
    1 <= recipes[i].length, ingredients[i][j].length, supplies[k].length <= 10
    recipes[i], ingredients[i][j], and supplies[k] consist only of lowercase English letters.
    All the values of recipes and supplies combined are unique.
    Each ingredients[i] does not contain any duplicate values.

*/

#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Classic Topological Sort on the Graph.

*/

/* Time  Beats: 36.50% */
/* Space Beats:  5.25% */

/* Time  Complexity: O(N + M) */
/* Space Complexity: O(N + M) */
class Solution {
public:
    vector<string> findAllRecipes(vector<string>& recipes,
                                  vector<vector<string>>& ingredients,
                                  vector<string>& supplies)
    {
        const int N = recipes.size();
        vector<string> result;

        unordered_set<string> uset_supplies(supplies.begin(), supplies.end());
        unordered_set<string> uset_recipes(recipes.begin(), recipes.end());

        unordered_map<string, vector<string>> adj_list;

        for (int i = 0; i < N; i++)
        {
            for (const string& ingr : ingredients[i])
                adj_list[recipes[i]].push_back(ingr);
        }

        unordered_set<string> uset_path;

        for (int i = 0; i < N; i++)
        {
            if (uset_supplies.count(recipes[i]))
                result.push_back(recipes[i]);
            else
            {
                if (dfs(uset_recipes, uset_supplies, adj_list, uset_path, recipes[i]))
                    result.push_back(recipes[i]);
            }
        }

        return result;
    }

private:
    bool dfs(unordered_set<string>& uset_recipes,
             unordered_set<string>& uset_supplies,
             unordered_map<string, vector<string>>& adj_list,
             unordered_set<string> uset_path,
             string curr_recipe)
    {
        if (uset_path.count(curr_recipe))
            return false;

        uset_path.insert(curr_recipe);

        for (const auto& neighbor_ingr : adj_list[curr_recipe])
        {
            if (uset_recipes.count(neighbor_ingr))
            {
                if (uset_supplies.count(neighbor_ingr))
                    continue;

                if ( ! dfs(uset_recipes, uset_supplies, adj_list, uset_path, neighbor_ingr))
                    return false;
            }
            else
            {
                if (uset_supplies.count(neighbor_ingr))
                    continue;

                return false;
            }
        }

        uset_path.erase(curr_recipe);
        uset_supplies.insert(curr_recipe);

        return true;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Topological Sort, Kahn's algortihm variation.

*/

/* Time  Beats: 93.87% */
/* Space Beats: 78.44% */

/* Time  Complexity: O(N + M) */
/* Space Complexity: O(N + M) */
class Solution_Kahns_Algorithm {
public:
    vector<string> findAllRecipes(vector<string>& recipes,
                                  vector<vector<string>>& ingredients,
                                  vector<string>& supplies)
    {
        const int N = recipes.size();
        vector<string> result;

        unordered_set<string> uset_supplies(supplies.begin(), supplies.end());
        unordered_map<string, int> umap_recipe_to_idx;

        unordered_map<string, vector<string>> adj_list;

        for (int idx = 0; idx < recipes.size(); idx++)
            umap_recipe_to_idx[recipes[idx]] = idx;

        // Count of non-supply ingredients needed for each recipe
        vector<int> indegree(recipes.size(), 0);

        for (int i = 0; i < N; i++)
        {
            for (string& ingredient : ingredients[i])
            {
                if ( ! uset_supplies.count(ingredient))
                {
                    adj_list[ingredient].push_back(recipes[i]);
                    indegree[i]++;
                }
            }
        }

        // Start with recipes that only need supplies
        queue<int> queue;
        for (int i = 0; i < N; i++)
        {
            if (indegree[i] == 0)
                queue.push(i);
        }

        // Process recipes in topological order
        while ( ! queue.empty())
        {
            int recipe_idx = queue.front();
            queue.pop();

            string curr_recipe = recipes[recipe_idx];
            result.push_back(curr_recipe);

            // Skip if no recipes depend on this one
            if ( ! adj_list.count(curr_recipe))
                continue;

            // Update recipes that depend on current recipe
            for (const string& dependent_recipe : adj_list[curr_recipe])
            {
                if (--indegree[umap_recipe_to_idx[dependent_recipe]] == 0)
                {
                    queue.push(umap_recipe_to_idx[dependent_recipe]);
                }
            }
        }

        return result;
    }
};
