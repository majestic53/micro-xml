/*
 * mxml_element.cpp
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
#include "mxml_element.hpp"

using namespace __mxml;

_mxml_element::_mxml_element(void) :
		_type(TYPE_GENERIC) {
	return;
}

_mxml_element::_mxml_element(size_t type) :
		_type(type) {
	return;
}

_mxml_element::_mxml_element(const std::string &name, size_t type) :
		 _type(type), _name(name) {
	return;
}

_mxml_element::_mxml_element(const _mxml_element &other) :
		_type(other._type), _name(other._name) {
	return;
}

_mxml_element::~_mxml_element(void) {
	return;
}

_mxml_element &_mxml_element::operator=(const _mxml_element &other) {
	if(this == &other)
		return *this;
	_type = other._type;
	_name = other._name;
	return *this;
}

bool _mxml_element::operator==(const _mxml_element &other) {
	if(this == &other)
		return true;
	return _type == other._type
			&& _name == other._name;
}

std::string &_mxml_element::get_name(void) {
	return _name;
}

size_t _mxml_element::get_type(void) {
	return _type;
}

void _mxml_element::set_name(std::string &name) {
	_name = name;
}

void _mxml_element::set_type(size_t type) {
	_type = type;
}

std::string _mxml_element::to_string(size_t tab_index) {
	size_t i = 0;
	std::stringstream ss;
	for(; i < tab_index; ++i)
		ss << "\t";
	ss << _name;
	return ss.str();
}

std::string _mxml_element::type_to_string(size_t type) {
	std::string output;
	switch(type) {
		case TYPE_GENERIC: output = "GENERIC";
			break;
		case TYPE_ATTRIBUTE: output = "ATTRIBUTE";
			break;
		case TYPE_NODE: output = "NODE";
			break;
		default: output = "UNKNOWN";
			break;
	}
	return output;
}
