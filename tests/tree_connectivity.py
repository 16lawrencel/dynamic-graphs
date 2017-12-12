import networkx as nx
import random
import sys

from collections import deque

SEED = 68512017
NUM_QUERY = 100
random.seed(SEED)

def generate_test_graph(num_nodes, num_edges, verbose=False):
    test_graph = nx.Graph()
    test_graph.add_nodes_from(range(num_nodes))
    add_edges_to_graph(test_graph, num_edges, verbose)
    return test_graph

def add_edges_to_graph(graph, num_new_edges, verbose=False):
    num_nodes = graph.number_of_nodes()
    for i in range(num_new_edges):
        while True:
            a, b = random.randint(0, num_nodes - 1), random.randint(0, num_nodes - 1)
            if (a != b) and (a not in graph[b]) and (not is_connected(graph, a, b)):
                if verbose:
                    print(f'add {a} {b}')
                graph.add_edge(a, b)
                break
    return graph

def del_edges_from_graph(graph, num_del_edge, verbose=False):
    num_nodes = graph.number_of_nodes()
    for i in range(num_del_edge):
        while True:
            a = random.randint(0, num_nodes-1)
            edges = list(graph.adj[a])
            if len(edges) is not 0:
                b = random.choice(edges)
                if verbose:
                    print(f'rem {a} {b}')
                graph.remove_edge(a, b)
                break
    return graph

def add_nodes_to_graph(graph, num_new_nodes, verbose=False):
    graph.add_nodes_from(range(graph.number_of_nodes(),
                               graph.number_of_nodes() + num_new_nodes))
    return graph

def is_connected(graph, a, b):
    if (a not in graph.nodes) or (b not in graph.nodes):
        return False
    # simple bidirectional search
    a_list = deque([a])
    a_seen = set([a])
    b_list = deque([b])
    b_seen = set([b])
    vis = set()
    while len(a_list) > 0 and len(b_list) > 0:
        a_left = a_list.popleft()
        if a_left in vis:
            continue
        if len(b_seen.intersection(graph.adj[a_left])):
            return True
        a_list.extend(graph.adj[a_left])
        a_seen.update(graph.adj[a_left])
        vis.add(a_left)

        b_left = b_list.popleft()
        if b_left in vis:
            continue
        if len(a_seen.intersection(graph.adj[b_left])):
            return True
        b_list.extend(graph.adj[b_left])
        b_seen.update(graph.adj[b_left])
        vis.add(b_left)

    return False

if __name__ == '__main__':
    # Usage: simple_connectivity.py num_nodes num_edges
    assert(len(sys.argv) >= 3), 'Incorrect number of parameters!'
    num_nodes, num_edges = int(sys.argv[1]), int(sys.argv[2])
    assert(num_edges < num_nodes), 'Graph isn\'t a forest'
    print(str(num_nodes) + '\n')
    test_graph = generate_test_graph(num_nodes, num_edges, True)
    add_del = min(100, num_edges // 10)
    for i in range(10):
        del_edges_from_graph(test_graph, add_del, True)
        for i in range(NUM_QUERY):
            a, b = random.randint(0, num_nodes - 1), random.randint(0, num_nodes - 1)
            print(f'conn {a} {b}')
            with open(f'tree_answer_{num_nodes}_{num_edges}.txt', 'a') as f:
                conn = is_connected(test_graph, a, b)
                if conn:
                    f.write('YES\n')
                else:
                    f.write('NO\n')
        add_edges_to_graph(test_graph, add_del, True)
