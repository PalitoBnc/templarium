#include <new>
#include <cstdlib>

#ifndef TEMPLARIUM_ARRAYLIST_INL
#define TEMPLARIUM_ARRAYLIST_INL

namespace templarium{

	template <typename T>

    //Array List class
	class ArrayList{

		T *array;   //array (<typename T>)
		std::size_t capacity;   //capacity
		std::size_t size;   //amount of items

        //Builders:
		public:
		ArrayList(){
			array = nullptr;
			capacity = 0;
			size = 0;
		}
		
        //Private methods:
		private:	
		void grow(){    //Triggers when size is bigger than capacity
			std::size_t newcapacity = capacity == 0 ? 1 : (capacity * 2);
			T *arraytmp = static_cast<T*>(::operator new(sizeof(T) * newcapacity));
			for (std::size_t i = 0; i < capacity; i++){
				new (arraytmp + i) T(array[i]);
				array[i].~T();
			}
			operator delete(array);
			array = arraytmp;
			capacity = newcapacity;
		}
		void shrink(){  //Triggers when size euqals or is smaller than half capacity
			std::size_t newcapacity = capacity / 2;
			if (newcapacity > 0){
				T *arraytmp = static_cast<T*>(::operator new(sizeof(T) * newcapacity));
				for (std::size_t i = 0; i < capacity; i++){
					if (i < newcapacity){
						new (arraytmp + i) T(array[i]);
					}
					array[i].~T();
				}
				operator delete (array);
				array = arraytmp;
			}
			else {
				for (std::size_t i = 0; i < capacity; i++){
					array[i].~T();
				}
				operator delete (array);
				array = nullptr;
			}
			capacity = newcapacity;
		}
	}
}

#endif
