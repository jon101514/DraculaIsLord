#include "Main.h"

int main(void)
{
	AppClass* pApp = new AppClass("Translation");
	pApp->Run();
	SafeDelete(pApp);
	return 0;
}