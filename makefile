# Micro-XML Makefile
# Copyright (C) 2012 David Jolly

CC=g++
SRC=src/
OUT=libmxml.a
FLAG=-std=c++0x -O3 -funroll-all-loops

all: mxml build

build: 
	ar rcs $(OUT) $(SRC)attribute.o $(SRC)attribute_list.o $(SRC)document.o $(SRC)element.o $(SRC)lexer.o $(SRC)node.o $(SRC)node_list.o $(SRC)parser.o $(SRC)pb_buff.o

clean:
	rm -f $(OUT)
	rm -f $(SRC)*.o

mxml: attribute.o attribute_list.o document.o element.o lexer.o node.o node_list.o parser.o pb_buff.o

attribute.o: $(SRC)attribute.cpp $(SRC)attribute.hpp
	$(CC) $(FLAG) -c $(SRC)attribute.cpp -o $(SRC)attribute.o

attribute_list.o: $(SRC)attribute_list.cpp $(SRC)attribute_list.hpp
	$(CC) $(FLAG) -c $(SRC)attribute_list.cpp -o $(SRC)attribute_list.o

document.o: $(SRC)document.cpp $(SRC)document.hpp
	$(CC) $(FLAG) -c $(SRC)document.cpp -o $(SRC)document.o

element.o: $(SRC)element.cpp $(SRC)element.hpp
	$(CC) $(FLAG) -c $(SRC)element.cpp -o $(SRC)element.o

lexer.o: $(SRC)lexer.cpp $(SRC)lexer.hpp
	$(CC) $(FLAG) -c $(SRC)lexer.cpp -o $(SRC)lexer.o

node.o: $(SRC)node.cpp $(SRC)node.hpp
	$(CC) $(FLAG) -c $(SRC)node.cpp -o $(SRC)node.o

node_list.o: $(SRC)node_list.cpp $(SRC)node_list.hpp
	$(CC) $(FLAG) -c $(SRC)node_list.cpp -o $(SRC)node_list.o

parser.o: $(SRC)parser.cpp $(SRC)parser.hpp
	$(CC) $(FLAG) -c $(SRC)parser.cpp -o $(SRC)parser.o

pb_buff.o: $(SRC)pb_buff.cpp $(SRC)pb_buff.hpp
	$(CC) $(FLAG) -c $(SRC)pb_buff.cpp -o $(SRC)pb_buff.o
