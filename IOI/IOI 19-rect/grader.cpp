#include "rect.h"
#include <cstdio>
#include <unistd.h>
#include <cassert>
#include <string>

using namespace std;

class InputReader {
private:
	static const int SIZE = 4096;
	
	int inputFileDescriptor;
	char buf[SIZE];
	int curChar;
	int numChars;

public:

	inline InputReader(int _inputFileDescriptor):
		inputFileDescriptor(_inputFileDescriptor),
		curChar(0),
		numChars(0) {
	}

	inline void close() {
		::close(inputFileDescriptor);
	}

	inline char read() {
		assert(numChars != -1);
		if (curChar >= numChars) {
			curChar = 0;
			numChars = ::read(inputFileDescriptor, buf, SIZE);
			if (numChars == -1)
				return -1;
		}
		return buf[curChar++];
	}

	inline int readInt() {
		int c = eatWhite();
		int sgn = 1;
		if (c == '-') {
			sgn = -1;
			c = read();
		}
		int res = 0;
		do {
			assert(c >= '0' && c <= '9');
			res *= 10;
			res += c - '0';
			c = read();
		} while (!isSpaceChar(c));
		return res * sgn;
	}

	inline string readString() {
		char c = eatWhite();
		string res;
		do {
			res += c;
			c = read();
		} while (!isSpaceChar(c));
		return res;
	}

	inline string readLine() {
		string res;
		while (true) {
			char c = read();
			if (c == '\n' || c == '\r' || c == -1)
				break;
			res += c;
		}
		return res;
	}

	inline char eatWhite() {
		char c = read();
		while (isSpaceChar(c)) 
			c = read();
		return c;
	}

	static inline bool isSpaceChar(char c) {
		return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
	}
};


int main() {
	InputReader inputReader(STDIN_FILENO);
	int n, m;
	n = inputReader.readInt();
	m = inputReader.readInt();
	vector<vector<int>> a(n, vector<int>(m));
	for (int i = 0; i < n; i++)	{
		for (int j = 0; j < m; j++) {
			a[i][j] = inputReader.readInt();
		}
	}
	inputReader.close();

	long long result = count_rectangles(a);

	printf("%lld\n", result);
	fclose(stdout);
	return 0;
}
