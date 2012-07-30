/*
 * mxml_parser.cpp
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
#include "mxml_parser.hpp"

using namespace __mxml;

const std::string _mxml_parser::_EXCEPTION_MESSAGE[_EXCEPTION_COUNT] = {
		"Success",
		"Expecting identifier",
		"Expecting assignment after declaration",
		"Expecting node open bracket",
		"Expecting node close bracket",
		"Expecting node terminator",
		"Expecting string value",
		"Expecting open quote after assignment",
		"Expecting close quote after string value",
		"Node name and terminator must match",
		"Node attributes must be unique",
};

_mxml_parser::_mxml_parser(void) {
	return;
}

_mxml_parser::_mxml_parser(const std::string &input, bool is_file) :
		_lex(input, is_file) {
	return;
}

_mxml_parser::_mxml_parser(const _mxml_parser &other) :
		_lex(other._lex) {
	return;
}

_mxml_parser::~_mxml_parser(void) {
	return;
}

_mxml_parser &_mxml_parser::operator=(const _mxml_parser &other) {
	if(this == &other)
		return *this;
	_lex = other._lex;
	return *this;
}

void _mxml_parser::_attribute(_mxml_attribute_list &attr_lst) {
	_mxml_attribute attr;
	if(!_lex.is_identifier())
		throw std::runtime_error(_format_exception(_lex, _EXCEPTION_EXPECTING_IDENTIFIER));
	if(attr_lst.contains(_lex.get_text()))
		throw std::runtime_error(_format_exception(_lex, _EXCEPTION_EXPECTING_UNIQUE_ATTRIBUTE));
	attr.set_name(_lex.get_text());
	_lex.next();
	if(!_lex.is_symbol(_mxml_lexer::SYMBOL_TYPE_ASSIGNMENT))
		throw std::runtime_error(_format_exception(_lex, _EXCEPTION_EXPECTING_ASSIGNMENT));
	_lex.next();
	if(!_lex.is_symbol(_mxml_lexer::SYMBOL_TYPE_QUOTE))
		throw std::runtime_error(_format_exception(_lex, _EXCEPTION_EXPECTING_STRING_OPEN_QUOTE));
	_lex.next();
	if(!_lex.is_string())
		throw std::runtime_error(_format_exception(_lex, _EXCEPTION_EXPECTING_STRING));
	attr.set_value(_lex.get_text());
	_lex.next();
	if(!_lex.is_symbol(_mxml_lexer::SYMBOL_TYPE_QUOTE))
		throw std::runtime_error(_format_exception(_lex, _EXCEPTION_EXPECTING_STRING_CLOSE_QUOTE));
	_lex.next();
	attr_lst.add_attribute(attr);
}

void _mxml_parser::_attribute_list(_mxml_node &nod) {
	if(!_lex.is_identifier())
		return;
	_attribute(nod.get_attributes());
	_attribute_list(nod);
}

std::string _mxml_parser::_format_exception(_mxml_lexer &lex, size_t exc) {
	std::stringstream ss;
	ss << "[ln. " << lex.get_buffer().get_line() << "], \"" << lex.get_text() << "\": " << _EXCEPTION_MESSAGE[exc];
	return ss.str();
}

void _mxml_parser::_parse(_mxml_node &nod) {
	if(_lex.has_next()) {
		_lex.next();
		_node(nod);
	}
}

void _mxml_parser::_node(_mxml_node &nod) {
	if(!_lex.is_symbol(_mxml_lexer::SYMBOL_TYPE_OPEN_BRACKET))
		throw std::runtime_error(_format_exception(_lex, _EXCEPTION_EXPECTING_OPEN_BRACKET));
	_lex.next();
	if(!_lex.is_identifier())
		throw std::runtime_error(_format_exception(_lex, _EXCEPTION_EXPECTING_IDENTIFIER));
	nod.set_name(_lex.get_text());
	_lex.next();
	_attribute_list(nod);
	_node_end(nod);
}

void _mxml_parser::_node_end(_mxml_node &nod) {
	if(_lex.is_symbol(_mxml_lexer::SYMBOL_TYPE_CLOSE_BRACKET_TERM))
		_lex.next();
	else if(_lex.is_symbol(_mxml_lexer::SYMBOL_TYPE_CLOSE_BRACKET)) {
		_lex.next();
		if(_lex.is_symbol(_mxml_lexer::SYMBOL_TYPE_OPEN_BRACKET))
			_node_list(nod.get_nodes());
		else if(_lex.is_string()) {
			nod.set_string(_lex.get_text());
			_lex.next();
		}
		if(!_lex.is_symbol(_mxml_lexer::SYMBOL_TYPE_OPEN_BRACKET_TERM))
			throw std::runtime_error(_format_exception(_lex, _EXCEPTION_EXPECTING_TERMINATOR));
		_lex.next();
		if(!_lex.is_identifier())
			throw std::runtime_error(_format_exception(_lex, _EXCEPTION_EXPECTING_IDENTIFIER));
		if(_lex.get_text() != nod.get_name())
			throw std::runtime_error(_format_exception(_lex, _EXCEPTION_EXPECTING_MATCHING_TERMINATOR));
		_lex.next();
		if(!_lex.is_symbol(_mxml_lexer::SYMBOL_TYPE_CLOSE_BRACKET))
			throw std::runtime_error(_format_exception(_lex, _EXCEPTION_EXPECTING_CLOSE_BRACKET));
		_lex.next();
	} else
		throw std::runtime_error(_format_exception(_lex, _EXCEPTION_EXPECTING_CLOSE_BRACKET));
}

void _mxml_parser::_node_list(std::vector<_mxml_node> &nod_lst) {
	_mxml_node nod;
	if(!_lex.is_symbol(_mxml_lexer::SYMBOL_TYPE_OPEN_BRACKET))
		return;
	_node(nod);
	nod_lst.push_back(nod);
	_node_list(nod_lst);
}

mxml_lexer &_mxml_parser::get_lexer(void) {
	return _lex;
}

std::string _mxml_parser::to_string(void) {
	return _lex.to_string();
}
