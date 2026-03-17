#define _CRT_SECURE_NO_WARNINGS
#include "WindowsComponentsPage.h"
#include "Intro.h"
#include <string.h>
#include <stdlib.h>

int IsWindowsFeatureEnabled(const char* featureName) {
    char command[512];
    snprintf(command, sizeof(command),
        "dism /online /Get-FeatureInfo /FeatureName:%s > nul 2>&1",
        featureName);

    return (system(command) == 0);
}


void InstallWindowsFeature(const char* featureName, const char* displayName) {
    printf("\033[33mChecking %s...\033[0m\n", displayName);

    if (IsWindowsFeatureEnabled(featureName)) {
        printf("\033[32m%s is already installed.\033[0m\n", displayName);
        return;
    }

    printf("\033[33mInstalling %s...\033[0m\n", displayName);

    char command[512];
    snprintf(command, sizeof(command),
        "dism /online /Enable-Feature /FeatureName:%s /All",
        featureName);

    int result = system(command);

    if (result == 0) {
        printf("\033[32m%s successfully installed!\033[0m\n", displayName);
    }
    else {
        printf("\033[31mError installing %s\033[0m\n", displayName);
    }
}



void WindowsComponentsPage(void) {
    int choice;

    while (1) {
        system("cls");
        Intro();
        printf("\033[36mWhat do you want to do?\033[0m\n\n");
        printf("\033[32mInstall DirectPlay [1]\033[0m\n");
        printf("\033[32mInstall .NET FRAEMWORK 2.0, 3.0, 3.5 [2]\033[0m\n");
        printf("\033[31mBack [0]\033[0m\n");

        if (scanf("%d", &choice) != 1) {
            printf("Error! Need a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
        case 1: {
            InstallWindowsFeature("DirectPlay", "DirectPlay");

            printf("Press Enter to continue...");
            fflush(stdout); 
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            getchar();  

            break;
        }

        case 2: {
            InstallWindowsFeature("NetFx3", ".NET Framework 3.5 (2.0, 3.0, 3.5)");

            printf("Press Enter to continue...");
            fflush(stdout);
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            getchar();

            break;
        }
        case 0: {
            system("cls");
            return;
        }
        }
    }
}