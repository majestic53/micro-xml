/*
 * parser.hpp
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

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <string>
#include "lexer.hpp"
#include "node.hpp"

namespace __mxml {

	typedef class _parser {
		protected:
			static const size_t _EXCEPTION_COUNT = 10;
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
				_EXCEPTION_EXPECTING_STRING_OR_NODE,
			};

			_lexer _lex;

			void _attribute(void);
			void _attribute_list(void);
			void _element(void);
			static std::string _format_exception(_lexer &lex, size_t exc);
			void _parse(_node &nod);
			void _node(void);
			void _node_end(void);

		public:
			_parser(void);
			_parser(const std::string &input, bool is_file);
			_parser(const _parser &other);
			virtual ~_parser(void);
			_parser &operator=(const _parser &other);
			lexer &get_lexer(void);
			std::string to_string(void);

			friend class _document;
	} parser;

};

#endif
