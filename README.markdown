Micro-XML
========

A super small xml parser library written in C++.

Purpose
========

The primary goal of this project was to create a small and simple xml parsing library for the purpose of reading-in and writing xml data files. For the sake of simplicity, Micro-XML follows a highly constrained version of the xml standard (See Syntax). Micro-XML does not allow declarations or namespaces. However, unique node attribute names are enforced. This allows for quick parsing by heavily reducing the complexity of the parsing process. This makes this library well suited for low-memory/low-spec applications, such as embedded systems.

Syntax
======

Simplified XML BNF used by Micro-XML (xml style comments are not shown, but are allowed):
```
attribute ::= <id> '=' '"' <string> '"'

attribute_list ::= <attribute> <attribute_list> | (empty)

node ::= '<' <id> <attribute_list> <node_end> | (empty)

node_end ::= '/>' | '>' <element> '</' <id> '>'

node_list ::= <node> <node_list> | (empty)

element ::= <node_list> | <string>
```

Use Cases
========

Micro-XML was designed with two seperate use cases in-mind. Firstly, Micro-XML needs to be able to read and parse xml from a string or file, and produce a searchable document. Secondly, Micro-XML needs to be able to create, modify, and write new xml files. Both of these operations can be accomplished by instantiating a 'document' and then calling the associated read or write method (see Types).

Types
========

An xml data file consists of a series of nodes and associated node attributes. Furthermore, nodes can either nest other nodes, or contain a single string value. For this reason, there are only two basic types: 'nodes' and 'attributes'; which derive from type 'element'.

![Primative type hierarchy](http://dl.dropbox.com/u/6410544/prim_types.png)

From these primitive types, more complex types can be formed. A 'document' is a representation of an xml file in memory, containing a single root 'node'. These types allows for modification, searching, reading and writing of xml files. 

![UML diagram of document type](http://dl.dropbox.com/u/6410544/document.png)

Some types can be aggregated into lists for easier processing. Both 'node' and 'attribute' types can be placed into associated 'node-list' and 'attribute-list' types.

Build
======

###Windows:

This project has not been tested in a Windows environment. However, the files should be able to be imported into a Visual Studios project without a problem.

###Linux (Unix):

Instructions for compiling Micro-XML from source code

Requirements:
* g++ 4.4 or newer (or any compiler with c++0x compliance)
* make 3.8 or newer

For Debian:
```
sudo apt-get install build-essential make
```

Build:
```
make
```

Clean:
```
make clean
```

Using This Library
======

To use Micro-XML, simply include the library in your project with the appropriate linker flag:
```
-lmxml
```

Make sure to include the header files and indicate the namespace  in your project as well:
```cpp
#include "[path-to-headers]/document.hpp"
#include "[path-to-headers]/nodes.hpp"
...

using namespace __mxml;
```

Examples will be coming soon.

License
======

Copyright(C) 2012 David Jolly <majestic53@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
