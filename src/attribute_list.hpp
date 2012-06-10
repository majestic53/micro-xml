/*
 * attribute_list.hpp
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

#ifndef ATTRIBUTE_LIST_HPP_
#define ATTRIBUTE_LIST_HPP_

#include <string>
#include <vector>
#include "attribute.hpp"

namespace __mxml {

	typedef class _attribute_list {
		protected:
			std::vector<_attribute> _attributes;

		public:
			_attribute_list(void);
			_attribute_list(const _attribute_list &other);
			virtual ~_attribute_list(void);
			_attribute_list &operator=(const _attribute_list &other);
			void add_attribute(attribute &attr);
			bool contains(const std::string &name);
			bool contains(_attribute &attr);
			attribute &get_attribute_at(size_t index);
			std::vector<attribute> &get_attributes(void);
			bool insert_attribute(attribute &attr, size_t index);
			bool is_empty(void);
			bool remove_attribute(size_t index);
			size_t size(void);
			std::string to_string(void);
	} attribute_list;

};

#endif
