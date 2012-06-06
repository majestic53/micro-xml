/*
 * node.hpp
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

#ifndef NODE_HPP_
#define NODE_HPP_

#include <string>
#include <vector>
#include "attribute.hpp"
#include "attribute_list.hpp"
#include "element.hpp"

namespace __mxml {

	typedef class _node :
		public element {
		protected:
			std::string _str;
			std::vector<_node> _nodes;
			_attribute_list _attributes;

		public:
			_node(void);
			_node(const std::string &name);
			_node(const _node &other);
			virtual ~_node(void);
			_node &operator=(const _node &other);
			void add_attribute(attribute &attr);
			void add_node(_node &nod);
			size_t attribute_size(void);
			attribute &get_attribute_at(size_t index);
			attribute_list &get_attributes(void);
			_node &get_node_at(size_t index);
			std::vector<_node> &get_nodes(void);
			std::string &get_string(void);
			bool insert_attribute(attribute &attr, size_t index);
			bool insert_node(_node &nod, size_t index);
			size_t node_size(void);
			bool remove_attribute(size_t index);
			bool remove_node(size_t index);
			void set_string(const std::string &str);
			std::string to_string(size_t tab_index);
	} node;

};

#endif
