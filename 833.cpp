#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


class DisjointSet {
public:
	vector<int> parent;
	vector<int> rank;

	DisjointSet(int n) {
		parent.resize(n);
		rank.resize(n, 0);
		for (int i = 0; i < n; i++) {
			parent[i] = i;
		}
	}

	int find(int x) {
		if (parent[x] == x) {
			return x;
		}
		return parent[x] = find(parent[x]);

	}

	bool uunion(int x, int y) {
		int xRoot = find(x);
		int yRoot = find(y);

		if (xRoot != yRoot) {
			if (rank[xRoot] <= rank[yRoot]) {
				parent[xRoot] = yRoot;
			}
			else {
				parent[yRoot] = xRoot;
			}
			if (rank[xRoot] == rank[yRoot]) {
				rank[yRoot]++;
			}
			return true;
		}
		return false;
	}
};

class Cell {
public:
	int height;
	int i;
	int j;

	Cell(int height, int i, int j) {
		this->height = height;
		this->i = i;
		this->j = j;
	}

	bool operator>(const Cell& other) const {
		return height > other.height;
	}
};
int main() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> grid(n, vector<int>(m));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> grid[i][j];
		}
	}

	int T;
	cin >> T;
	vector<int> years(T);

	for (int i = 0; i < T; i++) {
		cin >> years[i];
	}

	vector<Cell> cellInfo;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cellInfo.emplace_back(grid[i][j], i, j);
		}
	}

	sort(cellInfo.begin(), cellInfo.end(), greater<Cell>());

	DisjointSet ds(n * m);
	int islandCount = 0;
	int idx = 0;
	vector<int> ans(T);
	for (int i = T - 1; i >= 0; --i) {
		int water_level = years[i];
		while (idx < cellInfo.size() && cellInfo[idx].height > water_level) {
			islandCount++;
			int ri = cellInfo[idx].i;
			int cj = cellInfo[idx].j;
			vector<pair<int, int>> directions = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
			for (const auto& dir : directions) {
				int ni = ri + dir.first;
				int nj = cj + dir.second;
				if (ni >= 0 && ni < n && nj >= 0 && nj<m && grid[ni][nj]>water_level) {
					if (ds.uunion(ri * m + cj, ni * m + nj)) {
						islandCount--;
					}
				}

			}
			idx++;
		}
		ans[i] = islandCount;
	}

	cout << ans[0];
	for (int i = 1; i < T; i++) {
		cout << " " << ans[i] ;
	}
	cout << endl;
	return 0;

}