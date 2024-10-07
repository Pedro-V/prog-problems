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

def tokenize(s):
    return s.replace('(', ' ( ').replace(')', ' ) ').split()

def parse_tree(s):
    tokens = iter(tokenize(s))
    return build_tree(tokens)

def build_tree(tokens):
    node = Node()
    token = next(tokens)
    if token == '(':
        node.left = build_tree(tokens)
        node.right = build_tree(tokens)
        next(tokens)
    else:
        node.candy = int(token)
    return node

def main():
    for _ in range(NUM_CASES):
        tree_description = input()
        tree = parse_tree(tree_description)
        candy = tree_candy(tree)
        height = tree_height(tree)
        streets = tree_streets(tree) - height
        print(streets, candy)

if __name__ == '__main__':
    main()
