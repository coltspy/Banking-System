#include <windows.h>
#include <stdlib.h>
#include <stdio.h> 

typedef struct Account {
    float balance;
} Account;

Account account = {1000}; // Initial balance of 1000
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    MSG  msg;
    WNDCLASS wc = {0};
    HWND hwnd;

    wc.lpszClassName = TEXT("My Window");
    wc.hInstance     = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc   = WndProc;
    wc.hCursor       = LoadCursor(0, IDC_ARROW);

    RegisterClass(&wc);
    hwnd = CreateWindow(wc.lpszClassName, TEXT("Banking System"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, 150, 150, 600, 400, 0, 0, hInstance, 0);

    
    HWND hwndButtonDeposit = CreateWindow(TEXT("button"), TEXT("Deposit Money"),
                                      WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                                      10, 50, 100, 30, hwnd, (HMENU) 2, (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);

    HWND hwndButtonWithdraw = CreateWindow(TEXT("button"), TEXT("Withdraw Money"),
                                       WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                                       10, 90, 100, 30, hwnd, (HMENU) 3, (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);

    HWND hwndButtonBalance = CreateWindow(TEXT("button"), TEXT("Check Balance"),
                                      WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                                      10, 130, 100, 30, hwnd, (HMENU) 4, (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    HWND hwndTextDeposit = CreateWindow(TEXT("edit"), NULL,
                                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL,
                                    120, 55, 100, 20, hwnd, (HMENU) 5, (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);

    HWND hwndTextWithdraw = CreateWindow(TEXT("edit"), NULL,
                                     WS_TABSTOP | WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL,
                                     120, 95, 100, 20, hwnd, (HMENU) 6, (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_COMMAND:
    switch (LOWORD(wParam)) {
        case 2: {
            TCHAR buffer[256];
            GetWindowText(GetDlgItem(hwnd, 5), buffer, 256);
            float depositAmount = atof(buffer);
            account.balance += depositAmount;
            MessageBox(hwnd, "Amount Deposited", "Notification", MB_OK);
            break;
        }
        case 3: {
            TCHAR buffer[256];
            GetWindowText(GetDlgItem(hwnd, 6), buffer, 256);
            float withdrawAmount = atof(buffer);
            if (account.balance >= withdrawAmount) {
                account.balance -= withdrawAmount;
                MessageBox(hwnd, "Amount Withdrawn", "Notification", MB_OK);
            } else {
                MessageBox(hwnd, "Insufficient Funds", "Error", MB_OK);
            }
            break;
        }
        case 4: {
            TCHAR buffer[256];
            sprintf(buffer, "Current Balance: $%.2f", account.balance);
            MessageBox(hwnd, buffer, "Check Balance", MB_OK);
            break;
        }
    }
    break;


        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

