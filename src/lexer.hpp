/*
 * lexer.hpp
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

#ifndef LEXER_HPP_
#define LEXER_HPP_

#include <string>
#include <set>
#include <stack>
#include "pb_buff.hpp"

namespace __mxml {

	typedef class _lexer {
		protected:
			static const size_t _COMMENT_COUNT = 2;
			static const std::string _COMMENT_STR[_COMMENT_COUNT];
			static const std::set<std::string> _COMMENT_SET;
			static const size_t _SYMBOL_COUNT = 7;
			static const std::string _SYMBOL_STR[_SYMBOL_COUNT];
			static const std::set<std::string> _SYMBOL_SET;

			enum _COMMENT_TYPE {
				_COMMENT_TYPE_BANG,
				_COMMENT_TYPE_HYPHEN,
			};

			enum _STATE {
				_STATE_IDENTIFIER,
				_STATE_STRING,
			};

			bool _init;
			pb_buffer _buff;
			std::string _text;
			size_t _type, _state;

			static size_t _comment_to_type(const std::string &input);
			size_t _comment_to_type(void);
			static bool _is_comment(const std::string &input);
			bool _is_comment(void);
			bool _is_comment(size_t type);
			bool _read_type(size_t type);
			void _skip_whitespace(void);
			void _skip_whitespace_end(void);
			void _unskip_whitespace(size_t depth);

		public:
			enum SYMBOL_TYPE {
				SYMBOL_TYPE_OPEN_BRACKET,
				SYMBOL_TYPE_CLOSE_BRACKET,
				SYMBOL_TYPE_OPEN_BRACKET_TERM,
				SYMBOL_TYPE_CLOSE_BRACKET_TERM,
				SYMBOL_TYPE_TERMINATOR,
				SYMBOL_TYPE_QUOTE,
				SYMBOL_TYPE_ASSIGNMENT,
			};

			enum TYPE {
				TYPE_BEGIN,
				TYPE_END,
				TYPE_IDENTIFIER,
				TYPE_STRING,
				TYPE_SYMBOL,
			};

			_lexer(void);
			_lexer(const std::string &input, bool is_file);
			_lexer(const _lexer &other);
			virtual ~_lexer(void);
			_lexer &operator=(const _lexer &other);
			pb_buffer &get_buffer(void);
			std::string get_text(void);
			size_t get_type(void);
			bool has_next(void);
			bool is_identifier(void);
			bool is_string(void);
			static bool is_symbol(const std::string &input);
			bool is_symbol(void);
			bool is_symbol(size_t type);
			bool next(void);
			void reset(void);
			static size_t symbol_to_type(const std::string &input);
			size_t symbol_to_type(void);
			std::string to_string(void);
			static std::string type_to_string(size_t type);

			friend class _parser;
	} lexer;

};

#endif
