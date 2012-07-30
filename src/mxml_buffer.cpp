/*
 * mxml_buffer.cpp
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
#include "mxml_buffer.hpp"

using namespace __mxml;

_mxml_buffer::_mxml_buffer(void) {
	reset();
}

_mxml_buffer::_mxml_buffer(const std::string &input, bool is_file) {
	std::stringstream ss;
	if(is_file) {
		std::ifstream file(input.c_str(), std::ios::in);
		if(!file)
			throw std::runtime_error(std::string(input + " (file not found)"));
		ss << std::noskipws << file.rdbuf();
		_buff = ss.str();
		file.close();
	} else
		_buff = input;
	reset();
}

_mxml_buffer::_mxml_buffer(const _mxml_buffer &other) :
		_ch(other._ch), _line(other._line), _pos(other._pos), _buff(other._buff) {
	return;
}

_mxml_buffer::~_mxml_buffer(void) {
	return;
}

_mxml_buffer &_mxml_buffer::operator=(const _mxml_buffer &other) {
	if(this == &other)
		return *this;
	_ch = other._ch;
	_line = other._line;
	_pos = other._pos;
	_buff = other._buff;
	return *this;
}

char _mxml_buffer::current(void) {
	if(_pos >= _buff.size())
		return _EOS;
	return _buff.at(_pos);
}

std::string &_mxml_buffer::get_buffer(void) {
	return _buff;
}

size_t _mxml_buffer::get_line(void) {
	return _line;
}

bool _mxml_buffer::has_next(void) {
	return _pos < _buff.size();
}

bool _mxml_buffer::has_previous(void) {
	return _pos > 0;
}

bool _mxml_buffer::is_whitespace(void) {
	return isspace(_ch) > 0;
}

char _mxml_buffer::next(void) {
	++_pos;
	_ch = current();
	if(_ch == _NL)
		++_line;
	return _ch;
}

char _mxml_buffer::peek(void) {
	if(_pos + 1 >= _buff.size())
		return _EOS;
	return _buff.at(_pos + 1);
}

char _mxml_buffer::previous(void) {
	--_pos;
	_ch = current();
	if(_ch == _NL)
		--_line;
	return _ch;
}

void _mxml_buffer::reset(void) {
	_line = 1;
	_pos = 0;
	if(_buff.empty())
		_ch = _EOS;
	else
		_ch = current();
}

size_t _mxml_buffer::size(void) {
	return _buff.size();
}

std::string _mxml_buffer::to_string(void) {
	std::stringstream ss;
	ss << _line << " [" << _pos << "]: ";
	ss << (isspace(_ch) ? "(WS)" :
			((_ch == _EOS) ? "(EOS)" :
					std::string(1, _ch)));
	return ss.str();
}
