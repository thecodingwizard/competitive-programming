# Competitive Programming Solutions
This repository contains solutions to various competitive programming problems.

# USACO Solutions

Solutions to USACO training and USACO contest problems.

#### USACO Training:
| Problem Number | Problem Name | Solution Notes |
| -------------- | ------------ | -------------- |
| 1.5.1 | [Arithmetic Progressions][1.5.1] | Careful Brute Force |
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
| 3.2.3 | [Spinning Wheels][3.2.3] | Brute Force, max 360 seconds |
| 3.2.4 | [Feed Ratios][3.2.4] | Brute force |
| 3.2.5 | [Magic Squares][3.2.5] | BFS |
| 3.2.6 | [Sweet Butter][3.2.6] | APSP |
| 3.3.1 | [Riding the Fences][3.3.1] | Eulerian Path | 
| 3.3.2 | [Shopping Offers][3.3.2] | Dijkstra |
| 3.3.3 | [Camelot][3.3.3] | Brute force, king can take only two steps |
| 3.3.4 | [Home on the Range][3.3.4] | DP |
| 3.3.5 | [A Game][3.3.5] | DP |
| 3.4.1 | [American Heritage][3.4.1] | Recursively generate tree |
| 3.4.2 | [Electric Fence][3.4.2] | Pick's Theorem |
| 3.4.3 | [Raucous Rockers][3.4.3] | Brute Force (Bitmasking) |
| 4.1.1 | [Beef McNuggets][4.1.1] | DP |
| 4.1.2 | [Fence Loops][4.1.2] | Dijkstra |
| 4.2.1 | [Drainage Ditches][4.2.1] | Max Flow O(V^2E) |
| 4.2.2 | [The Perfect Stall][4.2.2] | Max Bipartite Matching |
| 4.2.3 | [Job Processing][4.2.3] | Greedy |
| 4.3.1 | [Buy Low, Buy Lower][4.3.1] | DP, BigInteger (less than + addition) |
| 4.3.2 | [Street Race][4.3.2] | DFS, Set, Brute Force |
| 4.3.3 | [Letter Game][4.3.3] | String permutation, brute force, map/set |
| 4.4.1 | [Shuttle Puzzle][4.4.1] | Brute Force, BFS (Queue), Implementation |
| 4.4.2 | [Pollutant Control][4.4.2] | Max Flow Min Cut, minimize removed edges |
| 4.4.3 | [Frame Up][4.4.3] | All Topological Sorts |

### Silver USACO Contests:
| Contest Date | Problem ID | Problem Name | Solution Notes |
| ------------ | ---------- | ------------ | -------------- |
| Feb 2018 | [reststops][reststops] | Rest Stops | Greedy |
| Feb 2019 | [revegetate][revegetate] | The Great Revegetation | Graph, DFS, Tricky |

### Gold USACO Contests:

