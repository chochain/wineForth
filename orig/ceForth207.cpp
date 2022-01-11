#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
TCHAR szClassName[] = _T("CodeBlocksWindowsApp");
HWND TextBox, SendButton, TextField;
HWND hwnd;               /* This is the handle for our window */
int WINAPI WinMain(HINSTANCE hThisInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpszArgument,
    int nCmdShow)
{
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof(WNDCLASSEX);
    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
    RegisterClassEx(&wincl);
    hwnd = CreateWindowEx(
        0,                   /* Extended possibilites for variation */
        szClassName,         /* Classname */
        _T("ceforth207"),       /* Title Text */
        WS_OVERLAPPEDWINDOW, /* default window */
        CW_USEDEFAULT,       /* Windows decides the position */
        CW_USEDEFAULT,       /* where the window ends up on the screen */
        500,                 /* The programs width */
        500,                 /* and height in pixels */
        HWND_DESKTOP,        /* The window is a child-window to desktop */
        NULL,                /* No menu */
        hThisInstance,       /* Program Instance handler */
        NULL                 /* No Window Creation data */
    );
    ShowWindow(hwnd, nCmdShow);
    TextBox = CreateWindow(_T("EDIT"),
        _T("input"),
        WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL | ES_MULTILINE,
        10, 220, 450, 200,
        hwnd, (HMENU)1, NULL, NULL);
    SendButton = CreateWindow(_T("BUTTON"),
        _T("Send"),
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        10, 430, 65, 20,
        hwnd, (HMENU)2, NULL, NULL);
    TextField = CreateWindow(_T("EDIT"),
        _T("output"),
        WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL | ES_MULTILINE,
        10, 10, 450, 200,
        hwnd, (HMENU)3, NULL, NULL);
    while (GetMessage(&messages, NULL, 0, 0))
    {  TranslateMessage(&messages);
        DispatchMessage(&messages);}
    return messages.wParam;
}
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{  switch (message)                  /* handle the messages */
    {
    //case WM_KEYDOWN:
    //    if (wParam == VK_RETURN)
    case WM_COMMAND:
        if (LOWORD(wParam) == 2)
        {  int len = GetWindowTextLength(TextBox) + 1;
            TCHAR* text = new TCHAR[len];
            GetWindowText(TextBox, &text[0], len);
            SendMessage(TextField, EM_SETSEL, -1, -1);
            SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)&text[0]);
            delete[] text;
            SetWindowText(TextBox, _T(""));
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);       /* send a WM_QUIT to the message queue */
        break;
    default:                      /* for messages that we don't deal with */
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

