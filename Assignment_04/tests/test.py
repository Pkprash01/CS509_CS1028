import random
import os

def generate_graph(V, target_edges_per_node, filename):
    print(f"Creating {filename} (V={V})...")
    adj = [set() for _ in range(V)]
    
    # 1. Ensure connectivity with a spanning backbone
    for i in range(V - 1):
        adj[i].add(i + 1)
        adj[i + 1].add(i)
    
    # 2. Add random undirected edges up to the target sparsity
    total_target = (V * target_edges_per_node) // 2
    current_edges = V - 1
    
    attempts = 0
    max_attempts = total_target * 5
    
    while current_edges < total_target and attempts < max_attempts:
        attempts += 1
        u = random.randint(0, V - 1)
        # Use a local window to avoid memory thrashing on large V
        span = min(200, V)
        v = (u + random.randint(1, span)) % V
        
        if u != v and v not in adj[u]:
            adj[u].add(v)
            adj[v].add(u)
            current_edges += 1

    # 3. Write directly to disk
    with open(filename, 'w') as f:
        # Header: V E (where E is the count of unique undirected edges)
        f.write(f"{V} {current_edges}\n")
        
        for u in range(V):
            nbrs = sorted(list(adj[u]))
            deg = len(nbrs)
            if deg == 0:
                f.write(f"{u} 0\n")
            else:
                nbr_str = " ".join(map(str, nbrs))
                f.write(f"{u} {deg} {nbr_str}\n")
                
    print(f"Finished {filename} with E={current_edges} edges.")

if __name__ == "__main__":
    # Required scales from Section 4.2: 10, 100, 10000, 50000, 100000
    configs = [
        (10, 3, "color_10.txt"),
        (100, 3, "color_100.txt"),
        (1000, 3, "color_1000.txt"),
        (10000, 3, "color_10000.txt"),
        (50000, 3, "color_50000.txt"),
        (100000, 3, "color_100000.txt")
    ]
    
    for V, deg, name in configs:
        generate_graph(V, deg, name)