#### Old USACO Gold (Silver):
| Contest Date | Problem ID | Problem Name | Solution Notes |
| ------------ | ---------- | ------------ | -------------- |
| Nov 2012 | [clumsy][clumsy] | Clumsy Cows | Greedy |
| Nov 2012 | [distant][distant] | Distant Pastures | APSP, dijkstra |
| Nov 2012 | [bbreeds][bbreeds] | Balanced Cow Breeds | Same problem as Gold |
| Dec 2012 | [crazy][crazy] | Crazy Fences | Computational Geometry |
| Dec 2012 | [wifi][wifi] | Wifi Setup | DP |
| Dec 2012 | [mroute][mroute] | Milk Routing | Dijkstra |
| Jan 2013 | [paint][paint] | Painting the Fence | Coordinate Compression, Store Deltas & Sweep |
| Jan 2013 | [squares][squares] | Square Overlap | Sweep |
| Jan 2013 | [invite][invite] | Party Invitations | precompute which groups each cow is in |
| Feb 2013 | [perimeter][perimeter] | Perimeter | Optimized Floodfill |
| Feb 2013 | [tractor][tractor] | Tractor | Binary search for answer, dfs |
| Feb 2013 | [msched][msched] | Milk Scheduling | Greedy |
| Mar 2013 | [poker][poker] | Poker Hands | Greedy |
| Mar 2013 | [painting][painting] | Farm Painting | Sweep |
| Mar 2013 | [cowrun][cowrun] | The Cow Run | DP, same as gold |
| Open 2013 | [gravity][gravity] | What's Up With Gravity? | Dijkstra |
| Open 2013 | [fuel][fuel] | Fuel Economy | Greedy |
| Open 2013 | [cruise][cruise] | Luxury River Cruise | Find where sequence repeats |
| Nov 2013 | [nocow][nocow] | Farmer John has no Large Brown Cow | Solvable with a bit of math |
| Nov 2013 | [crowded][crowded] | Crowded Cows | Sweep, can use multiset instead of monotonic queue |
| Nov 2013 | [pogocow][pogocow] | Pogo-Cow | DP, note that Bessie can go either direction |
| Dec 2013 | [msched][msched2] | Milk Scheduling | Greedy, sweep |
| Dec 2013 | [vacation][vacation] | Vacation Planning | Code is slightly modified from gold version, answer is unnecessarily complicated for silver |
| Dec 2013 | [shuffle][shuffle] | The Bessie Shuffle | Repeated Squaring, Permutations, Composing functions/permutations |
| Jan 2014 | [slowdown][slowdown] | Bessie Slows Down | Maintain two arrays, simulation |
| Jan 2014 | [ccski][ccski] | Cross Country Skiing | Prim's |
| Jan 2014 | [recording][recording] | Recording the Moolympics | Greedy |
| Feb 2014 | [auto][auto] | Auto-complete | Binary search |
| Feb 2014 | [rblock][rblock] | Roadblock | Dijkstra |
| Feb 2014 | [scode][scode] | Secret Code | DP |
| Mar 2014 | [irrigation][irrigation] | Watering the Fields | Kruskal/MST |
| Mar 2014 | [lazy][lazy] | The Lazy Cow | Rotate grid 45 degrees |
| Mar 2014 | [mooomoo][mooomoo] | Mooo Moo | DP |
| Open 2014 | [fairphoto][fairphoto] | Fair Photography | Sweep |
| Open 2014 | [gpsduel][gpsduel] | Dueling GPSs | Dijkstra |
| Dec 2014 | [piggyback][piggyback] | Piggy Back | Shortest Path on three nodes |
| Dec 2014 | [marathon][marathon] | Marathon | DP |
| Dec 2014 | [cowjog][cowjog] | Cow Jog | Sweep |
| Jan 2015 | [stampede][stampede] | Stampede | Sweep |
| Jan 2015 | [cowroute][cowroute] | Cow Routing | Dijkstra |
| Jan 2015 | [meeting][meeting] | Meeting Time | DP |
| Feb 2015 | [censor][censor] | Censoring | Rolling Hash |
| Feb 2015 | [hopscotch][hopscotch] | Cow Hopscotch | DP |
| Feb 2015 | [superbull][superbull] | Superbull | MST, Prim's O(V^2) |
| Open 2015 | [bgm][bgm] | Bessie Goes Moo | Parity |
| Open 2015 | [trapped][trapped] | Trapped in the Haybales (Silver) | Sort, Sweep |
| Open 2015 | [buffet][buffet] | Bessie's Birthday Buffet |  |

