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
		_attributes(other._attributes) {
	return;
}

_attribute_list::~_attribute_list(void) {
	return;
}

_attribute_list &_attribute_list::operator=(const _attribute_list &other) {
	if(this == &other)
		return *this;
	_attributes = other._attributes;
	return *this;
}

void _attribute_list::add_attribute(attribute &attr) {
	_attributes.push_back(attr);
}

attribute &_attribute_list::get_attribute_at(size_t index) {
	return _attributes.at(index);
}

std::vector<attribute> &_attribute_list::get_attributes(void) {
	return _attributes;
}

bool _attribute_list::insert_attribute(attribute &attr, size_t index) {
	if(index > _attributes.size())
		return false;
	else if(index == _attributes.size())
		_attributes.push_back(attr);
	else
		_attributes.insert(_attributes.begin() + index, attr);
	return true;
}

bool _attribute_list::is_empty(void) {
	return _attributes.empty();
}

bool _attribute_list::remove_attribute(size_t index) {
	if(index >= _attributes.size())
		return false;
	_attributes.erase(_attributes.begin() + index);
	return true;
}

size_t _attribute_list::size(void) {
	return _attributes.size();
}

std::string _attribute_list::to_string(void) {
	size_t i = 0;
	std::stringstream ss;
	for(; i < _attributes.size() - 1; ++i)
		ss << _attributes.at(i).to_string(0) << " ";
	ss << _attributes.at(i).to_string(0);
	return ss.str();
}
