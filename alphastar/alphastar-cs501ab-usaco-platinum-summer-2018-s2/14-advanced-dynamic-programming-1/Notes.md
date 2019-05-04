**Problem:** Given an array of size **N**, find the minimum of every contiguous subarray of 
length **K** in **O(n)** time.

**Solution:** Maintain a **monotonic queue** (using dequeue) of size k.

**Monotonic Queue:** A queue that is increasing. Hence, if we are adding a number **a**, we 
will pop any number that comes before **a** that is less than or equal to **a**.

**Monotonic Queue (max) Implementation:**

```
struct MaxQueue {
    //         value, index
    deque<pair<int,   int  >> dq;
    int L = 0, R = -1;
    
    void insert(int x) {
        while (dq.size() > 0 && dq.back.value <= x) {
            dq.pop_back();
        }
        dq.push_back(mp(x ++R));
    }
    
    int size() { return R - L + 1; }
    
    del() {
        if (dq.front.index == L++) dq.popfront();
    }
    
    query() { return dq.front.value }
}

// Actual
struct MaxQueue {
    //         value, index
    deque<pair<int,   int  >> dq;
    int L = 0, R = -1;

    void insert(int x) {
        while (!dq.empty() && dq.back().A <= x) {
            dq.pop_back();
        }
        dq.emplace_back(x, ++R);
    }

    int size() { return R - L + 1; }

    void del() {
        if (dq.front().B == L++) dq.pop_front();
    }

    int query() { return dq.front().A; }
};
```