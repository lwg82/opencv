#include <opencv2/opencv.hpp>

#include <cstdlib>
#include <iostream>

template <typename T, typename V>
	void func_impl(T iter, V v)
	{
		T tmp = T();

		std::cout << tmp << "\t" << v;
	}

template <typename T>
	inline void func(T iter)
	{
		func_impl(iter, *iter); // template 参数推导
	}


int main(int argc, char *argv[])
{
	int i = 10;
	func(&i);

	exit(EXIT_SUCCESS);
}

