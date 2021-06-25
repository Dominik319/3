#include "projekt1.h"
#include "stdafx.h"
#include <vector>
#include <cstdio>
#include <Windows.h>
#include <fstream>
#include <iostream>


#define MAX_LOADSTRING 100

// Zmienne globalne:
HINSTANCE hInst;                                // bieĹĽÄ…ce wystÄ…pienie
WCHAR szTitle[MAX_LOADSTRING];                  // Tekst paska tytuĹ‚u
WCHAR szWindowClass[MAX_LOADSTRING];            // nazwa klasy okna gĹ‚Ăłwnego
std::vector<float> Data;
int T = 1;//zmiana na osi czasu 
int A = 2; // amplituda;
int n = 100;//ilosc pominietych probek

// PrzekaĹĽ dalej deklaracje funkcji doĹ‚Ä…czone w tym module kodu:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void inputData()
{
    float x;
    std::fstream plik;
    plik.open("outputPendulum01.txt", std::ios::in);
    int i = 0;
    if (plik.good() == true)
    {
        while (!plik.eof()) {
            plik >> x;
            if (i == 0) {
                Data.push_back(x);
            }
            if (i == 11)i = -1;
            i++;
        }
        plik.close();
    }
    else std::cout << "Dostep do pliku zostal zabroniony!" << std::endl;

}

int OnCreate(HWND window)
{
    inputData();
    return 0;
}

void MyOnPaint(HDC hdc)
{
    Graphics graphics(hdc);
    Pen pen(Color(255, 255, 255, 255));
    Pen pen2(Color(255, 0, 0, 0));
    inputData();
    float a = Data.front();
    float q1 = 0, q2 = 0;
    if (Data.size() < n) { }//usuwanie n probek z wektora
    else {
        if (n > 0) {
            for (int i = 0; i < n; i++) {
                Data.erase(Data.begin());
            }
        }
    }
    int x = 0; int y = 1000 * a; int z = y/1000;
    while (!Data.empty()) {//rysowanie wykresu i kompasu
        q1 = 100+100 * sin(a * 3.14 / 180);
        q2 = 30+100 * cos(a * 3.14 / 180);
        graphics.DrawLine(&pen2, q1-12,q2-12,q1+12,q2+12);
        graphics.DrawLine(&pen2, q1 + 12, q2 - 12, q1 - 12, q2 + 12);
        graphics.DrawLine(&pen2, q1 , q2 - 12, q1 , q2 + 12);
        graphics.DrawLine(&pen2, q1+12, q2 , q1-12, q2 );
        graphics.DrawLine(&pen2, q1-q1+100, q2-q2+30 , q1, q2);
        graphics.DrawLine(&pen2, 300 + T * (x), 100 + A*z, 300 + T * (x + 1), 100 + A*y / 1000);//wykres
        Sleep(10);
        a = Data.front();
        Data.erase(Data.begin());
        if (!Data.empty()) {
            graphics.DrawLine(&pen, q1 - 12, q2 - 12, q1 + 12, q2 + 12);
            graphics.DrawLine(&pen, q1 + 12, q2 - 12, q1 - 12, q2 + 12);
            graphics.DrawLine(&pen, q1, q2 - 12, q1, q2 + 12);
            graphics.DrawLine(&pen, q1 + 12, q2, q1 - 12, q2);
            graphics.DrawLine(&pen, q1 - q1 + 100, q2 - q2 + 30, q1, q2);
            x++;
            z = y/1000;
            y = 1000 * a;
            
        }
        
    }

}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR           gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    // Inicjuj ciÄ…gi globalne
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PROJEKT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Wykonaj inicjowanie aplikacji:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJEKT1));
    
    OnCreate(HWND(hInstance));
    MSG msg;

    // GĹ‚Ăłwna pÄ™tla komunikatĂłw:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    GdiplusShutdown(gdiplusToken);
    return (int)msg.wParam;
}



//
//  FUNKCJA: MyRegisterClass()
//
//  PRZEZNACZENIE: Rejestruje klasÄ™ okna.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJEKT1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_PROJEKT1);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNKCJA: InitInstance(HINSTANCE, int)
//
//   PRZEZNACZENIE: Zapisuje dojĹ›cie wystÄ…pienia i tworzy okno gĹ‚Ăłwne
//
//   KOMENTARZE:
//
//        W tej funkcji dojĹ›cie wystÄ…pienia jest zapisywane w zmiennej globalnej i
//        jest tworzone i wyĹ›wietlane okno gĹ‚Ăłwne programu.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Przechowuj dojĹ›cie wystÄ…pienia w naszej zmiennej globalnej

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  FUNKCJA: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PRZEZNACZENIE: Przetwarza komunikaty dla okna gĹ‚Ăłwnego.
//
//  WM_COMMAND  - przetwarzaj menu aplikacji
//  WM_PAINT    - Maluj okno gĹ‚Ăłwne
//  WM_DESTROY  - opublikuj komunikat o wyjĹ›ciu i wrĂłÄ‡
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Analizuj zaznaczenia menu:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);


        MyOnPaint(hdc);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Procedura obsĹ‚ugi komunikatĂłw dla okna informacji o programie.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}