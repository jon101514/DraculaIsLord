#include "Main.h"

int main(void)
{
	AppClass* pApp = new AppClass("System");
	pApp->Run();
	SafeDelete(pApp);
	return 0;
}