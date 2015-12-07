/**
 * @cond
 *
 * Copyright (c) 2015-2016
 * 
 * Bezborodov, V.A. vyacheslav.bezborodov@gmail.com
 * Golodov, V.A. avaksa@gmail.com
 * 
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * @endcond
 */

#pragma once

#include <map>
#include <set>

#ifdef TESTS
class set_test;
#endif

namespace sgl
{
	namespace disjoint
	{
		/**
		 * Disjoint-set.
		 * Represents disjoint-set data structure.
		 * @tparam T - value type.
		 */
		template<typename T>
		class set
		{
			#ifdef TESTS
			friend class ::set_test;
	        #endif

			typedef T value_type;
			typedef std::size_t rank_type;
			typedef std::set<T> set_type;
			typedef std::pair<rank_type, set_type> mapped_type;
			typedef std::map<value_type, mapped_type> map_type;

		public:
			/**
			 * Inserts value to the set.
             * @param value - the value to be inserted.
			 * @throw std::invalid_argument If the value already exists.
             */
			void insert(const value_type& value)
			{
				if(this->map.find(value) != this->map.end())
				{
					throw std::invalid_argument("set::make: value already exists");
				}

				this->map.insert(std::make_pair(value, std::make_pair(0, set_type{value})));
			}

			/**
			 * Finds the value in set.
             * @param value - a value to search.
             * @return The representative of the set where the value is located.
			 * @throw std::out_of_range If the value doesn't exists.
             */
			const value_type& find(const value_type& value) const
			{
				for(const typename map_type::value_type& pair : this->map)
				{
					if(pair.second.second.find(value) != pair.second.second.end())
					{
						return pair.first;
					}
				}

				throw std::out_of_range("set::find: value doesn't exists");
			}

			/**
			 * Unites sets referenced by given values.
			 * A bigger set will be merged with a less. A size of a set depend on it's rank. After merging a set with less rank no longer exists.
             * @param first - a first value containing in first set,
             * @param second - a second value containing in second set.
			 * @throw std::out_of_range If first or second value doesn't exist.
             */
			void unite(const value_type& first, const value_type& second)
			{
				const value_type& first_pos = this->find(first);
				const value_type& second_pos = this->find(second);

				if(first_pos != second_pos)
				{
					mapped_type& lhs = this->map[first_pos];
					mapped_type& rhs = this->map[second_pos];

					if(lhs.first < rhs.first)
					{
						lhs.second.insert(rhs.second.begin(), rhs.second.end());
						this->map.erase(second_pos);
						++lhs.first;
					}
					else
					{
						rhs.second.insert(lhs.second.begin(), lhs.second.end());
						this->map.erase(first_pos);
						++rhs.first;
					}
				}
			}

		private:
			map_type map;
		};
	} // disjoint
} // sgl
