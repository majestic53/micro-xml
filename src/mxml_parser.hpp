/*
 * mxml_parser.hpp
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

#ifndef MXML_PARSER_HPP_
#define MXML_PARSER_HPP_

#include <string>
#include <vector>
#include "mxml_lexer.hpp"
#include "mxml_node.hpp"

namespace __mxml {

	typedef class _mxml_parser {
		protected:
			static const size_t _EXCEPTION_COUNT = 11;
			static const std::string _EXCEPTION_MESSAGE[_EXCEPTION_COUNT];

			enum _EXCEPTION_TYPE {
				_EXCEPTION_SUCCESS,
				_EXCEPTION_EXPECTING_IDENTIFIER,
				_EXCEPTION_EXPECTING_ASSIGNMENT,
				_EXCEPTION_EXPECTING_OPEN_BRACKET,
				_EXCEPTION_EXPECTING_CLOSE_BRACKET,
				_EXCEPTION_EXPECTING_TERMINATOR,
				_EXCEPTION_EXPECTING_STRING,
				_EXCEPTION_EXPECTING_STRING_OPEN_QUOTE,
				_EXCEPTION_EXPECTING_STRING_CLOSE_QUOTE,
				_EXCEPTION_EXPECTING_MATCHING_TERMINATOR,
				_EXCEPTION_EXPECTING_UNIQUE_ATTRIBUTE,
			};

			_mxml_lexer _lex;

			void _attribute(_mxml_attribute_list &attr_lst);
			void _attribute_list(_mxml_node &nod);
			static std::string _format_exception(_mxml_lexer &lex, size_t exc);
			void _parse(_mxml_node &nod);
			void _node(_mxml_node &nod);
			void _node_end(_mxml_node &nod);
			void _node_list(std::vector<_mxml_node> &nod_lst);

		public:
			_mxml_parser(void);
			_mxml_parser(const std::string &input, bool is_file);
			_mxml_parser(const _mxml_parser &other);
			virtual ~_mxml_parser(void);
			_mxml_parser &operator=(const _mxml_parser &other);
			mxml_lexer &get_lexer(void);
			std::string to_string(void);

			friend class _mxml_document;
	} mxml_parser;

};

#endif
