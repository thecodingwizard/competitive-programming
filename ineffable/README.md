Test link: https://contest.usaco.org/OPEN09.htm

![ ](http://codeforces.com/predownloaded/f4/3d/f43d1d912eca2f8c25b30418f592eb7717eaf88f.png)

# What is ineffable?

Simple command-line grader for local grading of solutions for problems of competitive programming contests.
It is written in Python and it uses `timeout` Perl library to limit resources (time and memory limits) of program being tested.

It works on Ubuntu, and I guess it should work on any Linux/Unix system as long as Python and Perl are installed.

# Screenshots

![ ](http://codeforces.com/predownloaded/a9/36/a936a7ff09cf8bd714f2321847676328a99f674d.png) ![ ](http://codeforces.com/predownloaded/23/ca/23ca3a3112a7b22ea5a809f6a4a1e5f0502475dd.png)  
(Original quote is "Success consists of going from failure to failure without loss of enthusiasm")

# Installation

Run the following commands on your terminal:

~~~~~
$ mkdir ~/.ineffable
$ cd ~/.ineffable
$ wget https://bitbucket.org/silap/ineffable/downloads/ineffable-1.0.zip
$ unzip master.zip
$ rm master.zip
$ mv silap-ineffable-*/* .
$ rm -r silap-ineffable-*/
$ sudo ln -s ~/.ineffable/ineffable /usr/local/bin/ineffable
~~~~~

Or alternatively you may run this command if you have curl installed:

~~~~~
$ bash < <(curl -sL https://bitbucket.org/silap/ineffable/raw/f208b207160eacd8ba4c30c078d1255e309c6b40/install.sh)
~~~~~

# Configuration

Whenever you run ineffable it looks for `ineff.json` file. You can also tell ineffable which configuration file to use using this syntax: `inefabble another.json`.

Configuring ineffable is easy and quite intuitive. After you install ineffable you can view the example configuration file that is located at `~/.ineffable/ineff.json.example`.

Available configuration options are as follows:

| key        | example value | Description                                           |
|------------|---------------|-------------------------------------------------------|
| pkdesc     | "Balkan OI 2014 Day 2 Problem Ephesus" | Package description. (Optional) |
| pbcode     | "steeple"         | Problem code. Ineffable searches for string `{PROBLEM}` in keys `warmup`, `execute`, `inp`, `out` and `tstdir`, and replaces them with `pbcode` value. (Optional) |
| tl         | 1000          | Time limit (in milliseconds). (Required) |
| ml         | 65536         | Memory limit (in kilobytes). (Required) |
| warmup     | "g++ -O2 -o solution solution.cpp" | Command to be executed before the grading starts. For example, it can be used to compile C++ code. Grading stops if the command exits with non-zero code (such as, when compilation fails). (Optional) |
| execute    | "./solution" or "python solution.py"  | Command that runs the solution. <span style="color:red">Solution needs to read from stdin and write to stdout.</span> (Required) |
| tstdir     | "steeple_tests" | Directory where the test files are located. If ommited, it is assumed that tests are located in the current directory. (Optional) |

There are 2 different ways to show ineffable which files are input files and which files are output files:

1. Smart stars:

        "inp": "input*.txt",
        "out": "output*.txt"


2. Listing files.

        # Syntax 1
        
        "iopairs": {
          "input1.txt": "output1.txt",
          "input2.txt": "output2.txt",
          "input3.txt": "output3.txt"
        }
        
        # Syntax 2
        
        "iopairs": {
          "inp": {"input1.txt", "input2.txt", "input3.txt"},
          "out": {"output1.txt", "output2.txt", "output3.txt"}
        }

# See it at work (sample session)

Let's solve problem Cow Steeplechase of [USACO 2011 November Contest](http://usaco.org/index.php?page=nov11problems).


~~~~~
$ # Create folder `steeple` in your desktop and another folder `steeple_tests` inside it.
$ mkdir Desktop/steeple
$ cd Desktop/steeple
$ mkdir steeple_tests
$ cd steeple_tests
$
$ # Download and extract test data into `steeple/steeple_tests/`.
$ wget -q http://usaco.org/current/data/steeple.zip
$ unzip -q steeple.zip
$ rm steeple.zip
$ cd ..
$
$ # Create file `ineff.json` and configure.
$ touch ineff.json
$ echo '{
  "pkdesc": "Cow Steeplechase (USACO Gold November 2011 Contest)",
  "pbcode": "steeple",
  "tl": 3000,
  "ml": 65536,
  "warmup": "g++ -std=c++11 -O2 -o {PROBLEM} {PROBLEM}.cpp",
  "execute": "./{PROBLEM}",
  "tstdir": "{PROBLEM}_tests/",
  "inp": "I.*",
  "out": "O.*"
}' >ineff.json
$
$ # Create `steeple.cpp` and open it with your favorite editor to code your solution.
$ touch steeple.cpp
$ vim steeple.cpp
$ # ...
$
$ # Test your solution
$ ineffable
~~~~~

As I haven't spent much effort in making ineffable, there may be some bugs. I won't be able to fix the bugs at least till the IOI 2015 ends.

Ineffable is a simple project and anyone who knows some Python can alter it for their own purpose or even add some features. Project is available on [Bitbucket](https://bitbucket.org/silap/ineffable/) (sorry no Github, it is blocked in my country :/).