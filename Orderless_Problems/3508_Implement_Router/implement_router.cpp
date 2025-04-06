/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    3508) Implement Router
    ===========================

    ============
    Description:
    ============

    Design a data structure that can efficiently manage data packets in a
    network router. Each data packet consists of the following attributes:

        + source: A unique identifier for the machine that generated the packet
        + destination: A unique identifier for the target machine.
        + timestamp: The time at which the packet arrived at the router.

    Implement the Router class:

    Router(int memoryLimit): Initializes the Router object with a fixed memory
    limit.

        + memoryLimit is the maximum number of packets the router can store at
          any given time.

        + If adding a new packet would exceed this limit, the oldest packet
          must be removed to free up space.

    bool addPacket(int source, int destination, int timestamp): Adds a packet
    with the given attributes to the router.

        + A packet is considered a duplicate if another packet with the same
          source, destination, and timestamp already exists in the router.

        + Return true if the packet is successfully added (i.e., it is not a
          duplicate); otherwise return false.

    int[] forwardPacket(): Forwards the next packet in FIFO (First In First
    Out) order.

        + Remove the packet from storage.
        + Return the packet as an array [source, destination, timestamp].
        + If there are no packets to forward, return an empty array.

    int getCount(int destination, int startTime, int endTime):

        Returns the number of packets currently stored in the router (i.e., not
        yet forwarded) that have the specified destination and have timestamps
        in the inclusive range [startTime, endTime].

    =====
    Note: that queries for addPacket will be made in increasing order of timestamp.
    =====

    ==========================================================================
    CLASS:
    class Router {
    public:
        Router(int memoryLimit)
        {

        }

        bool addPacket(int source, int destination, int timestamp)
        {

        }

        vector<int> forwardPacket()
        {

        }

        int getCount(int destination, int startTime, int endTime)
        {

        }
    };
    ==========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:
    ["Router", "addPacket", "addPacket", "addPacket", "addPacket", "addPacket", "forwardPacket", "addPacket", "getCount"]
    [[3], [1, 4, 90], [2, 5, 90], [1, 4, 90], [3, 5, 95], [4, 5, 105], [], [5, 2, 110], [5, 100, 110]]

    Output:
    [null, true, true, false, true, true, [2, 5, 90], true, 1]

    Explanation
    Router router = new Router(3); // Initialize Router with memoryLimit of 3.
    router.addPacket(1, 4, 90); // Packet is added. Return True.
    router.addPacket(2, 5, 90); // Packet is added. Return True.
    router.addPacket(1, 4, 90); // This is a duplicate packet. Return False.
    router.addPacket(3, 5, 95); // Packet is added. Return True
    router.addPacket(4, 5, 105); // Packet is added, [1, 4, 90] is removed as number of packets exceeds memoryLimit. Return True.
    router.forwardPacket(); // Return [2, 5, 90] and remove it from router.
    router.addPacket(5, 2, 110); // Packet is added. Return True.
    router.getCount(5, 100, 110); // The only packet with destination 5 and timestamp in the inclusive range [100, 110] is [4, 5, 105]. Return 1.


    --- Example 2 ---
    Input:
    ["Router", "addPacket", "forwardPacket", "forwardPacket"]

    [[2], [7, 4, 90], [], []]

    Output:
    [null, true, [7, 4, 90], []]

    Explanation
    Router router = new Router(2); // Initialize Router with memoryLimit of 2.
    router.addPacket(7, 4, 90); // Return True.
    router.forwardPacket(); // Return [7, 4, 90].
    router.forwardPacket(); // There are no packets left, return [].


    *** Constraints ***
    2 <= memoryLimit <= 10^5
    1 <= source, destination <= 2 * 10^5
    1 <= timestamp <= 10^9
    1 <= startTime <= endTime <= 10^9
    At most 10^5 calls will be made to addPacket, forwardPacket, and getCount methods altogether.
    queries for addPacket will be made in increasing order of timestamp.

*/

