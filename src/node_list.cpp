/*
 * node_list.cpp
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
#include "node_list.hpp"

using namespace __mxml;

_node_list::_node_list(void) {
	return;
}

_node_list::_node_list(const _node_list &other) :
		_nodes(other._nodes) {
	return;
}

_node_list::~_node_list(void) {
	return;
}

_node_list &_node_list::operator=(const _node_list &other) {
	if(this == &other)
		return *this;
	_nodes = other._nodes;
	return *this;
}

void _node_list::add_node(node &nod) {
	_nodes.push_back(nod);
}

node &_node_list::get_node_at(size_t index) {
	return _nodes.at(index);
}

std::vector<node> &_node_list::get_nodes(void) {
	return _nodes;
}

bool _node_list::insert_node(node &nod, size_t index) {
	if(index > _nodes.size())
		return false;
	else if(index == _nodes.size())
		_nodes.push_back(nod);
	else
		_nodes.insert(_nodes.begin() + index, nod);
	return true;
}

bool _node_list::is_empty(void) {
	return _nodes.empty();
}

bool _node_list::remove_node(size_t index) {
	if(index >= _nodes.size())
		return false;
	_nodes.erase(_nodes.begin() + index);
	return true;
}

size_t _node_list::size(void) {
	return _nodes.size();
}

std::string _node_list::to_string() {
	size_t i = 0;
	std::stringstream ss;
	for(; i < _nodes.size(); ++i)
		ss << _nodes.at(i).to_string(0) << std::endl;
	return ss.str();
}
