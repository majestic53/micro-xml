/*
 * attribute.hpp
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

#ifndef ATTRIBUTE_HPP_
#define ATTRIBUTE_HPP_

#include <string>
#include "element.hpp"

namespace __mxml {

	typedef class _attribute :
		public element {
		protected:
			std::string _value;

		public:
			_attribute(void);
			_attribute(const std::string &name, const std::string &value);
			_attribute(const _attribute &other);
			virtual ~_attribute(void);
			_attribute &operator=(const _attribute &other);
			bool operator==(const _attribute &other);
			std::string &get_value(void);
			void set_value(const std::string &value);
			std::string to_string(size_t tab_index);
	} attribute;

};

#endif
