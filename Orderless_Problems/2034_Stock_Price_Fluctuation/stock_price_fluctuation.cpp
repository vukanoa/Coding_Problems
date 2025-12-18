/*
    ==============
    === MEDIUM ===
    ==============

    =============================
    2034) Stock Price Fluctiation
    =============================

    ============
    Description:
    ============

    You are given a stream of records about a particular stock. Each record
    contains a timestamp and the corresponding price of the stock at that
    timestamp.

    Unfortunately due to the volatile nature of the stock market, the records
    do not come in order. Even worse, some records may be incorrect. Another
    record with the same timestamp may appear later in the stream correcting
    the price of the previous wrong record.

    Design an algorithm that:

        + Updates the price of the stock at a particular timestamp, correcting
          the price from any previous records at the timestamp.

        + Finds the latest price of the stock based on the current records. The
          latest price is the price at the latest timestamp recorded.

        + Finds the maximum price the stock has been based on the current
          records.

        + Finds the minimum price the stock has been based on the current
          records.

    Implement the StockPrice class:

        StockPrice() Initializes the object with no price records.

        + void update(int timestamp, int price) Updates the price of the stock
          at the given timestamp.

        + int current() Returns the latest price of the stock.

        + int maximum() Returns the maximum price of the stock.

        + int minimum() Returns the minimum price of the stock.

    ===============================
    CLASS:
    class StockPrice {
    public:
        StockPrice() {
            
        }
        
        void update(int timestamp, int price) {
            
        }
        
        int current() {
            
        }
        
        int maximum() {
            
        }
        
        int minimum() {
            
        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input
    ["StockPrice", "update", "update", "current", "maximum", "update", "maximum", "update", "minimum"]
    [[], [1, 10], [2, 5], [], [], [1, 3], [], [4, 2], []]
    Output
    [null, null, null, 5, 10, null, 5, null, 2]

    Explanation
    StockPrice stockPrice = new StockPrice();
    stockPrice.update(1, 10); // Timestamps are [1] with corresponding prices [10].
    stockPrice.update(2, 5);  // Timestamps are [1,2] with corresponding prices [10,5].
    stockPrice.current();     // return 5, the latest timestamp is 2 with the price being 5.
    stockPrice.maximum();     // return 10, the maximum price is 10 at timestamp 1.
    stockPrice.update(1, 3);  // The previous timestamp 1 had the wrong price, so it is updated to 3.
                              // Timestamps are [1,2] with corresponding prices [3,5].
    stockPrice.maximum();     // return 5, the maximum price is 5 after the correction.
    stockPrice.update(4, 2);  // Timestamps are [1,2,4] with corresponding prices [3,5,2].
    stockPrice.minimum();     // return 2, the minimum price is 2 at timestamp 4.


    *** Constraints ***
    1 <= timestamp, price <= 10^9
    At most 10^5 calls will be made in total to update, current, maximum, and
    minimum. current, maximum, and minimum will be called only after update has
    been called at least once.

*/

#include <queue>
#include <unordered_map>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 85.12% */
/* Space Beats: 66.37% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class StockPrice {
    priority_queue<int> max_price_heap;
    priority_queue<int, vector<int>, greater<int>> min_price_heap;

    unordered_map<int,int> price_frequency;    // Frequency of each price
    unordered_map<int,int> timestamp_to_price; // Price at each timestamp
    
    int latest_timestamp;
    int current_price;

public:
    StockPrice()
    {
        latest_timestamp = 0;
        current_price    = 0;
    }
    
    void update(int timestamp, int price)
    {
        if (timestamp_to_price.find(timestamp) != timestamp_to_price.end()) // Existing timestamp
        {
            price_frequency[timestamp_to_price[timestamp]]--;
            
            while ( ! max_price_heap.empty() && price_frequency[max_price_heap.top()] == 0)
                max_price_heap.pop();

            while ( ! min_price_heap.empty() && price_frequency[min_price_heap.top()] == 0)
                min_price_heap.pop();
        }
        
        timestamp_to_price[timestamp] = price; // Update timestamp with new price
        
        if (price_frequency[price]++ == 0) // First time seeing this price
        {
            max_price_heap.push(price);
            min_price_heap.push(price);    
        }
        
        if (timestamp >= latest_timestamp) // Maintain latest price
        {
            latest_timestamp = timestamp;
            current_price    = price;
        }
    }
    
    int current()
    {
        return current_price;
    }
    
    int maximum()
    {
        return max_price_heap.top();
    }
    
    int minimum()
    {
        return min_price_heap.top();
    }
};
