/*
 * lexer.cpp
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
#include "lexer.hpp"

using namespace __mxml;

const std::string _lexer::_COMMENT_STR[_COMMENT_COUNT] = { "!", "-", };
const std::set<std::string> _lexer::_COMMENT_SET(_COMMENT_STR, _COMMENT_STR + _COMMENT_COUNT);
const std::string _lexer::_SYMBOL_STR[_SYMBOL_COUNT] = { "<", ">", "</", "/>", "/", "\"", "=", };
const std::set<std::string> _lexer::_SYMBOL_SET(_SYMBOL_STR, _SYMBOL_STR + _SYMBOL_COUNT);

_lexer::_lexer(void) {
	reset();
}

_lexer::_lexer(const std::string &input, bool is_file) :
		_buff(input, is_file) {
	reset();
}

_lexer::_lexer(const _lexer &other) :
		_text(other._text), _type(other._type) {
	_buff.operator =(other._buff);
}

_lexer::~_lexer(void) {
	return;
}

_lexer &_lexer::operator=(const _lexer &other) {
	if(this == &other)
		return *this;
	_text = other._text;
	_type = other._type;
	_state = other._state;
	_buff.operator =(other._buff);
	return *this;
}

size_t _lexer::_comment_to_type(const std::string &input) {
	size_t i = 0;
	for(; i < _COMMENT_COUNT; ++i)
		if(_COMMENT_STR[i] == input)
			return i;
	return (size_t) -1;
}

size_t _lexer::_comment_to_type(void) {
	return _comment_to_type(_text);
}

bool _lexer::_is_comment(const std::string &input) {
	return _COMMENT_SET.find(input) != _COMMENT_SET.end();
}

bool _lexer::_is_comment(void) {
	return _is_comment(_text);
}

bool _lexer::_is_comment(size_t type) {
	return _comment_to_type() == type;
}

bool _lexer::_read_type(size_t type) {
	size_t tp;
	char ch = _buff.current();
	_text += ch;
	tp = symbol_to_type(std::string(1, ch));
	switch(type) {
		case TYPE_IDENTIFIER:
			while(!isspace(ch)
					&& tp != SYMBOL_TYPE_QUOTE
					&& tp != SYMBOL_TYPE_ASSIGNMENT
					&& tp != SYMBOL_TYPE_CLOSE_BRACKET) {
				if(!_buff.has_next())
					break;
				ch = _buff.next();
				_text += ch;
				tp = symbol_to_type(std::string(1, ch));
			}
			break;
		case TYPE_STRING:
			while(tp != SYMBOL_TYPE_QUOTE
					&& tp != SYMBOL_TYPE_OPEN_BRACKET) {
				if(!_buff.has_next())
					break;
				ch = _buff.next();
				_text += ch;
				tp = symbol_to_type(std::string(1, ch));
			}
			break;
		default: return false;
	}
	if(_buff.has_previous()) {
		ch = _buff.previous();
		_text = _text.substr(0, _text.size() - 1);
	}
	return true;
}

void _lexer::_skip_whitespace(void) {
	size_t i, depth = 0;
	while(_buff.has_next()) {
		if(symbol_to_type(std::string(1, _buff.current())) == SYMBOL_TYPE_OPEN_BRACKET) {
			if(_comment_to_type(std::string(1, _buff.peek())) == _COMMENT_TYPE_BANG)
				if(_buff.has_next()) {
					_buff.next();
					++depth;
					for(i = 0; i < 2; ++i)
						if(_comment_to_type(std::string(1, _buff.peek())) == _COMMENT_TYPE_HYPHEN) {
							if(_buff.has_next()) {
								_buff.next();
								++depth;
							} else {
								_unskip_whitespace(depth);
								return;
							}
						} else {
							_unskip_whitespace(depth);
							return;
						}
					_skip_whitespace_end();
					_skip_whitespace();
					return;
				} else
					return;
			else
				return;
		} else if(!_buff.is_whitespace())
			return;
		_buff.next();
	}
}

void _lexer::_skip_whitespace_end(void) {
	while(_buff.has_next()) {
		if(_comment_to_type(std::string(1, _buff.current())) == _COMMENT_TYPE_HYPHEN) {
			if(_buff.has_next()) {
				_buff.next();
				if(_comment_to_type(std::string(1, _buff.current())) == _COMMENT_TYPE_HYPHEN) {
					if(_buff.has_next()) {
						_buff.next();
						if(symbol_to_type(std::string(1, _buff.current())) == SYMBOL_TYPE_CLOSE_BRACKET) {
							_buff.next();
							return;
						} else
							continue;
					} else
						return;
				} else
					continue;
			} else
				return;
		}
		_buff.next();
	}
}

void _lexer::_unskip_whitespace(size_t depth) {
	size_t i = 0;
	for(; i < depth; ++i) {
		if(!_buff.has_previous())
			return;
		_buff.previous();
	}
}

pb_buffer &_lexer::get_buffer(void) {
	return _buff;
}

std::string _lexer::get_text(void) {
	return _text;
}

size_t _lexer::get_type(void) {
	return _type;
}

bool _lexer::has_next(void) {
	return _type != TYPE_END;
}

bool _lexer::is_identifier(void) {
	return _type == TYPE_IDENTIFIER;
}

bool _lexer::is_string(void) {
	return _type == TYPE_STRING;
}

bool _lexer::is_symbol(const std::string &input) {
	return _SYMBOL_SET.find(input) != _SYMBOL_SET.end();
}

bool _lexer::is_symbol(void) {
	return is_symbol(_text);
}

bool _lexer::is_symbol(size_t type) {
	return symbol_to_type() == type;
}

bool _lexer::next(void) {
	char ch;
	size_t type;
	_text.clear();
	if(!_buff.has_next()) {
		_type = TYPE_END;
		return false;
	}
	if(_init)
		_skip_whitespace();
	ch = _buff.current();
	if(ch == pb_buffer::_EOS)
		return false;
	if(is_symbol(std::string(1, ch))) {
		type = symbol_to_type(std::string(1, ch));
		if(!_init
				&& (type == SYMBOL_TYPE_QUOTE
						|| type == SYMBOL_TYPE_OPEN_BRACKET
						|| type == SYMBOL_TYPE_CLOSE_BRACKET))
			_state = !_state;
		_type = TYPE_SYMBOL;
		_text += ch;
		type = symbol_to_type();
		if(type == SYMBOL_TYPE_OPEN_BRACKET
				|| type == SYMBOL_TYPE_TERMINATOR)
			if(_buff.has_next()) {
				ch = _buff.next();
				_text += ch;
				if(!is_symbol()) {
					_text = _text.substr(0, _text.size() - 1);
					_buff.previous();
					type = symbol_to_type();
					if(type == SYMBOL_TYPE_OPEN_BRACKET)
						_state = _STATE_IDENTIFIER;
				} else
					_state = _STATE_IDENTIFIER;
			}
	} else {
		switch(_state) {
			case _STATE_IDENTIFIER: _type = TYPE_IDENTIFIER;
				break;
			case _STATE_STRING: _type = TYPE_STRING;
				break;
			default: _type = TYPE_END;
				return false;
		}
		_read_type(_type);
	}
	_init = false;
	_buff.next();
	_skip_whitespace();
	return true;
}

void _lexer::reset(void) {
	_init = true;
	_text.clear();
	_type = TYPE_BEGIN;
	_state = _STATE_IDENTIFIER;
	_buff.reset();
}

size_t _lexer::symbol_to_type(const std::string &input) {
	size_t i = 0;
	for(; i < _SYMBOL_COUNT; ++i)
		if(_SYMBOL_STR[i] == input)
			return i;
	return (size_t) -1;
}

size_t _lexer::symbol_to_type(void) {
	return symbol_to_type(_text);
}

std::string _lexer::to_string(void) {
	std::stringstream ss;
	ss << "[" << type_to_string(_type) << "]";
	if(!_text.empty())
		ss << " " << _text;
	return ss.str();
}

std::string _lexer::type_to_string(size_t type) {
	std::string output;
	switch(type) {
		case TYPE_BEGIN: output = "BEGIN";
			break;
		case TYPE_END: output = "END";
			break;
		case TYPE_IDENTIFIER: output = "IDENTIFIER";
			break;
		case TYPE_STRING: output = "STRING";
			break;
		case TYPE_SYMBOL: output = "SYMBOL";
			break;
		default: output = "UNKNOWN";
			break;
	}
	return output;
}
