/*
 * node_list.hpp
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

#ifndef NODE_LIST_HPP_
#define NODE_LIST_HPP_

#include <string>
#include <vector>
#include "node.hpp"

namespace __mxml {

	typedef class _node_list {
		protected:
			std::vector<_node> _nodes;

		public:
			_node_list(void);
			_node_list(const _node_list &other);
			virtual ~_node_list(void);
			_node_list &operator=(const _node_list &other);
			void add_node(node &nod);
			node &get_node_at(size_t index);
			std::vector<node> &get_nodes(void);
			bool insert_node(node &nod, size_t index);
			bool is_empty(void);
			bool remove_node(size_t index);
			size_t size(void);
			std::string to_string();
	} node_list;

};

#endif
