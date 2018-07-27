# USACO Solutions

Solutions to USACO training and USACO contest problems.

#### USACO Training:
| Problem Number | Problem Name | Solution Notes |
| -------------- | ------------ | -------------- |
| 1.6.3 | [Superprime Rib][1.6.3] | Brute force |
| 2.1.1 | [The Castle][2.1.1] | Floodfill to assign each room a number |
| 2.1.2 | [Ordered Fractions][2.1.2] | Generate all possible fractions |
| 2.1.3 | [Sorting A Three-Valued Sequence][2.1.3] | Notes written as comments in code |
| 2.1.4 | [Healthy Holsteins][2.1.4] | Brute force |
| 2.1.5 | [Hamming Codes][2.1.5] | Brute force |
| 2.2.1 | [Preface Numbering][2.2.1] | Brute force |
| 2.2.2 | [Subset Sums][2.2.2] | DP |
| 2.2.3 | [Runaround Numbers][2.2.3] | Brute force |
| 2.2.4 | [Party Lamps][2.2.4] | Brute force 2^4, doesn't matter if you press button twice |
| 2.3.1 | [Longest Prefix][2.3.1] | DP |
| 2.3.2 | [Cow Pedigrees][2.3.2] | DP |
| 2.3.3 | [Zero Sum][2.3.3] | Brute force (DFS) |

#### USACO Contests:
| Contest Date | Problem ID | Problem Name | Solution Notes | Division | Score |
| ------------ | ---------- | ------------ | -------------- | -------- | ----- |
| Nov 2012 | [clumsy][clumsy] | Clumsy Cows | Greedy | Silver | 16/16 |
| Nov 2012 | [distant][distant] | Distant Pastures | APSP, dijkstra | Silver | 16/16 |
| Nov 2012 | [bbreeds][bbreeds] | Balanced Cow Breeds | Same problem as Gold | Silver | 16/16 |
| Nov 2012 | [bbreeds][bbreeds] | Balanced Cow Breeds | DP | Gold | 16/16 |
| Dec 2012 | [wifi][wifi] | Wifi Setup | DP | Silver | 10/10 |
| Dec 2012 | [mroute][mroute] | Milk Routing | Dijkstra | Silver | 10/10 |
| Dec 2012 | [gangs][gangs] | Gangs of Istanbull/Cowstantinople | Greedy | Gold | 12/12 |
| Dec 2012 | [first][first] | First! | trie, checking DAG for cycles | Gold | 12/12 |
| Dec 2012 | [runaway][runaway] | Running Away From the Barn |  | Gold | 10/10 | 
| Jan 2013 | [paint][paint] | Painting the Fence | Coordinate Compression, Store Deltas & Sweep | Silver | 10/10 |
| Jan 2013 | [squares][squares] | Square Overlap | Sweep | Silver | 10/10 |
| Jan 2013 | [invite][invite] | Party Invitations | precompute which groups each cow is in | Silver | 10/10 |
| Jan 2013 | [lineup][lineup] | Cow Lineup | sweep with two pointers | Gold | 10/10 |
| Jan 2013 | [island][island] | Island Travels | bfs | Gold | 11/11 |
| Jan 2013 | [seating][seating] | Seating | Binary Tree, Lazy Propagation | Gold | 10/10 |
| Feb 2013 | [perimeter][perimeter] | Perimeter | Optimized Floodfill | Silver | 10/10 |
| Feb 2013 | [tractor][tractor] | Tractor | Binary search for answer, dfs | Silver | 10/10 |
| Feb 2013 | [msched][msched] | Milk Scheduling | Greedy | Silver | 10/10 |
| Feb 2013 | [partition][partition] | Partitioning The Farm | DP | Gold | 17/17 |
| Feb 2013 | [taxi][taxi] | Taxi | Min Cost Matching, calculate distance driven w/o cow | Gold | 12/12 |
| Feb 2013 | [route][route] | Route Designing | DP | Gold | 10/10 |
| Mar 2013 | [poker][poker] | Poker Hands | Greedy | Silver | 10/10 |
| Mar 2013 | [painting][painting] | Farm Painting | Sweep | Silver | 10/10 |
| Mar 2013 | [cowrun][cowrun] | The Cow Run | DP | Gold | 14/14 |
| Mar 2013 | [hillwalk][hillwalk] | Hill Walk | Line sweep, find a way to order hills | Gold | 12/12 |
| Nov 2013 | [nochange][nochange] | No Change | DP, 2^k state | Gold | 13/13 |
| Nov 2013 | [sight][sight] | Line of Sight | If two cows can see the same point on the silo, they can see each other | Gold | 11/11 |
| Nov 2013 | [empty][empty] | Empty Stalls | Sweep | Gold | 11/11 |
| Dec 2013 | [vacationgold][vacationgold] | Vacation Planning (Gold) | Dijkstra | Gold | 10/10 |
| Dec 2013 | [optmilk][optmilk] | Optimal Milking | Binary Tree | Gold | 11/11 |
| Jan 2014 | [skicourse][skicourse] | Building A Ski Course | DP | Gold | 10/10 |
| Jan 2014 | [skilevel][skilevel] | Ski Course Rating | Kruskal | Gold | 10/10 |
| Feb 2014 | [rblock][rblock] | Roadblock | Dijkstra | Gold | 10/10 |
| Feb 2014 | [dec][dec] | Cow Decathlon | DP | Gold | 10/10 |
| Mar 2014 | [sabotage][sabotage] | Sabotage | Binary search, 1D max sum | Gold | 14/14 |
| Mar 2014 | [fcount][fcount] | Counting Friends | Brute Force, greedily connect friends | Gold | 11/11 |
| Dec 2014 | [guard][guard] | Guard Mark | DP | Gold | 12/12 |
| Dec 2014 | [marathon][marathon] | Marathon | Segment Tree | Gold | 10/10 |
| Dec 2014 | [cowjog][cowjog] | Cow Jog | Longest Non-Increasing Subsequence | Gold | 14/14 |
| Jan 2015 | [cowrect][cowrect] | Cow Rectangles | Sweep, assume we have to take one of the Holsteins | Gold | 14/14 |
| Jan 2015 | [movie][movie] | Moovie Mooving | DP, bitmasking | Gold | 14/14 |
| Open 2015 | [palpath][palpath] | Palindromic Paths | DP | Gold | 12/12 |
| Open 2015 | [trapped][trapped] | Trapped in the Haybales | Sort haybales by weight | Gold | 15/15 |

