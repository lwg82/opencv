#include <opencv2/opencv.hpp>

#include <cstdlib>
#include <iostream>


template<typename T>
	struct MyIter
	{
		typedef T value_type;
		
		T* ptr;
		MyIter(T *p=0):ptr(p){}
	
		T& operator*() const{return *ptr;}
	};


template<typename K>
	typename K::value_type func(K iter) // 定义参数返回值
	{
		return *iter;
	}

int main(int argc, char *argv[])
{
	MyIter<int> iter(new int(8));
	
	std::cout << func(iter);

	exit(EXIT_SUCCESS);
}

