#include <iostream>
#include <vector>
#include <unordered_map>

/*
    ============
    === EASY ===
    ============

    ==================================================
    1460) Make Two Arrays Equal by Reversing Subarrays
    ==================================================

    ============
    Description:
    ============

    You are given two integer arrays of equal length target and arr. In one
    step, you can select any non-empty subarray of arr and reverse it. You are
    allowed to make any number of steps.

    Return true if you can make arr equal to target or false otherwise.

    =================================================================
    FUNCTION: bool canBeEqual(vector<int>& target, vector<int>& arr);
    =================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: target = [1,2,3,4], arr = [2,4,1,3]
    Output: true
    Explanation: You can follow the next steps to convert arr to target:
    1- Reverse subarray [2,4,1], arr becomes [1,4,2,3]
    2- Reverse subarray [4,2], arr becomes [1,2,4,3]
    3- Reverse subarray [4,3], arr becomes [1,2,3,4]
    There are multiple ways to convert arr to target, this is not the only way
    to do so.


    --- Example 2 ---
    Input: target = [7], arr = [7]
    Output: true
    Explanation: arr is equal to target without any reverses.


    --- Example 3 ---
    Input: target = [3,7,9], arr = [3,7,11]
    Output: false
    Explanation: arr does not have value 9 and it can never be converted to
                 target.


    *** Constraints ***
    target.length == arr.length
    1 <= target.length <= 1000
    1 <= target[i] <= 1000
    1 <= arr[i] <= 1000

*/

/*
    ------------
    --- IDEA ---
    ------------

    The only case in which we are UNABLE to reverse "arr" to be like "target"
    is the case if they don't have the exact same elements.

    That's absolutely THE ONLY case in which we are UNABLE to do what we're
    being asked.

    Think about it - You'd always go:"What is the first number in target? Oh,
    okay, then I'll take first x numbers in arr that end in with that number
    and I will reverse it, that way I made arr's first number be the exact same
    and at the exact same position."

    Afterwards you just continue. You continue to do that for 2nd number, 3rd,
    etc.

    As they said:"You are allowed to make any number of steps."

    They don't care. They only care if we can actually make them equal. It's
    purposefully written to confuse you.

    We don't have to do any of that. We only have to check if they have the
    same elements. That's it.

    If yes - True.
    If no  - False.

*/

/* Time  Beats: 87.76% */
/* Space Beats:  6.79% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    bool canBeEqual(vector<int>& target, vector<int>& arr)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        const int n = target.size();

        unordered_map<int, int> umap_target;
        unordered_map<int, int> umap_arr;

        for (int i = 0; i < n; i++)
        {
            umap_target[target[i]]++;
            umap_arr[arr[i]]++;
        }

        return umap_target == umap_arr;
    }
};
