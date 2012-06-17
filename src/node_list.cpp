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
		_lst(other._lst) {
	return;
}

_node_list::~_node_list(void) {
	return;
}

_node_list &_node_list::operator=(const _node_list &other) {
	if(this == &other)
		return *this;
	_lst = other._lst;
	return *this;
}

void _node_list::_get_nodes_by_name_helper(const std::string &name, node &nod, _node_list &nod_lst) {
	size_t i = 0;
	if(nod.get_name() == name)
		nod_lst.add_node(nod);
	for(; i < nod.node_size(); ++i)
		_get_nodes_by_name_helper(name, nod.get_node_at(i), nod_lst);
}

void _node_list::add_node(node &nod) {
	_lst.push_back(nod);
}

void _node_list::clear(void) {
	_lst.clear();
}

node &_node_list::get_node_at(size_t index) {
	return _lst.at(index);
}

std::vector<node> &_node_list::get_nodes(void) {
	return _lst;
}

size_t _node_list::get_nodes_by_name(const std::string &name, node &nod, _node_list &nod_lst) {
	_get_nodes_by_name_helper(name, nod, nod_lst);
	return nod_lst.size();
}

bool _node_list::insert_node(node &nod, size_t index) {
	if(index > _lst.size())
		return false;
	else if(index == _lst.size())
		_lst.push_back(nod);
	else
		_lst.insert(_lst.begin() + index, nod);
	return true;
}

bool _node_list::is_empty(void) {
	return _lst.empty();
}

bool _node_list::remove_node(size_t index) {
	if(index >= _lst.size())
		return false;
	_lst.erase(_lst.begin() + index);
	return true;
}

size_t _node_list::size(void) {
	return _lst.size();
}

std::string _node_list::to_string() {
	size_t i = 0;
	std::stringstream ss;
	for(; i < _lst.size(); ++i)
		ss << _lst.at(i).to_string(0) << std::endl;
	return ss.str();
}
