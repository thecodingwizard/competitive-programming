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
| 2.3.4 | [Money Systems][2.3.4] | DP (VN) |
| 2.3.5 | [Controlling Companies][2.3.5] | Recursion |
| 2.4.1 | [The Tamworth Two][2.4.1] | Brute force, maximum (100*4)^2 steps before "impossible" |
| 2.4.2 | [Overfencing][2.4.2] | run shortest path BFS on two exit nodes |
| 2.4.3 | [Cow Tours][2.4.3] | Dijkstra |
| 2.4.4 | [Bessie Come Home][2.4.4] | Dijkstra |
| 2.4.5 | [Fractions to Decimals][2.4.5] | Recursion |
| 3.1.1 | [Agri-Net][3.1.1] | Prim's (or Kruskal) |
| 3.1.2 | [Score Inflation][3.1.2] | Knapsack |
| 3.1.3 | [Humble Numbers][3.1.3] | Create size N set of possible numbers, brute force |
| 3.1.4 | [Contact][3.1.4] | Brute force |
| 3.1.5 | [Stamps][3.1.5] | DP |
| 3.2.1 | [Factorials][3.2.1] | Count number of twos and fives |
| 3.2.2 | [Stringsobits][3.2.2] | Define `dp(i, j) = # of numbers with i bits and at most j ones` |

### Gold USACO Contests:

#### Old USACO Gold (Silver):
| Contest Date | Problem ID | Problem Name | Solution Notes | Score |
| ------------ | ---------- | ------------ | -------------- | ----- |
| Nov 2012 | [clumsy][clumsy] | Clumsy Cows | Greedy | 16/16 |
| Nov 2012 | [distant][distant] | Distant Pastures | APSP, dijkstra | 16/16 |
| Nov 2012 | [bbreeds][bbreeds] | Balanced Cow Breeds | Same problem as Gold | 16/16 |
| Dec 2012 | [wifi][wifi] | Wifi Setup | DP | 10/10 |
| Dec 2012 | [mroute][mroute] | Milk Routing | Dijkstra | 10/10 |
| Jan 2013 | [paint][paint] | Painting the Fence | Coordinate Compression, Store Deltas & Sweep | 10/10 |
| Jan 2013 | [squares][squares] | Square Overlap | Sweep | 10/10 |
| Jan 2013 | [invite][invite] | Party Invitations | precompute which groups each cow is in | 10/10 |
| Feb 2013 | [perimeter][perimeter] | Perimeter | Optimized Floodfill | 10/10 |
| Feb 2013 | [tractor][tractor] | Tractor | Binary search for answer, dfs | 10/10 |
| Feb 2013 | [msched][msched] | Milk Scheduling | Greedy | 10/10 |
| Mar 2013 | [poker][poker] | Poker Hands | Greedy | 10/10 |
| Mar 2013 | [painting][painting] | Farm Painting | Sweep | 10/10 |
| Mar 2013 | [cowrun][cowrun] | The Cow Run | DP, same as gold | 15/15 |
| Open 2013 | [gravity][gravity] | What's Up With Gravity? | Dijkstra | 10/10 |
| Open 2013 | [fuel][fuel] | Fuel Economy | Greedy | 10/10 |
| Open 2013 | [cruise][cruise] | Luxury River Cruise | Find where sequence repeats | 10/10 |
| Nov 2013 | [nocow][nocow] | Farmer John has no Large Brown Cow | Solvable with a bit of math | 10/10 |
| Nov 2013 | [crowded][crowded] | Crowded Cows | Sweep, can use multiset instead of monotonic queue | 11/11 |
| Nov 2013 | [pogocow][pogocow] | Pogo-Cow | DP, note that Bessie can go either direction | 11/11 |
| Dec 2013 | [msched][msched2] | Milk Scheduling | Greedy, sweep | 11/11 |
| Dec 2013 | [vacation][vacation] | Vacation Planning | Code is slightly modified from gold version, answer is unnecessarily complicated for silver | 10/10 |
| Jan 2014 | [slowdown][slowdown] | Bessie Slows Down | Maintain two arrays, simulation | 10/10 |
| Jan 2014 | [ccski][ccski] | Cross Country Skiing | Prim's | 10/10 |
| Jan 2014 | [recording][recording] | Recording the Moolympics | Greedy | 10/10 |
| Feb 2014 | [auto][auto] | Auto-complete | Binary search | 10/10 |
| Feb 2014 | [rblock][rblock] | Roadblock | Dijkstra | 10/10 |
| Feb 2014 | [scode][scode] | Secret Code | DP | 10/10 |
| Mar 2014 | [irrigation][irrigation] | Watering the Fields | Kruskal/MST | 10/10 |
| Mar 2014 | [lazy][lazy] | The Lazy Cow | Rotate grid 45 degrees | 10/10 |
| Mar 2014 | [mooomoo][mooomoo] | Mooo Moo | DP | 10/10 |
| Open 2014 | [fairphoto][fairphoto] | Fair Photography | Sweep | 10/10 |
| Open 2014 | [gpsduel][gpsduel] | Dueling GPSs | Dijkstra | 10/10 |
| Dec 2014 | [piggyback][piggyback] | Piggy Back | Shortest Path on three nodes | 11/11 |
| Dec 2014 | [cowjog][cowjog] | Cow Jog | Sweep | 15/15 |
| Jan 2015 | [stampede][stampede] | Stampede | Sweep | 15/15 |
| Jan 2015 | [cowroute][cowroute] | Cow Routing | Dijkstra | 12/12 |
| Jan 2015 | [meeting][meeting] | Meeting Time | DP | 15/15 |
| Feb 2015 | [censor][censor] | Censoring | Rolling Hash | 15/15 |
| Feb 2015 | [hopscotch][hopscotch] | Cow Hopscotch | DP | 15/15 |
| Feb 2015 | [superbull][superbull] | Superbull | MST, Prim's O(V^2) | 10/10 |
| Open 2015 | [bgm][bgm] | Bessie Goes Moo | Parity | 10/10 |
| Open 2015 | [trapped][trapped] | Trapped in the Haybales (Silver) | Sort, Sweep | 14/14 |

