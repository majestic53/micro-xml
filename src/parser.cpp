/*
 * parser.cpp
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
#include "parser.hpp"

using namespace __mxml;

const std::string _parser::_EXCEPTION_MESSAGE[_EXCEPTION_COUNT] = {
		"Success",
		"Expecting identifier",
		"Expecting assignment after declaration",
		"Expecting node open bracket",
		"Expecting node close bracket",
		"Expecting node terminator",
		"Expecting string value",
		"Expecting open quote after assignment",
		"Expecting close quote after string value",
};

_parser::_parser(void) {
	return;
}

_parser::_parser(const std::string &input, bool is_file) :
		_lex(input, is_file) {
	return;
}

_parser::_parser(const _parser &other) :
		_lex(other._lex) {
	return;
}

_parser::~_parser(void) {
	return;
}

_parser &_parser::operator=(const _parser &other) {
	if(this == &other)
		return *this;
	_lex = other._lex;
	return *this;
}

void _parser::_attribute(void) {
	if(!_lex.is_identifier())
		throw std::runtime_error(_format_exception(_lex, _EXCEPTION_EXPECTING_IDENTIFIER));
	_lex.next();
	if(!_lex.is_symbol(_lexer::SYMBOL_TYPE_ASSIGNMENT))
		throw std::runtime_error(_format_exception(_lex, _EXCEPTION_EXPECTING_ASSIGNMENT));
	_lex.next();
	if(!_lex.is_symbol(_lexer::SYMBOL_TYPE_QUOTE))
		throw std::runtime_error(_format_exception(_lex, _EXCEPTION_EXPECTING_STRING_OPEN_QUOTE));
	_lex.next();
	if(!_lex.is_string())
		throw std::runtime_error(_format_exception(_lex, _EXCEPTION_EXPECTING_STRING));
	_lex.next();
	if(!_lex.is_symbol(_lexer::SYMBOL_TYPE_QUOTE))
		throw std::runtime_error(_format_exception(_lex, _EXCEPTION_EXPECTING_STRING_CLOSE_QUOTE));
	_lex.next();
}

void _parser::_attribute_list(void) {
	if(!_lex.is_identifier())
		return;
	_attribute();
	_attribute_list();
}

std::string _parser::_format_exception(_lexer &lex, size_t exc) {
	std::stringstream ss;
	ss << "[ln. " << lex.get_buffer().get_line() << "], \"" << lex.get_text() << "\": " << _EXCEPTION_MESSAGE[exc];
	return ss.str();
}

void _parser::_parse(node &nod) {

	// TODO: Incorporate the generation of the root node in the parsing process

	while(_lex.has_next()) {
		_lex.next();
		_node();
	}
}

void _parser::_node(void) {
	if(!_lex.is_symbol(_lexer::SYMBOL_TYPE_OPEN_BRACKET))
		throw std::runtime_error(_format_exception(_lex, _EXCEPTION_EXPECTING_OPEN_BRACKET));
	_lex.next();
	if(!_lex.is_identifier())
		throw std::runtime_error(_format_exception(_lex, _EXCEPTION_EXPECTING_IDENTIFIER));
	_lex.next();
	_attribute_list();
	_node_end();
}

void _parser::_node_end(void) {
	if(_lex.is_symbol(_lexer::SYMBOL_TYPE_CLOSE_BRACKET_TERM))
		_lex.next();
	else if(_lex.is_symbol(_lexer::SYMBOL_TYPE_CLOSE_BRACKET)) {
		_lex.next();
		if(_lex.is_symbol(_lexer::SYMBOL_TYPE_OPEN_BRACKET))
			_node_list();
		else if(_lex.is_string())
				_lex.next();
		if(!_lex.is_symbol(_lexer::SYMBOL_TYPE_OPEN_BRACKET_TERM))
			throw std::runtime_error(_format_exception(_lex, _EXCEPTION_EXPECTING_TERMINATOR));
		_lex.next();
		if(!_lex.is_identifier())
			throw std::runtime_error(_format_exception(_lex, _EXCEPTION_EXPECTING_IDENTIFIER));
		_lex.next();
		if(!_lex.is_symbol(_lexer::SYMBOL_TYPE_CLOSE_BRACKET))
			throw std::runtime_error(_format_exception(_lex, _EXCEPTION_EXPECTING_CLOSE_BRACKET));
		_lex.next();
	} else
		throw std::runtime_error(_format_exception(_lex, _EXCEPTION_EXPECTING_CLOSE_BRACKET));
}

void _parser::_node_list(void) {
	if(!_lex.is_symbol(_lexer::SYMBOL_TYPE_OPEN_BRACKET))
		return;
	_node();
	_node_list();
}

lexer &_parser::get_lexer(void) {
	return _lex;
}

std::string _parser::to_string(void) {
	return _lex.to_string();
}
