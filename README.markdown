Micro-XML
========

A super small xml parser library written in C++.

Comments
========

My attempt at writing a modestly featured, yet simple xml parser. At the moment, the parser can create basic xml files with nested nodes, attributes, and strings.

Build
======

Instructions for compiling Micro-XML from source code

Requirements (tested on):
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

Syntax
======

Here's the simplified XML BNF:
```
node ::= '<' <id> <attribute_list> <node_end> | (empty)

attribute_list ::= <attribute> <attribute_list> | (empty)

attribute ::= <id> '=' '"' <string> '"'

node_end ::= '/>' | '>' <element> '</' <id> '>'

element ::= <node> | <string>
```

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