#### USACO Gold (2015-now)
| Contest Date | Problem ID | Problem Name | Solution Notes | Score |
| ------------ | ---------- | ------------ | -------------- | ----- |
| Dec 2015 | [cardgame][cardgame] | High Card Low Card (Gold) | Greedy | 15/15 |
| Dec 2015 | [feast][feast] | Fruit Feast | DP (Knapsack) | 12/12 |
| Dec 2015 | [dream][dream] | Bessie's Dream | Dijkstra | 16/16 |
| Jan 2016 | [radio][radio] | Radio Contact | DP | 10/10 |
| Feb 2016 | [cbarn][cbarn] | Circular Barn | Greedy | 10/10 |
| Feb 2016 | [cbarn2][cbarn2] | Circular Barn (Revisited) | DP | 10/10 |
| Feb 2016 | [fencedin][fencedin] | Fenced In | MST (Kruskal) | 10/10 |
| Open 2016 | [split][split] | Splitting The Field | Sweep | 10/10 |
| Open 2016 | [closing][closing] | Closing The Farm | UFDS (Note: Runs really close to time limit) | 10/10 |
| Dec 2016 | [moocast][moocast] | Moocast | UFDS, brute force | 10/10 |
| Dec 2016 | [checklist][checklist] | Cow Checklist | DP | 10/10 |
| Dec 2016 | [lasers][lasers] | Lasers and Mirrors | BFS | 11/11 |
| Jan 2017 | [bphoto][bphoto] | Balanced Photo | Fenwick Tree | 10/10 |
| Jan 2017 | [hps][hps] | Hoof, Paper, Scissors | 3D DP | 10/10 |
| Jan 2017 | [cownav][cownav] | Cow Navigation | BFS | 10/10 |
| Feb 2017 | [visitfj][visitfj] | Why Did The Cow Cross The Road | Dijkstra | 11/11 |
| Feb 2017 | [nocross][nocross] | Why Did The Cow Cross The Road II | DP | 10/10 |
| Feb 2017 | [circlecross][circlecross] | Why Did The Cow Cross The Road III | Fenwick Tree (BIT) | 10/10 |
| Open 2017 | [cownomics][cownomics] | Bovine Genomics | Rolling Hash | 10/10 |
| Open 2017 | [art2][art2] | Modern Art 2 | Calculate start/end points | 10/10 |
| Dec 2017 | [piepie][piepie] | A Pie For A Pie | BFS, binary search | 10/10 |
| Dec 2017 | [barnpainting][barnpainting] | Barn Painting | DP | 10/10 |
| Dec 2017 | [hayfeast][hayfeast] | Haybale Feast | Two Pointers | 10/10 |
| Jan 2018 | [mootube][mootube] | MooTube | UFDS | 10/10 |
| Jan 2018 | [atlarge][atlarge] | Cow At Large | DFS/BFS | 13/13 |
| Jan 2018 | [spainting][spainting] | Stamp Painting | DP, recurrence | 12/12 |
| Feb 2018 | [snowboots][snowboots] | Snow Boots | Sort, Doubly-Linked List | 12/12 |
| Feb 2018 | [dirtraverse][dirtraverse] | Directory Traversal | DFS | 10/10 |
| Feb 2018 | [taming][taming] | Taming The Herd | DP | 11/11 |
| Open 2018 | [sort][sort] | Out of Sorts | BIT | 10/10 |
| Open 2018 | [milkorder][milkorder] | Milking Order | Topological Sort (Lexicographically earliest) | 10/10 |
| Open 2018 | [talent][talent] | Talent Show | Binary search for answer, DP | 10/10 |

