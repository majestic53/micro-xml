/*
 * mxml_node.hpp
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

#ifndef MXML_NODE_HPP_
#define MXML_NODE_HPP_

#include <string>
#include <vector>
#include "mxml_attribute.hpp"
#include "mxml_attribute_list.hpp"
#include "mxml_element.hpp"

namespace __mxml {

	typedef class _mxml_node :
		public _mxml_element {
		protected:
			std::string _str;
			std::vector<_mxml_node> _nodes;
			_mxml_attribute_list _attributes;

		public:
			_mxml_node(void);
			_mxml_node(const std::string &name);
			_mxml_node(const _mxml_node &other);
			virtual ~_mxml_node(void);
			_mxml_node &operator=(const _mxml_node &other);
			void add_attribute(mxml_attribute &attr);
			void add_node(_mxml_node &nod);
			size_t attribute_size(void);
			mxml_attribute &get_attribute_at(size_t index);
			bool get_attribute_by_name(const std::string &name, mxml_attribute &attr);
			mxml_attribute_list &get_attributes(void);
			_mxml_node &get_node_at(size_t index);
			std::vector<_mxml_node> &get_nodes(void);
			std::string &get_string(void);
			bool insert_attribute(mxml_attribute &attr, size_t index);
			bool insert_node(_mxml_node &nod, size_t index);
			size_t node_size(void);
			bool remove_attribute(size_t index);
			bool remove_node(size_t index);
			void set_string(const std::string &str);
			std::string to_string(size_t tab_index);
	} mxml_node;

};

#endif
