#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

int dp[16];
int c1[14];
int c2[14];

class PalindromeMatrix {

public:

	int minChange(vector <string> A, int rowCount, int columnCount) {

		const int N = A.size();
		const int M = A.front().size();

		int best = 15 * 15;

		for (int i = 0; i< (1<<N); ++i) {
			vector<bool> use(N,false);
			for (int j=0; j<N; ++j)
				if (i & (1<<j))
					use[j] = true;
			if (count(use.begin(), use.end(), true) < rowCount)
				continue;

			int baseswap = 0;
			for (int n=0; n<N; ++n)
				if (use[n])
					for (int m=0; m<M/2; ++m)
						if (A[n][m] != A[n][M-m-1])
							baseswap++;

			std::fill(c1, c1+14, 0);
			for (int j=0; j<M; ++j) {
				for (int k=0; k<N/2; ++k) {
					int u = k, v = N - k - 1;
					if (use[v] && !use[u])
						swap(u, v);

					if (use[u] && use[v]) {
						if (A[u][j] == A[u][M-j-1] && A[v][j] == A[v][M-j-1] && A[u][j] != A[v][j])
							c1[j] += 2;
					}
					else if (use[u]) {
						if (A[u][j] == A[u][M-j-1])
							c1[j]++;
					}
					else {
						if (A[u][j] != A[v][j]) {
							c1[j]++;
						}
					}
				}
			}

			std::fill(c2, c2+14, 0);
			for (int j=0; j<M/2; ++j) {
				for (int k=0; k<N/2; ++k) {
					int u=k, v = N-k-1;
					if (use[v] && !use[u])
						swap(u, v);

					if (use[u] && use[v]) {
						if (A[u][j] == A[u][M-j-1] && A[v][j] == A[v][M-j-1] && A[u][j] != A[v][j])
							c2[j] += 2;
					}
					else if (use[u]) {
						if (A[u][j] == A[u][M-j-1]) {
							if (A[u][j] != A[v][j]) c2[j]++;
							if (A[u][M-j-1] != A[v][M-j-1]) c2[j]++;
						}
						else {
							if (A[v][j] != A[v][M-j-1]) {
								c2[j]++;
							}
						}
					}
					else {
						if (A[u][j] != A[v][j])
							c2[j]++;
						if (A[u][M-j-1] != A[v][M-j-1])
							c2[j]++;
					}
				}
			}

			std::fill(dp, dp+16, 15*15);
			dp[0] = baseswap;

			for (int j=0; j<M/2; ++j) {
				for (int k=columnCount-1; k>=0; k--) {
					dp[k+2] = min(dp[k+2], dp[k]+c2[j]);
					dp[k+1] = min(dp[k+1], dp[k]+c1[j]);
					dp[k+1] = min(dp[k+1], dp[k]+c1[M-j-1]);
				}
			}

			best = min(best, dp[columnCount]);
		}

		return best;
	}
};
