#include <iostream>
#include <Windows.h>

#include "stdafx.h"

#include "Core/Device/Device.h"
#include "Core/Application.h"

using namespace std;
using namespace jaengine;

int main()
{
	CApplication* app = new CApplication();
	app->GetDevice()->SetWidth(800);
	app->GetDevice()->SetHeight(600);
	if (app->Init())
	{
		while (app->IsRunning())
		{
			app->Update();
			Sleep(100);
		}
		app->Deinit();
	}
    return 0;
}

