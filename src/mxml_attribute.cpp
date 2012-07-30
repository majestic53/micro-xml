/*
 * mxml_attribute.cpp
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
#include "mxml_attribute.hpp"

using namespace __mxml;

_mxml_attribute::_mxml_attribute(void) :
		_mxml_element(TYPE_ATTRIBUTE) {
	return;
}

_mxml_attribute::_mxml_attribute(const std::string &name, const std::string &value) :
		_mxml_element(name, TYPE_ATTRIBUTE), _value(value) {
	return;
}

_mxml_attribute::_mxml_attribute(const _mxml_attribute &other) :
		_mxml_element(other._name, TYPE_ATTRIBUTE), _value(other._value) {
	return;
}

_mxml_attribute::~_mxml_attribute(void) {
	return;
}

_mxml_attribute &_mxml_attribute::operator=(const _mxml_attribute &other) {
	if(this == &other)
		return *this;
	_mxml_element::operator=(other);
	_value = other._value;
	return *this;
}

bool _mxml_attribute::operator==(const _mxml_attribute &other) {
	if(this == &other)
		return true;
	return _mxml_element::operator==(other)
			&& _value == other._value;
}

std::string &_mxml_attribute::get_value(void) {
	return _value;
}

void _mxml_attribute::set_value(const std::string &value) {
	_value = value;
}

std::string _mxml_attribute::to_string(size_t tab_index) {
	std::stringstream ss;
	ss << _name << "=\"" << _value << "\"";
	return ss.str();
}
