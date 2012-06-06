/*
 * document.cpp
 * Copyright (C) 2012 David Jolly
 * ----------------------
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <fstream>
#include <iostream>
#include <stdexcept>
#include "document.hpp"
#include "parser.hpp"

using namespace __mxml;

_document::_document(void) {
	return;
}

_document::_document(_node &root) :
		_root(root) {
	return;
}

_document::_document(const _document &other) :
		_root(other._root) {
	return;
}

_document::~_document(void) {
	return;
}

_document &_document::operator=(const _document &other) {
	if(this == &other)
		return *this;
	_root = other._root;
	return *this;
}

std::string _document::_format_xml(_node &root) {
	return root.to_string(0);
}

bool _document::_parse_xml(const std::string &input, bool is_file, _node &root) {
	parser par;
	try {
		par = parser(input, is_file);
		par._parse(root);
	} catch(std::runtime_error &exc) {
		std::cerr << "Exception: " << exc.what() << std::endl;
		return false;
	}
	return true;
}

node &_document::get_root_node(void) {
	return _root;
}

bool _document::read(const std::string &path, _document &doc) {
	return _parse_xml(path, true, doc.get_root_node());
}

bool _document::read(const std::string &path) {
	return read(path, *this);
}

bool _document::read_from_string(const std::string &input, _document &doc) {
	return _parse_xml(input, false, doc.get_root_node());
}

bool _document::read_from_string(const std::string &input) {
	return read_from_string(input, *this);
}

void _document::set_root_node(node &root) {
	_root = root;
}

std::string _document::to_string(void) {
	return _root.to_string(0);
}

bool _document::write(const std::string &path, _document &doc) {
	std::ofstream output(path.c_str(), std::ios::out | std::ios::trunc);
	if(!output)
		return false;
	output << _format_xml(doc.get_root_node());
	output.close();
	return true;
}

bool _document::write(const std::string &path) {
	return write(path, *this);
}
