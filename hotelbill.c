#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct items {
    char item[50];
    float price;
    int qty;
};

struct orders {
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];
};

struct node {
    struct orders order;
    struct node* next;
};

void generateBillHeader(char name[50], char date[50]) {
    printf("\n\n");
    printf("\t    ADV. Restaurant");
    printf("\n\t   -----------------");
    printf("\nDate:%s", date);
    printf("\nInvoice To: %s", name);
    printf("\n");
    printf("---------------------------------------\n");
    printf("Items\t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
    printf("\n---------------------------------------");
    printf("\n\n");
}

void generateBillBody(char item[30], int qty, float price) {
    printf("%s\t\t", item);
    printf("%d\t\t", qty);
    printf("%.2f\t\t", qty * price);
    printf("\n");
}

void generateBillFooter(float total) {
    printf("\n");
    float dis = 0.1 * total;
    float netTotal = total - dis;
    float cgst = 0.09 * netTotal;
    float grandTotal = netTotal + 2 * cgst; //netTotal + cgst + sgst
    printf("---------------------------------------\n");
    printf("Sub Total\t\t\t%.2f", total);
    printf("\nDiscount @10%s\t\t\t%.2f", "%", dis);
    printf("\n\t\t\t\t-------");
    printf("\nNet Total\t\t\t%.2f", netTotal);
    printf("\nCGST @9%s\t\t\t%.2f", "%", cgst);
    printf("\nSGST @9%s\t\t\t%.2f", "%", cgst);
    printf("\n---------------------------------------");
    printf("\nGrand Total\t\t\t%.2f", grandTotal);
    printf("\n---------------------------------------\n");
}

struct node* createNode(struct orders ord) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->order = ord;
    newNode->next = NULL;
    return newNode;
}

void deleteInvoice(struct node** head, char name[50]) {
    if (*head == NULL) {
        printf("\nNo invoices found.");
        return;
    }
    struct node* current = *head;
    struct node* prev = NULL;

    if (strcmp(current->order.customer, name) == 0) {
        *head = current->next;
        free(current);
        printf("\nInvoice deleted successfully");
        return;
    }

    while (current != NULL) {
        if (strcmp(current->order.customer, name) == 0) {
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("\nInvoice deleted successfully");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("\nInvoice for %s not found", name);
}

void clearList(struct node** head) {
    struct node* current = *head;
    struct node* next = NULL;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}

int main() {
    char username[10], user[10];
    int password = 1234, pass;
    strcpy(username, "sridevi");
    printf("Enter the username:");
    scanf("%s", user);
    printf("Enter the password");
    scanf("%d", &pass);
    if (strcmp(user, username) == 0 && pass == password)
        printf("Welcome, %s", user);
    else {
        printf("Enter correct credentials!!\n");
        main();
    }
    system("cls");
    int opt, n;
    struct orders ord;
    struct node* head = NULL;
    char saveBill = 'y', contFlag = 'y';
    char name[50];

    while (contFlag == 'y') {
        system("cls");
        float total = 0;
        int invoiceFound = 0;
        printf("\t============ADV. RESTAURANT============");
        printf("\n\nPlease select your preferred operation");
        printf("\n\n1.Generate Invoice");
        printf("\n2.Show all Invoices");
        printf("\n3.Delete Invoice");
        printf("\n4.Exit");

        printf("\n\nYour choice:\t");
        scanf("%d", &opt);
        fgetc(stdin);
        switch (opt) {
            case 1:
                system("cls");
                printf("\nPlease enter the name of the customer:\t");
                fgets(ord.customer, 50, stdin);
                ord.customer[strlen(ord.customer) - 1] = 0;
                strcpy(ord.date, __DATE__);
                printf("\nidly      Rs.40");
                printf("\npongal    Rs.30");
                printf("\ndosa      Rs.20");
                printf("\npuri      Rs.25");
                printf("\nvada      Rs.10");
                printf("\nPlease enter the number of items:\t");
                scanf("%d", &n);
                ord.numOfItems = n;
                for (int i = 0; i < n; i++) {
                    printf("Enter the item number %d\n", i + 1);
                    scanf("%s", ord.itm[i].item);
                    printf("Please enter the quantity:\t");
                    scanf("%d", &ord.itm[i].qty);
                    if (strcmp(ord.itm[i].item, "vada") == 0) {
                        ord.itm[i].price = 10;
                        total += ord.itm[i].qty * ord.itm[i].price;
                    } else if (strcmp(ord.itm[i].item, "idly") == 0) {
                        ord.itm[i].price = 40;
                        total += ord.itm[i].qty * ord.itm[i].price;
                    } else if (strcmp(ord.itm[i].item, "pongal") == 0) {
                        ord.itm[i].price = 30;
                        total += ord.itm[i].qty * ord.itm[i].price;
                    } else if (strcmp(ord.itm[i].item, "dosa") == 0) {
                        ord.itm[i].price = 20;
                        total += ord.itm[i].qty * ord.itm[i].price;
                    } else if (strcmp(ord.itm[i].item, "puri") == 0) {
                        ord.itm[i].price = 25;
                        total += ord.itm[i].qty * ord.itm[i].price;
                    }
                }
                generateBillHeader(ord.customer, ord.date);
                for (int i = 0; i < ord.numOfItems; i++) {
                    generateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
                }
                generateBillFooter(total);

                if (saveBill == 'y') {
                    struct node* newNode = createNode(ord);
                    if (head == NULL) {
                        head = newNode;
                    } else {
                        struct node* current = head;
                        while (current->next != NULL) {
                            current = current->next;
                        }
                        current->next = newNode;
                    }
                }
                break;

            case 2:
                system("cls");
                if (head == NULL) {
                    printf("\nNo invoices found.");
                } else {
                    struct node* current = head;
                    int count = 1;
                    while (current != NULL) {
                        printf("\nInvoice %d:", count);
                        printf("\nCustomer Name: %s", current->order.customer);
                        printf("\nDate: %s", current->order.date);
                        printf("\nItems: \n");
                        for (int i = 0; i < current->order.numOfItems; i++) {
                            printf("%s - %d\n", current->order.itm[i].item, current->order.itm[i].qty);
                        }
                        printf("--------------------------\n");
                        current = current->next;
                        count++;
                    }
                }
                break;

            case 3:
                system("cls");
                if (head == NULL) {
                    printf("\nNo invoices found.");
                } else {
                    printf("\nEnter the name of the customer to delete the invoice:\t");
                    scanf("%s", name);
                    deleteInvoice(&head, name);
                }
                break;

            case 4:
                clearList(&head);
                exit(0);

            default:
                printf("\nInvalid option. Please select a valid option.");
        }
        printf("\nDo you want to continue (y/n)? ");
        scanf(" %c", &contFlag);
    }
    return 0;
}
