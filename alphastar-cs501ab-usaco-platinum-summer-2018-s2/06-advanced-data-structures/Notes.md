# String Hashing

**Purpose**: Given two strings, "abab" and "abac", check equality in O(1) time.

Checking character by character gives O(n), which is too slow. With string hashing,
we can assign an integer value to each string in O(1) time and check equality in O(1).

------

**Motivating Problem**: Given a string of length `N`, find all palindromic substrings of
length `M`.

**Polynomial Hashing**: Given a string defined by S, S(1), S(2), ... S(N), where S(i) is
the ith character of the string. The polynomial hash of the string is given by
`S(1) * b^(n-1) + S(2) * b(n-2) + ... + S(n) % p`. Without the mod, the number may quickly
grow too big. Hence, we take the mod of `p` in order to keep the size reasonable.
However, taking an arbitrary mod `p` may lead to collision errors, so we set `p` to a
large _prime_ number. The reason `p` is prime is to ensure that `b` and `p` do not share
any common factors; otherwise, there will be a greater chance of collision. Note that this
hash takes O(n) time.

**Solution**: We define the following:

Given a string S, compute `h(1), h(2), ... h(n)`.
Given a string R, where `R = reverse(S)`, compute `hr(1), hr(2), ... hr(n)`.

Say we have a string `S(1) S(2) S(3) S(4) S(5)`. If we want to find if `S(2) S(3) S(4)` is
a substring, we check if the hash of `S(2) S(3) S(4)` is equal to the hash of
`S(4) S(3) S(2) = R(2) R(3) R(4)`. We can compute these hashes in O(1): 
`hash(S(2) S(3) S(4)) = h(4) - h(1) * b^3, hash(R(2) R(3) R(4)) = hr(1) - hr(4) * b^3`
We compute the hash of `S(L) ... S(R) = h(R) - h(L - 1) * b^(R - L + 1)`.

Note that `h(x) = h(x - 1) * b + S(x)`. Make sure that `p * b < long long`.

In order to prevent collisions, we test each substring with two values of `p`. The chances
of two collisions with two different mods are very low.

The runtime is O(n).

---

**Pseudocode**:

```c++
base = 23
mod = 10^9 + 7 (or 10^9 + 9). Note that many problem sets will purposely try to
                              break these mods, so it may be beneficial to choose another
                              mod around 10^9: 2e+9+11
string s
H: H(0) = 0
pwr(0) = 1
for i = 1 to N:
    H(i) = (H(i - 1) * base + S(i)) % mod
    pwr(i) = pwr(i - 1) * base % mod

To find hash (L, R): return h(R) - h(L - 1) * base^(R - L + 1) (will have to precompute power to avoid overflow)
```


---

# Suffix Arrays

**Definition**: A suffix array is a sorted array of all the suffixes of a string.

**Example**: `"banana": ["a", "ana", "anana", "banana", "na", "nana"]`

### Generating Suffix Arrays

**Fast way**: Sort substrings of length 1, then 2, then 4, 8, 16, etc.

Assign numbers to every substring:
```
1 0 2 0 2 0
b a n a n a
```

Sort using **radix sort** for O(n log n) time. Using the default sort runs in 
O(n log^2 n) time.

Now to sort length 2:
```$xslt
 b  a    n  a    n  a
[1, 0]  [2, 0]  [2, 0]
```

Assign numbers to each of these again:
```$xslt
 b  a    n  a    n  a
[1, 0]  [2, 0]  [2, 0]
   0      1        1
```
Note: Some pairs are left out.

Next, repeat with length 4, 8, and so on. Sample implementation in C++:

**Implementation 1**
```$xslt
string 
```

**Implementation 2**

![Suffix Array implementation](suffixarray.png)

**Radix sort:** Given an array `0022121`, count the number of `0`s, `1`s and `2`s.
```$xslt
0: 2
1: 2
2: 3
```
Hence, put two zeroes, two ones, and three twos in that order:
```$xslt
0011222
```

**Using Hash Tables (O(n log^2 n), slow)**:

If hash tables have been created for the string, then it is possible to use binary search
in order to compare substrings, so we can generate a suffix array in O(n log^2 n) time, but
this is rather slow since modding and multiplication is slow.