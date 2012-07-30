/*
 * mxml_document.hpp
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

#ifndef MXML_DOCUMENT_HPP_
#define MXML_DOCUMENT_HPP_

#include <string>
#include "mxml_node.hpp"
#include "mxml_node_list.hpp"

namespace __mxml {

	typedef class _mxml_document {
		protected:
			_mxml_node _root;

			static std::string _format_xml(_mxml_node &root);
			static void _parse_xml(const std::string &input, bool is_file, _mxml_node &root);

		public:
			_mxml_document(void);
			_mxml_document(mxml_node &root);
			_mxml_document(const std::string &name);
			_mxml_document(const _mxml_document &other);
			virtual ~_mxml_document(void);
			_mxml_document &operator=(const _mxml_document &other);
			mxml_node_list get_nodes_by_name(const std::string &name);
			mxml_node &get_root_node(void);
			static void read(const std::string &path, _mxml_document &doc);
			void read(const std::string &path);
			static void read_from_string(const std::string &input, _mxml_document &doc);
			void read_from_string(const std::string &input);
			void set_root_node(mxml_node &root);
			std::string to_string(void);
			static bool write(const std::string &path, _mxml_document &doc);
			bool write(const std::string &path);
	} mxml_document;

};

#endif
