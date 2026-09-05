import random
import os

def generate_vertex_coloring_tests():
    """
    Generates unweighted, undirected graphs for Vertex Coloring.
    Format:
    V E
    u degree v1 v2 ...
    """
    print("\n--- Generating Vertex Coloring Test Inputs ---")
    
    # Required sizes from Section 4.2
    configs = [
        (10, 3, "color_10.txt"),
        (100, 3, "color_100.txt"),
        (1000, 3, "color_1000.txt"),
        (10000, 3, "color_10000.txt"),
        (50000, 3, "color_50000.txt"),
        (100000, 3, "color_100000.txt")
    ]
    
    for V, avg_deg, filename in configs:
        print(f"Generating {filename} (V={V})...")
        adj = [set() for _ in range(V)]
        
        # 1. Ensure connectivity with a linear backbone
        for i in range(V - 1):
            adj[i].add(i + 1)
            adj[i + 1].add(i)
            
        target_edges = (V * avg_deg) // 2
        current_edges = V - 1
        attempts = 0
        max_attempts = target_edges * 8
        
        # 2. Add random undirected edges within a local window
        while current_edges < target_edges and attempts < max_attempts:
            attempts += 1
            u = random.randint(0, V - 1)
            window = min(200, V)
            v = (u + random.randint(1, window)) % V
            
            if u != v and v not in adj[u]:
                adj[u].add(v)
                adj[v].add(u)
                current_edges += 1
                
        # 3. Write unweighted undirected adjacency list
        with open(filename, 'w') as f:
            f.write(f"{V} {current_edges}\n")
            for u in range(V):
                nbrs = sorted(list(adj[u]))
                deg = len(nbrs)
                if deg == 0:
                    f.write(f"{u} 0\n")
                else:
                    f.write(f"{u} {deg} {' '.join(map(str, nbrs))}\n")
                    
        print(f"-> Created {filename} with V={V}, E={current_edges}")


def generate_pagerank_tests():
    """
    Generates unweighted, directed graphs for PageRank.
    Format:
    V E
    u outdegree v1 v2 ...
    DAMPING d
    TOLERANCE epsilon
    MAX_ITERATIONS n
    """
    print("\n--- Generating PageRank Test Inputs ---")
    
    # Required sizes from Section 4.2: 10, 100, 1000, 10000, 50000 (100000 optional)
    configs = [
        (10, 3, "pagerank_10.txt"),
        (100, 3, "pagerank_100.txt"),
        (1000, 3, "pagerank_1000.txt"),
        (10000, 3, "pagerank_10000.txt"),
        (50000, 3, "pagerank_50000.txt")
    ]
    
    damping = 0.85
    tolerance = 0.0001
    max_iterations = 100

    for V, avg_outdeg, filename in configs:
        print(f"Generating {filename} (V={V})...")
        adj = [set() for _ in range(V)]
        
        # 1. Create a directed cycle to ensure all vertices are reachable
        for i in range(V):
            adj[i].add((i + 1) % V)
            
        target_edges = V * avg_outdeg
        current_edges = V
        attempts = 0
        max_attempts = target_edges * 8
        
        # 2. Add random directed outgoing edges
        while current_edges < target_edges and attempts < max_attempts:
            attempts += 1
            u = random.randint(0, V - 1)
            window = min(200, V)
            v = (u + random.randint(1, window)) % V
            
            if u != v and v not in adj[u]:
                adj[u].add(v)
                current_edges += 1
                
        # 3. Write directed adjacency list with parameters appended
        with open(filename, 'w') as f:
            f.write(f"{V} {current_edges}\n")
            for u in range(V):
                nbrs = sorted(list(adj[u]))
                outdeg = len(nbrs)
                if outdeg == 0:
                    f.write(f"{u} 0\n")
                else:
                    f.write(f"{u} {outdeg} {' '.join(map(str, nbrs))}\n")
            
            # Required parameter block from Section 6.1
            f.write(f"DAMPING {damping}\n")
            f.write(f"TOLERANCE {tolerance}\n")
            f.write(f"MAX_ITERATIONS {max_iterations}\n")
            
        print(f"-> Created {filename} with V={V}, E={current_edges}")


if __name__ == "__main__":
    # Generate both suites
    generate_vertex_coloring_tests()
    generate_pagerank_tests()