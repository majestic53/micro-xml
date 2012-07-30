/*
 * mxml_attribute_list.cpp
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
#include "mxml_attribute_list.hpp"

using namespace __mxml;

_mxml_attribute_list::_mxml_attribute_list(void) {
	return;
}

_mxml_attribute_list::_mxml_attribute_list(const _mxml_attribute_list &other) :
		_lst(other._lst) {
	return;
}

_mxml_attribute_list::~_mxml_attribute_list(void) {
	return;
}

_mxml_attribute_list &_mxml_attribute_list::operator=(const _mxml_attribute_list &other) {
	if(this == &other)
		return *this;
	_lst = other._lst;
	return *this;
}

void _mxml_attribute_list::add_attribute(mxml_attribute &attr) {
	_lst.push_back(attr);
}

void _mxml_attribute_list::clear(void) {
	_lst.clear();
}

bool _mxml_attribute_list::contains(const std::string &name) {
	size_t i = 0;
	for(; i < _lst.size(); ++i)
		if(_lst.at(i).get_name() == name)
			return true;
	return false;
}

bool _mxml_attribute_list::contains(mxml_attribute &attr) {
	size_t i = 0;
	for(; i < _lst.size(); ++i)
		if(_lst.at(i) == attr)
			return true;
	return false;
}

mxml_attribute &_mxml_attribute_list::get_attribute_at(size_t index) {
	return _lst.at(index);
}

bool _mxml_attribute_list::get_attribute_by_name(const std::string &name, mxml_attribute &attr) {
	size_t i = 0;
	for(; i < _lst.size(); ++i)
		if(_lst.at(i).get_name() == name) {
			attr = _lst.at(i);
			return true;
		}
	return false;
}

std::vector<mxml_attribute> &_mxml_attribute_list::get_attributes(void) {
	return _lst;
}

bool _mxml_attribute_list::insert_attribute(mxml_attribute &attr, size_t index) {
	if(index > _lst.size())
		return false;
	else if(index == _lst.size())
		_lst.push_back(attr);
	else
		_lst.insert(_lst.begin() + index, attr);
	return true;
}

bool _mxml_attribute_list::is_empty(void) {
	return _lst.empty();
}

bool _mxml_attribute_list::remove_attribute(size_t index) {
	if(index >= _lst.size())
		return false;
	_lst.erase(_lst.begin() + index);
	return true;
}

size_t _mxml_attribute_list::size(void) {
	return _lst.size();
}

std::string _mxml_attribute_list::to_string(void) {
	size_t i = 0;
	std::stringstream ss;
	for(; i < _lst.size() - 1; ++i)
		ss << _lst.at(i).to_string(0) << " ";
	ss << _lst.at(i).to_string(0);
	return ss.str();
}
