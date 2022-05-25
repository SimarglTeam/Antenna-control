#include "tty.h"
#include "cmdForRotator.h"
#include <iostream>

int main(int argc, char* argv[]) {
	cmdForRotator cmd;
	cmd.connectToPort();
	std::vector<unsigned char> a;
	a.push_back(5);

	cmd.tty.Read(a);

	for (int i = 0; i < a.size(); i++) {
		std::cout << a[i];
	}

	cmd.tty.Disconnect();

	return EXIT_SUCCESS;

}