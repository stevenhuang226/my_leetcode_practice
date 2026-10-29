#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	struct FenwickTree {
		vector<uint32_t> data;
		size_t size;

		explicit FenwickTree(size_t sz) {
			data = vector<uint32_t>(sz+2, 0);
			size = sz;
		}

		void update(int i, uint32_t delta) {
			++i;
			while (i <= size) {
				data[i] ^= delta;
				i += i & (-i);
			}
		}

		uint32_t query(int i) {
			++i;
			uint32_t res = 0;
			while (i > 0) {
				res ^= data[i];
				i -= i & (-i);
			}
			return res;
		}

		void rangeXor(int l, int r, uint32_t delta) {
			update(l, delta);
			update(r+1, delta);
		}
	};

	struct DynamicArray {
		vector<int> head;
		vector<int> nextNode;
		vector<int> target;
		int edgesCount;

		explicit DynamicArray(size_t sz) {
			head = vector<int>(sz, -1);
			nextNode = vector<int>(sz * 2);
			target = vector<int>(sz * 2);
			edgesCount = 0;
		}

		void link(int from, int to) {
			target[edgesCount] = to;
			nextNode[edgesCount] = head[from];
			head[from] = edgesCount;
			++edgesCount;
		}

		void dlink(int a, int b) {
			link(a, b);
			link(b, a);
		}

		int nxt(int edgeId) {
			return nextNode[edgeId];
		}

		int hd(int edgeId) {
			return head[edgeId];
		}

		int trg(int edgeId) {
			return target[edgeId];
		}
	};

	vector<uint32_t> maskPrefix;
	vector<int> timeIn;
	vector<int> timeOut;
	int meetTime;

	vector<vector<int>> nodeParent;
	vector<int> depth;
	int lg;

	void buildPrefix(int curr, int parent,
	string &s, DynamicArray &arr) {
		timeIn[curr] = ++meetTime;

		int nxt = arr.hd(curr);
		while (nxt >= 0) {
			int trg = arr.trg(nxt);
			nxt = arr.nxt(nxt);

			if (trg == parent)
				continue;

			uint32_t mask = (1 << (s[trg] - 'a'));
			maskPrefix[trg] = maskPrefix[curr] ^ mask;

			nodeParent[0][trg] = curr;
			depth[trg] = depth[curr] + 1;

			for (int k = 1; k < lg; ++k) {
				int mid = nodeParent[k-1][trg];
				if (mid != -1) {
					nodeParent[k][trg] =
					nodeParent[k-1][mid];
				}
			}

			buildPrefix(trg, curr, s, arr);
		}

		timeOut[curr] = meetTime;
	}

	int findLCA(int u, int v) {

		if (depth[u] < depth[v])
			swap(u, v);

		int diff = depth[u] - depth[v];

		for (int k = 0; k < lg; ++k) {
			if (diff & (1 << k))
				u = nodeParent[k][u];
		}

		if (u == v)
			return u;

		for (int k = lg-1; k >= 0; --k) {
			if (nodeParent[k][u] != nodeParent[k][v]) {
				u = nodeParent[k][u];
				v = nodeParent[k][v];
			}
		}

		return nodeParent[0][u];
	}
public:
	vector<bool> palindromePath(int nodes,
		vector<vector<int>> &edges,
		string chars,
		vector<string> &queries)
	{
		maskPrefix.resize(nodes, 0);
		timeIn.resize(nodes);
		timeOut.resize(nodes);

		DynamicArray darr = DynamicArray(nodes);

		for (const vector<int> &e : edges) {
			darr.dlink(e[0], e[1]);
		}

		lg = 1;
		while ((1 << lg) <= nodes)
			++lg;
		nodeParent.resize(lg, vector<int>(nodes, -1));
		depth.resize(nodes);

		maskPrefix[0] = 1 << (chars[0] - 'a');
		meetTime = -1;
		buildPrefix(0, -1, chars, darr);

		FenwickTree fwTree = FenwickTree(nodes);

		vector<bool> res;
		for (const string &q : queries) {
			istringstream iss(q);

			string h;
			int u,v;
			char b;

			iss >> h >> u;

			if (h == "update") {
				iss >> b;
				int tin = timeIn[u];
				int tout = timeOut[u];
				uint32_t mask = 1 << (b - 'a');
				mask ^= 1 << (chars[u] - 'a');
				chars[u] = b;

				fwTree.rangeXor(tin, tout, mask);
			} else if (h == "query") {
				iss >> v;

				int tinU = timeIn[u];
				int tinV = timeIn[v];

				uint32_t maskU = maskPrefix[u] ^ fwTree.query(tinU);
				uint32_t maskV = maskPrefix[v] ^ fwTree.query(tinV);
				int lca = findLCA(u, v);
				uint32_t lcaMask = 1 << (chars[lca] - 'a');
				uint32_t pathMask = maskU ^ maskV ^ lcaMask;

				res.push_back((pathMask & (pathMask-1)) == 0);
			}
		}

		return res;
	}
};
