#pragma once

#include <map>
#include <set>

namespace sgl
{
	namespace details
	{
		template<typename T>
		class dsu
		{
			typedef T value_type;
			typedef std::set<T> set_type;
			typedef std::map<value_type, set_type> container_type;
			typedef typename container_type::size_type size_type;

		public:
			void make(const value_type& value)
			{
				this->container[value];
			}

			value_type find(const value_type& value) const
			{
				/*if(value == this->container.at(value))
				{
					return value;
				}

				return this->find(this->container.at(value));*/
			}

			void unite(const value_type& first, const value_type& second)
			{
				/*value_type first_ = this->find(first);
				value_type second_ = this->find(second);

				if(first_ != second_)
				{
					this->container.at(second_) = first_;
				}*/
			}

			size_type size() const
			{
				/*return this->container.size();*/
			}

		private:
			container_type container;
		};
	} // details
} // sgl
