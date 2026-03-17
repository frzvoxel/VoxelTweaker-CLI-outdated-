#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Intro.h"
#include "WindowsComponentsPage.h"
#include <Windows.h>

int IsRunningAsAdmin() {
    BOOL isAdmin = FALSE;
    PSID adminGroup = NULL;

  
    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    if (!AllocateAndInitializeSid(&NtAuthority, 2,
        SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_ADMINS,
        0, 0, 0, 0, 0, 0, &adminGroup)) {
        return 0;
    }

    if (!CheckTokenMembership(NULL, adminGroup, &isAdmin)) {
        isAdmin = FALSE;
    }

    FreeSid(adminGroup);
    return isAdmin;
}

void EnableANSIConsole() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}


void Start() {
    int choice;

    while (1) {
        printf("What do you want to do?\n\n");
        printf("\033[32m Windows Components Page [1]  \033[0m\n");

        int result = scanf("%d", &choice);

        if (result == 1) {
            break;
        }
        else {
            printf("Error! Need a number.\n");
            while (getchar() != '\n');
        }
    }

    switch (choice) {
    case 1: {
        WindowsComponentsPage();
        break;
    }
    }
}


int main() { // entry point
    EnableANSIConsole();
    int isAdmin = IsRunningAsAdmin();
    if (isAdmin) {
    }
    else {
        printf("The program is not running from the admin :C");
        return;
    }

    while (1) {
        Intro();
        Start();
    }
    return 0;
}