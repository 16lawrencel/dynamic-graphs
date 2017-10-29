dynamic-graphs
Stuff we need to fix:
If you try compiling dsu.cpp, you'll note that it doesn't compile.
This is because I'm trying to declare everything as a pointer machine 
class, and the pointer machine class contains a Node subclass.
But I'm not sure how to access the Node subclass after inheriting 
from the PM class.
