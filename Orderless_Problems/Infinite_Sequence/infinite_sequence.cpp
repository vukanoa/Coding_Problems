#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional> // Lambda




/* Bottom-Up Dynamic Programming */
/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Bottom_Up_1 {
public:
    int solution(int N)
    {
        if (N == 0)
            return 0;

        int dp_2 = 0;
        int dp_1 = 1;

        for (int i = 2; i < N; i++)
        {
            int num = dp_2 + dp_1;

            // If it's greater than 9, we have to sum the digits
            if (num > 9)
                num = sum_digits(num);

            dp_2 = dp_1;
            dp_1 = num;
        }

        return dp_2 + dp_1;
    }

private:
    int sum_digits(int n)
    {
        int sum = 0;

        while (n > 0)
        {
            sum += n % 10;
            n /= 10;
        }

        return sum;
    }
};




/* Bottom-Up Dynamic Programming */
/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Bottom_Up_2 {
public:
    int solution(int N)
    {
        if (N == 0)
            return 0;

        /* Lambda Function */
        std::function<int(int)> sum_digits;
        sum_digits = [&](int num) -> int
        {
            int ret = 0;
            while (num)
            {
                ret += num % 10;
                num /= 10;
            }

            return ret;
        };

        int even = 0;
        int odd  = 1;
        for (int i = 2; i <  N; i++)
        {
            if (i & 1) // Odd
                odd  = sum_digits(odd + even);
            else // Even
                even = sum_digits(odd + even);
        }

        return even + odd;
    }
};




/* Bottom-Up Dynamic Programming */
/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Bottom_Up_3 {
public:
    int solution(int N)
    {
        if (N == 0)
            return 0;

        int prev = 0;
        int curr = 1;

        for (int i = 2; i <= N; i++)
        {
            int sum_digits_curr = 0;
            while (curr)
            {
                sum_digits_curr += curr % 10;
                curr /= 10;
            }

            // Prev holds a sum of digits of the 2nd element to the left
            int tmp = prev + sum_digits_curr;

            prev = sum_digits_curr;
            curr = tmp;
        }

        return curr;
    }
};




/* Top-Down Memoization */
/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Top_Down {
public:
    int solution(int N)
    {
        std::unordered_map<int, int> dp;
        dp.insert({0, 0});
        dp.insert({1, 1});

        return fib(N - 2, dp) + fib(N - 1, dp);
    }

private:
    int fib(int N, std::unordered_map<int, int>& dp)
    {
        if (dp.find(N) != dp.end())
            return dp[N];

        int num = fib(N - 2, dp) + fib(N - 1, dp);

        if (num < 10)
            dp.insert({N, num});
        else
            dp.insert({N, sum_digits(num)});

        return dp[N];
    }

    int sum_digits(int n)
    {
        int sum = 0;

        while (n > 0)
        {
            sum += n % 10;
            n /= 10;
        }

        return sum;
    }
};


int
main()
{
    Solution_Bottom_Up_1 sol_bot_1;
    Solution_Bottom_Up_2 sol_bot_2;
    Solution_Bottom_Up_3 sol_bot_3;
    Solution_Top_Down    sol_top;

    /* Example 1 */
    // int N = 2;

    /* Example 2 */
    // int N = 6;

    /* Example 3 */
    // int N = 10;

    /* Example 4 */
    // int N = 11;

    /* Example 5 */
    // int N = 12;

    /* Example 6 */
    // int N = 100;

    /* Example 7 */
    // int N = 1000;

    /* Example 8 */
    // int N = 10000;

    /* Example 9 */
    int N = 1000000;

    /* Example 10 */
    // int N = 10000000;

    /* Example 11 */
    // int N = 100000000;

    /* Example 12 */
    // int N = 1000000000;

    std::cout << "\n\t=========================";
    std::cout << "\n\t=== INFINITE SEQUENCE ===";
    std::cout << "\n\t=========================\n\n";

    /* Write Input */
    std::cout << "\n\tN : " << N << "\n";

    /* Solution */
    int number_bot_1 = sol_bot_1.solution(N);
    int number_bot_2 = sol_bot_2.solution(N);
    // int number_top   = sol_top.solution(N);

    /* Write Output */
    std::cout << "\n\tBottom-Up_1: " << number_bot_1;
    std::cout << "\n\tBottom-Up_2: " << number_bot_2;
    // std::cout << "\n\tTop-Down   : " << number_top;

    std::cout << "\n\n";

    return 0;
}
