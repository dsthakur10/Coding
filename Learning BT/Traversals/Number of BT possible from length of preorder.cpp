// Count the number of Binary Tree possible for a given Preorder Sequence length n.

// Examples:
// Input : n = 1 & Output : 1

// Input : n = 2 & Output : 2

// Input : n = 3 & Output : 5

// Catalan number => 2nCn / (n+1)

// T(n) = Σ(T(n-k)*T(k-1)) {k = 1 to n-1} ==> LST contains k-1 nodes. RST contains n-k nodes. root = 1 node. Each of LST & RST can be arranged independently as BT with given preorder
// Use dynamic programming to store #subtrees possible for every length of preorder starting from n = 0