### Platinum USACO Contests:

#### Old USACO Platinum (Gold):
| Contest Date | Problem ID | Problem Name | Solution Notes | Score |
| ------------ | ---------- | ------------ | -------------- | ----- |
| Nov 2012 | [bbreeds][bbreeds] | Balanced Cow Breeds | DP | 16/16 |
| Dec 2012 | [gangs][gangs] | Gangs of Istanbull/Cowstantinople | Greedy | 12/12 |
| Dec 2012 | [first][first] | First! | trie, checking DAG for cycles | 12/12 |
| Dec 2012 | [runaway][runaway] | Running Away From the Barn |  | 10/10 | 
| Jan 2013 | [lineup][lineup] | Cow Lineup | sweep with two pointers | 10/10 |
| Jan 2013 | [island][island] | Island Travels | bfs | 11/11 |
| Jan 2013 | [seating][seating] | Seating | Binary Tree, Lazy Propagation | 10/10 |
| Feb 2013 | [partition][partition] | Partitioning The Farm | DP | 17/17 |
| Feb 2013 | [taxi][taxi] | Taxi | Min Cost Matching, calculate distance driven w/o cow | 12/12 |
| Feb 2013 | [route][route] | Route Designing | DP | 10/10 |
| Mar 2013 | [cowrun][cowrun] | The Cow Run | DP | 14/14 |
| Mar 2013 | [hillwalk][hillwalk] | Hill Walk | Line sweep, find a way to order hills | 12/12 |
| Nov 2013 | [nochange][nochange] | No Change | DP, 2^k state | 13/13 |
| Nov 2013 | [sight][sight] | Line of Sight | If two cows can see the same point on the silo, they can see each other | 11/11 |
| Nov 2013 | [empty][empty] | Empty Stalls | Sweep | 11/11 |
| Dec 2013 | [vacationgold][vacationgold] | Vacation Planning (Gold) | Dijkstra | 10/10 |
| Dec 2013 | [optmilk][optmilk] | Optimal Milking | Binary Tree | 11/11 |
| Jan 2014 | [skicourse][skicourse] | Building A Ski Course | DP | 10/10 |
| Jan 2014 | [skilevel][skilevel] | Ski Course Rating | Kruskal | 10/10 |
| Feb 2014 | [rblock][rblock] | Roadblock | Dijkstra | 10/10 |
| Feb 2014 | [dec][dec] | Cow Decathlon | DP | 10/10 |
| Mar 2014 | [sabotage][sabotage] | Sabotage | Binary search, 1D max sum | 14/14 |
| Mar 2014 | [fcount][fcount] | Counting Friends | Brute Force, greedily connect friends | 11/11 |
| Dec 2014 | [guard][guard] | Guard Mark | DP | 12/12 |
| Dec 2014 | [marathon][marathon] | Marathon | Segment Tree | 10/10 |
| Dec 2014 | [cowjog][cowjog] | Cow Jog | Longest Non-Increasing Subsequence | 14/14 |
| Jan 2015 | [cowrect][cowrect] | Cow Rectangles | Sweep, assume we have to take one of the Holsteins | 14/14 |
| Jan 2015 | [movie][movie] | Moovie Mooving | DP, bitmasking | 14/14 |
| Open 2015 | [palpath][palpath] | Palindromic Paths | DP | 12/12 |
| Open 2015 | [trapped][trapped] | Trapped in the Haybales | Sort haybales by weight | 15/15 |
| Open 2015 | [buffet][buffet] | Bessie's Birthday Buffet | DP | 15/15 |

