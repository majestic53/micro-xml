/*
 * pb_buff.cpp
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
#include "pb_buff.hpp"

using namespace __mxml;

_pb_buffer::_pb_buffer(void) {
	reset();
}

_pb_buffer::_pb_buffer(const std::string &input, bool is_file) {
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

_pb_buffer::_pb_buffer(const _pb_buffer &other) :
		_ch(other._ch), _line(other._line), _pos(other._pos), _buff(other._buff) {
	return;
}

_pb_buffer::~_pb_buffer(void) {
	return;
}

_pb_buffer &_pb_buffer::operator=(const _pb_buffer &other) {
	if(this == &other)
		return *this;
	_ch = other._ch;
	_line = other._line;
	_pos = other._pos;
	_buff = other._buff;
	return *this;
}

char _pb_buffer::current(void) {
	if(_pos >= _buff.size())
		return _EOS;
	return _buff.at(_pos);
}

std::string &_pb_buffer::get_buffer(void) {
	return _buff;
}

size_t _pb_buffer::get_line(void) {
	return _line;
}

bool _pb_buffer::has_next(void) {
	return _pos < _buff.size();
}

bool _pb_buffer::has_previous(void) {
	return _pos;
}

bool _pb_buffer::is_whitespace(void) {
	return isspace(_ch);
}

char _pb_buffer::next(void) {
	++_pos;
	_ch = current();
	if(_ch == _NL)
		++_line;
	return _ch;
}

char _pb_buffer::peek(void) {
	if(_pos + 1 >= _buff.size())
		return _EOS;
	return _buff.at(_pos + 1);
}

char _pb_buffer::previous(void) {
	--_pos;
	_ch = current();
	if(_ch == _NL)
		--_line;
	return _ch;
}

void _pb_buffer::reset(void) {
	_line = 1;
	_pos = 0;
	if(_buff.empty())
		_ch = _EOS;
	else
		_ch = current();
}

size_t _pb_buffer::size(void) {
	return _buff.size();
}

std::string _pb_buffer::to_string(void) {
	std::stringstream ss;
	ss << _line << " [" << _pos << "]: ";
	ss << (isspace(_ch) ? "(WS)" :
			((_ch == _EOS) ? "(EOS)" :
					std::string(1, _ch)));
	return ss.str();
}
