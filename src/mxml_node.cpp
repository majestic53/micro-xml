/*
 * mxml_node.cpp
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

#include <sstream>
#include <stdexcept>
#include "mxml_node.hpp"

using namespace __mxml;

_mxml_node::_mxml_node(void) :
		_mxml_element(TYPE_NODE) {
	return;
}

_mxml_node::_mxml_node(const std::string &name) :
		_mxml_element(name, TYPE_NODE) {
	return;
}

_mxml_node::_mxml_node(const _mxml_node &other) :
		_mxml_element(other._name, TYPE_NODE), _str(other._str), _nodes(other._nodes), _attributes(other._attributes) {
	return;
}

_mxml_node::~_mxml_node(void) {
	return;
}

_mxml_node &_mxml_node::operator=(const _mxml_node &other) {
	if(this == &other)
		return *this;
	_mxml_element::operator=(other);
	_str = other._str;
	_nodes = other._nodes;
	_attributes = other._attributes;
	return *this;
}

void _mxml_node::add_attribute(mxml_attribute &attr) {
	_attributes.add_attribute(attr);
}

void _mxml_node::add_node(_mxml_node &nod) {
	_nodes.push_back(nod);
}

size_t _mxml_node::attribute_size(void) {
	return _attributes.size();
}

mxml_attribute &_mxml_node::get_attribute_at(size_t index) {
	return _attributes.get_attribute_at(index);
}

bool _mxml_node::get_attribute_by_name(const std::string &name, mxml_attribute &attr) {
	return _attributes.get_attribute_by_name(name, attr);
}

mxml_attribute_list &_mxml_node::get_attributes(void) {
	return _attributes;
}

_mxml_node &_mxml_node::get_node_at(size_t index) {
	return _nodes.at(index);
}

std::vector<_mxml_node> &_mxml_node::get_nodes(void) {
	return _nodes;
}

std::string &_mxml_node::get_string(void) {
	return _str;
}

bool _mxml_node::insert_attribute(mxml_attribute &attr, size_t index) {
	if(index > _attributes.size())
		return false;
	else if(index == _attributes.size())
		_attributes.add_attribute(attr);
	else
		return _attributes.insert_attribute(attr, index);
	return true;
}

bool _mxml_node::insert_node(_mxml_node &nod, size_t index) {
	if(index > _nodes.size())
		return false;
	else if(index == _nodes.size())
		_nodes.push_back(nod);
	else
		_nodes.insert(_nodes.begin() + index, nod);
	return true;
}

size_t _mxml_node::node_size(void) {
	return _nodes.size();
}

bool _mxml_node::remove_attribute(size_t index) {
	if(index >= _attributes.size())
		return false;
	return _attributes.remove_attribute(index);
}

bool _mxml_node::remove_node(size_t index) {
	if(index >= _nodes.size())
		return false;
	_nodes.erase(_nodes.begin() + index);
	return true;
}

void _mxml_node::set_string(const std::string &str) {
	_str = str;
}

std::string _mxml_node::to_string(size_t tab_index) {
	size_t i, j;
	std::stringstream ss;
	for(i = 0; i < tab_index; ++i)
		ss << "\t";
	ss << "<" << _mxml_element::to_string(0);
	if(!_attributes.is_empty())
		ss << " " << _attributes.to_string();
	if(_nodes.empty()
			&& _str.empty())
		ss << " />";
	else if(!_nodes.empty()
			&& !_str.empty())
		throw std::runtime_error(std::string("Node '" + _mxml_element::to_string(0) + "' contains both a string and a nested node"));
	else if(!_str.empty())
		ss << ">" << _str << "</" << _mxml_element::to_string(0) << ">";
	else {
		ss << ">" << std::endl;
		for(i = 0; i < _nodes.size(); ++i)
			ss << _nodes.at(i).to_string(tab_index + 1) << std::endl;
		for(j = 0; j < tab_index; ++j)
			ss << "\t";
		ss << "</" << _mxml_element::to_string(0) << ">";
	}
	return ss.str();
}
