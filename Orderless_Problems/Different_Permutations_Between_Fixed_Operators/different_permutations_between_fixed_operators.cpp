#include <iostream>
#include <vector>
#include <sstream>
#include <queue>
#include <unordered_set>

/*
    I thought I am doing LeetCode 241, however I was solving this Description:

    How many distinct results can you get if you're allowed to do all the
    permutations of numbers between operators, but operators themselves aren't
    allowed to be moved?

*/
class Solution {
public:
    std::vector<int> diffWaysToCompute(std::string expression)
    {
        std::vector<int>  nums;
        std::vector<std::string> operators;

        std::ostringstream out;
        for (const char& chr : expression)
        {
            if (std::isdigit(chr))
                out << chr;
            else
            {
                std::string number = out.str();
                nums.push_back(std::stoi(number));

                // Reset std::ostringstream
                out.str("");
                out.clear();

                std::string str_tmp(1, chr);
                operators.push_back(str_tmp);
            }
        }

        /* Backtracking */
        std::vector<std::vector<int>> combinations;
        std::queue<int> queue;
        std::vector<int> curr;
        std::unordered_set<std::string> uset;

        for (int& num : nums)
            queue.push(num);

        backtracking(queue, curr, combinations, uset);


    /* Write Output */
    bool first = true;
    std::cout << "\n\tCombinations: [";
    for (auto x: combinations)
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
    std::cout << "]\n\n";


        std::vector<int> results;
        for (int i = 0; i < combinations.size(); i++)
        {
            std::stack<std::string> stack;

            for (int j = 0; j < operators.size(); j++)
            {
                if ( ! stack.empty() && stack.top() == "*")
                {
                    stack.pop();
                    int num = std::stoi(stack.top());
                    stack.pop();

                    stack.push(std::to_string(num * combinations[i][j]));
                }
                else
                    stack.push(std::to_string(combinations[i][j]));

                stack.push(operators[j]);
            }

            stack.push(std::to_string(combinations[i][combinations[0].size()-1]));


            while (stack.size() >= 3)
            {
                int num2 = std::stoi(stack.top());
                stack.pop();

                std::string oper = stack.top();
                stack.pop();

                int num1 = std::stoi(stack.top());
                stack.pop();

                if (oper == "+")
                    num1 += num2;
                else // It's "-"
                    num1 -= num2;

                stack.push(std::to_string(num1));
            }

            results.push_back(std::stoi(stack.top()));
        }

        return results;
    }

private:
    void backtracking(std::queue<int> queue,
                      std::vector<int> curr,
                      std::vector<std::vector<int>>& combinations,
                      std::unordered_set<std::string>& uset)
    {
        if (queue.empty())
        {
            std::ostringstream out;
            for (int i = 0; i < curr.size() - 1; i++)
                out << curr[i] << "#";
            out << curr[curr.size()-1];

            std::string str = out.str();

            if (uset.find(str) == uset.end()) // If it doesn't exist
            {
                uset.insert(str);
                combinations.push_back(curr); // Unique permutation
            }

            return;
        }

        for (int i = 0; i < queue.size(); i++)
        {
            int num = queue.front();
            queue.pop();
            curr.push_back(num);

            backtracking(queue, curr, combinations, uset);

            curr.pop_back();
            queue.push(num);
        }
    }
};
