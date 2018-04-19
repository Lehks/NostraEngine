#include "nostrautils/NostraUtils.hpp"

#include <iostream>


int main()
{
	NOU::NOU_DAT_ALG::Vector<NOU::char8> v();
	v.emplaceBack('a');

	std::cout << v[0] << std::endl;
	system("pause");
	return 0;
}