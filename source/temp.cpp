// 
// temp.cpp 
// projectXLibMacOS 
// Created by Leonexxe on 24.04.22.
// copyright (c) Leon marcellus nitschke-Höfer (Leonexxe) 2022
//

#pragma once
#include <list>
#include <csignal>

namespace px
{
	namespace tools
	{
		namespace lists
		{
			/**
			 * @brief get a element in a list by index
			 *
			 * @tparam type
			 * @param list
			 * @param index
			 * @return type (list->back if (index > list))
			 */
			template<typename type>
			type getElementByIndex(std::list<type> *list, int index)
			{
				index+=1;
				if(list->size() == 0)
				{
					std::cerr<<"list empty, rasing SIGABRT"<<std::endl;
					raise(SIGABRT);
				}
				if(index >= list->size())// as to my knowledge list->size() should be faster than iterating through the list, please correct me if im wrong
					return list->back();
				
				int count = 0;
				for(type I : *list)
				{
					if(count++ == index)
					{
						return I;
					}
				}
				return list->back();
			}
			
			
			/**
			 * @brief in most cases you should be able to just use list->size() but i have seen cases where this didn't work, i would assume list->size() performs much much better
			 *
			 * @tparam type
			 * @param list
			 * @return const int
			 */
			template<typename type>
			const int getSize(std::list<type>* list) {
				int i = 0;
				for(type I : *list)  {
					i++;
				}
				return i;
			}
			
			/**
			 * @brief in most cases you should be able to just use list->front() but i have seen cases where this didn't work, i would assume list->front() performs much much better
			 *
			 * @tparam T
			 * @param list
			 * @return T*
			 */
			template<typename T>
			T* getFirst(std::list<T>* list)
			{
				T* ret = nullptr;
				for(T i : *list)
				{
					ret = &i;
					break;
				}
				return ret;
			}
			template<typename T>
			T* getLast(std::list<T>* list)
			{
				T* ret = nullptr;
				for(T i : *list)
				{
					ret = &i;
				}
				return ret;
			}
			
			template<typename T>
			bool contains(std::list<T>* list, T target)
			{
				if(list == nullptr)
					return 0;
				if(list->size() == 0)
					return 0;
				for(T I : *list)
				{
					if(I == target)
						return 1;
				}
				return 0;
			}
			
			template<typename T>
			unsigned int findDuplicates(std::list<std::list<T>> data,std::list<std::list<T>>* duplicateStorage)
			{
				unsigned int ret = 0;
				for(std::list<T> I : data)
				{
					for(std::list<T> II : data)
					{
						if(I == II)
							continue;
						int listPos = 0;
						T a;
						T b;
						while(listPos < I.size())
						{
							int IV = 0;
							for(T III : I)
							{
								if(++IV > listPos)
									a = III;
							}
							IV = 0;
							for(T III : I)
							{
								if(++IV > listPos)
									b = III;
							}
							if(a == b)
							{
								duplicateStorage->push_back(II);
								ret++;
							}
						}
					}
				}
			}
		}
	}
}
