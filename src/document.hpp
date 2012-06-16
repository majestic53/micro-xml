/*
 * document.hpp
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

#ifndef DOCUMENT_HPP_
#define DOCUMENT_HPP_

#include <string>
#include "node.hpp"
#include "node_list.hpp"

namespace __mxml {

	typedef class _document {
		protected:
			_node _root;

			static std::string _format_xml(_node &root);
			static bool _parse_xml(const std::string &input, bool is_file, _node &root);

		public:
			_document(void);
			_document(_node &root);
			_document(const std::string &name);
			_document(const _document &other);
			virtual ~_document(void);
			_document &operator=(const _document &other);
			node_list get_nodes_by_name(const std::string &name);
			node &get_root_node(void);
			static bool read(const std::string &path, _document &doc);
			bool read(const std::string &path);
			static bool read_from_string(const std::string &input, _document &doc);
			bool read_from_string(const std::string &input);
			void set_root_node(node &root);
			std::string to_string(void);
			static bool write(const std::string &path, _document &doc);
			bool write(const std::string &path);
	} document;

};

#endif
