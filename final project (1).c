

//Arman hossain  Dept:csit ID:231061008
//project name : Distribution business  management :::;

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MaxProduct 100
#define MaxDelivery 100

struct Product {
    char itemname[50];
    float itemprice;
    int stock;
};

struct Delivery {
    char itemname[50];
    int quantity;
    float subtotal;
};

struct Product Item[MaxProduct];
struct Delivery supply[MaxDelivery];
int ICount = 0;
int DCount = 0;

void display() {
    printf("Products:\n");
    for (int i = 0; i < ICount; i++) {
        printf("%d. %s - %.2f Taka - Stock: %d\n", i + 1, Item[i].itemname, Item[i].itemprice, Item[i].stock);
    }
}


void addProduct() {
    if (ICount < MaxProduct) {
        printf("Enter the name of the product: ");
        scanf("%s", Item[ICount].itemname);

        printf("Enter the price of the new product: ");
        scanf("%f", &Item[ICount].itemprice);

        printf("Enter the initial stock of the product: ");
        scanf("%d", &Item[ICount].stock);

        ICount++;
        printf("Item added to the stock.\n");
    } else {
        printf("Cannot add more items. Stock is full.\n");
    }
}

void delivery() {
    display();

    printf("\nHow many products do you want to deliver?\n=");
    int d;
    scanf("%d", &d);

    float totalBill = 0;

    for (int i = 0; i < d; i++) {
        printf("Enter the number of the product you want to sell: ");
        int itemNumber;
        scanf("%d", &itemNumber);

        if (itemNumber >= 1 && itemNumber <= ICount) {
            printf("Enter the quantity: ");
            int quantity;
            scanf("%d", &quantity);

            if (quantity <= Item[itemNumber - 1].stock) {
                float subtotal = Item[itemNumber - 1].itemprice * quantity;
                totalBill += subtotal;

                strcpy(supply[DCount].itemname, Item[itemNumber - 1].itemname);
                supply[DCount].quantity = quantity;
                supply[DCount].subtotal = subtotal;

                Item[itemNumber - 1].stock -= quantity;
                DCount++;
            } else {
                printf("Insufficient stock. Please choose a quantity less than or equal to %d.\n", Item[itemNumber - 1].stock);
                i--;
            }
        } else {
            printf("Invalid item number. Please enter a valid and available product number.\n");
            i--;
        }
    }

    printf("Delivery Summary:\n");
    for (int i = 0; i < DCount; i++) {
        printf("%s - Quantity: %d - Subtotal: %.2f Taka\n", supply[i].itemname, supply[i].quantity, supply[i].subtotal);
    }

    printf("Total Bill: %.2f Taka\n", totalBill);
}
void deleteProduct() {
    display();
    if (ICount == 0) {
        printf("No products in stock to delete.\n");
        return;
    }

    printf("Enter the number of the product you want to delete: ");
    int deleteIndex;
    scanf("%d", &deleteIndex);

    if (deleteIndex < 1 || deleteIndex > ICount) {
        printf("Invalid product number. Please enter a valid product number.\n");
        return;
    }

    printf("%s has been deleted from the stock.\n", Item[deleteIndex - 1].itemname);

    for (int i = deleteIndex - 1; i < ICount - 1; i++) {
        strcpy(Item[i].itemname, Item[i + 1].itemname);
        Item[i].itemprice = Item[i + 1].itemprice;
        Item[i].stock = Item[i + 1].stock;
    }
    ICount--;
}

int main() {
    printf("\\\\\\\\\\\\Olympic Industries Limited\\\\\\\\\\\\\n");

    char adminUsername[] = "Olympic";
    char adminPassword[] = "admin";

    char inputUsername[100], inputPassword[100];

    printf("Enter username: ");
    scanf("%s", inputUsername);

    printf("Enter password: ");
    scanf("%s", inputPassword);

    if (strcmp(inputUsername, adminUsername) == 0 && strcmp(inputPassword, adminPassword) == 0) {
        printf("Login successful. Welcome, Admin!\n");
    } else { 
        printf("Login failed. Invalid username or password.\n");
        return 1; // Exit if login failed
    }

    int choice;

    while (1) {
        printf("1. Add product in stock\n");
        printf("2. Display stock products\n");
        printf("3. Enter the products you want to deliver\n");
        printf("4. Delete product from the stock\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                display();
                break;
            case 3:
                delivery();
                break;
                case 4:
                deleteProduct();
            case 5:
                printf("Exiting the program. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}