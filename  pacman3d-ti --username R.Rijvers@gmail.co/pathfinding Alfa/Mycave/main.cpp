#pragma comment(lib, "opengl32")

#include "MyCave.h"
#include <vrj/Kernel/Kernel.h>
using namespace vrj;

int main(int argc, char* argv[])
{
	Kernel* kernel = Kernel::instance();
	kernel->init(argc, argv);
	for ( int i = 1; i < argc; ++i )
	{
		if(strcmp(argv[i], "--vrjconfig") == 0)
		{
			i++;
			kernel->loadConfigFile(argv[i]);
		}
	}

	Mycave* application = new Mycave();

	kernel->start();
	kernel->setApplication(application);
	kernel->waitForKernelStop();
	delete application;



	return 0;
}