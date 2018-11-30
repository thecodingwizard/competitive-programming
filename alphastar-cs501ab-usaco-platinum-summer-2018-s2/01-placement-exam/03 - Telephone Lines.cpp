/*
Telephone Lines
===============

Farmer John wants to set up a telephone line at his farm. Unfortunately,
the phone company is uncooperative, so he needs to pay for some of
the cables required to connect his farm to the phone system.

There are N (1 <= N <= 1,000) forlorn telephone poles conveniently
numbered 1..N that are scattered around Farmer John's property; no
cables connect any them.  A total of P (1 <= P <= 10,000) pairs of
poles can be connected by a cable; the rest are too far apart.

The i-th cable can connect the two distinct poles A_i and B_i, with
length L_i (1 <= L_i <= 1,000,000) units if used. The input data
set never names any {A_i,B_i} pair more than once. Pole 1 is already
connected to the phone system, and pole N is at the farm. Poles 1
and N need to be connected by a path of cables; the rest of the
poles might be used or might not be used.

As it turns out, the phone company is willing to provide Farmer
John with K (0 <= K < N) lengths of cable for free. Beyond that he
will have to pay a price equal to the length of the longest remaining
cable he requires (each pair of poles is connected with a separate
cable), or 0 if he does not need any additional cables.

Determine the minimum amount that Farmer John must pay.

PROBLEM NAME: phoneline

INPUT FORMAT:

* Line 1: Three space-separated integers: N, P, and K

* Lines 2..P+1: Line i+1 contains the three space-separated integers:
        A_i, B_i, and L_i

SAMPLE INPUT:

5 7 1
1 2 5
3 1 4
2 4 8
3 2 3
5 2 9
3 4 7
4 5 6

INPUT DETAILS:

There are 5 poles. Pole 1 cannot be connected directly to poles 4 or 5.
Pole 5 cannot be connected directly to poles 1 or 3. All other pairs can be
connected. The phone company will provide one free cable.

OUTPUT FORMAT:

* Line 1: A single integer, the minimum amount Farmer John can pay. If
        it is impossible to connect the farm to the phone company,
        print -1.

SAMPLE OUTPUT:

4

OUTPUT DETAILS:

If pole 1 is connected to pole 3, pole 3 to pole 2, and pole 2 to pole 5
then Farmer John requires cables of length 4, 3, and 9. The phone company
will provide the cable of length 9, so the longest cable needed has length 4.
*/