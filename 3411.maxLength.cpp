#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	struct SegmentTree {
		vector<int64_t> gcdTree;
		vector<int64_t> lcmTree;
		int sz;

		SegmentTree (const vector<int> &source) {
			size_t n = source.size();
			gcdTree = vector<int64_t>(n * 4);
			lcmTree = vector<int64_t>(n * 4);
			sz = n;

			build(source, 0, 0, sz);
		}

		void buildMerge(int curr, int l, int r) {
			gcdTree[curr] = gcd(gcdTree[l], gcdTree[r]);
			lcmTree[curr] = lcm(lcmTree[l], lcmTree[r]);
		}

		void build(const vector<int> &source,
			int curr,
			int l, int r) {
			if (r - l == 1) {
				gcdTree[curr] = source[l];
				lcmTree[curr] = source[l];
				return;
			}

			int mid = (l + r) / 2;

			build(source, curr * 2 + 1, l, mid);
			build(source, curr * 2 + 2, mid, r);

			buildMerge(curr, curr*2+1, curr*2+2);
		}

		pair<int64_t, int64_t> query(int curr, int cl, int cr, int ql, int qr) {
			if (ql <= cl && cr <= qr) {
				return {gcdTree[curr], lcmTree[curr]};
			}

			if (qr <= cl || cr <= ql) {
				return {0, 1};
			}

			int mid = (cl + cr) / 2;

			auto left = query(curr * 2 + 1, cl, mid, ql, qr);
			auto right = query(curr * 2 + 2, mid, cr, ql, qr);

			return {
				gcd(left.first, right.first),
				lcm(left.second, right.second)
			};
		}

		pair<int64_t, int64_t> qry(int l, int r) {
			return query(0, 0, sz, l, r+1);
		}
	};
public:
	int maxLength(vector<int> &nums) {
		size_t sz = nums.size();

		SegmentTree sgtree(nums);

		int mxLen = 0;
		for (int l = 0; l < sz; ++l) {
			uint64_t pro = nums[l];
			for (int r = l; r < sz; ++r) {
				pro *= nums[r];

				auto res = sgtree.qry(l, r);
				if (pro == res.first * res.second) {
					mxLen = max(mxLen,
						r - l + 1
					);
				}
			}
		}

		return mxLen;
	}
};