#### USACO Platinum (2015-now):
| Contest Date | Problem ID | Problem Name | Solution Notes | Score |
| ------------ | ---------- | ------------ | -------------- | ----- |
| Dec 2015 | [maxflow][maxflow] | Max Flow | LCA, prefix sums | 15/15 |
| Dec 2015 | [cardgame][cardgame] | High Card Low Card | Greedy | 15/15 |
| Dec 2015 | [haybales][haybales] | Counting Haybales | Seg Tree, Lazy, Min Query & Sum Query | 10/10 |
| Jan 2016 | [fortmoo][fortmoo] | Fort Moo | DP/Sliding Window | 13/13 |
| Jan 2016 | [mowing][mowing] | Mowing The Field | 2D Range Tree | 10/10 |

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
[2.3.4]: usaco-training/Chapter%202/2.3.4%20-%20Money%20Systems.cpp
[2.3.5]: usaco-training/Chapter%202/2.3.5%20-%20Controlling%20Companies.cpp
[2.4.1]: usaco-training/Chapter%202/2.4.1%20-%20The%20Tamworth%20Two.cpp
[2.4.2]: usaco-training/Chapter%202/2.4.2%20-%20Overfencing.cpp
[2.4.3]: usaco-training/Chapter%202/2.4.3%20-%20Cow%20Tours.cpp
[2.4.4]: usaco-training/Chapter%202/2.4.4%20-%20Bessie%20Come%20Home.cpp
[2.4.5]: usaco-training/Chapter%202/2.4.5%20-%20Fractions%20to%20Decimals.cpp
[3.1.1]: usaco-training/Chapter%203/3.1.1%20-%20Agri-Net.cpp
[3.1.2]: usaco-training/Chapter%203/3.1.2%20-%20Score%20Inflation.cpp
[3.1.3]: usaco-training/Chapter%203/3.1.3%20-%20Humble%20Numbers.cpp
[3.1.4]: usaco-training/Chapter%203/3.1.4%20-%20Contact.cpp
[3.1.5]: usaco-training/Chapter%203/3.1.5%20-%20Stamps.cpp
[3.2.1]: usaco-training/Chapter%203/3.2.1%20-%20Factorials.cpp
[3.2.2]: usaco-training/Chapter%203/3.2.2%20-%20Stringsobits.cpp

[clumsy]: usaco-contests/2012nov/silver/clumsy.cpp
[distant]: usaco-contests/2012nov/silver/distant.cpp
[wifi]: usaco-contests/2012dec/silver/wifi.cpp
[mroute]: usaco-contests/2012dec/silver/mroute.cpp
[paint]: usaco-contests/2013jan/silver/paint.cpp
[invite]: usaco-contests/2013jan/silver/invite.cpp
[squares]: usaco-contests/2013jan/silver/squares.cpp
[perimeter]: usaco-contests/2013feb/silver/perimeter.cpp
[tractor]: usaco-contests/2013feb/silver/tractor.cpp
[msched]: usaco-contests/2013feb/silver/msched.cpp
[poker]: usaco-contests/2013mar/silver/poker.cpp
[painting]: usaco-contests/2013mar/silver/painting.cpp
[gravity]: usaco-contests/2013open/silver/gravity.cpp
[fuel]: usaco-contests/2013open/silver/fuel.cpp
[cruise]: usaco-contests/2013open/silver/cruise.cpp
[nocow]: usaco-contests/2013nov/silver/nocow.cpp
[crowded]: usaco-contests/2013nov/silver/crowded.cpp
[pogocow]: usaco-contests/2013nov/silver/pogocow.cpp
[msched2]: usaco-contests/2013dec/silver/msched.cpp
[vacation]: usaco-contests/2013dec/silver/vacation.cpp
[slowdown]: usaco-contests/2014jan/silver/slowdown.cpp
[ccski]: usaco-contests/2014jan/silver/ccski.cpp
[recording]: usaco-contests/2014jan/silver/recording.cpp
[auto]: usaco-contests/2014feb/silver/auto.cpp
[scode]: usaco-contests/2014feb/silver/scode.cpp
[irrigation]: usaco-contests/2014mar/silver/irrigation.cpp
[lazy]: usaco-contests/2014mar/silver/lazy.cpp
[mooomoo]: usaco-contests/2014mar/silver/mooomoo.cpp
[fairphoto]: usaco-contests/2014open/silver/fairphoto.cpp
[gpsduel]: usaco-contests/2014open/silver/gpsduel.cpp
[cowjogsilver]: usaco-contests/2014dec/silver/cowjog.cpp
[piggyback]: usaco-contests/2014dec/silver/piggyback.cpp
[stampede]: usaco-contests/2015jan/silver/stampede.cpp
[cowroute]: usaco-contests/2015jan/silver/cowroute.cpp
[meeting]: usaco-contests/2015jan/silver/meeting.cpp
[censor]: usaco-contests/2015feb/silver/censor.cpp
[hopscotch]: usaco-contests/2015feb/silver/hopscotch.cpp
[superbull]: usaco-contests/2015feb/silver/superbull.cpp
[bgm]: usaco-contests/2015open/silver/bgm.cpp
[trapped]: usaco-contests/2015open/silver/trapped.cpp
[buffet]: usaco-contests/2015open/silver/buffet.cpp

