#include <Windows.h>
#include <gl/GL.h>

#include "Types.h"
#include "Core/Device/Win32Device.h"
#include "Core/Application.h"

static u32 LocaleIdToCodepage(u32 lcid)
{
	switch (lcid)
	{
	case 1098:  // Telugu
	case 1095:  // Gujarati
	case 1094:  // Punjabi
	case 1103:  // Sanskrit
	case 1111:  // Konkani
	case 1114:  // Syriac
	case 1099:  // Kannada
	case 1102:  // Marathi
	case 1125:  // Divehi
	case 1067:  // Armenian
	case 1081:  // Hindi
	case 1079:  // Georgian
	case 1097:  // Tamil
		return 0;
	case 1054:  // Thai
		return 874;
	case 1041:  // Japanese
		return 932;
	case 2052:  // Chinese (PRC)
	case 4100:  // Chinese (Singapore)
		return 936;
	case 1042:  // Korean
		return 949;
	case 5124:  // Chinese (Macau S.A.R.)
	case 3076:  // Chinese (Hong Kong S.A.R.)
	case 1028:  // Chinese (Taiwan)
		return 950;
	case 1048:  // Romanian
	case 1060:  // Slovenian
	case 1038:  // Hungarian
	case 1051:  // Slovak
	case 1045:  // Polish
	case 1052:  // Albanian
	case 2074:  // Serbian (Latin)
	case 1050:  // Croatian
	case 1029:  // Czech
		return 1250;
	case 1104:  // Mongolian (Cyrillic)
	case 1071:  // FYRO Macedonian
	case 2115:  // Uzbek (Cyrillic)
	case 1058:  // Ukrainian
	case 2092:  // Azeri (Cyrillic)
	case 1092:  // Tatar
	case 1087:  // Kazakh
	case 1059:  // Belarusian
	case 1088:  // Kyrgyz (Cyrillic)
	case 1026:  // Bulgarian
	case 3098:  // Serbian (Cyrillic)
	case 1049:  // Russian
		return 1251;
	case 8201:  // English (Jamaica)
	case 3084:  // French (Canada)
	case 1036:  // French (France)
	case 5132:  // French (Luxembourg)
	case 5129:  // English (New Zealand)
	case 6153:  // English (Ireland)
	case 1043:  // Dutch (Netherlands)
	case 9225:  // English (Caribbean)
	case 4108:  // French (Switzerland)
	case 4105:  // English (Canada)
	case 1110:  // Galician
	case 10249:  // English (Belize)
	case 3079:  // German (Austria)
	case 6156:  // French (Monaco)
	case 12297:  // English (Zimbabwe)
	case 1069:  // Basque
	case 2067:  // Dutch (Belgium)
	case 2060:  // French (Belgium)
	case 1035:  // Finnish
	case 1080:  // Faroese
	case 1031:  // German (Germany)
	case 3081:  // English (Australia)
	case 1033:  // English (United States)
	case 2057:  // English (United Kingdom)
	case 1027:  // Catalan
	case 11273:  // English (Trinidad)
	case 7177:  // English (South Africa)
	case 1030:  // Danish
	case 13321:  // English (Philippines)
	case 15370:  // Spanish (Paraguay)
	case 9226:  // Spanish (Colombia)
	case 5130:  // Spanish (Costa Rica)
	case 7178:  // Spanish (Dominican Republic)
	case 12298:  // Spanish (Ecuador)
	case 17418:  // Spanish (El Salvador)
	case 4106:  // Spanish (Guatemala)
	case 18442:  // Spanish (Honduras)
	case 3082:  // Spanish (International Sort)
	case 13322:  // Spanish (Chile)
	case 19466:  // Spanish (Nicaragua)
	case 2058:  // Spanish (Mexico)
	case 10250:  // Spanish (Peru)
	case 20490:  // Spanish (Puerto Rico)
	case 1034:  // Spanish (Traditional Sort)
	case 14346:  // Spanish (Uruguay)
	case 8202:  // Spanish (Venezuela)
	case 1089:  // Swahili
	case 1053:  // Swedish
	case 2077:  // Swedish (Finland)
	case 5127:  // German (Liechtenstein)
	case 1078:  // Afrikaans
	case 6154:  // Spanish (Panama)
	case 4103:  // German (Luxembourg)
	case 16394:  // Spanish (Bolivia)
	case 2055:  // German (Switzerland)
	case 1039:  // Icelandic
	case 1057:  // Indonesian
	case 1040:  // Italian (Italy)
	case 2064:  // Italian (Switzerland)
	case 2068:  // Norwegian (Nynorsk)
	case 11274:  // Spanish (Argentina)
	case 1046:  // Portuguese (Brazil)
	case 1044:  // Norwegian (Bokmal)
	case 1086:  // Malay (Malaysia)
	case 2110:  // Malay (Brunei Darussalam)
	case 2070:  // Portuguese (Portugal)
		return 1252;
	case 1032:  // Greek
		return 1253;
	case 1091:  // Uzbek (Latin)
	case 1068:  // Azeri (Latin)
	case 1055:  // Turkish
		return 1254;
	case 1037:  // Hebrew
		return 1255;
	case 5121:  // Arabic (Algeria)
	case 15361:  // Arabic (Bahrain)
	case 9217:  // Arabic (Yemen)
	case 3073:  // Arabic (Egypt)
	case 2049:  // Arabic (Iraq)
	case 11265:  // Arabic (Jordan)
	case 13313:  // Arabic (Kuwait)
	case 12289:  // Arabic (Lebanon)
	case 4097:  // Arabic (Libya)
	case 6145:  // Arabic (Morocco)
	case 8193:  // Arabic (Oman)
	case 16385:  // Arabic (Qatar)
	case 1025:  // Arabic (Saudi Arabia)
	case 10241:  // Arabic (Syria)
	case 14337:  // Arabic (U.A.E.)
	case 1065:  // Farsi
	case 1056:  // Urdu
	case 7169:  // Arabic (Tunisia)
		return 1256;
	case 1061:  // Estonian
	case 1062:  // Latvian
	case 1063:  // Lithuanian
		return 1257;
	case 1066:  // Vietnamese
		return 1258;
	}
	return 65001;   // utf-8
}

