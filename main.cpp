#include <iostream>
#include <cassert>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>

class HouseElf {
public:
	bool bIsHouse = false;
	std::string nameElf = "NONE";
public:
	HouseElf(std::string in_nameElf) {
		this->bIsHouse = true;
		assert(in_nameElf != "NONE");
		this->nameElf = in_nameElf;
	}
};

class Branch {
public:
	Branch* parent = nullptr;
	int count = 0;
	Branch** childs = nullptr;
	HouseElf* houseElf = nullptr;
public:
	Branch(int in_rand, int out_rand) {
		std::srand(std::time(nullptr));
		int rand = (std::rand() % out_rand);
		while (rand < in_rand)
			rand = (std::rand() % out_rand);
		count = rand;
		in_rand -= 1;
		out_rand -= 3;
		if (out_rand > 0) {
			childs = new Branch *[count];
			for (int i = 0; i < count; ++i) {
				childs[i] = new Branch(in_rand, out_rand);
				std::cout << "Input name of elf:";
				std::string in_name;
				std::cin >> in_name;
				if (in_name != "NONE")
					childs[i]->houseElf = new HouseElf(in_name);
			}
		} else
			return;
	}

	Branch* getTopBranch() {
		if (parent == nullptr) return nullptr;
		if (parent->parent == nullptr) return parent;
		return parent->getTopBranch();
	}

	void sowInfo() {
		if (houseElf != nullptr)
			std::cout << houseElf->nameElf << std::endl;
		for (int i = 0; i < count; ++i) {
			if (childs[i]->houseElf != nullptr) {
				std::cout << childs[i]->houseElf->nameElf << std::endl;
			}
		}
	}

};

int main() {
	std::srand(std::time(nullptr));

	auto* branch = new Branch(3, 6);

	branch->sowInfo();

	delete branch;
	branch = nullptr;

	return 0;
}