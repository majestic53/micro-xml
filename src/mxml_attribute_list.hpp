/*
 * mxml_attribute_list.hpp
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

#ifndef MXML_ATTRIBUTE_LIST_HPP_
#define MXML_ATTRIBUTE_LIST_HPP_

#include <string>
#include <vector>
#include "mxml_attribute.hpp"

namespace __mxml {

	typedef class _mxml_attribute_list {
		protected:
			std::vector<_mxml_attribute> _lst;

		public:
			_mxml_attribute_list(void);
			_mxml_attribute_list(const _mxml_attribute_list &other);
			virtual ~_mxml_attribute_list(void);
			_mxml_attribute_list &operator=(const _mxml_attribute_list &other);
			void add_attribute(mxml_attribute &attr);
			void clear(void);
			bool contains(const std::string &name);
			bool contains(mxml_attribute &attr);
			mxml_attribute &get_attribute_at(size_t index);
			bool get_attribute_by_name(const std::string &name, mxml_attribute &attr);
			std::vector<mxml_attribute> &get_attributes(void);
			bool insert_attribute(mxml_attribute &attr, size_t index);
			bool is_empty(void);
			bool remove_attribute(size_t index);
			size_t size(void);
			std::string to_string(void);
	} mxml_attribute_list;

};

#endif
