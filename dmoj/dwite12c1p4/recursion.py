import re

NUM_CASES = 5

class Node:
    def __init__(self, left=None, right=None, candy=0):
        self.left = left
        self.right = right
        self.candy = candy

    def is_leaf(self):
        return self.left is None and self.right is None

def tree_height(node):
    if node.is_leaf():
        return 0
    return max(tree_height(node.left), tree_height(node.right)) + 1

def tree_candy(node):
    if node.is_leaf():
        return node.candy
    return tree_candy(node.left) + tree_candy(node.right)

def tree_streets(node):
    if node.is_leaf():
        return 0
    return tree_streets(node.left) + tree_streets(node.right) + 4

def build_tree(tree_description, idx):
    node = Node()
    if tree_description[idx] == '(':
        idx += 1
        node.left, idx = build_tree(tree_description, idx)
        idx += 1
        node.right, idx = build_tree(tree_description, idx)
        idx += 1
    else:
        match = re.match(r'\d+', tree_description[idx:])
        node.candy = int(match.group(0))
        idx += len(match.group(0))

    return node, idx

def main():
    for _ in range(NUM_CASES):
        tree_description = input()
        tree, _ = build_tree(tree_description, 0)
        candy = tree_candy(tree)
        height = tree_height(tree)
        streets = tree_streets(tree) - height
        print(streets, candy)

if __name__ == '__main__':
    main()
