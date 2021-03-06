Micro-XML
========

A super small xml parser library written in C++.

1. [Purpose](https://github.com/majestic53/micro-xml#purpose)
2. [Syntax](https://github.com/majestic53/micro-xml#syntax)
3. [Use Cases](https://github.com/majestic53/micro-xml#use-cases)
4. [Types](https://github.com/majestic53/micro-xml#types)
5. [Build](https://github.com/majestic53/micro-xml#build)
	* [Windows](https://github.com/majestic53/micro-xml#windows)
	* [Linux/Unix](https://github.com/majestic53/micro-xml#linux-unix)
6. [Using This Library](https://github.com/majestic53/micro-xml#using-this-library)
7. [Examples](https://github.com/majestic53/micro-xml#examples)
	* [Parsing nodes from XML Files](https://github.com/majestic53/micro-xml#parsing-nodes-from-xml-files)
	* [Parsing attributes from nodes](https://github.com/majestic53/micro-xml#parsing-attributes-from-nodes)
	* [Reading XML Files](https://github.com/majestic53/micro-xml#reading-xml-files)
	* [Writing XML Files](https://github.com/majestic53/micro-xml#writing-xml-files)
8. [License](https://github.com/majestic53/micro-xml#license)

Purpose
========

The primary goal of this project was to create a small and simple xml parsing library for the purpose of reading-in and writing xml data files. For the sake of simplicity, Micro-XML follows a highly constrained version of the xml standard (See Syntax). Micro-XML does not allow declarations or namespaces. However, unique node attribute names are enforced. This allows for quick parsing by heavily reducing the complexity of the parsing process, making the library well suited for low-memory environments, such as embedded systems.

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

###Linux/Unix:

Using the makefile to generate a static library (.a)

Requirements (tested with):
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
#include "[path-to-headers]/mxml.hpp"
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

###Parsing nodes from XML Files

There are currently two different ways to create nodelists of sub-nodes. The first method involves search from a document's root node; returning a list of all sub-nodes with a given name.
```cpp
mxml_document doc = ...; // some document
...
mxml_node_list lst = doc.get_nodes_by_name("name");
```

The second method is more general, and can be used to both retrieve a series of sub-nodes, as well as a count of the sub-nodes with a given name. This method can be used from any node.
```cpp
mxml_node nod = ...; // some node either parsed or created
...
size_t count;
mxml_node_list lst;
count = mxml_node_list::get_nodes_by_name("name", nod, lst);
```

###Parsing attributes from nodes

Due to the restriction that nodes only contain unique attribute names, only one occurance of any given attribute is expected per node. Therefore, finding attributes can be done through a simple search by calling the function ``` get_attribute_by_name(<name>, <attr>) ```, as shown below.
```cpp
mxml_node_list lst = doc.get_nodes_by_name("contact"); // retrieve a list of contact nodes
for(size_t i = 0; i < lst.size(); ++i) {
	mxml_attribute attr;
	lst.get_node_at(i).get_attribute_by_name("id", attr);
	std::cout << attr.to_string(0) << std::endl; // print the id attribute
}
```

This example will produce the following output:
```
id="0"
id="1"
id="2"
```

###Reading XML Files

This example shows how to read-in an xml file and parse the xml document for data. In this example, we will be parsing the demo xml file (above) for contact names.
```cpp
#include <iostream>
#include <stdexcept.h>
#include "mxml.hpp"

using namespace __mxml;

int main(void) {

	// instantiate an xml document and read-in file
	mxml_document doc;

	try {
		doc.read("demo.xml");
	} catch(std::runtime_error &exc) {
		std::cerr << "Exception: " << exc.what() << std::endl;
		return 1;
	}

	// retrieve a node list containing all contact names
	mxml_node_list lst = doc.get_nodes_by_name("name");

	// process the nodes...
	std::cout << "Contact Names: " << std::endl;
	for(size_t i = 0; i < lst.size(); ++i)
		std::cout << "(" << (i + 1) << "): " << lst.get_node_at(i).get_string() << std::endl;
	return 0;
}
```

This example will produce the following output:
```
Contact Names: 
(1): John
(2): Sarah
(3): Dave
```

###Writing XML Files

This example shows how to create an xml document and then write it to a file. The example below creates the demo xml file shown above.
```cpp
#include <iostream>
#include <sstream>
#include "mxml.hpp"

using namespace __mxml;

std::string to_string(size_t input) {
	std::stringstream ss;
	ss << input;
	return ss.str();
}

int main(void) {

	std::string names[] = {"John", "Sarah", "Dave",};
	std::string phones[] = {"555-5555", "444-4444", "333-3333",};
	std::string emails[] = {"john@internet.com", "sarah@internet.com", "dave@internet.com",};

	// instantiate a new xml document
	mxml_document doc("address_book");

	// generate contact nodes
	for(size_t i = 0; i < 3; ++i) {
		mxml_node contact("contact");
		mxml_attribute contact_id("id", to_string(i));
		contact.add_attribute(contact_id);

		// generate sub-nodes
		mxml_node name("name"), phone("phone"), email("email");
		name.set_string(names[i]);
		phone.set_string(phones[i]);
		email.set_string(emails[i]);

		// add sub-nodes to contact node
		contact.add_node(name);
		contact.add_node(phone);
		contact.add_node(email);

		// add contact node to root node
		doc.get_root_node().add_node(contact);
	}

	// write the document to a file
	doc.write("demo.xml");
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
