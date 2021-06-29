// projekt1.cpp : Definiuje punkt wejścia dla aplikacji.
//
#include "projekt1.h"
#include "stdafx.h"
#include <vector>
#include <cstdio>
#include <Windows.h>
#include <fstream>
#include <iostream>
#include <string>

#define MAX_LOADSTRING 100

int timestep = 10;
// Zmienne globalne:
HINSTANCE hInst;                                // bieżące wystąpienie
WCHAR szTitle[MAX_LOADSTRING];                  // Tekst paska tytułu
WCHAR szWindowClass[MAX_LOADSTRING];            // nazwa klasy okna głównego
std::vector<float> Data;
int T = 1;//zmiana na osi czasu 
int A = 2;//amplituda
int n = 200;//ilosc pominietych probek
HWND g_hPrzycisk;
HWND g_hPrzycisk2, g_hPrzycisk3, g_hPrzycisk4, g_hPrzycisk5;
HWND hStatic, hStatic2, hStatic3, hStatic4, hStatic10, hStatic9;
int z = 0;
HWND hwndButton;
// Przekaż dalej deklaracje funkcji dołączone w tym module kodu:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

RECT drawArea1 = { 30, 0, 1200, 360 };
RECT drawArea2 = { 900,400,1100,450  };

void inputData()
{
        float x;
        std::fstream plik;
        plik.open("outputCatapult01.txt", std::ios::in);
        int i = 0;
        if (plik.good() == true)
        {
            while ( !plik.eof()) {
                plik >> x;
                if (i == 0) {
                    Data.push_back( x);
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

void kierunki(HDC hdc) {
    Graphics graphics(hdc);
    Pen pen2(Color(255, 0, 0, 0));
    graphics.DrawLine(&pen2, 993, 40, 993, 25);//N
    graphics.DrawLine(&pen2, 993, 25, 1007, 40);//N
    graphics.DrawLine(&pen2, 1007, 40, 1007, 25);//N

    graphics.DrawLine(&pen2, 1007, 165, 1000, 160);//S
    graphics.DrawLine(&pen2, 1000, 160, 993, 165);//S
    graphics.DrawLine(&pen2, 993, 165, 1007, 175);//S
    graphics.DrawLine(&pen2, 1007, 175, 1000, 180);//S
    graphics.DrawLine(&pen2, 1000, 180, 993, 175);//S

    graphics.DrawLine(&pen2, 1060, 92, 1070, 92);//E
    graphics.DrawLine(&pen2, 1060, 100, 1070, 100);//E
    graphics.DrawLine(&pen2, 1060, 108, 1070, 108);//E
    graphics.DrawLine(&pen2, 1060, 92, 1060, 108);//E

    graphics.DrawLine(&pen2, 932, 100, 936, 105);//W
    graphics.DrawLine(&pen2, 932, 100, 928, 105);//W
    graphics.DrawLine(&pen2, 936, 105, 940, 90);//W
    graphics.DrawLine(&pen2, 928, 105, 924, 90);//W
    int k = A;
    graphics.DrawLine(&pen2, 30, 10, 30, 100+k*90);//OY
    graphics.DrawLine(&pen2, 29, 12, 29, 100 + k * 90);//OY
    graphics.DrawLine(&pen2, 31, 12, 31, 100 + k * 90);//OY
    graphics.DrawLine(&pen2, 30, 10, 35, 15);//OY strzalka
    graphics.DrawLine(&pen2, 30, 9, 35, 14);//OY strzalka
    graphics.DrawLine(&pen2, 30, 10, 25, 15);//OY strzalka
    graphics.DrawLine(&pen2, 30, 9, 25, 14);//OY strzalka
    graphics.DrawLine(&pen2, 30, 10, 30, 100 + k * 90);//OY
    graphics.DrawLine(&pen2, 130, 10, 130, 100 + k * 90);//OY
    graphics.DrawLine(&pen2, 230, 10, 230, 100 + k * 90);//OY
    graphics.DrawLine(&pen2, 330, 10, 330, 100 + k * 90);//OY
    graphics.DrawLine(&pen2, 430, 10, 430, 100 + k * 90);//OY
    int p = 0;
    if (n == 100 || n==150) { p = 100;
    graphics.DrawLine(&pen2, 530, 10, 530, 100 + k * 90);//OY
    graphics.DrawLine(&pen2, 600, 100, 595, 95);//OX strzalka
    graphics.DrawLine(&pen2, 600, 99, 595, 94);//OX strzalka
    graphics.DrawLine(&pen2, 600, 100, 595, 105);//OX strzalka
    graphics.DrawLine(&pen2, 600, 101, 595, 106);//OX strzalka
    }

    if (n > 199) {
        graphics.DrawLine(&pen2, 500, 100, 495, 95);//OX strzalka
        graphics.DrawLine(&pen2, 500, 99, 495, 94);//OX strzalka
        graphics.DrawLine(&pen2, 500, 100, 495, 105);//OX strzalka
        graphics.DrawLine(&pen2, 500, 101, 495, 106);//OX strzalka
    }

    if (n < 100) {
        p = 200;
        graphics.DrawLine(&pen2, 630, 10, 630, 100 + k * 90);//OY
        graphics.DrawLine(&pen2, 530, 10, 530, 100 + k * 90);//OY
        graphics.DrawLine(&pen2, 700, 100, 695, 95);//OX strzalka
        graphics.DrawLine(&pen2, 700, 99, 695, 94);//OX strzalka
        graphics.DrawLine(&pen2, 700, 100, 695, 105);//OX strzalka
        graphics.DrawLine(&pen2, 700, 101, 695, 106);//OX strzalka
    }

    graphics.DrawLine(&pen2, 30, 100, 500+p, 100);//OX
    graphics.DrawLine(&pen2, 30, 99, 498+p, 99);//OX
    graphics.DrawLine(&pen2, 30, 101, 498+p, 101);//OX

    graphics.DrawLine(&pen2, 506+p, 95,520+p , 95);//T
    graphics.DrawLine(&pen2, 513+p, 105, 513 + p,95 );//T
    
    if(A==1){
        graphics.DrawLine(&pen2, 30, 100 - A * 50, 500+p, 100 - 50 * A);//OX 
        graphics.DrawLine(&pen2, 30, 100 - A * 150 / 2, 500+p, 100 - 150 * A / 2);//OX 
    }
    graphics.DrawLine(&pen2, 30, 100 - A * 50 / 2, 500+p, 100 - A * 50 / 2);//OX
    graphics.DrawLine(&pen2, 30, 100 + A * 50 / 2, 500+p, 100 + A * 50 / 2);//OX
    graphics.DrawLine(&pen2, 30, 100 + A * 50, 500+p, 100 + 50 * A);//OX 
    graphics.DrawLine(&pen2, 30, 100 + A * 150/2, 500+p, 100 + 150 * A/2);//OX 
}

void osie() {
    switch (A) {
    case 1:
        SetWindowText(hStatic10, L"           50"); break;
        break;
    case 2:
        SetWindowText(hStatic10, L"    50     "); break;
        break;
    case 3:
        SetWindowText(hStatic10, L"50"); break;
        break;
    }
}
void MyOnPaint(HDC hdc)
{
    Graphics graphics(hdc);
    Pen pen(Color(255, 255, 255, 255));
    Pen pen2(Color(255, 0, 0, 0));
    inputData();
    int x = 0;//czas
    float a = Data.front();
    int y = 1000 * a;//zmienna koncowa 
    int z = 0;//zmienna poczatkowa czyli koncowa chwile wczesniej
    float q1 = 0, q2 = 0, q3 = 0, q4 = 0;
    if (Data.size() < n) {}//usuwanie n probek z wektora
    else {
        if (n > 0) {
            for (int i = 0; i < n; i++) {
                Data.erase(Data.begin());
            }
        }
    }
    int max = Data.size() + 5;
    kierunki(hdc);
    while (!Data.empty()&&x<620-n){//rysowanie wykresu i kompasu
            x++;
            if (n > 601)break;
           
            q1 = 1000 + 50 * sin(a*3.14 / 180);
            q2 = 100 + 50 * cos(a * 3.14 / 180);
            q3 = 1000 - 50 * sin(a * 3.14 / 180);
            q4 = 100 - 50 * cos(a * 3.14 / 180);
            graphics.DrawLine(&pen2, 30 + (x), 100 - A * (z) / 2000, 30 + (x + 1), 100 - A * (y / 2000));//wykres
            graphics.DrawLine(&pen2, q1, q2,q3,q4); //kompas4
            
            Sleep(timestep);
            a = Data.front();
            Data.erase(Data.begin());
            if (Data.size() > 0 && x!= 620-n) {
                graphics.DrawLine(&pen, q1, q2, q3, q4); //kompas usuniecie poprzedniej 
            }
            z = y;
            y = 1000 * a;
    }
    
}

void repaintWindow(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea)
{
    if (drawArea == NULL)
        InvalidateRect(hWnd, NULL, TRUE); // repaint all
    else
        InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
    hdc = BeginPaint(hWnd, &ps);
    MyOnPaint(hdc);
    EndPaint(hWnd, &ps);
    if (Data.size() == 0)
    {
        //   KillTimer(hWnd, TMR_1);
    }
}

void napisOkno() {
    switch (n) {
    case 0:SetWindowText(hStatic4, L"0");
        break;
    case 50:SetWindowText(hStatic4, L"50");
        break;
    case 100:SetWindowText(hStatic4, L"100");
        break;
    case 150:SetWindowText(hStatic4, L"150");
        break;
    case 200:SetWindowText(hStatic4, L"200");
        break;
    case 250:SetWindowText(hStatic4, L"250");
        break;
    case 300:SetWindowText(hStatic4, L"300");
        break;
    case 350:SetWindowText(hStatic4, L"350");
        break;
    case 400:SetWindowText(hStatic4, L"400");
        break;
    case 450:SetWindowText(hStatic4, L"450");
        break;
    case 500:SetWindowText(hStatic4, L"500");
        break;
    case 550:SetWindowText(hStatic4, L"550");
        break;
    case 600:SetWindowText(hStatic4,L"600");
        break;
    default:SetWindowText(hStatic4, L"nie ma tylu danych");

    }
}

void napisOkno2() {
    switch (A) {
    case 1:SetWindowText(hStatic2, L"1");break;
    case 2:SetWindowText(hStatic2, L"2"); break;
    case 3:SetWindowText(hStatic2, L"3"); break;
    }
}
void napisOkno3() {
    switch (timestep) {
    case 10:SetWindowText(hStatic3, L"10"); SetWindowText(hStatic9, L"przedzialka czasowa ma 2s"); break;
    case 8:SetWindowText(hStatic3, L"8"); SetWindowText(hStatic9, L"przedzialka czasowa ma 1,8s"); break;
    case 6:SetWindowText(hStatic3, L"6"); SetWindowText(hStatic9, L"przedzialka czasowa ma 1,6s"); break;
    case 4:SetWindowText(hStatic3, L"4"); SetWindowText(hStatic9, L"przedzialka czasowa ma 1,4s"); break;
    case 2:SetWindowText(hStatic3, L"2"); SetWindowText(hStatic9, L"przedzialka czasowa ma 1,2s"); break;
    case 0:SetWindowText(hStatic3, L"0"); SetWindowText(hStatic9, L"Wykres wykonany bez czasu"); break;
    case 12:SetWindowText(hStatic3, L"12"); SetWindowText(hStatic9, L"przedzialka czasowa ma 2,2s"); break;
    case 14:SetWindowText(hStatic3, L"14"); SetWindowText(hStatic9, L"przedzialka czasowa ma 2,4s"); break;
    case 16:SetWindowText(hStatic3, L"16"); SetWindowText(hStatic9, L"przedzialka czasowa ma 2,6s"); break;
    case 18:SetWindowText(hStatic3, L"18"); SetWindowText(hStatic9, L"przedzialka czasowa ma 2,8s"); break;
    case 20:SetWindowText(hStatic3, L"20"); SetWindowText(hStatic9, L"przedzialka czasowa ma 3s"); break;
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

    // Inicjuj ciągi globalne
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PROJEKT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Wykonaj inicjowanie aplikacji:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJEKT1));

    OnCreate(HWND(hInstance));
    MSG msg;

    // Główna pętla komunikatów:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    GdiplusShutdown(gdiplusToken);
    return (int) msg.wParam;
}



//
//  FUNKCJA: MyRegisterClass()
//
//  PRZEZNACZENIE: Rejestruje klasę okna.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJEKT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PROJEKT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNKCJA: InitInstance(HINSTANCE, int)
//
//   PRZEZNACZENIE: Zapisuje dojście wystąpienia i tworzy okno główne
//
//   KOMENTARZE:
//
//        W tej funkcji dojście wystąpienia jest zapisywane w zmiennej globalnej i
//        jest tworzone i wyświetlane okno główne programu.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Przechowuj dojście wystąpienia w naszej zmiennej globalnej

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   
   g_hPrzycisk = CreateWindowEx(0, L"BUTTON", L"Generuj", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
       100, 370, 150, 30, hWnd, NULL, hInstance, NULL);

   g_hPrzycisk2 = CreateWindowEx(0, L"BUTTON", L"reset ", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
       100, 420, 150, 30, hWnd, NULL, hInstance, NULL);

   g_hPrzycisk3 = CreateWindowEx(0, L"BUTTON", L"Amplituda up ", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
       300, 370, 150, 30, hWnd, NULL, hInstance, NULL);

   g_hPrzycisk5 = CreateWindowEx(0, L"BUTTON", L"Amplituda normal ", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
       300, 420, 150, 30, hWnd, NULL, hInstance, NULL);

   g_hPrzycisk4 = CreateWindowEx(0, L"BUTTON", L"Amplituda down ", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
       300, 470, 150, 30, hWnd, NULL, hInstance, NULL);
   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
       TEXT("przyspieszenie 2ms"),                  // the caption of the button
       WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
       500, 370,                                  // the left and top co-ordinates
       150, 30,                              // width and height
       hWnd,                                 // parent window handle
       (HMENU)ID_BUTTON1,                   // the ID of your button
       hInstance,                            // the instance of your application
       NULL);                               // extra bits you dont really need
   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
       TEXT("spowolnienie 2ms"),                  // the caption of the button
       WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
       500, 420,                                  // the left and top co-ordinates
       150, 30,                              // width and height
       hWnd,                                 // parent window handle
       (HMENU)ID_BUTTON2,                   // the ID of your button
       hInstance,                            // the instance of your application
       NULL);                               // extra bits you dont really need
   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
       TEXT("ilosc probek +50"),                  // the caption of the button
       WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
       700, 370,                                  // the left and top co-ordinates
       150, 30,                              // width and height
       hWnd,                                 // parent window handle
       (HMENU)ID_BUTTON3,                   // the ID of your button
       hInstance,                            // the instance of your application
       NULL);                               // extra bits you dont really need
   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
       TEXT("ilosc probek -50"),                  // the caption of the button
       WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
       700, 420,                                  // the left and top co-ordinates
       150, 30,                              // width and height
       hWnd,                                 // parent window handle
       (HMENU)ID_BUTTON4,                   // the ID of your button
       hInstance,                            // the instance of your application
       NULL);                               // extra bits you dont really need
   

   hStatic = CreateWindowEx(0, L"STATIC", NULL, WS_CHILD | WS_VISIBLE |
       SS_LEFT, 880, 370, 200, 40, hWnd, NULL, hInstance, NULL);
   HWND hStatic5 = CreateWindowEx(0, L"STATIC", NULL, WS_CHILD | WS_VISIBLE |
       SS_LEFT, 880, 410, 150, 40, hWnd, NULL, hInstance, NULL);
   HWND hStatic6 = CreateWindowEx(0, L"STATIC", NULL, WS_CHILD | WS_VISIBLE |
       SS_LEFT, 880, 450, 150, 40, hWnd, NULL, hInstance, NULL);
   HWND hStatic7 = CreateWindowEx(0, L"STATIC", NULL, WS_CHILD | WS_VISIBLE |
       SS_LEFT, 880, 490, 150, 40, hWnd, NULL, hInstance, NULL);

   hStatic2 = CreateWindowEx(0, L"STATIC", NULL, WS_CHILD | WS_VISIBLE |
       SS_LEFT, 1030, 410, 50, 40, hWnd, NULL, hInstance, NULL);
   hStatic3 = CreateWindowEx(0, L"STATIC", NULL, WS_CHILD | WS_VISIBLE |
       SS_LEFT, 1030, 450, 50, 40, hWnd, NULL, hInstance, NULL);
   hStatic4 = CreateWindowEx(0, L"STATIC", NULL, WS_CHILD | WS_VISIBLE |
       SS_LEFT, 1030, 490, 50, 40, hWnd, NULL, hInstance, NULL);
   SetWindowText(hStatic5, L"Amplituda:");
   SetWindowText(hStatic6, L"Odstepy czasu");
   SetWindowText(hStatic7, L"Odrzucone probki");
   SetWindowText(hStatic, L"INFORMACJE");
   SetWindowText(hStatic2, L"2");
   SetWindowText(hStatic3, L"10");
   SetWindowText(hStatic4, L"200");
  HWND hStatic8 = CreateWindowEx(0, L"STATIC", NULL, WS_CHILD | WS_VISIBLE |
       SS_LEFT, 2, 2, 20, 20, hWnd, NULL, hInstance, NULL);
  SetWindowText(hStatic8, L"x(t)");

   hStatic10 = CreateWindowEx(0, L"STATIC", NULL, WS_CHILD | WS_VISIBLE |
       SS_LEFT, 10, 20, 15, 70, hWnd, NULL, hInstance, NULL);
   SetWindowText(hStatic10, L"    50      ");

   hStatic9 = CreateWindowEx(0, L"STATIC", NULL, WS_CHILD | WS_VISIBLE |
       SS_CENTER, 950, 250, 100, 50, hWnd, NULL, hInstance, NULL);
   SetWindowText(hStatic9, L"przedzialka czasowa ma 2s");
       
   

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
//  PRZEZNACZENIE: Przetwarza komunikaty dla okna głównego.
//
//  WM_COMMAND  - przetwarzaj menu aplikacji
//  WM_PAINT    - Maluj okno główne
//  WM_DESTROY  - opublikuj komunikat o wyjściu i wróć
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    switch (message)
    {
    case WM_COMMAND:
        {   
        if ((HWND)lParam == g_hPrzycisk)
        {
            osie();
            SetWindowText(hStatic, L"INFORMACJE");
            repaintWindow(hWnd, hdc, ps, &drawArea1);            
        }
        if ((HWND)lParam == g_hPrzycisk2)
        {   
            A = 2; n = 200; timestep = 10;
            napisOkno();
            napisOkno2();
            napisOkno3();
            SetWindowText(hStatic, L"INFORMACJE");
            repaintWindow(hWnd, hdc, ps, &drawArea1);
        }
        if ((HWND)lParam == g_hPrzycisk3)
        {
            A = 3; napisOkno2();
            SetWindowText(hStatic, L"GENERUJ!!!");
        }
        if ((HWND)lParam == g_hPrzycisk4)
        {
                A = 1; napisOkno2();
                SetWindowText(hStatic, L"GENERUJ!!!");
        }
        if ((HWND)lParam == g_hPrzycisk5)
        {
            A = 2; napisOkno2();
            SetWindowText(hStatic, L"GENERUJ!!!");
        }
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
            case ID_BUTTON1:
                if (timestep>1) {
                    timestep = timestep - 2;
                    napisOkno3();
                    SetWindowText(hStatic, L"GENERUJ!!!");
                    // SetTimer(hWnd, TMR_1, 30, 0);
                }
                break;
            case ID_BUTTON2:
                if(timestep<19)
                timestep = timestep + 2;

                napisOkno3();
                SetWindowText(hStatic, L"GENERUJ!!!");
                //  SetTimer(hWnd, TMR_1, 30, 0)
                break;
            case ID_BUTTON3:
                if(n<601)n += 50; napisOkno();

                SetWindowText(hStatic, L"GENERUJ!!!");
                break;
            case ID_BUTTON4:
                if(n==0){}
                else {
                    n -= 50;
                }
                napisOkno();
                SetWindowText(hStatic, L"GENERUJ!!!");
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
        // case WM_TIMER:
          //  switch (wParam)
       //     {
       //    case TMR_1: // OgĂłlne rysowanie ruchĂłw
         //      SetTimer(hWnd, TMR_1, 30, NULL);
         //      break;
         //  }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Procedura obsługi komunikatów dla okna informacji o programie.
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
