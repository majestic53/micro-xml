/*
 * mxml_node_list.hpp
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

#ifndef MXML_NODE_LIST_HPP_
#define MXML_NODE_LIST_HPP_

#include <string>
#include <vector>
#include "mxml_node.hpp"

namespace __mxml {

	typedef class _mxml_node_list {
		protected:
			std::vector<_mxml_node> _lst;

			static void _get_nodes_by_name_helper(const std::string &name, _mxml_node &nod, _mxml_node_list &nod_lst);

		public:
			_mxml_node_list(void);
			_mxml_node_list(const _mxml_node_list &other);
			virtual ~_mxml_node_list(void);
			_mxml_node_list &operator=(const _mxml_node_list &other);
			void add_node(mxml_node &nod);
			void clear(void);
			mxml_node &get_node_at(size_t index);
			std::vector<mxml_node> &get_nodes(void);
			static size_t get_nodes_by_name(const std::string &name, mxml_node &nod, _mxml_node_list &nod_lst);
			bool insert_node(mxml_node &nod, size_t index);
			bool is_empty(void);
			bool remove_node(size_t index);
			size_t size(void);
			std::string to_string();
	} mxml_node_list;

};

#endif
