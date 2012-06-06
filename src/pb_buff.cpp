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

#include <stdexcept>
#include "pb_buff.hpp"

using namespace __mxml;

_pb_buffer::_pb_buffer(void) {
	_line = 1;
	_pos = 0;
}

_pb_buffer::_pb_buffer(const std::string &input, bool is_file) {
	if(is_file) {
		std::ifstream file(input.c_str(), std::ios::in);
		if(!file)
			throw std::runtime_error(std::string(input + " (file not found)"));
		_buff << std::noskipws << file.rdbuf();
		file.close();
	} else
		_buff << std::noskipws << input;
	reset();
}

_pb_buffer::_pb_buffer(const _pb_buffer &other) :
		_line(other._line), _pos(other._pos) {
	_buff << std::noskipws << other._buff.rdbuf();
	_buff.seekg(_pos, std::ios::beg);
}

_pb_buffer::~_pb_buffer(void) {
	return;
}

_pb_buffer &_pb_buffer::operator=(const _pb_buffer &other) {
	if(this == &other)
		return *this;
	_line = other._line;
	_pos = other._pos;
	_buff << std::noskipws << other._buff.rdbuf();
	_buff.seekg(_pos, std::ios::beg);
	return *this;
}

size_t _pb_buffer::_size_helper(std::stringstream &buff) {
	size_t len, off = buff.tellg();
	buff.seekg(0, std::ios::end);
	len = buff.tellg();
	buff.seekg(off, std::ios::beg);
	return len;
}

char _pb_buffer::current(void) {
	return _ch;
}

std::stringstream &_pb_buffer::get_buffer(void) {
	return _buff;
}

size_t _pb_buffer::get_line(void) {
	return _line;
}

bool _pb_buffer::has_next(void) {
	return _buff.good();
}

bool _pb_buffer::has_previous(void) {
	return _pos;
}

bool _pb_buffer::is_whitespace(void) {
	return isspace(_ch)
			|| _ch == _EOS;
}

char _pb_buffer::next(void) {
	if(!_buff.good())
		return _EOS;
	_ch = (char) _buff.get();
	if(_ch == _NL)
		++_line;
	++_pos;
	return _ch;
}

char _pb_buffer::peek(void) {
	return _buff.peek();
}

char _pb_buffer::previous(void) {
	if(!_pos)
		return _EOS;
	else if(!_buff.good())
		_buff.clear();
	_buff.seekg(-1, std::ios::cur);
	_ch = (char) _buff.peek();
	if(_ch == _NL)
		--_line;
	--_pos;
	return _ch;
}

void _pb_buffer::reset(void) {
	_line = 1;
	_pos = 0;
	_buff.clear();
	_buff.seekg(0, std::ios::beg);
	_ch = _EOS;
}

size_t _pb_buffer::size(void) {
	return _size_helper(_buff) + 1;
}

std::string _pb_buffer::to_string(void) {
	int ch;
	std::stringstream ss;
	ss << _line << " [" << _pos << "]: ";
	ch = _buff.peek();
	ss << (isspace(ch) ? "(WS)" :
			((ch == _EOS) ? "(EOS)" :
					std::string(1, ch)));
	return ss.str();
}
