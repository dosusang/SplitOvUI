#include "SimpleWindow.h"
#include "Windows.h"

#ifdef _DEBUG
int main()
#else
#undef APIENTRY
#include "Windows.h"
INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
#endif
{
	auto app = new SimpleWindow();
	app->Run();
	return 0;
}