CWin32Device::CWin32Device() :
	m_WindowHandler(0),
	m_DeviceContext(0),
	m_Fullscreen(0),
	m_KeyboardLayout(0),
	m_KeyboardCodepage(0)
{
}


CWin32Device::~CWin32Device()
{
}

bool CWin32Device::Init()
{
	HINSTANCE hInstance = GetModuleHandle(0);

	if (!m_WindowHandler)
	{
		WNDCLASSEX wcex;
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = (HICON)LoadIcon(hInstance, MAKEINTRESOURCE(110));;
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = 0;
		wcex.lpszClassName = "JAEngineWin32Class";
		wcex.hIconSm = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(110), IMAGE_ICON, 32, 32, 0);

		if (!RegisterClassEx(&wcex))
			return false;

		RECT clientSize;
		clientSize.top = 0;
		clientSize.left = 0;
		clientSize.right = m_Width;
		clientSize.bottom = m_Height;

		DWORD style = WS_POPUP;

		if (!m_Fullscreen)
			style = WS_SYSMENU | WS_BORDER | WS_CAPTION | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

		AdjustWindowRect(&clientSize, style, FALSE);

		const s32 realWidth = clientSize.right - clientSize.left;
		const s32 realHeight = clientSize.bottom - clientSize.top;

		s32 windowLeft = (GetSystemMetrics(SM_CXSCREEN) - realWidth) / 2;
		s32 windowTop = (GetSystemMetrics(SM_CYSCREEN) - realHeight) / 2;

		if (windowLeft < 0)
			windowLeft = 0;
		if (windowTop < 0)
			windowTop = 0;    // make sure window menus are in screen on creation

		if (m_Fullscreen)
		{
			windowLeft = 0;
			windowTop = 0;
		}

		m_WindowHandler = CreateWindow(wcex.lpszClassName, "JustAnotherEngine", style, windowLeft, windowTop, realWidth, realHeight, NULL, NULL, hInstance, NULL);

		if (!m_WindowHandler)
			return false;

		ShowWindow(m_WindowHandler, SW_SHOW);
		UpdateWindow(m_WindowHandler);

		// fix ugly ATI driver bugs. Thanks to ariaci
		MoveWindow(m_WindowHandler, windowLeft, windowTop, realWidth, realHeight, TRUE);

		// make sure everything gets updated to the real sizes
		//Resized = true;
	}

	SetActiveWindow(m_WindowHandler);
	SetForegroundWindow(m_WindowHandler);

	m_DeviceContext = GetDC(m_WindowHandler);

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),             // Size Of This Pixel Format Descriptor
		1,                                         // Version Number
		PFD_DRAW_TO_WINDOW |                       // Format Must Support Window
		PFD_SUPPORT_OPENGL |                       // Format Must Support OpenGL
		PFD_DOUBLEBUFFER,			               // Must Support Double Buffering
		PFD_TYPE_RGBA,                             // Request An RGBA Format
		32,								            // Select Our Color Depth
		0, 0, 0, 0, 0, 0,                          // Color Bits Ignored
		0,                                         // No Alpha Buffer
		0,                                         // Shift Bit Ignored
		0,                                         // No Accumulation Buffer
		0, 0, 0, 0,                                   // Accumulation Bits Ignored
		0,		                                  // Z-Buffer (Depth Buffer)
		0,					                      // Stencil Buffer Depth
		0,                                         // No Auxiliary Buffer
		0,//PFD_MAIN_PLANE,                            // Main Drawing Layer
		0,                                         // Reserved
		0, 0, 0                                    // Layer Masks Ignored
	};

	int PixelFormat = ChoosePixelFormat(m_DeviceContext, &pfd);

	SetPixelFormat(m_DeviceContext, PixelFormat, &pfd);

	// get the codepage used for keyboard input
	m_KeyboardLayout = GetKeyboardLayout(0);
	m_KeyboardCodepage = LocaleIdToCodepage(LOWORD(m_KeyboardLayout));

	return true;
}

void CWin32Device::Deinit()
{
	if (m_WindowHandler)
	{
		if (m_DeviceContext)
		{
			ReleaseDC(m_WindowHandler, m_DeviceContext);
			m_DeviceContext = 0;
		}
		DestroyWindow(m_WindowHandler);
		m_WindowHandler = 0;
	}
}

void CWin32Device::Update()
{
	MSG msg = { 0 };
	if (GetMessage(&msg, m_WindowHandler, 0, 0) > 0)
		DispatchMessage(&msg);
}

LRESULT CWin32Device::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	case WM_ACTIVATE:
	case WM_DESTROY:
	case WM_INPUT:
		break;
	case WM_CLOSE:
		CApplication::GetInstance()->Quit();
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}
