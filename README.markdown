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

Using the makefile to generate a static library (.a)

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

Examples
======

For the purpose of those examples, we will be using the demo xml file listed below.
```xml
<!-- 
	A list of contacts
-->

<address_book>
	<contact id="0">
		<name>John</name>
		<phone>555-5555</phone>
		<email>john@internet.com</email>
	</contact>
	<contact id="1">
		<name>Sarah</name>
		<phone>444-4444</phone>
		<email>sarah@internet.com</email>
	</contact>
	<contact id="2">
		<name>Dave</name>
		<phone>333-3333</phone>
		<email>dave@internet.com</email>
	</contact>
</address_book>
```

###Reading XML Files

This example shows how to read-in an xml file and parse the xml document for data. In this example, we will be parsing the demo xml file (above) for contact names.
```cpp
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "document.hpp"
#include "node.hpp"
#include "node_list.hpp"

using namespace __mxml;

int main(void) {

	// instantiate an xml document and read-in file
	document doc;
	doc.read("demo.xml");

	// retrieve a node list containing all contact's names
	node_list lst = doc.get_nodes_by_name("name");

	// process the nodes...
	std::cout << "Contact Names: " << std::endl;
	for(size_t i = 0; i < lst.size(); ++i)
		std::cout << "[" << (i + 1) << "]: " << lst.get_node_at(i).get_string() << std::endl;
	return 0;
}
```

This example will produce the following output:
```
Contact Names: 
\[1\]: John
\[2\]: Sarah
\[3\]: Dave
```

###Writing XML Files

This example shows how to create an xml document and then write it to a file. The example below creates the demo xml file shown above.
```cpp
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "attribute.hpp"
#include "document.hpp"
#include "node.hpp"
#include "node_list.hpp"

using namespace __mxml;

std::string to_string(size_t input) {
	std::stringstream ss;
	ss << input;
	return ss.str();
}

int main(void) {

	std::string names[] = {"John", "Sarah", "Dave",};
	std::string phones[] = {"555-5555", "444-4444", "333-3333",};

	// instantiate a new xml document
	document doc("address_book");

	// generate contact nodes
	for(size_t i = 0; i < 3; ++i) {
		node contact("contact");
		attribute contact_id("id", to_string(i));
		contact.add_attribute(contact_id);

		// generate sub-nodes
		node name("name"), phone("phone"), email("email");
		name.set_string(names[i]);
		phone.set_string(phones[i]);
		email.set_string(names[i] + "@internet.com");

		// add sub-nodes to contact node
		contact.add_node(name);
		contact.add_node(phone);
		contact.add_node(email);

		// add contact node to root node
		doc.get_root_node().add_node(contact);
	}

	// write the document to a file
	doc.write("demo_write.xml");
	return 0;
}
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