[cardgame]: usaco-contests/2015dec/gold/cardgame.cpp
[feast]: usaco-contests/2015dec/gold/feast.cpp
[dream]: usaco-contests/2015dec/gold/dream.cpp
[radio]: usaco-contests/2016jan/gold/radio.cpp
[cbarn]: usaco-contests/2016feb/gold/cbarn.cpp
[cbarn2]: usaco-contests/2016feb/gold/cbarn2.cpp
[fencedin]: usaco-contests/2016feb/gold/fencedin.cpp
[split]: usaco-contests/2016open/gold/split.cpp
[closing]: usaco-contests/2016open/gold/closing.cpp
[moocast]: usaco-contests/2016dec/gold/moocast.cpp
[checklist]: usaco-contests/2016dec/gold/checklist.cpp
[lasers]: usaco-contests/2016dec/gold/lasers.cpp
[bphoto]: usaco-contests/2017jan/gold/bphoto.cpp
[hps]: usaco-contests/2017jan/gold/hps.cpp
[cownav]: usaco-contests/2017jan/gold/cownav.cpp
[visitfj]: usaco-contests/2017feb/gold/visitfj.cpp
[nocross]: usaco-contests/2017feb/gold/nocross.cpp
[circlecross]: usaco-contests/2017feb/gold/circlecross.cpp
[cownomics]: usaco-contests/2017open/gold/cownomics.cpp
[art2]: usaco-contests/2017open/gold/art2.cpp
[piepie]: usaco-contests/2017dec/gold/piepie.cpp
[barnpainting]: usaco-contests/2017dec/gold/barnpainting.cpp
[hayfeast]: usaco-contests/2017dec/gold/hayfeast.cpp
[mootube]: usaco-contests/2018jan/gold/mootube.cpp
[atlarge]: usaco-contests/2018jan/gold/atlarge.cpp
[spainting]: usaco-contests/2018jan/gold/spainting.cpp
[snowboots]: usaco-contests/2018feb/gold/snowboots.cpp
[dirtraverse]: usaco-contests/2018feb/gold/dirtraverse.cpp
[taming]: usaco-contests/2018feb/gold/taming.cpp
[sort]: usaco-contests/2018open/gold/sort.cpp
[milkorder]: usaco-contests/2018open/gold/milkorder.cpp
[talent]: usaco-contests/2018open/gold/talent.cpp

[bbreeds]: usaco-contests/2012nov/gold/bbreeds.cpp
[gangs]: usaco-contests/2012dec/gold/gangs.cpp
[first]: usaco-contests/2012dec/gold/first.cpp
[runaway]: usaco-contests/2012dec/gold/runaway.cpp
[lineup]: usaco-contests/2013jan/gold/lineup.cpp
[island]: usaco-contests/2013jan/gold/island.cpp
[seating]: usaco-contests/2013jan/gold/seating.cpp
[partition]: usaco-contests/2013feb/gold/partition.cpp
[taxi]: usaco-contests/2013feb/gold/taxi.cpp
[route]: usaco-contests/2013feb/gold/route.cpp
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

[maxflow]: usaco-contests/2015dec/plat/maxflow.cpp
[cardgame]: usaco-contests/2015dec/plat/cardgame.cpp
[haybales]: usaco-contests/2015dec/plat/haybales.cpp
[fortmoo]: usaco-contests/2016jan/plat/fortmoo.cpp
[mowing]: usaco-contests/2016jan/plat/mowing.cpp

Note: Code primarily written in C++.