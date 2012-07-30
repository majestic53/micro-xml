/*
 * mxml_node_list.cpp
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
#include "mxml_node_list.hpp"

using namespace __mxml;

_mxml_node_list::_mxml_node_list(void) {
	return;
}

_mxml_node_list::_mxml_node_list(const _mxml_node_list &other) :
		_lst(other._lst) {
	return;
}

_mxml_node_list::~_mxml_node_list(void) {
	return;
}

_mxml_node_list &_mxml_node_list::operator=(const _mxml_node_list &other) {
	if(this == &other)
		return *this;
	_lst = other._lst;
	return *this;
}

void _mxml_node_list::_get_nodes_by_name_helper(const std::string &name, mxml_node &nod, _mxml_node_list &nod_lst) {
	size_t i = 0;
	if(nod.get_name() == name)
		nod_lst.add_node(nod);
	for(; i < nod.node_size(); ++i)
		_get_nodes_by_name_helper(name, nod.get_node_at(i), nod_lst);
}

void _mxml_node_list::add_node(mxml_node &nod) {
	_lst.push_back(nod);
}

void _mxml_node_list::clear(void) {
	_lst.clear();
}

mxml_node &_mxml_node_list::get_node_at(size_t index) {
	return _lst.at(index);
}

std::vector<mxml_node> &_mxml_node_list::get_nodes(void) {
	return _lst;
}

size_t _mxml_node_list::get_nodes_by_name(const std::string &name, mxml_node &nod, _mxml_node_list &nod_lst) {
	nod_lst.clear();
	_get_nodes_by_name_helper(name, nod, nod_lst);
	return nod_lst.size();
}

bool _mxml_node_list::insert_node(mxml_node &nod, size_t index) {
	if(index > _lst.size())
		return false;
	else if(index == _lst.size())
		_lst.push_back(nod);
	else
		_lst.insert(_lst.begin() + index, nod);
	return true;
}

bool _mxml_node_list::is_empty(void) {
	return _lst.empty();
}

bool _mxml_node_list::remove_node(size_t index) {
	if(index >= _lst.size())
		return false;
	_lst.erase(_lst.begin() + index);
	return true;
}

size_t _mxml_node_list::size(void) {
	return _lst.size();
}

std::string _mxml_node_list::to_string() {
	size_t i = 0;
	std::stringstream ss;
	for(; i < _lst.size(); ++i)
		ss << _lst.at(i).to_string(0) << std::endl;
	return ss.str();
}
