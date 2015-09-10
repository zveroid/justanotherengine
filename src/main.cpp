#include <iostream>
#include <Windows.h>

#include "Types.h"

#include "Core/Device/Device.h"
#include "Core/Application.h"

using namespace std;

int main()
{
	CApplication* app = new CApplication();
	app->GetDevice()->SetWidth(800);
	app->GetDevice()->SetHeight(600);
	if (app->Init())
	{
		while (true)
		{
			app->Update();
			Sleep(100);
		}
	}
    return 0;
}

