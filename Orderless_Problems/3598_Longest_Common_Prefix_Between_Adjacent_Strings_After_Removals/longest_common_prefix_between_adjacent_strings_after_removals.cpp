/*
    ==============
    === MEDIUM ===
    ==============

    ===================================================================
    3598) Longest Common Prefix Between Adjacent Strings After Removals
    ===================================================================

    ============
    Description:
    ============


    You are given an array of strings words. For each index i in the range
    [0, words.length - 1], perform the following steps:

        + Remove the element at index i from the words array.

        + Compute the length of the longest common prefix among all adjacent
          pairs in the modified array.

    Return an array answer, where answer[i] is the length of the longest common
    prefix between the adjacent pairs after removing the element at index i.
    If no adjacent pairs remain or if none share a common prefix, then
    answer[i] should be 0.


    =================================================================
    FUNCTION: vector<int> longestCommonPrefix(vector<string>& words);
    =================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: words = ["jump","run","run","jump","run"]
    Output: [3,0,0,3,3]
    Explanation:
        Removing index 0:
            words becomes ["run", "run", "jump", "run"]
            Longest adjacent pair is ["run", "run"] having a common prefix "run" (length 3)
        Removing index 1:
            words becomes ["jump", "run", "jump", "run"]
            No adjacent pairs share a common prefix (length 0)
        Removing index 2:
            words becomes ["jump", "run", "jump", "run"]
            No adjacent pairs share a common prefix (length 0)
        Removing index 3:
            words becomes ["jump", "run", "run", "run"]
            Longest adjacent pair is ["run", "run"] having a common prefix "run" (length 3)
        Removing index 4:
            words becomes ["jump", "run", "run", "jump"]
            Longest adjacent pair is ["run", "run"] having a common prefix "run" (length 3)


    --- Example 2 ---
    Input: words = ["dog","racer","car"]
    Output: [0,0,0]
    Explanation:
        Removing any index results in an answer of 0.


    *** Constraints ***
    1 <= words.length <= 10^5
    1 <= words[i].length <= 10^4
    words[i] consists of lowercase English letters.
    The sum of words[i].length is smaller than or equal 10^5.

*/

#include <queue>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 5.04% */
/* Space Beats: 8.32% */

/* Time  Complexity: O(N * M * logN) */
/* Space Complexity: O(N)            */
class Solution {
public:
    vector<int> longestCommonPrefix(vector<string>& words)
    {
        const int N = words.size();

        if (N == 1)
            return {0};
        
        if (N == 2)
            return {0, 0};

        vector<int> answer(N, 0);
        priority_queue<vector<int>> max_heap;

        for (int i = 1; i < N-1; i++)
        {
            int LCP = longest_common_prefix(words[i], words[i+1]);
            max_heap.push( {LCP, i, i+1} );
        }

        answer[0] = max_heap.top()[0];


        for (int i = 1; i < N; i++)
        {

            if (i < N-1)
            {
                int LCP = longest_common_prefix(words[i-1], words[i+1]);
                max_heap.push( {LCP, i-1, i+1} );
            }

            vector<int> buffer;
            while ( ! max_heap.empty())
            {
                auto top = max_heap.top();

                int len = top[0];
                int L   = top[1];
                int R   = top[2];

                if (L == i || R == i)
                {
                    max_heap.pop();
                    buffer = top;
                }
                else if (abs(R - L) > 1)
                {
                    max_heap.pop();

                    if (L < i && i < R)
                    {
                        answer[i] = len;
                        break;
                    }
                }
                else
                {
                    answer[i] = len;
                    break;
                }
            }

            max_heap.push(buffer);

            int LCP = longest_common_prefix(words[i-1], words[i]);
            max_heap.push( {LCP, i-1, i} );
        }

        return answer;
    }

private:
    int longest_common_prefix(string& w1, string& w2)
    {
        const int N = w1.length();
        const int M = w2.length();

        int result = 0;

        int i = 0;
        int j = 0;
        while (i < N && j < M)
        {
            if (w1[i] != w2[j])
                break;

            i++;
            j++;

            result++;
        }

        return result;
    }
};