#### USACO Gold (2015-now)
| Contest Date | Problem ID | Problem Name | Solution Notes |
| ------------ | ---------- | ------------ | -------------- |
| Dec 2015 | [cardgame][cardgame] | High Card Low Card (Gold) | Greedy |
| Dec 2015 | [feast][feast] | Fruit Feast | DP (Knapsack) |
| Dec 2015 | [dream][dream] | Bessie's Dream | Dijkstra |
| Jan 2016 | [angry][angry] | Angry Cows | Sweep/Greedy/DP, Binary Search (Optional) |
| Jan 2016 | [radio][radio] | Radio Contact | DP |
| Jan 2016 | [lightsout][lightsout] | Lights Out | Simulation, Coordinates, Brute Force, Implementation |
| Feb 2016 | [cbarn][cbarn] | Circular Barn | Greedy |
| Feb 2016 | [cbarn2][cbarn2] | Circular Barn (Revisited) | DP |
| Feb 2016 | [fencedin][fencedin] | Fenced In | MST (Kruskal) |
| Open 2016 | [split][split] | Splitting The Field | Sweep |
| Open 2016 | [closing][closing] | Closing The Farm | UFDS (Note: Runs really close to time limit) |
| Open 2016 | [248][248] | 248 | DP |
| Dec 2016 | [moocast][moocast] | Moocast | UFDS, brute force |
| Dec 2016 | [checklist][checklist] | Cow Checklist | DP |
| Dec 2016 | [lasers][lasers] | Lasers and Mirrors | BFS |
| Jan 2017 | [bphoto][bphoto] | Balanced Photo | Fenwick Tree |
| Jan 2017 | [hps][hps] | Hoof, Paper, Scissors | 3D DP |
| Jan 2017 | [cownav][cownav] | Cow Navigation | BFS |
| Feb 2017 | [visitfj][visitfj] | Why Did The Cow Cross The Road | Dijkstra |
| Feb 2017 | [nocross][nocross] | Why Did The Cow Cross The Road II | DP |
| Feb 2017 | [circlecross][circlecross] | Why Did The Cow Cross The Road III | Fenwick Tree (BIT) |
| Open 2017 | [cownomics][cownomics] | Bovine Genomics | Rolling Hash |
| Open 2017 | [art2][art2] | Modern Art 2 | Calculate start/end points |
| Dec 2017 | [piepie][piepie] | A Pie For A Pie | BFS, binary search |
| Dec 2017 | [barnpainting][barnpainting] | Barn Painting | DP |
| Dec 2017 | [hayfeast][hayfeast] | Haybale Feast | Two Pointers |
| Jan 2018 | [mootube][mootube] | MooTube | UFDS |
| Jan 2018 | [atlarge][atlarge] | Cow At Large | DFS/BFS |
| Jan 2018 | [spainting][spainting] | Stamp Painting | DP, recurrence |
| Feb 2018 | [snowboots][snowboots] | Snow Boots | Sort, Doubly-Linked List |
| Feb 2018 | [dirtraverse][dirtraverse] | Directory Traversal | DFS |
| Feb 2018 | [taming][taming] | Taming The Herd | DP |
| Open 2018 | [sort][sort] | Out of Sorts | BIT |
| Open 2018 | [milkorder][milkorder] | Milking Order | Topological Sort (Lexicographically earliest) |
| Open 2018 | [talent][talent] | Talent Show | Binary search for answer, DP |
| Dec 2018 | [dining][dining] | Fine Dining | Dijkstra |
| Dec 2018 | [cowpatibility][cowpatibility] | Cowpatibility | PIE |
| Dec 2018 | [teamwork][teamwork] | Teamwork | DP |
| Jan 2019 | [poetry][poetry] | Cow Poetry | DP, power under mod, math |
| Jan 2019 | [sleepy][sleepy] | Sleepy Cow Sorting | Fenwick Tree |
| Jan 2019 | [shortcut][shortcut] | Shortcut | Dijkstra, find path |
| Feb 2019 | [cowland][cowland] | Cow Land | Tree Traversal Array, or alternatively Heavy-Light Decomposition |
| Feb 2019 | [dishes][dishes] | Dishwashing | Greedy (Also doable with [Greedy + Binary Search][dishes_binarysearch]) |
| Feb 2019 | [paintbarn][paintbarn] | Painting the Barn | Geometry, Prefix Sums, Line Sweep |