#include <algorithm>
#include <deque>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    You have probably experienced a bunch of TLEs solving this problem and
    wondered"How the heck is this supposed to be implemented?!?!".

    And you're justified in thinking so.

    However, I must diappoint you. It's not LeetCode, it's you. (It's me as
    well. It took me quie a bit of time to solve this one because of it)

    We haven't read the problem CAREFULLY.

    In problems like these you NEED to utilize EVERY PIECE OF INFORMATION they
    got you.


    First, once you get a TLE(but preferrably before that) look at the
    Constraints!

        2 <= memoryLimit <= 10^5
        1 <= source, destination <= 2 * 10^5
        1 <= timestamp <= 10^9
        1 <= startTime <= endTime <= 10^9
        At most 10^5 calls will be made to addPacket, forwardPacket, and getCount methods altogether.
        queries for addPacket will be made in increasing order of timestamp.

    Three things are important and telling in these Constraints:

        a) 2 <= memoryLimit <= 10^5

        b) At most 10^5 calls will be made to addPacket, forwardPacket, and getCount methods altogether.

        c)  queries for addPacket will be made in increasing order of timestamp.


    Both a) and b) tell us that if Time Complexity of ANY OF OUR FUNCTIONS is
    O(N), it will result int O(N^2) total time.

    Why?

    Because in b), they've told us that at most 10^5 calls will be made, but
    we know that 10^5 is the size of N as well, therefore, that makes it O(N^2)


    Once limits are 10^5, it's almost never acceptable to do a O(N^2) Solution.
    Usually what they're hinting at when they give you a limit of 10^5 is:

        O(N * logN) Time Complexity in total.


    Another thing--If you see a limit of 10^9, it almost always means - DO NOT
    EVEN TRY to use 10^9 Memory and do NOT think you can solve it worse than
    O(N) without getting a TLE.


    Here we had a limit of 10^5, which means in total we should be able to
    solve it using O(N * logN) Time complxity.


    But let me emphasize once again--10^5 CALLS will be made, therefore each
    function Time Complexity should be at worst O(logN).

    It's not that you can have a function be O(N * logN) and then call that
    function 10^5(i.e. N) times.

    That would be O(N^2 * logN) Time Complexity, which is unacceptable given
    our Constraints.



    The next thing that went over your heard is the c) part:

        c)  queries for addPacket will be made in increasing order of timestamp

    USE THAT!

    It's literally sorted for you. It SCREAMS "Binary Search".


    Once you utilize both of these information from the Constraints, you come
    up with this data structure:

        unordered_map<int, deque<int>> dst_to_timestamp;



    Also in C++, you can't do: lower_bound and upper_bound on a deque, however
    you can do this:

    // WRONG
        auto iter_begin = deque.lower_bound(startTime);
        auto iter_end   = deque.upper_bound(endTime);

    // CORRECT
        auto iter_begin = lower_bound(deque.begin(), deque.end(), startTime);
        auto iter_end   = upper_bound(deque.begin(), deque.end(), endTime);


    Also:
        int left_idx  = iter_end   - deque.begin();
        int right_idx = iter_begin - deque.begin();

        return right_idx - left_idx; // ---------
                                                |
    ____________________________________________|
    |
    |
    ----> Is this SAME as:

        return std::distance(iter_begin, iter_end)
*/

/* Time  Complexity: O(logN) */
/* Space Complexity: O(N)    */
class Router {
private:
    int mem_limit = 0;

    deque<vector<int>> deque_list;
    unordered_set<string> uset;

    unordered_map<int, deque<int>> dst_to_timestamp;

public:
    Router(int memoryLimit)
    {
        mem_limit = memoryLimit;
    }

    bool addPacket(int source, int destination, int timestamp)
    {
        string str = to_string(source) + "_" + to_string(destination) + "_" + to_string(timestamp);

        if (uset.find(str) != uset.end()) // If it DOES exist
            return false;

        if (deque_list.size() == mem_limit)
        {
            vector<int> first = deque_list.front();
            deque_list.pop_front();

            int src = first[0];
            int dst = first[1];
            int tim = first[2];

            string str_first = to_string(first[0]) + "_" + to_string(first[1]) + "_" + to_string(first[2]);
            uset.erase(str_first);

            dst_to_timestamp[dst].pop_front();

            if (dst_to_timestamp[dst].empty())
                dst_to_timestamp.erase(dst);
        }

        deque_list.push_back( {source, destination, timestamp} );
        uset.insert(str);
        dst_to_timestamp[destination].push_back(timestamp);

        return true;
    }

    vector<int> forwardPacket()
    {
        if (deque_list.empty())
            return {};

        vector<int> first = deque_list.front();
        deque_list.pop_front();

        int src = first[0];
        int dst = first[1];
        int tim = first[2];

        string str_first = to_string(first[0]) + "_" + to_string(first[1]) + "_" + to_string(first[2]);
        uset.erase(str_first);

        dst_to_timestamp[dst].pop_front();

        if (dst_to_timestamp[tim].empty())
            dst_to_timestamp.erase(tim);

        return first;
    }

    int getCount(int destination, int startTime, int endTime)
    {
        auto L = lower_bound(dst_to_timestamp[destination].begin(), dst_to_timestamp[destination].end(), startTime);
        auto R = upper_bound(dst_to_timestamp[destination].begin(), dst_to_timestamp[destination].end(), endTime);

        return std::distance(L, R);
    }
};