[1.6.3]: usaco-training/Chapter%201/1.6.3%20sprime%20-%20Superprime%20Rib.cpp
[2.1.1]: usaco-training/Chapter%202/2.1.1%20-%20The%20Castle.cpp
[2.1.2]: usaco-training/Chapter%202/2.1.2%20-%20Ordered%20Fractions.cpp
[2.1.3]: usaco-training/Chapter%202/2.1.3%20-%20Sorting%20A%20Three-Valued%20Sequence.cpp
[2.1.4]: usaco-training/Chapter%202/2.1.4%20-%20Healthy%20Holsteins.cpp
[2.1.5]: usaco-training/Chapter%202/2.1.5%20-%20Hamming%20Codes.cpp
[2.2.1]: usaco-training/Chapter%202/2.2.1%20-%20Preface%20Numbering.cpp
[2.2.2]: usaco-training/Chapter%202/2.2.2%20-%20Subset%20Sums.cpp
[2.2.3]: usaco-training/Chapter%202/2.2.3%20-%20Runaround%20Numbers.cpp
[2.2.4]: usaco-training/Chapter%202/2.2.4%20-%20Party%20Lamps.cpp
[2.3.1]: usaco-training/Chapter%202/2.3.1%20-%20Longest%20Prefix.cpp
[2.3.2]: usaco-training/Chapter%202/2.3.2%20-%20Cow%20Pedigrees.cpp
[2.3.3]: usaco-training/Chapter%202/2.3.3%20-%20Zero%20Sum.cpp

[clumsy]: usaco-contests/2012nov/silver/clumsy.cpp
[distant]: usaco-contests/2012nov/silver/distant.cpp
[bbreeds]: usaco-contests/2012nov/gold/bbreeds.cpp
[wifi]: usaco-contests/2012dec/silver/wifi.cpp
[mroute]: usaco-contests/2012dec/silver/mroute.cpp
[gangs]: usaco-contests/2012dec/gold/gangs.cpp
[first]: usaco-contests/2012dec/gold/first.cpp
[runaway]: usaco-contests/2012dec/gold/runaway.cpp
[paint]: usaco-contests/2013jan/silver/paint.cpp
[invite]: usaco-contests/2013jan/silver/invite.cpp
[squares]: usaco-contests/2013jan/silver/squares.cpp
[lineup]: usaco-contests/2013jan/gold/lineup.cpp
[island]: usaco-contests/2013jan/gold/island.cpp
[seating]: usaco-contests/2013jan/gold/seating.cpp
[perimeter]: usaco-contests/2013feb/silver/perimeter.cpp
[tractor]: usaco-contests/2013feb/silver/tractor.cpp
[msched]: usaco-contests/2013feb/silver/msched.cpp
[partition]: usaco-contests/2013feb/gold/partition.cpp
[taxi]: usaco-contests/2013feb/gold/taxi.cpp
[route]: usaco-contests/2013feb/gold/route.cpp
[poker]: usaco-contests/2013mar/silver/poker.cpp
[painting]: usaco-contests/2013mar/silver/painting.cpp
[cowrun]: usaco-contests/2013mar/gold/cowrun.cpp
[hillwalk]: usaco-contests/2013mar/gold/hillwalk.cpp
[nochange]: usaco-contests/2013nov/gold/nochange.cpp
[sight]: usaco-contests/2013nov/gold/sight.cpp
[empty]: usaco-contests/2013nov/gold/empty.cpp
[vacationgold]: usaco-contests/2013dec/gold/vacationgold.cpp
[optmilk]: usaco-contests/2013dec/gold/optmilk.cpp
[skicourse]: usaco-contests/2014jan/gold/skicourse.cpp
[skilevel]: usaco-contests/2014jan/gold/skilevel.cpp
[rblock]: usaco-contests/2014feb/gold/rblock.cpp
[dec]: usaco-contests/2014feb/gold/dec.cpp
[sabotage]: usaco-contests/2014mar/gold/sabotage.cpp
[fcount]: usaco-contests/2014mar/gold/fcount.cpp
[guard]: usaco-contests/2014dec/gold/guard.cpp
[marathon]: usaco-contests/2014dec/gold/marathon.cpp
[cowjog]: usaco-contests/2014dec/gold/cowjog.cpp
[cowrect]: usaco-contests/2015jan/gold/cowrect.cpp
[movie]: usaco-contests/2015jan/gold/movie.cpp
[palpath]: usaco-contests/2015open/gold/palpath.cpp
[trapped]: usaco-contests/2015open/gold/trapped.cpp

Note: Code primarily written in C++.