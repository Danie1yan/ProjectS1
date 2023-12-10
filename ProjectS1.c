#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Mission {
    int Price;
    char MissionName[50];
    char Location[50];
    char VehicleType[50];
    struct Mission *left;
    struct Mission *right;
};

struct Mission* createMission(int price, char* name, char* location, char* vehicle) {
    struct Mission* newNode = (struct Mission*)malloc(sizeof(struct Mission));
    newNode->Price = price;
    strcpy(newNode->MissionName, name);
    strcpy(newNode->Location, location);
    strcpy(newNode->VehicleType, vehicle);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Mission* insertMission(struct Mission* root, int price, char* name, char* location, char* vehicle) {
    if (root == NULL) {
        return createMission(price, name, location, vehicle);
    }

    if (price > root->Price) {
        root->left = insertMission(root->left, price, name, location, vehicle);
    } else if (price < root->Price) {
        root->right = insertMission(root->right, price, name, location, vehicle);
    }

    return root;
}

void printMissions(struct Mission* root) {
    if (root != NULL) {
        printMissions(root->left);
        printf("Mission price: %d$ Name: %s Location: %s Vehicle: %s\n", root->Price, root->MissionName, root->Location, root->VehicleType);
        printf("$$$--------------------------------------------------------------------------------$$$\n");
        printMissions(root->right);
    }
}

struct Mission* findExpensiveMission(struct Mission* root, int price) {
    struct Mission* result = NULL;

    while (root != NULL) {
        if (root->Price <= price) {
            result = root;
            root = root->left;
        } else {
            root = root->right;
        }
    }

    return result;
}

int main() {
    struct Mission* root = NULL;
    int price;
    char name[50], location[50], vehicle[50];
    FILE *file = fopen("missions.txt", "r");

    if (file == NULL) {
        printf("Could not open the file.\n");
        return 1;
    }

    while (fscanf(file, "%d,%[^,],%[^,],%s", &price, name, location, vehicle) == 4) {
        root = insertMission(root, price, name, location, vehicle);
    }

    fclose(file);

    printf("\nMissions:\n");
    printf("$$$--------------------------------------------------------------------------------$$$\n");
    printMissions(root);

    int givenPrice;
    printf("\nWrite the cost of the mission, then we will show you info about it: ");
    scanf("%d",&givenPrice);
    struct Mission* expensiveMission = findExpensiveMission(root, givenPrice);

    if (expensiveMission != NULL) {
        printf("\n$$$--------------------------------------------------------------------------------$$$");
        printf("\nMost Expensive Mission (Price <= %d$):\n", givenPrice);
        printf("Price: %d$, Name: %s, Location: %s, Vehicle: %s\n", expensiveMission->Price, expensiveMission->MissionName, expensiveMission->Location, expensiveMission->VehicleType);
        printf("$$$--------------------------------------------------------------------------------$$$\n");
    } else {
        printf("$$$--------------------------------------------------------------------------------$$$\n");
        printf("\nNo mission with Price <= %d found.\n", givenPrice);
        printf("$$$--------------------------------------------------------------------------------$$$\n");
    }


    return 0;
}
