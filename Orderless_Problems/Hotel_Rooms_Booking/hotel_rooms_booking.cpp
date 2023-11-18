#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <sstream>

/*
    Given a hotel which has 10 floors [0-9] and each floor has 26 rooms [A-Z].
    You are given a sequence of rooms, where + suggests room is booked, - room
    is freed. You have to find which room is booked maximum number of times.

    You may assume that the list describe a correct sequence of bookings in
    chronological order; that is, only free rooms can be booked and only booked
    rooms can be freeed. All rooms are initially free. Note that this does not
    mean that all rooms have to be free at the end. In case, 2 rooms have been
    booked the same number of times, return the lexographically smaller room.

    You may assume:

        - N (length of input) is an integer within the range [1, 600]

        - each element of array A is a string consisting of three characters:
          "+" or "-"; a digit "0"-"9"; and uppercase English letter "A" - "Z"

        - the sequence is correct. That is every booked room was previously
          free and every freed room was previously booked.

    Example:

    Input: ["+1A", "+3E", "-1A", "+4F", "+1A", "-3E"] Output: "1A" Explanation:
    1A as it has been booked 2 times.

*/

class Solution {
public:
    std::string solution(std::vector<std::string>& input)
    {
        // Space: O(1) Since its always going to be 10 * 26
        std::vector<std::vector<int>> hotel(10, std::vector<int>(26));

        // O(n)
        for (std::string& str : input)
        {
            // Since the sequence is guarantted to be correct, we only care
            // about bookings and not about freeings of the rooms.
            if (str[0] == '+')
                hotel[str[1] - '0'][str[2] - 'A']++;
        }

        // Red-Black Tree (by number of bookings)
        std::map<int,
                 std::priority_queue<std::string,
                                     std::vector<std::string>,
                                     std::greater<std::string>>,
                 std::greater<int>> descending_map;

        // Time Complexity of this outer loop is : O(1) since
        // it's always going to be 10 * 26
        // However because we insert in the Heap at max 10*26 times, then the
        // overall Time Complexity is: O(10 * 26 * log n) where n is 10*26

        // So it's: O(10*26 * 10*26) which is just O(1)
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 26; j++)
            {
                char num    = i + '0';
                char letter = j + 'A';

                std::ostringstream out;
                out << num << letter;

                // O(log n) is the insertion time for a Heap
                // However since n is a constant(10 * 26 in this case)
                // then it's just going to be O(1)
                descending_map[hotel[i][j]].push(out.str());
            }
        }

        return descending_map.begin()->second.top();
    }
};


int
main()
{
    Solution sol;

    /* Example 1 */
    std::vector<std::string> input = {"+1A", "+3E", "-1A", "+4F", "+1A", "-3E"};


    /* Write Input */
    bool first = true;
    std::cout << "\n\tInput: [";
    for (auto x: input)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n\n";


    /* Solution */
    std::string result = sol.solution(input);


    /* Write Input */
    std::cout << "\n\tResult: " << result << "\n\n";


    return 0;
}
