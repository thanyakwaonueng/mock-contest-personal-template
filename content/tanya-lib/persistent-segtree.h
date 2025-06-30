/**
 * Author: Tanya
 * Description: TODO
 */
//Warning!This implementation is not garbage collected, so the tree nodes aren't deleted even if the instance of the segment tree is taken out of scope.
struct Node {
    ll val;
	Node *l, *r;

	Node(ll x) : val(x), l(nullptr), r(nullptr) {}
	Node(Node *ll, Node *rr) {
		l = ll, r = rr;
		val = 0;
		if (l) val += l->val;
		if (r) val += r->val;
	}
	Node(Node *cp) : val(cp->val), l(cp->l), r(cp->r) {}
};

int n, cnt = 1;
ll a[200001];
Node *roots[200001];

Node *build(int l = 1, int r = n) {
	if (l == r) return new Node(a[l]);
	int mid = (l + r) / 2;
	return new Node(build(l, mid), build(mid + 1, r));
}

Node *update(Node *node, int val, int pos, int l = 1, int r = n) {
	if (l == r) return new Node(val);
	int mid = (l + r) / 2;
	if (pos > mid) return new Node(node->l, update(node->r, val, pos, mid + 1, r));
	else return new Node(update(node->l, val, pos, l, mid), node->r);
}

ll query(Node *node, int a, int b, int l = 1, int r = n) {
	if (l > b || r < a) return 0;
	if (l >= a && r <= b) return node->val;
	int mid = (l + r) / 2;
	return query(node->l, a, b, l, mid) + query(node->r, a, b, mid + 1, r);
}
