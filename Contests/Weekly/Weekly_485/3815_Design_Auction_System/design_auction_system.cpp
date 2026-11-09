/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    3815) Design Auction System
    ===========================

    ============
    Description:
    ============


    You are asked to design an auction system that manages bids from multiple
    users in real time.

    Each bid is associated with a userId, an itemId, and a bidAmount.

    Implement the AuctionSystem class:

        + AuctionSystem(): Initializes the AuctionSystem object.

        + void addBid(int userId, int itemId, int bidAmount): Adds a new bid
          for itemId by userId with bidAmount. If the same userId already has a
          bid on itemId, replace it with the new bidAmount.

        + void updateBid(int userId, int itemId, int newAmount): Updates the
          existing bid of userId for itemId to newAmount. It is guaranteed that
          this bid exists.

        + void removeBid(int userId, int itemId): Removes the bid of userId for
          itemId. It is guaranteed that this bid exists.

        + int getHighestBidder(int itemId): Returns the userId of the highest
          bidder for itemId. If multiple users have the same highest bidAmount,
          return the user with the highest userId. If no bids exist for the
          item, return -1.

    ===============================
    CLASS:
    class AuctionSystem {
    public:
        AuctionSystem() {
            
        }
        
        void addBid(int userId, int itemId, int bidAmount) {
            
        }
        
        void updateBid(int userId, int itemId, int newAmount) {
            
        }
        
        void removeBid(int userId, int itemId) {
            
        }
        
        int getHighestBidder(int itemId) {
            
        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:
    ["AuctionSystem", "addBid", "addBid", "getHighestBidder", "updateBid",
    "getHighestBidder", "removeBid", "getHighestBidder", "getHighestBidder"]
    [[], [1, 7, 5], [2, 7, 6], [7], [1, 7, 8], [7], [2, 7], [7], [3]]

    Output:
    [null, null, null, 2, null, 1, null, 1, -1]

    Explanation
    AuctionSystem auctionSystem = new AuctionSystem(); // Initialize the Auction system
    auctionSystem.addBid(1, 7, 5); // User 1 bids 5 on item 7
    auctionSystem.addBid(2, 7, 6); // User 2 bids 6 on item 7
    auctionSystem.getHighestBidder(7); // return 2 as User 2 has the highest bid
    auctionSystem.updateBid(1, 7, 8); // User 1 updates bid to 8 on item 7
    auctionSystem.getHighestBidder(7); // return 1 as User 1 now has the highest bid
    auctionSystem.removeBid(2, 7); // Remove User 2's bid on item 7
    auctionSystem.getHighestBidder(7); // return 1 as User 1 is the current highest bidder
    auctionSystem.getHighestBidder(3); // return -1 as no bids exist for item 3


    *** Constraints ***
    1 <= userId, itemId <= 5 * 10^4
    1 <= bidAmount, newAmount <= 10^9
    At most 5 * 10^4 total calls to addBid, updateBid, removeBid, and
    getHighestBidder.
    The input is generated such that for updateBid and removeBid, the bid from
    the given userId for the given itemId will be valid.

*/

#include <queue>
#include <unordered_map>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Lazy Deletion. A concept you MUST know for CP/Interviews. Good thing is
    that it's not very difficult.

*/

/* Time  Beats: 47.39% */
/* Space Beats: 12.45% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N * k)    */ // Where 'k' is the numbe of items
class AuctionSystem {
private:
    unordered_map<int, unordered_map<int, int>> user_to_items_map;
    unordered_map<int, priority_queue<pair<int, int>>> item_to_heap;

public:
    AuctionSystem()
    {
    }

    // TC: O(N * logN)
    void addBid(int userId, int itemId, int bidAmount)
    {
        user_to_items_map[userId][itemId] = bidAmount;
        item_to_heap[itemId].push( {bidAmount, userId} );
    }

    // TC: O(N * logN)
    void updateBid(int userId, int itemId, int newAmount)
    {
        user_to_items_map[userId][itemId] = newAmount;
        item_to_heap[itemId].push( {newAmount, userId} );
    }

    // TC: O(1)
    void removeBid(int userId, int itemId)
    {
        user_to_items_map[userId].erase(itemId);
    }

    // TC: O(N * logN)
    int getHighestBidder(int itemId)
    {
        auto& heap = item_to_heap[itemId];

        while ( ! heap.empty())
        {
            const auto [bidAmount, userId] = heap.top();

            auto it = user_to_items_map.find(userId); // it = {user : umap_items}

            // it->second  <==> umap_items
            if (it == user_to_items_map.end() || it->second.count(itemId) == 0 || it->second[itemId] != bidAmount)
            {
                heap.pop();
                continue;
            }

            return userId;
        }

        return -1;
    }
};
