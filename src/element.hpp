/*
 * element.hpp
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

#ifndef ELEMENT_HPP_
#define ELEMENT_HPP_

#include <string>

namespace __mxml {

	typedef class _element {
		protected:
			size_t _type;
			std::string _name;

		public:
			enum ELEMENT_TYPE {
				TYPE_GENERIC,
				TYPE_ATTRIBUTE,
				TYPE_NODE,
			};

			_element(void);
			_element(size_t type);
			_element(const std::string &name, size_t type);
			_element(const _element &other);
			virtual ~_element(void);
			_element &operator=(const _element &other);
			std::string &get_name(void);
			size_t get_type(void);
			void set_name(std::string &name);
			void set_type(size_t type);
			virtual std::string to_string(size_t tab_index);
			static std::string type_to_string(size_t type);

			friend class _attribute;
			friend class _node;
	} element;

};

#endif
