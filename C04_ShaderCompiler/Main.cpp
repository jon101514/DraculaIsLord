#include "Main.h"

int main(void)
{
	AppClass* pApp = new AppClass("Shader Compiler");
	pApp->Run();
	SafeDelete(pApp);
	return 0;
}