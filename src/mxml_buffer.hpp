/*
 * mxml_buffer.hpp
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

#ifndef MXML_BUFFER_HPP_
#define MXML_BUFFER_HPP_

#include <fstream>
#include <string>

namespace __mxml {

	typedef class _mxml_buffer {
		protected:
			static const char _NL = '\n';
			static const char _EOS = '\0';

			char _ch;
			size_t _line, _pos;
			std::string _buff;

		public:
			_mxml_buffer(void);
			_mxml_buffer(const std::string &input, bool is_file);
			_mxml_buffer(const _mxml_buffer &other);
			virtual ~_mxml_buffer(void);
			_mxml_buffer &operator=(const _mxml_buffer &other);
			char current(void);
			std::string &get_buffer(void);
			size_t get_line(void);
			bool has_next(void);
			bool has_previous(void);
			bool is_whitespace(void);
			char next(void);
			char peek(void);
			char previous(void);
			void reset(void);
			size_t size(void);
			std::string to_string(void);

			friend class _mxml_lexer;
	} mxml_buffer;

};

#endif
