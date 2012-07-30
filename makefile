# Micro-XML Makefile
# Copyright (C) 2012 David Jolly

CC=g++
SRC=src/
OUT=libmxml.a
FLAG=-std=c++0x -O3 -funroll-all-loops

all: mxml build

build: 
	ar rcs $(OUT) $(SRC)mxml_attribute.o $(SRC)mxml_attribute_list.o $(SRC)mxml_buffer.o $(SRC)mxml_document.o $(SRC)mxml_element.o $(SRC)mxml_lexer.o $(SRC)mxml_node.o $(SRC)mxml_node_list.o $(SRC)mxml_parser.o

clean:
	rm -f $(OUT)
	rm -f $(SRC)*.o

mxml: mxml_attribute.o mxml_attribute_list.o mxml_buffer.o mxml_document.o mxml_element.o mxml_lexer.o mxml_node.o mxml_node_list.o mxml_parser.o

mxml_attribute.o: $(SRC)mxml_attribute.cpp $(SRC)mxml_attribute.hpp
	$(CC) $(FLAG) -c $(SRC)mxml_attribute.cpp -o $(SRC)mxml_attribute.o

mxml_attribute_list.o: $(SRC)mxml_attribute_list.cpp $(SRC)mxml_attribute_list.hpp
	$(CC) $(FLAG) -c $(SRC)mxml_attribute_list.cpp -o $(SRC)mxml_attribute_list.o

mxml_buffer.o: $(SRC)mxml_buffer.cpp $(SRC)mxml_buffer.hpp
	$(CC) $(FLAG) -c $(SRC)mxml_buffer.cpp -o $(SRC)mxml_buffer.o

mxml_document.o: $(SRC)mxml_document.cpp $(SRC)mxml_document.hpp
	$(CC) $(FLAG) -c $(SRC)mxml_document.cpp -o $(SRC)mxml_document.o

mxml_element.o: $(SRC)mxml_element.cpp $(SRC)mxml_element.hpp
	$(CC) $(FLAG) -c $(SRC)mxml_element.cpp -o $(SRC)mxml_element.o

mxml_lexer.o: $(SRC)mxml_lexer.cpp $(SRC)mxml_lexer.hpp
	$(CC) $(FLAG) -c $(SRC)mxml_lexer.cpp -o $(SRC)mxml_lexer.o

mxml_node.o: $(SRC)mxml_node.cpp $(SRC)mxml_node.hpp
	$(CC) $(FLAG) -c $(SRC)mxml_node.cpp -o $(SRC)mxml_node.o

mxml_node_list.o: $(SRC)mxml_node_list.cpp $(SRC)mxml_node_list.hpp
	$(CC) $(FLAG) -c $(SRC)mxml_node_list.cpp -o $(SRC)mxml_node_list.o

mxml_parser.o: $(SRC)mxml_parser.cpp $(SRC)mxml_parser.hpp
	$(CC) $(FLAG) -c $(SRC)mxml_parser.cpp -o $(SRC)mxml_parser.o