### Platinum USACO Contests:

#### Old USACO Platinum (Gold):
| Contest Date | Problem ID | Problem Name | Solution Notes |
| ------------ | ---------- | ------------ | -------------- |
| Nov 2012 | [bbreeds][bbreeds] | Balanced Cow Breeds | DP |
| Dec 2012 | [gangs][gangs] | Gangs of Istanbull/Cowstantinople | Greedy |
| Dec 2012 | [first][first] | First! | trie, checking DAG for cycles |
| Dec 2012 | [runaway][runaway] | Running Away From the Barn |  | 
| Jan 2013 | [lineup][lineup] | Cow Lineup | sweep with two pointers |
| Jan 2013 | [island][island] | Island Travels | bfs |
| Jan 2013 | [seating][seating] | Seating | Binary Tree, Lazy Propagation |
| Feb 2013 | [partition][partition] | Partitioning The Farm | DP |
| Feb 2013 | [taxi][taxi] | Taxi | Min Cost Matching, calculate distance driven w/o cow |
| Feb 2013 | [route][route] | Route Designing | DP |
| Mar 2013 | [cowrun][cowrun] | The Cow Run | DP |
| Mar 2013 | [hillwalk][hillwalk] | Hill Walk | Line sweep, find a way to order hills |
| Nov 2013 | [nochange][nochange] | No Change | DP, 2^k state |
| Nov 2013 | [sight][sight] | Line of Sight | If two cows can see the same point on the silo, they can see each other |
| Nov 2013 | [empty][empty] | Empty Stalls | Sweep |
| Dec 2013 | [vacationgold][vacationgold] | Vacation Planning (Gold) | Dijkstra |
| Dec 2013 | [optmilk][optmilk] | Optimal Milking | Binary Tree |
| Jan 2014 | [skicourse][skicourse] | Building A Ski Course | DP |
| Jan 2014 | [skilevel][skilevel] | Ski Course Rating | Kruskal |
| Feb 2014 | [rblock][rblock] | Roadblock | Dijkstra |
| Feb 2014 | [dec][dec] | Cow Decathlon | DP |
| Mar 2014 | [sabotage][sabotage] | Sabotage | Binary search, 1D max sum |
| Mar 2014 | [fcount][fcount] | Counting Friends | Brute Force, greedily connect friends |
| Dec 2014 | [guard][guard] | Guard Mark | DP |
| Dec 2014 | [marathon][marathon] | Marathon | Segment Tree |
| Dec 2014 | [cowjog][cowjog] | Cow Jog | Longest Non-Increasing Subsequence |
| Jan 2015 | [cowrect][cowrect] | Cow Rectangles | Sweep, assume we have to take one of the Holsteins |
| Jan 2015 | [movie][movie] | Moovie Mooving | DP, bitmasking |
| Open 2015 | [palpath][palpath] | Palindromic Paths | DP |
| Open 2015 | [trapped][trapped] | Trapped in the Haybales | Sort haybales by weight |
| Open 2015 | [buffet][buffet] | Bessie's Birthday Buffet | DP |

