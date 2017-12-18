## Usage
To use, include "ds.h"
Compile with make (although you may have to move some main files first)

We implemented Link Cut Trees, Euler Tour Trees, Fully Dynamic Connectivity, and Incremental Two-Edge Connectivity

## API
The API is fairly simple; first, add nodes by calling struct.add(x), then call link / cut / connectivity operations.

# Example:
'''
FullDynamic struct = FullDynamic();
struct.add(1);
struct.add(2);
struct.add(3);
struct.link(1, 2);
struct.link(2, 3);
struct.link(3, 1);
std::cout << struct.conn(1, 2) << '\n'; // should be 1
struct.cut(1, 2);
std::cout << struct.conn(1, 2) << '\n'; // should still be 1
struct.cut(1, 3);
std::cout << struct.conn(1, 2) << '\n'; // should be 0
'''

Here are the specific APIs and operations supported by each data structure:

# Link Cut Trees
* void add(x)
* bool link(x, y)
* bool cut(x, y)
* bool conn(x, y)

# Euler Tour Trees
* bool link(x, y)
* bool cut(x, y)
* bool conn(x, y)

# Full Dynamic
* void add(x)
* bool link(x, y)
* bool cut(x, y)
* bool conn(x, y)

# Incremental Two-edge Connectivity
* void add(x)
* bool link(x, y)
* bool two_edge_conn(x, y)

Note that Euler Tour Trees don't require adding nodes.
For all structures, link and cut operations return a boolean indicating whether it was successful (did anything).

