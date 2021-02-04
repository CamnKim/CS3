#include "hashmap.hpp"
#include <iostream>
#include <string>

int main() {

	//testing the bool value returned from insert
	std::cout << "testing insert..." << std::endl << std::endl;
	hashmap<int, int> myhash;
	
	auto i = myhash.insert(make_pair(6, 2));
	auto j = myhash.insert(make_pair(6, 60));

	// i should return (2, 1) and j should return (2, 0)
	std::cout << "i should return (2, 1) and j should return (2, 0)" << std::endl;
	std::cout << "i: (" << *i.first << ", " << i.second << ')' << std::endl;
	std::cout << "j: (" << *j.first << ", " << j.second << ')' << std::endl;

	std::cout << "==================================================" << std::endl;



	std::cout << "testing erase..." << std::endl << std::endl;
	myhash.erase(6);
	auto x = myhash.find(6);
	if (x == nullptr) {
		std::cout << "erased!" << std::endl;
	}

}