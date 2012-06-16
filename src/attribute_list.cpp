/*
 * attribute_list.cpp
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
#include "attribute_list.hpp"

using namespace __mxml;

_attribute_list::_attribute_list(void) {
	return;
}

_attribute_list::_attribute_list(const _attribute_list &other) :
		_lst(other._lst) {
	return;
}

_attribute_list::~_attribute_list(void) {
	return;
}

_attribute_list &_attribute_list::operator=(const _attribute_list &other) {
	if(this == &other)
		return *this;
	_lst = other._lst;
	return *this;
}

void _attribute_list::add_attribute(attribute &attr) {
	_lst.push_back(attr);
}

bool _attribute_list::contains(const std::string &name) {
	size_t i = 0;
	for(; i < _lst.size(); ++i)
		if(_lst.at(i).get_name() == name)
			return true;
	return false;
}

bool _attribute_list::contains(attribute &attr) {
	size_t i = 0;
	for(; i < _lst.size(); ++i)
		if(_lst.at(i) == attr)
			return true;
	return false;
}

attribute &_attribute_list::get_attribute_at(size_t index) {
	return _lst.at(index);
}

std::vector<attribute> &_attribute_list::get_attributes(void) {
	return _lst;
}

bool _attribute_list::insert_attribute(attribute &attr, size_t index) {
	if(index > _lst.size())
		return false;
	else if(index == _lst.size())
		_lst.push_back(attr);
	else
		_lst.insert(_lst.begin() + index, attr);
	return true;
}

bool _attribute_list::is_empty(void) {
	return _lst.empty();
}

bool _attribute_list::remove_attribute(size_t index) {
	if(index >= _lst.size())
		return false;
	_lst.erase(_lst.begin() + index);
	return true;
}

size_t _attribute_list::size(void) {
	return _lst.size();
}

std::string _attribute_list::to_string(void) {
	size_t i = 0;
	std::stringstream ss;
	for(; i < _lst.size() - 1; ++i)
		ss << _lst.at(i).to_string(0) << " ";
	ss << _lst.at(i).to_string(0);
	return ss.str();
}
