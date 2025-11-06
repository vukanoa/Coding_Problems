/*
    ============
    === HARD ===
    ============

    ===========================================
    3321) Find X-Sum of All K-Long Subarrays II 
    ===========================================

    ============
    Description:
    ============

    You are given an array nums of n integers and two integers k and x.

    The x-sum of an array is calculated by the following procedure:

        + Count the occurrences of all elements in the array.

        + Keep only the occurrences of the top x most frequent elements. If two
          elements have the same number of occurrences, the element with the
          bigger value is considered more frequent.

        + Calculate the sum of the resulting array.

    Note that if an array has less than x distinct elements, its x-sum is the
    sum of the array.

    Return an integer array answer of length n - k + 1 where answer[i] is the
    x-sum of the nums[i..i + k - 1].

    ======================================================================
    FUNCTION: vector<long long> findXSum(vector<int>& nums, int k, int x);
    ======================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,1,2,2,3,4,2,3], k = 6, x = 2
    Output: [6,10,12]
    Explanation:
        For subarray [1, 1, 2, 2, 3, 4], only elements 1 and 2 will be kept in
        the resulting array. Hence, answer[0] = 1 + 1 + 2 + 2.
        For subarray [1, 2, 2, 3, 4, 2], only elements 2 and 4 will be kept in
        the resulting array. Hence, answer[1] = 2 + 2 + 2 + 4. Note that 4 is
        kept in the array since it is bigger than 3 and 1 which occur the same
        number of times.
        For subarray [2, 2, 3, 4, 2, 3], only elements 2 and 3 are kept in the
        resulting array. Hence, answer[2] = 2 + 2 + 2 + 3 + 3.


    --- Example 2 ---
    Input: nums = [3,8,7,8,7,5], k = 2, x = 2
    Output: [11,15,15,15,12]
    Explanation:
    Since k == x, answer[i] is equal to the sum of the subarray nums[i..i + k - 1].


    *** Constraints ***
    nums.length == n
    1 <= n <= 10^5
    1 <= nums[i] <= 10^9
    1 <= x <= k <= nums.length

*/

#include <bits/stdc++.h>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 23.08% */
/* Space Beats: 11.54% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */

class Solution {
private:
    map<int, int> freq;
    multiset<pair<int, int>> top;
    multiset<pair<int, int>> rest;
    long long top_sum = 0;
    int x;

public:
    vector<long long> findXSum(vector<int>& nums, int k, int x)
    {
        this->x = x;
        freq.clear();
        top.clear();
        rest.clear();
        top_sum = 0;

        vector<long long> result;

        for (int i = 0; i < k; ++i)
            add(nums[i]);
        result.push_back(top_sum);

        for (int i = k; i < (int)nums.size(); ++i)
        {
            remove(nums[i - k]);
            add(nums[i]);
            result.push_back(top_sum);
        }

        return result;
    }

private:
    void balance()
    {
        while ((int)top.size() < x && !rest.empty())
        {
            auto it = prev(rest.end());
            top.insert(*it);
            top_sum += 1LL * it->first * it->second;
            rest.erase(it);
        }

        while ((int)top.size() > x)
        {
            auto it = top.begin();
            top_sum -= 1LL * it->first * it->second;
            rest.insert(*it);
            top.erase(it);
        }

        while ( ! rest.empty() && !top.empty() && *prev(rest.end()) > *top.begin())
        {
            auto it1 = prev(rest.end());
            auto it2 = top.begin();
            top_sum += 1LL * it1->first * it1->second - 1LL * it2->first * it2->second;

            rest.insert(*it2);
            top.insert(*it1);
            rest.erase(it1);
            top.erase(it2);
        }
    }

    void add(int num)
    {
        pair<int, int> old = {freq[num], num};

        if (top.find(old) != top.end())
        {
            top.erase(top.find(old));
            top_sum -= 1LL * old.first * old.second;
        }
        else if (rest.find(old) != rest.end())
        {
            rest.erase(rest.find(old));
        }

        freq[num]++;
        rest.insert({freq[num], num});
        balance();
    }

    void remove(int num)
    {
        pair<int, int> old = {freq[num], num};

        if (top.find(old) != top.end())
        {
            top.erase(top.find(old));
            top_sum -= 1LL * old.first * old.second;
        }
        else
        {
            rest.erase(rest.find(old));
        }

        freq[num]--;
        if (freq[num] > 0)
            rest.insert({freq[num], num});
        else
            freq.erase(num);

        balance();
    }
};
