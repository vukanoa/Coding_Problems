/*
    ============
    === EASY ===
    ============

    ===========================================
    1356) Sort Integers by the Number of 1 Bits
    ===========================================

    ============
    Description:
    ============

    You are given an integer array arr. Sort the integers in the array in
    ascending order by the number of 1's in their binary representation and in
    case of two or more integers have the same number of 1's you have to sort
    them in ascending order.

    Return the array after sorting it.

    ===================================================
    FUNCTION: vector<int> sortByBits(vector<int>& arr);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: arr = [0,1,2,3,4,5,6,7,8]
    Output: [0,1,2,4,8,3,5,6,7]
    Explantion: [0] is the only integer with 0 bits.
    [1,2,4,8] all have 1 bit.
    [3,5,6] have 2 bits.
    [7] has 3 bits.
    The sorted array by bits is [0,1,2,4,8,3,5,6,7]

    --- Example 2 ---
    Input: arr = [1024,512,256,128,64,32,16,8,4,2,1]
    Output: [1,2,4,8,16,32,64,128,256,512,1024]
    Explantion: All integers have 1 bit in the binary representation, you
                should just sort them in ascending order.


    *** Constraints ***
    1 <= arr.length <= 500
    0 <= arr[i] <= 10^4

*/

#include <algorithm>
#include <bitset>
#include <queue>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    "Manually" count bits using 31 shifts.

*/

/* Time  Beats: 21.84% */
/* Space Beats: 26.68% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution_1 {
public:
    vector<int> sortByBits(vector<int>& arr)
    {
        const int N = arr.size();
        vector<int> result;

        vector<priority_queue<int, vector<int>, greater<int>>> bits(32);

        for (int i = 0; i < N; i++)
        {
            int num = arr[i];

            int bits_count = 0;
            while (num > 0)
            {
                if (num & 1)
                    bits_count++;

                num >>= 1;
            }

            bits[bits_count].push(arr[i]);
        }

        for (int i = 0; i < 32; i++)
        {
            while ( ! bits[i].empty())
            {
                result.push_back(bits[i].top());
                bits[i].pop();
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Count bits using GCC and Clang's compiler feature "__builtin_popcount".

*/

/* Time  Beats: 100.00% */
/* Space Beats:  33.41% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution_2 {
public:
    vector<int> sortByBits(vector<int>& arr)
    {
        const int N = arr.size();
        vector<int> result;

        vector<priority_queue<int, vector<int>, greater<int>>> bits(32);

        for (int i = 0; i < N; i++)
        {
            int set_bits = __builtin_popcount(arr[i]);
            bits[set_bits].push(arr[i]);
        }

        for (int i = 0; i < 32; i++)
        {
            while ( ! bits[i].empty())
            {
                result.push_back(bits[i].top());
                bits[i].pop();
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Count bits in O(k) where 'k' is the number of set-bits in a number, using
    Brian Kernigham's Algorithm.

*/

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution_Brian_Kernigham_Algo {
public:
    vector<int> sortByBits(vector<int>& arr)
    {
        const int N = arr.size();
        vector<int> result;

        // 32 MIN-Heaps
        vector<priority_queue<int, vector<int>, greater<int>>> bits(32);

        for (int i = 0; i < N; i++)
        {
            int bits_count = count_bits_Brian_Kernigham_Algo(arr[i]);

            bits[bits_count].push(arr[i]);
        }

        for (int i = 0; i < 32; i++)
        {
            while ( ! bits[i].empty())
            {
                result.push_back(bits[i].top());
                bits[i].pop();
            }
        }

        return result;
    }

private:
    int count_bits_Brian_Kernigham_Algo(int number)
    {
        int bits_count = 0;
        while (number > 0) // O(k), where 'k' is the number of set-bits
        {
            bits_count++;
            number = number & (number - 1);
        }

        return bits_count;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Using Bitsets in a standard sort.

*/

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(logN)     */
class Solution_Bitset {
public:
    vector<int> sortByBits(vector<int>& arr)
    {
        sort(arr.begin(), arr.end(),
             []( int x, int y )
             {
                 int bits_in_x = bitset<31>(x).count();
                 int bits_in_y = bitset<31>(y).count();

                 if (bits_in_x == bits_in_y)
                     return x < y;

                 return bits_in_x < bits_in_y;
             });

        return arr;
    }
};
