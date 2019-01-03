//#include <vld.h> // For memory leak detection
#include "Application.h"
#include <iostream>


/// The main function of the program
int main(int argc, char* argv[])
{
	try {
		core::Application app;

		app.run(argc, argv);

		return 0;
	}
	catch (std::exception& e)
	{
		std::cerr << "Fatal exception " << e.what() << std::endl;
		return -1;
	}
	catch(...)
	{
		std::cerr << "Unknown fatal exception" << std::endl;
		return -2;
	}
}