#### USACO Platinum (2015-now):
| Contest Date | Problem ID | Problem Name | Solution Notes |
| ------------ | ---------- | ------------ | -------------- |
| Dec 2015 | [maxflow][maxflow] | Max Flow | LCA, prefix sums |
| Dec 2015 | [cardgame][cardgame] | High Card Low Card | Greedy |
| Dec 2015 | [haybales][haybales] | Counting Haybales | Seg Tree, Lazy, Min Query & Sum Query |
| Jan 2016 | [fortmoo][fortmoo] | Fort Moo | DP/Sliding Window |
| Jan 2016 | [mowing][mowing] | Mowing The Field | 2D Range Tree |
| Feb 2016 | [balancing][balancing] | Load Balancing | Binary Search, BIT |
| Feb 2016 | [fencedinplat][fencedinplat] | Fenced In |  |
| Open 2016 | [262144][262144] | 262144 | DP |
| Dec 2016 | [team][team] | Team Building | DP | 9/9 |
| Jan 2017 | [promote][promote] | Promotion Counting | BIT on preorder of tree |
| Jan 2017 | [tallbarn][tallbarn] | Building a Tall Barn | Binary Search |
| Jan 2017 | [subrev][subrev] | Subsequence Reversal | DP |
| Feb 2017 | [mincross][mincross] | Why Did The Cow Cross The Road | Fenwick Tree |
| Feb 2017 | [nocross][nocross] | Why Did The Cow Cross The Road II | DP, RMQ (Seg Tree) |
| Feb 2017 | [friendcross][friendcross] | Why Did The Cow Cross The Road III | 2D Seg Tree |
| Open 2017 | [art][art] | Modern Art | Prefix Sums/Deltas |
| Open 2017 | [grass][grass] | Switch Grass | MST, Sets, I/O Optimization |
| Dec 2017 | [pushabox][pushabox] | Push A Box | Biconnected Components, BFS |
| Dec 2017 | [greedy][greedy] | Greedy Gift Takers | Binary Search, Prefix Sums |
| Jan 2018 | [lifeguards][lifeguards] | Lifeguards | DP (Note: Solution code is very sketchy and really shouldn't run in time) |
| Feb 2018 | [newbarn][newbarn] | New Barns | Centroid Decomposition |
| Jan 2019 | [redistricting][redistricting] | Redistricting | DP, Monotonic Queue |

[1.5.1]: usaco-training/Chapter%201/1.5.1%20ariprog%20-%20Arithmetic%20Progressions.cpp
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
[3.2.3]: usaco-training/Chapter%203/3.2.3%20-%20Spinning%20Wheels.cpp
[3.2.4]: usaco-training/Chapter%203/3.2.4%20-%20Feed%20Ratios.cpp
[3.2.5]: usaco-training/Chapter%203/3.2.5%20-%20Magic%20Squares.cpp
[3.2.6]: usaco-training/Chapter%203/3.2.6%20-%20Sweet%20Butter.cpp
[3.3.1]: usaco-training/Chapter%203/3.3.1%20-%20Riding%20the%20Fences.cpp
[3.3.2]: usaco-training/Chapter%203/3.3.2%20-%20Shopping%20Offers.cpp
[3.3.3]: usaco-training/Chapter%203/3.3.3%20-%20Camelot.cpp
[3.3.4]: usaco-training/Chapter%203/3.3.4%20-%20Home%20on%20the%20Range.cpp
[3.3.5]: usaco-training/Chapter%203/3.3.5%20-%20A%20Game.cpp
[3.4.1]: usaco-training/Chapter%203/3.4.1%20-%20American%20Heritage.cpp
[3.4.2]: usaco-training/Chapter%203/3.4.2%20-%20Electric%20Fence.cpp
[3.4.3]: usaco-training/Chapter%203/3.4.3%20-%20Raucous%20Rockers.cpp
[4.1.1]: usaco-training/Chapter%204/4.1.1%20-%20Beef%20McNuggets.cpp
[4.1.2]: usaco-training/Chapter%204/4.1.2%20-%20Fence%20Loops.cpp
[4.2.1]: usaco-training/Chapter%204/4.2.1%20-%20Drainage%20Ditches.cpp
[4.2.2]: usaco-training/Chapter%204/4.2.2%20-%20The%20Perfect%20Stall.cpp
[4.2.3]: usaco-training/Chapter%204/4.2.3%20-%20Job%20Processing.cpp
[4.3.1]: usaco-training/Chapter%204/4.3.1%20-%20Buy%20Low,%20Buy%20Lower.cpp
[4.3.2]: usaco-training/Chapter%204/4.3.2%20-%20Street%20Race.cpp
[4.3.3]: usaco-training/Chapter%204/4.3.3%20-%20Letter%20Game.cpp
[4.4.1]: usaco-training/Chapter%204/4.4.1%20-%20Shuttle%20Puzzle.cpp
[4.4.2]: usaco-training/Chapter%204/4.4.2%20-%20Pollutant%20Control.cpp
[4.4.3]: usaco-training/Chapter%204/4.4.3%20-%20Frame%20Up.cpp

[reststops]: usaco-contests/2018feb/silver/reststops.cpp
[revegetate]: usaco-contests/2019feb/silver/revegetate.cpp

[clumsy]: usaco-contests/2012nov/silver/clumsy.cpp
[distant]: usaco-contests/2012nov/silver/distant.cpp
[crazy]: usaco-contests/2012dec/silver/crazy.cpp
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
[shuffle]: usaco-contests/2013dec/silver/shuffle.cpp
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
[angry]: usaco-contests/2016jan/gold/angry.cpp
[radio]: usaco-contests/2016jan/gold/radio.cpp
[lightsout]: usaco-contests/2016jan/gold/lightsout.cpp
[cbarn]: usaco-contests/2016feb/gold/cbarn.cpp
[cbarn2]: usaco-contests/2016feb/gold/cbarn2.cpp
[fencedin]: usaco-contests/2016feb/gold/fencedin.cpp
[split]: usaco-contests/2016open/gold/split.cpp
[closing]: usaco-contests/2016open/gold/closing.cpp
[248]: usaco-contests/2016open/gold/248.cpp
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
[dining]: usaco-contests/2018dec/gold/dining.cpp
[cowpatibility]: usaco-contests/2018dec/gold/cowpatibility.cpp
[teamwork]: usaco-contests/2018dec/gold/teamwork.cpp
[poetry]: usaco-contests/2019jan/gold/poetry.cpp
[sleepy]: usaco-contests/2019jan/gold/sleepy.cpp
[shortcut]: usaco-contests/2019jan/gold/shortcut.cpp
[cowland]: usaco-contests/2019feb/gold/cowland.cpp
[dishes_binarysearch]: usaco-contests/2019feb/gold/dishes_binarysearch.cpp
[dishes]: usaco-contests/2019feb/gold/dishes.cpp
[paintbarn]: usaco-contests/2019feb/gold/paintbarn.cpp

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
[balancing]: usaco-contests/2016feb/plat/balancing.cpp
[fencedinplat]: usaco-contests/2016feb/plat/fencedin.cpp
[262144]: usaco-contests/2016open/plat/262144.cpp
[team]: usaco-contests/2016dec/plat/team.cpp
[promote]: usaco-contests/2017jan/plat/promote.cpp
[tallbarn]: usaco-contests/2017jan/plat/tallbarn.cpp
[subrev]: usaco-contests/2017jan/plat/subrev.cpp
[mincross]: usaco-contests/2017feb/plat/mincross.cpp
[nocross]: usaco-contests/2017feb/plat/nocross.cpp
[friendcross]: usaco-contests/2017feb/plat/friendcross.cpp
[art]: usaco-contests/2017open/plat/art.cpp
[grass]: usaco-contests/2017open/plat/grass.cpp
[pushabox]: usaco-contests/2017dec/plat/pushabox.cpp
[greedy]: usaco-contests/2017dec/plat/greedy.cpp
[lifeguards]: usaco-contests/2018jan/plat/lifeguards.cpp
[newbarn]: usaco-contests/2018feb/plat/newbarn.cpp
[redistricting]: usaco-contests/2019jan/plat/redistricting.cpp

# Codeforces
Solutions to various Codeforces problems.

[Here is the complete solutions folder.](codeforces)

| Problem ID | Problem Name | Solution Notes |
| ---------- | ------------ | -------------- |
| 321C | C. Ciel the Commander | Centroid Decomposition |
| [342E](codeforces/342E%20-%20Xenia%20and%20Tree.cpp) | E. Xenia and Tree | Centroid Decomposition, LCA |
| [383D](codeforces/383D%20-%20Antimatter.cpp) | D. Antimatter | DP |
| [497A](codeforces/497A%20-%20Reorder%20The%20Array.cpp) | A. Reorder The Array | Multiset |
| [762B](codeforces/762B%20-%20USB%20vs%20PS2.cpp) | B. USB vs PS/2 | Sorting, Greedy |
| [809A](codeforces/809A%20-%20Do%20you%20want%20a%20date.cpp) | A. Do you want a date? | Math, power, mod |
| [817D](codeforces/817D%20-%20Imbalanced%20Array.cpp) | D. Imbalanced Array | Stack, Sweep, Math |
| [937A](codeforces/937A%20-%20Olympiad.cpp) | A. Olympiad | Set |
| [946D](codeforces/946D%20-%20Timetable.cpp) | D. Timetable | DP |
| [989D](codeforces/989D%20-%20A%20Shade%20of%20Moonlight.cpp) | D. A Shade of Moonlight | Binary Search, Math |
| [991B](codeforces/991B%20-%20Getting%20an%20A.cpp) | B. Getting an A | Sorting |
| 1012B | B. Chemical table | Bipartite Graph |
| 1038C | C. Gambling | |
| [1061D](codeforces/1061D%20-%20TV%20Shows.cpp) | D. TV Shows | Multiset, Greedy |
| 1067B | B. Multihedgehog | |
| 1095F | F. Make it Connected | UFDS |
| 1098A | A. Sum in the tree | |
| 1099F | F. Cookies | Fenwick Tree |
| [1104A](codeforces/1104A%20-%20Splitting%20into%20digits.cpp) | A. Splitting into digits | brute force |
| [1104B](codeforces/1104B%20-%20Game%20with%20String.cpp) | B. Game with string | Stack |
| 1104C | C. Grid Game | Ad Hoc |
| 1104D | D. Game with modulo | binary search, math |
| 1105A | A. Salem and Sticks | |
| 1105B | B. Zuhair and Strings | |
| 1105C | C. Ayoub and Lost Array | |
| 1105D | D. Kilani and the Game | |
| 1111A | A. Superhero Transformation | |
| 1111C | C. Creative Snap | |
| 1113A | A. Sasha and His Trip | Greedy |
| 1113B | B. Sasha and Magnetic Machines | |
| 1113C | C. Sasha and a Bit of Relax | |
| 1113D | D. Sasha and One More Name | |
| 1114D | D. Flood Fill | |
| 1117E | E. Decypher the String | Math, string processing |
| 1118E | E. Yet Another Ball Problem | Constructive Algorithms, Ad Hoc |
| 1130A | A. Be Positive | Ad Hoc |
| 1130B | B. Two Cakes | Greedy |
| 1130C | C. Connect | Floodfill, Brute Force |
| 1130D1 | D. Toy Train (Simplified) | Simulation |
| 1130D2 | D. Toy Train | Math, Precomputation |
| 1131D | D. Gourmet Choice | DAG, Detecting Cycles, Topo Sort |
| 1141F1 | F1. Same Sum Blocks (Easy) | See 1141F2, though O(N^4) dp should also work |
| 1141F2 | F2. Same Sum Blocks (Hard) | Prefix sums O(N^2) |

# UVa Online Judge (Competitive Programming 3, Starred)
Solutions to UVa Online Judge problems. Mostly starred problems from Competitive Programming 3.

[Solutions Folder](UVa%20Online%20Judge)

# Google Kick Start
Solutions to various [Google Kick Start](https://codingcompetitions.withgoogle.com/kickstart) competitions.

## [Kick Start 2018](google-kickstart/2018)
| Problem Name | Solution Notes |
| ------------ | -------------- |
| A - Even Digits | Ad Hoc |
| A - Lucky Dip | Brute Force / Binary Search |
| A - Scrambled Words | Strings, implementation |
| B - No Nine | Digit DP (Alternatively, Ad Hoc) |

[Solutions Folder](google-kickstart)