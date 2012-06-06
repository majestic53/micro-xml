/*
 * node.cpp
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
#include "node.hpp"

using namespace __mxml;

_node::_node(void) :
		_element(TYPE_NODE) {
	return;
}

_node::_node(const std::string &name) :
		_element(name, TYPE_NODE) {
	return;
}

_node::_node(const _node &other) :
		_element(other._name, TYPE_NODE), _str(other._str), _nodes(other._nodes), _attributes(other._attributes) {
	return;
}

_node::~_node(void) {
	return;
}

_node &_node::operator=(const _node &other) {
	if(this == &other)
		return *this;
	_element::operator=(other);
	_str = other._str;
	_nodes = other._nodes;
	_attributes = other._attributes;
	return *this;
}

void _node::add_attribute(attribute &attr) {
	_attributes.add_attribute(attr);
}

void _node::add_node(node &nod) {
	_nodes.push_back(nod);
}

size_t _node::attribute_size(void) {
	return _attributes.size();
}

attribute &_node::get_attribute_at(size_t index) {
	return _attributes.get_attribute_at(index);
}

attribute_list &_node::get_attributes(void) {
	return _attributes;
}

_node &_node::get_node_at(size_t index) {
	return _nodes.at(index);
}

std::vector<_node> &_node::get_nodes(void) {
	return _nodes;
}

std::string &_node::get_string(void) {
	return _str;
}

bool _node::insert_attribute(attribute &attr, size_t index) {
	if(index > _attributes.size())
		return false;
	else if(index == _attributes.size())
		_attributes.add_attribute(attr);
	else
		return _attributes.insert_attribute(attr, index);
	return true;
}

bool _node::insert_node(_node &nod, size_t index) {
	if(index > _nodes.size())
		return false;
	else if(index == _nodes.size())
		_nodes.push_back(nod);
	else
		_nodes.insert(_nodes.begin() + index, nod);
	return true;
}

size_t _node::node_size(void) {
	return _nodes.size();
}

bool _node::remove_attribute(size_t index) {
	if(index >= _attributes.size())
		return false;
	return _attributes.remove_attribute(index);
}

bool _node::remove_node(size_t index) {
	if(index >= _nodes.size())
		return false;
	_nodes.erase(_nodes.begin() + index);
	return true;
}

void _node::set_string(const std::string &str) {
	_str = str;
}

std::string _node::to_string(size_t tab_index) {
	size_t i, j;
	std::stringstream ss;
	for(i = 0; i < tab_index; ++i)
		ss << "\t";
	ss << "<" << _element::to_string(0);
	if(!_attributes.is_empty())
		ss << " " << _attributes.to_string();
	if(_nodes.empty()
			&& _str.empty())
		ss << " />";
	else if(!_str.empty())
		ss << ">" << _str << "</" << _element::to_string(0) << ">";
	else {
		ss << ">" << std::endl;
		for(i = 0; i < _nodes.size(); ++i)
			ss << _nodes.at(i).to_string(tab_index + 1) << std::endl;
		for(j = 0; j < tab_index; ++j)
			ss << "\t";
		ss << "</" << _element::to_string(0) << ">";
	}
	return ss.str();
}
