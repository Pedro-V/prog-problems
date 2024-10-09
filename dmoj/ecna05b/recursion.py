class Node:
    def __init__(self, name, children=None):
        self.name = name
        self.children = children or []
        self.score = 0

def read_tree(num_lines):
    node_dict = {}
    for _ in range(num_lines):
        name, _, *children = input().split()
        parent_node = node_dict.get(name, Node(name))
        for child in children:
            child_node = node_dict.get(child, Node(child))
            node_dict[child] = child_node
            parent_node.children.append(child_node)
        node_dict[name] = parent_node
    return node_dict

def score_one(node, dist):
    if dist == 1:
        return len(node.children)
    score = 0
    for child in node.children:
        score += score_one(child, dist-1)
    return score

def score_all(node_dict, dist):
    for node in node_dict.values():
        node.score = score_one(node, dist)

def sorting_key(node):
    return -node.score, node.name

def output_info(nodes, case_num):
    print(f'Tree {case_num}:')
    for i, node in enumerate(nodes):
        if node.score == 0 or (i >= 3 and node.score != nodes[i-1].score):
            return
        print(node.name, node.score)

def main():
    num_cases = int(input())
    for case_num in range(1, num_cases+1):
        num_lines, dist = map(int, input().split())
        node_dict = read_tree(num_lines)
        score_all(node_dict, dist)
        nodes = sorted(node_dict.values(), key=sorting_key)
        output_info(nodes, case_num)
        if case_num < num_cases:
            print()

if __name__ == '__main__':
    main()
