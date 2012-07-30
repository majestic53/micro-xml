/*
 * mxml_document.cpp
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
#include "mxml_document.hpp"
#include "mxml_parser.hpp"

using namespace __mxml;

_mxml_document::_mxml_document(void) {
	return;
}

_mxml_document::_mxml_document(mxml_node &root) :
		_root(root) {
	return;
}

_mxml_document::_mxml_document(const std::string &name) :
		_root(name) {
	return;
}

_mxml_document::_mxml_document(const _mxml_document &other) :
		_root(other._root) {
	return;
}

_mxml_document::~_mxml_document(void) {
	return;
}

_mxml_document &_mxml_document::operator=(const _mxml_document &other) {
	if(this == &other)
		return *this;
	_root = other._root;
	return *this;
}

std::string _mxml_document::_format_xml(_mxml_node &root) {
	std::string output;
	try {
		output = root.to_string(0);
	} catch(std::runtime_error &exc) {
		std::cerr << "Exception: " << exc.what() << std::endl;
	}
	return output;
}

void _mxml_document::_parse_xml(const std::string &input, bool is_file, _mxml_node &root) {
	mxml_parser par;
	std::string exc_mess;
	try {
		par = mxml_parser(input, is_file);
		par._parse(root);
	} catch(std::runtime_error &exc) {
		exc_mess = "mxml: ";
		exc_mess += exc.what();
		throw std::runtime_error(exc_mess);
	}
}

mxml_node_list _mxml_document::get_nodes_by_name(const std::string &name) {
	mxml_node_list nod_lst;
	_mxml_node_list::get_nodes_by_name(name, _root, nod_lst);
	return nod_lst;
}

mxml_node &_mxml_document::get_root_node(void) {
	return _root;
}

void _mxml_document::read(const std::string &path, _mxml_document &doc) {
	_parse_xml(path, true, doc.get_root_node());
}

void _mxml_document::read(const std::string &path) {
	read(path, *this);
}

void _mxml_document::read_from_string(const std::string &input, _mxml_document &doc) {
	_parse_xml(input, false, doc.get_root_node());
}

void _mxml_document::read_from_string(const std::string &input) {
	read_from_string(input, *this);
}

void _mxml_document::set_root_node(mxml_node &root) {
	_root = root;
}

std::string _mxml_document::to_string(void) {
	return _root.to_string(0);
}

bool _mxml_document::write(const std::string &path, _mxml_document &doc) {
	std::ofstream output(path.c_str(), std::ios::out | std::ios::trunc);
	if(!output)
		return false;
	output << _format_xml(doc.get_root_node());
	output.close();
	return true;
}

bool _mxml_document::write(const std::string &path) {
	return write(path, *this);
}
