#include <iostream>
#include <cassert>
#include <string>
#include <ctime>
#include <cstdlib>

class HouseElf {
public:
	bool bIsHouse = false;
	std::string nameElf = "NONE";

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
				auto* child = new Branch(in_rand, out_rand);
				childs[i] = child;
				childs[i]->parent = this;
				std::srand(std::time(nullptr));
				int rand = (std::rand() % out_rand);
				while (rand < in_rand)
					rand = (std::rand() % out_rand);
				childs[i]->count = rand;
				childs[i]->childs = new Branch*[childs[i]->count];
				for (int j = 0; j < childs[i]->count; j++) {
					auto* child = new Branch(in_rand, out_rand);
					childs[i]->childs[j] = child;
					childs[i]->childs[j]->parent = this;
					std::cout << "Input name of elf:";
					std::string in_name;
					std::cin >> in_name;
					if (in_name != "NONE")
						childs[i]->childs[j]->houseElf = new HouseElf(in_name);
				}
				std::cout << "Input name of elf:";
				std::string in_name;
				std::cin >> in_name;
				if (in_name != "NONE")
					childs[i]->houseElf = new HouseElf(in_name);
			}
		} else
			return;
	}
	
	std::string getNameElf() {
		return this->houseElf->nameElf;
	}

	

	Branch* getTopBranch() {
		if (parent == nullptr) return nullptr;
		if (parent->parent == nullptr) return parent;
		return parent->getTopBranch();
	}

	void showAllElf() {
		for (int i = 0; i < count; ++i) {
			if (childs[i]->houseElf != nullptr) {
				std::cout << childs[i]->houseElf->nameElf << std::endl;
			}
			for (int j = 0; j < childs[i]->count; ++j) {
				if (childs[i]->childs[j]->houseElf != nullptr) {
					std::cout << childs[i]->childs[j]->houseElf->nameElf << std::endl;
				}
			}
		}
	}

	bool isOnTree(std::string in_name) {
		int count = 0;
		for (int i = 0; i < this->count; ++i) {
			if (childs[i]->houseElf != nullptr) {
				if (in_name == childs[i]->houseElf->nameElf) {
					count++;
					break;
				}
			}
			for (int j = 0; j < childs[i]->count; ++j) {
				if (childs[i]->childs[j]->houseElf != nullptr) {
					if (in_name == childs[i]->childs[j]->houseElf->nameElf) {
						count++;
						break;
					}
				}
			}
		}
		if (count > 0)
			return true;
		else
			return false;
	}

	void showNeighborsNamesByName(std::string in_name) {
		int parent_index;
		for (int i = 0; i < count; ++i) {
			if (childs[i]->houseElf != nullptr) {
				if (in_name == childs[i]->houseElf->nameElf)
					parent_index = i;
				break;
			}
			for (int j = 0; j < childs[i]->count; ++j) {
				if (childs[i]->childs[j]->houseElf != nullptr) {
					if (in_name == childs[i]->childs[j]->houseElf->nameElf) {
						parent_index = i;
						break;
					}
				}
			}
		}
		std::cout << "Neighbor's List of elf " << in_name << ":" << std::endl;
		int neighbors = 0;
		if (childs[parent_index]->houseElf != nullptr) {
			if (in_name != childs[parent_index]->houseElf->nameElf) {
				std::cout << childs[parent_index]->houseElf->nameElf << std::endl;
				neighbors++;
			}
		}
		for (int i = 0; i < childs[parent_index]->count; ++i) {
			if (childs[parent_index]->childs[i]->houseElf != nullptr) {
				if (in_name != childs[parent_index]->childs[i]->houseElf->nameElf) {
					std::cout << childs[parent_index]->childs[i]->houseElf->nameElf << std::endl;
					neighbors++;
				}
			}
		}
		std::cout << "Number of neighbors = " << neighbors << std::endl;
	}

};

int main() {
	std::srand(std::time(nullptr));

	auto* branch = new Branch(3, 6);

	branch->showAllElf();

	std::cout << "Input name for search neighbors on branch:";
	std::string in_name;
	std::cin >> in_name;
	while (!(branch->isOnTree(in_name))) {
		std::cout << "Incorrect name. Try again." << std::endl;
		std::cout << "Input name for search neighbors on branch:";
		std::cin >> in_name;
	}
	branch->showNeighborsNamesByName(in_name);

	delete branch;

	return 0;
}