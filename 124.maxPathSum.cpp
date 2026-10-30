#include "shdstd-cpp.h"

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

#define INF32 (INT32_MAX / 4)
#define NEG_INF32 -(INF32)
class Solution {
private:
	int maxRes;

	int searchMax(TreeNode *curr) {
		if (curr == nullptr)
			return 0;

		int leftVal = max(0, searchMax(curr->left));
		int rightVal = max(0, searchMax(curr->right));

		maxRes = max(
			maxRes,
			leftVal + rightVal + curr->val
		);

		return curr->val + max(leftVal, rightVal);
	}
public:
	int maxPathSum(TreeNode *root) {
		if (root == nullptr)
			return 0;

		maxRes = NEG_INF32;

		searchMax(root);

		return maxRes;
	}
};
