#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ========== DATA STRUCTURES ==========

struct Product {
    int id;
    char name[100];
    int quantity;
    float price;
};

struct StockItem {
    int id;
    char name[50];
    int quantity;
    int threshold;
    int active;
};

struct Supplier {
    char cat_ID[10];
    char cat_name[30];
    char sup_ID[10];
    char name[30];
    char phone[15];
    char address[100];
};

struct User {
    int userId;
    char name[50];
    char password[20];
    int transId;
    char itemName[50];
    int quantity;
    char status[20];
};

// Linked list structures for file operations
typedef struct ProductNode {
    int id;
    char name[100];
    int quantity;
    float price;
    struct ProductNode *next;
} ProductNode;

typedef struct StockNode {
    int id;
    char name[50];
    int quantity;
    int threshold;
    int active;
    struct StockNode *next;
} StockNode;

typedef struct SupplierNode {
    char cat_ID[10];
    char cat_name[30];
    char sup_ID[10];
    char name[30];
    char phone[15];
    char address[100];
    struct SupplierNode *next;
} SupplierNode;

typedef struct UserNode {
    int userId;
    char name[50];
    char password[20];
    int transId;
    char itemName[50];
    int quantity;
    char status[20];
    struct UserNode *next;
} UserNode;

// ========== ROLE 1: PRODUCT MANAGEMENT ==========

void add_product() {
    FILE *fp = fopen("products.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Product p;
    char buffer[100];
    int valid = 0;

    printf("Enter product ID: ");
    while (scanf("%d", &p.id) != 1) {
        printf("Invalid ID. Enter a valid number: ");
        while (getchar() != '\n');
    }
    getchar();

    printf("Enter product name: ");
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = 0;

    do {
        printf("Enter quantity: ");
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%d", &p.quantity) == 1 && p.quantity >= 0) valid = 1;
        else printf("Invalid input. Try again.\n");
    } while (!valid);

    valid = 0;
    do {
        printf("Enter price: ");
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%f", &p.price) == 1 && p.price >= 0) valid = 1;
        else printf("Invalid input. Try again.\n");
    } while (!valid);

    fprintf(fp, "%d,%s,%d,%.2f\n", p.id, p.name, p.quantity, p.price);
    fclose(fp);
    printf("Product added successfully.\n");
}

void update_product() {
    FILE *fp = fopen("products.txt", "r");
    FILE *temp = fopen("temp_product.txt", "w");
    struct Product p;
    int targetId, found = 0;
    char line[200], buffer[100];
    int valid = 0;

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter product ID to update: ");
    scanf("%d", &targetId);
    getchar();

    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "%d,%[^,],%d,%f", &p.id, p.name, &p.quantity, &p.price) == 4) {
            if (p.id == targetId) {
                found = 1;
                printf("Enter new name: ");
                fgets(p.name, sizeof(p.name), stdin);
                p.name[strcspn(p.name, "\n")] = 0;

                valid = 0;
                do {
                    printf("Enter new quantity: ");
                    fgets(buffer, sizeof(buffer), stdin);
                    if (sscanf(buffer, "%d", &p.quantity) == 1 && p.quantity >= 0) valid = 1;
                    else printf("Invalid quantity.\n");
                } while (!valid);

                valid = 0;
                do {
                    printf("Enter new price: ");
                    fgets(buffer, sizeof(buffer), stdin);
                    if (sscanf(buffer, "%f", &p.price) == 1 && p.price >= 0) valid = 1;
                    else printf("Invalid price.\n");
                } while (!valid);
            }
            fprintf(temp, "%d,%s,%d,%.2f\n", p.id, p.name, p.quantity, p.price);
        }
    }

    fclose(fp);
    fclose(temp);
    remove("products.txt");
    rename("temp_product.txt", "products.txt");

    if (found)
        printf("Product updated successfully.\n");
    else
        printf("Product ID not found.\n");
}

void delete_product() {
    FILE *fp = fopen("products.txt", "r");
    FILE *temp = fopen("temp_product.txt", "w");
    struct Product p;
    int targetId, found = 0;
    char line[200];

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter product ID to delete: ");
    scanf("%d", &targetId);

    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "%d,%[^,],%d,%f", &p.id, p.name, &p.quantity, &p.price) == 4) {
            if (p.id != targetId) {
                fprintf(temp, "%d,%s,%d,%.2f\n", p.id, p.name, p.quantity, p.price);
            } else {
                found = 1;
            }
        }
    }

    fclose(fp);
    fclose(temp);
    remove("products.txt");
    rename("temp_product.txt", "products.txt");

    if (found)
        printf("Product deleted successfully.\n");
    else
        printf("Product ID not found.\n");
}

void view_products() {
    FILE *fp = fopen("products.txt", "r");
    if (fp == NULL) {
        printf("No product records found.\n");
        return;
    }

    struct Product p;
    char line[200];

    printf("\n=== Product List ===\n");

    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "%d,%[^,],%d,%f", &p.id, p.name, &p.quantity, &p.price) == 4) {
            printf("ID: %d | Name: %s | Qty: %d | Price: %.2f\n", p.id, p.name, p.quantity, p.price);
        }
    }

    fclose(fp);
}

void product_menu() {
    int choice;
    do {
        printf("\n=== Product Management Menu ===\n");
        printf("1. Add Product\n");
        printf("2. Update Product\n");
        printf("3. Delete Product\n");
        printf("4. View Products\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: add_product(); break;
            case 2: update_product(); break;
            case 3: delete_product(); break;
            case 4: view_products(); break;
            case 5: printf("Returning to Main Menu...\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 5);
}

// ========== ROLE 2: INVENTORY AND STOCK MANAGEMENT ==========

void addStock() {
    FILE *fp = fopen("inventory.txt", "a");
    if (!fp) {
        printf("Error opening file.\n");
        return;
    }

    struct StockItem item;
    printf("Enter Item ID: ");
    scanf("%d", &item.id);
    while (getchar() != '\n');

    printf("Enter Item Name: ");
    fgets(item.name, sizeof(item.name), stdin);
    item.name[strcspn(item.name, "\n")] = '\0';

    printf("Enter Quantity: ");
    scanf("%d", &item.quantity);

    printf("Enter Threshold: ");
    scanf("%d", &item.threshold);

    item.active = 1;

    fprintf(fp, "%d,%s,%d,%d,%d\n", item.id, item.name, item.quantity, item.threshold, item.active);
    fclose(fp);
    printf("Item added successfully.\n");
}

void viewInventory() {
    FILE *fp = fopen("inventory.txt", "r");
    if (!fp) {
        printf("Error opening file.\n");
        return;
    }

    struct StockItem item;
    char line[200];

    printf("%-5s %-20s %-10s %-10s\n", "ID", "Name", "Qty", "Status");
    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "%d,%49[^,],%d,%d,%d", &item.id, item.name, &item.quantity, &item.threshold, &item.active) == 5) {
            if (item.active) {
                printf("%-5d %-20s %-10d %-10s\n", item.id, item.name, item.quantity,
                       (item.quantity <= item.threshold ? "Low" : "Ok"));
            }
        }
    }

    fclose(fp);
}

void updateStock() {
    FILE *fp = fopen("inventory.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!fp || !temp) {
        printf("Error opening files.\n");
        return;
    }

    int id, change, found = 0;
    struct StockItem item;
    char line[200];

    printf("Enter Item ID to update: ");
    scanf("%d", &id);
    printf("Enter quantity change (positive to increase, negative to decrease): ");
    scanf("%d", &change);

    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "%d,%49[^,],%d,%d,%d", &item.id, item.name, &item.quantity, &item.threshold, &item.active) == 5) {
            if (item.id == id && item.active) {
                item.quantity += change;
                found = 1;
            }
            fprintf(temp, "%d,%s,%d,%d,%d\n", item.id, item.name, item.quantity, item.threshold, item.active);
        }
    }

    fclose(fp);
    fclose(temp);
    remove("inventory.txt");
    rename("temp.txt", "inventory.txt");

    if (found)
        printf("Stock updated.\n");
    else
        printf("Item not found.\n");
}

void removeStock() {
    FILE *fp = fopen("inventory.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!fp || !temp) {
        printf("Error opening files.\n");
        return;
    }

    int id, found = 0;
    struct StockItem item;
    char line[200];

    printf("Enter Item ID to remove: ");
    scanf("%d", &id);

    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "%d,%49[^,],%d,%d,%d", &item.id, item.name, &item.quantity, &item.threshold, &item.active) == 5) {
            if (item.id == id && item.active) {
                item.active = 0;
                found = 1;
            }
            fprintf(temp, "%d,%s,%d,%d,%d\n", item.id, item.name, item.quantity, item.threshold, item.active);
        }
    }

    fclose(fp);
    fclose(temp);
    remove("inventory.txt");
    rename("temp.txt", "inventory.txt");

    if (found)
        printf("Item removed.\n");
    else
        printf("Item not found.\n");
}

void checkLowStock() {
    FILE *fp = fopen("inventory.txt", "r");
    if (!fp) {
        printf("Error opening file.\n");
        return;
    }

    struct StockItem item;
    char line[200];
    int found = 0;

    printf("Low Stock Items:\n");

    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "%d,%49[^,],%d,%d,%d", &item.id, item.name, &item.quantity, &item.threshold, &item.active) == 5) {
            if (item.active && item.quantity <= item.threshold) {
                printf("ID: %d\tName: %s\tQuantity: %d\n", item.id, item.name, item.quantity);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("No items are currently low on stock.\n");
    }

    fclose(fp);
}

void generateReport() {
    printf("\n--- Inventory Report ---\n");
    viewInventory();
}

void inventory_menu() {
    int choice;
    do {
        printf("\n----- Inventory and Stock Management -----\n");
        printf("1. Add Stock\n");
        printf("2. Update Stock\n");
        printf("3. Remove Stock\n");
        printf("4. View Inventory\n");
        printf("5. Generate Inventory Report\n");
        printf("6. Check Low Stock\n");
        printf("7. Exit\n");
        printf("Enter your choice (1-7): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStock(); break;
            case 2: updateStock(); break;
            case 3: removeStock(); break;
            case 4: viewInventory(); break;
            case 5: generateReport(); break;
            case 6: checkLowStock(); break;
            case 7: printf("Returning to Main Menu...\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }

    } while (choice != 7);
}

// ========== ROLE 3: CATEGORY AND SUPPLIER MANAGEMENT ==========

void add_supplier() {
    struct Supplier s;
    FILE *fp = fopen("suppliers.txt", "a");
    if (!fp) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter Category ID: ");
    fgets(s.cat_ID, sizeof(s.cat_ID), stdin);
    s.cat_ID[strcspn(s.cat_ID, "\n")] = '\0';

    printf("Enter Category Name: ");
    fgets(s.cat_name, sizeof(s.cat_name), stdin);
    s.cat_name[strcspn(s.cat_name, "\n")] = '\0';

    printf("Enter Supplier ID: ");
    fgets(s.sup_ID, sizeof(s.sup_ID), stdin);
    s.sup_ID[strcspn(s.sup_ID, "\n")] = '\0';

    printf("Enter Supplier Name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = '\0';

    printf("Enter Phone: ");
    fgets(s.phone, sizeof(s.phone), stdin);
    s.phone[strcspn(s.phone, "\n")] = '\0';

    printf("Enter Address: ");
    fgets(s.address, sizeof(s.address), stdin);
    s.address[strcspn(s.address, "\n")] = '\0';

    fprintf(fp, "%s,%s,%s,%s,%s,%s\n",
            s.cat_ID, s.cat_name, s.sup_ID, s.name, s.phone, s.address);
    fclose(fp);

    printf("Supplier added successfully.\n");
}

void view_supplier() {
    struct Supplier s;
    FILE *fp = fopen("suppliers.txt", "r");

    if (!fp) {
        printf("No supplier data found.\n");
        return;
    }

    printf("\n--- Supplier List ---\n");

    while (fscanf(fp, "%9[^,],%29[^,],%9[^,],%29[^,],%14[^,],%99[^\n]\n",
                  s.cat_ID, s.cat_name, s.sup_ID, s.name, s.phone, s.address) == 6) {
        printf("%s | %s | %s | %s | %s | %s\n",
               s.cat_ID, s.cat_name, s.sup_ID, s.name, s.phone, s.address);
    }

    fclose(fp);
}

void update_supplier() {
    struct Supplier s;
    char targetCatID[10];
    int found = 0;

    FILE *fp = fopen("suppliers.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!fp || !temp) {
        printf("File error.\n");
        return;
    }

    printf("Enter Category ID to update: ");
    fgets(targetCatID, sizeof(targetCatID), stdin);
    targetCatID[strcspn(targetCatID, "\n")] = '\0';

    while (fscanf(fp, "%9[^,],%29[^,],%9[^,],%29[^,],%14[^,],%99[^\n]\n",
                  s.cat_ID, s.cat_name, s.sup_ID, s.name, s.phone, s.address) == 6) {
        if (strcmp(s.cat_ID, targetCatID) == 0) {
            found = 1;

            printf("Enter New Category ID: ");
            fgets(s.cat_ID, sizeof(s.cat_ID), stdin);
            s.cat_ID[strcspn(s.cat_ID, "\n")] = '\0';

            printf("Enter New Category Name: ");
            fgets(s.cat_name, sizeof(s.cat_name), stdin);
            s.cat_name[strcspn(s.cat_name, "\n")] = '\0';

            printf("Enter New Supplier ID: ");
            fgets(s.sup_ID, sizeof(s.sup_ID), stdin);
            s.sup_ID[strcspn(s.sup_ID, "\n")] = '\0';

            printf("Enter New Name: ");
            fgets(s.name, sizeof(s.name), stdin);
            s.name[strcspn(s.name, "\n")] = '\0';

            printf("Enter New Phone: ");
            fgets(s.phone, sizeof(s.phone), stdin);
            s.phone[strcspn(s.phone, "\n")] = '\0';

            printf("Enter New Address: ");
            fgets(s.address, sizeof(s.address), stdin);
            s.address[strcspn(s.address, "\n")] = '\0';
        }

        fprintf(temp, "%s,%s,%s,%s,%s,%s\n",
                s.cat_ID, s.cat_name, s.sup_ID, s.name, s.phone, s.address);
    }

    fclose(fp);
    fclose(temp);
    remove("suppliers.txt");
    rename("temp.txt", "suppliers.txt");

    if (found)
        printf("Supplier updated successfully.\n");
    else
        printf("Category ID not found.\n");
}

void delete_supplier() {
    struct Supplier s;
    char targetCatID[10];
    int found = 0;

    FILE *fp = fopen("suppliers.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!fp || !temp) {
        printf("File error.\n");
        return;
    }

    printf("Enter Category ID to delete: ");
    fgets(targetCatID, sizeof(targetCatID), stdin);
    targetCatID[strcspn(targetCatID, "\n")] = '\0';

    while (fscanf(fp, "%9[^,],%29[^,],%9[^,],%29[^,],%14[^,],%99[^\n]\n",
                  s.cat_ID, s.cat_name, s.sup_ID, s.name, s.phone, s.address) == 6) {
        if (strcmp(s.cat_ID, targetCatID) == 0) {
            found = 1;
            continue;
        }

        fprintf(temp, "%s,%s,%s,%s,%s,%s\n",
                s.cat_ID, s.cat_name, s.sup_ID, s.name, s.phone, s.address);
    }

    fclose(fp);
    fclose(temp);
    remove("suppliers.txt");
    rename("temp.txt", "suppliers.txt");

    if (found)
        printf("Supplier deleted successfully.\n");
    else
        printf("Category ID not found.\n");
}

void supplier_menu() {
    int choice;

    do {
        printf("\n=== Supplier Management ===\n");
        printf("1. Add Supplier\n");
        printf("2. View Suppliers\n");
        printf("3. Update Supplier\n");
        printf("4. Delete Supplier\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: add_supplier(); break;
            case 2: view_supplier(); break;
            case 3: update_supplier(); break;
            case 4: delete_supplier(); break;
            case 5: printf("Returning to Main Menu...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 5);
}

// ========== ROLE 4: USER AND TRANSACTION MANAGEMENT ==========

void add_user() {
    FILE *fp = fopen("records.txt", "a");
    if (fp == NULL) {
        printf("Error: Cannot open records.txt for writing.\n");
        return;
    }

    struct User r;

    printf("Enter user ID: ");
    scanf("%d", &r.userId);
    printf("Enter user Name: ");
    scanf("%s", r.name);
    printf("Password (4 digits): ");
    scanf("%s", r.password);
    printf("Transaction ID: ");
    scanf("%d", &r.transId);
    printf("Item Name: ");
    scanf("%s", r.itemName);
    printf("Quantity: ");
    scanf("%d", &r.quantity);
    printf("Status: ");
    scanf("%s", r.status);

    fprintf(fp, "%d,%s,%s,%d,%s,%d,%s\n", r.userId, r.name, r.password, r.transId, r.itemName, r.quantity, r.status);
    fclose(fp);

    printf("User and transaction added successfully.\n");
}

void update_user() {
    FILE *fp = fopen("records.txt", "r");
    FILE *tmp = fopen("tmp.txt", "w");

    if (fp == NULL || tmp == NULL) {
        printf("File error.\n");
        return;
    }

    char line[200];
    struct User r;
    int id, found = 0;

    printf("Enter User ID to update: ");
    scanf("%d", &id);

    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "%d,%49[^,],%19[^,],%d,%49[^,],%d,%19[^\n]",
            &r.userId, r.name, r.password, &r.transId, r.itemName, &r.quantity, r.status) == 7) {

            if (r.userId == id) {
                found = 1;
                printf("New name: ");
                scanf("%s", r.name);
                printf("New password: ");
                scanf("%s", r.password);
            }

            fprintf(tmp, "%d,%s,%s,%d,%s,%d,%s\n", r.userId, r.name, r.password, r.transId, r.itemName, r.quantity, r.status);
        }
    }

    fclose(fp);
    fclose(tmp);
    remove("records.txt");
    rename("tmp.txt", "records.txt");

    if (found) printf("User info updated.\n");
    else printf("User ID not found.\n");
}

void update_transaction() {
    FILE *fp = fopen("records.txt", "r");
    FILE *tmp = fopen("tmp.txt", "w");

    if (fp == NULL || tmp == NULL) {
        printf("File error.\n");
        return;
    }

    char line[200];
    struct User r;
    int id, found = 0;

    printf("Enter Transaction ID to update: ");
    scanf("%d", &id);

    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "%d,%[^,],%[^,],%d,%[^,],%d,%[^\n]",
            &r.userId, r.name, r.password, &r.transId, r.itemName, &r.quantity, r.status) == 7) {

            if (r.transId == id) {
                found = 1;
                printf("New item name: ");
                scanf(" %[^\n]", r.itemName);
                printf("New quantity: ");
                scanf("%d", &r.quantity);
                printf("New status: ");
                scanf(" %[^\n]", r.status);
            }

            fprintf(tmp, "%d,%s,%s,%d,%s,%d,%s\n", r.userId, r.name, r.password, r.transId, r.itemName, r.quantity, r.status);
        }
    }

    fclose(fp);
    fclose(tmp);
    remove("records.txt");
    rename("tmp.txt", "records.txt");

    if (found) printf("Transaction updated.\n");
    else printf("Transaction ID not found.\n");
}

void delete_user() {
    FILE *fp = fopen("records.txt", "r");
    FILE *tmp = fopen("tmp.txt", "w");

    if (fp == NULL || tmp == NULL) {
        printf("File error.\n");
        return;
    }

    char line[200];
    struct User r;
    int id, found = 0;

    printf("Enter user ID to remove: ");
    scanf("%d", &id);

    while (fgets(line, sizeof(line), fp)){
        if (sscanf(line, "%d,%[^,],%[^,],%d,%[^,],%d,%[^\n]",
            &r.userId, r.name, r.password, &r.transId, r.itemName, &r.quantity, r.status) == 7) {

            if (r.userId != id) {
                fprintf(tmp, "%d,%s,%s,%d,%s,%d,%s\n", r.userId, r.name, r.password, r.transId, r.itemName, r.quantity, r.status);
            } else {
                found = 1;
            }
        }
    }

    fclose(fp);
    fclose(tmp);
    remove("records.txt");
    rename("tmp.txt", "records.txt");

    if (found) printf("Record deleted.\n");
    else printf("User ID not found.\n");
}

void view_user() {
    FILE *fp = fopen("records.txt", "r");

    if (fp == NULL) {
        printf("File error.\n");
        return;
    }

    char line[200];
    struct User r;

    printf("User Details\n");
    printf("-----------------------\n");

    while (fgets(line, sizeof(line), fp)){
        if (sscanf(line, "%d,%[^,],%[^,],%d,%[^,],%d,%[^\n]",
            &r.userId, r.name, r.password, &r.transId, r.itemName, &r.quantity, r.status) == 7) {

            printf("UserID: %d\nName: %s\nPassword: %s\n", r.userId, r.name, r.password);
            printf("TransID: %d\nItem: %s\nQty: %d\nStatus: %s\n\n", r.transId, r.itemName, r.quantity, r.status);
        }
    }

    fclose(fp);
}

void user_menu() {
    int choice;

    do {
        printf("User and Transaction Management Menu\n");
        printf("-----------------------------------------\n");
        printf("1. Add new users and transaction records\n");
        printf("2. Update user information\n");
        printf("3. Update transaction information\n");
        printf("4. Delete/archive transactions and user accounts\n");
        printf("5. View user details and transaction history\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_user(); break;
            case 2: update_user(); break;
            case 3: update_transaction(); break;
            case 4: delete_user(); break;
            case 5: view_user(); break;
            case 6: printf("Returning to Main Menu...\n"); break;
            default: printf("Invalid choice. Select (1-6)\n");
        }
    } while (choice >= 1 && choice <= 5);
}

// ========== ROLE 5: FILE OPERATIONS AND ADVANCED FEATURES ==========
// Add these functions to your existing code

// Function to read products from file into linked list
ProductNode* ProductLists() {
    FILE *fp = fopen("products.txt", "r"); //read products.txt
    if (!fp) return NULL;
    ProductNode *start = NULL, *end = NULL;
    while (1) {
        ProductNode *p = malloc(sizeof(ProductNode)); //allocate memory with malloc
        //data types to read
        if (fscanf(fp, "%d,%99[^,],%d,%f\n", &p->id, p->name, &p->quantity, &p->price) != 4) {
            free(p); break;
        }
        p->next = NULL;
        if (!start) start = end = p;
        else { end->next = p; end = p; }
    }
    fclose(fp);
    return start;
}

//show product list
void ShowProducts(ProductNode *start) {
    printf("\n=== Product List ===\n");
    while (start) {
        printf("Product ID: %d |Name: %s |Quantity: %d |Price: %.2f\n", //product list 
               start->id, start->name, start->quantity, start->price);
        start = start->next;
    }
}

//save the products
void SaveProduct(ProductNode *start) {
    FILE *fp = fopen("products.txt", "w");
    if (!fp) return;
    while (start) {
        fprintf(fp, "%d,%s,%d,%.2f\n", start->id, start->name, start->quantity, start->price);
        start = start->next;
    }
    fclose(fp);
}

//update product
void UpdateProduct(ProductNode *start) {
    int updatedID;
    printf("Enter Product ID to update: ");
    scanf("%d", &updatedID);
    getchar();
    
    ProductNode *current = start;
    while (current) {
        if (current->id == updatedID) {
            printf("Enter new name: ");
            fgets(current->name, sizeof(current->name), stdin);
            current->name[strcspn(current->name, "\n")] = '\0';
            printf("Enter new quantity: ");
            scanf("%d", &current->quantity);
            printf("Enter new price: ");
            scanf("%f", &current->price);
            SaveProduct(start);
            printf("Success updating product.\n");
            return;
        }
        current = current->next;
    }
    printf("Product ID not found. Please re-check your product ID!\n");
}

//remove product
void DeleteProduct(ProductNode **ref) {
    int updatedID;
    printf("Enter Product ID to delete: ");
    scanf("%d", &updatedID);
    getchar();
    ProductNode *current = *ref;
    ProductNode *prev = NULL;
    while (current) {
        if (current->id == updatedID) {
            if (prev == NULL) *ref = current->next;
            else prev->next = current->next;
            free(current);
            SaveProduct(*ref);
            printf("Product deleted successfully.\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Product ID not found. Please re-check again!\n");
}

//remove product list from linked list
void RemoveProduct(ProductNode *start) {
    while (start) {
        ProductNode *temp = start;
        start = start->next;
        free(temp);
    }
}

//inventory list
StockNode* InventoryLists() {
    FILE *fp = fopen("inventory.txt", "r");
    if (!fp) return NULL;
    StockNode *start = NULL, *end = NULL;
    while (1) {
        StockNode *item = malloc(sizeof(StockNode));
        if (fscanf(fp, "%d,%49[^,],%d,%d,%d\n", &item->id, item->name, &item->quantity, &item->threshold, &item->active) != 5) {
            free(item); break;
        }
        item->next = NULL;
        if (!start) start = end = item;
        else { end->next = item; end = item;}
    }
    fclose(fp);
    return start;
}
//show stock in inventory lists
void ShowInventory(StockNode *start) {
    printf("\n=== Inventory List ===\n");
    while (start) {
        printf("ItemID: %d | Name: %s | Quantity: %d | Threshold: %d | Active: %d\n",
               start->id, start->name, start->quantity, start->threshold, start->active);
        start = start->next;
    }
}

//save the stocks
void SaveInventory(StockNode *start) {
    FILE *fp = fopen("inventory.txt", "w");
    if (!fp) return;
    while (start) {
        fprintf(fp, "%d,%s,%d,%d,%d\n", start->id, start->name, start->quantity, start->threshold, start->active);
        start = start->next;
    }
    fclose(fp);
}

//update the inventory list
void UpdateInventory(StockNode *start) {
    int updatedID;
    printf("Enter Inventory ID to update: ");
    scanf("%d", &updatedID); getchar();
    StockNode *current = start;
    while (current) {
        if (current->id == updatedID) {
            printf("Enter new name: ");
            fgets(current->name, sizeof(current->name), stdin);
            current->name[strcspn(current->name, "\n")] = '\0';
            printf("Enter new quantity: ");
            scanf("%d", &current->quantity);
            printf("Enter new threshold: ");
            scanf("%d", &current->threshold);
            printf("Enter new active (0 or 1): ");
            scanf("%d", &current->active);
            SaveInventory(start);
            printf("Inventory updated.\n");
            return;
        }
        current = current->next;
    }
    printf("Inventory ID not found. Please re-check again!\n");
}

//delete a stock in inventory
void DeleteInventory(StockNode **ref) {
    int updatedID;
    printf("Enter Inventory ID to delete: ");
    scanf("%d", &updatedID); 
    getchar();
    StockNode *current = *ref, *prev = NULL;
    while (current) {
        if (current->id == updatedID) {
            if (!prev) *ref = current->next;
            else prev->next = current->next;
            free(current);
            SaveInventory(*ref);
            printf("Inventory deleted.\n");
            return;
        }
        prev = current; current = current->next;
    }
    printf("Inventory ID not found. Please re-check again!\n");
}

//free up inventory from the linked list
void RemoveInventory(StockNode *start) {
    while (start) {
        StockNode *temp = start;
        start = start->next;
        free(temp);
    }
}

//supplier lists
SupplierNode* SupplierLists() {
    FILE *fp = fopen("suppliers.txt", "r");
    if (!fp) return NULL;
    SupplierNode *start = NULL, *end = NULL;
    while (1) {
        SupplierNode *s = malloc(sizeof(SupplierNode));
        if (fscanf(fp, "%9[^,],%29[^,],%9[^,],%29[^,],%14[^,],%99[^\n]\n",
                   s->cat_ID, s->cat_name, s->sup_ID, s->name, s->phone, s->address) != 6) {
            free(s); break;
        }
        s->next = NULL;
        if (!start) start = end = s;
        else { end->next = s; end = s; }
    }
    fclose(fp);
    return start;
}

//show the supplier lists
void ShowSuppliers(SupplierNode *start) {
    printf("\n=== Supplier List ===\n");
    while (start) {
        printf("CategoryID: %s | CatName: %s | SupplierID: %s | SupName: %s | Phone: %s | Address: %s\n",
               start->cat_ID, start->cat_name, start->sup_ID, start->name, start->phone, start->address);
        start = start->next;
    }
}

//save the supplier list
void SaveSupplier(SupplierNode *start) {
    FILE *fp = fopen("suppliers.txt", "w");
    if (!fp) return;
    while (start) {
        fprintf(fp, "%s,%s,%s,%s,%s,%s\n",
                start->cat_ID, start->cat_name, start->sup_ID,
                start->name, start->phone, start->address);
        start = start->next;
    }
    fclose(fp);
}

//update the supplier list
void UpdateSuppliers(SupplierNode *start) {
    char updatedID[10];
    printf("Enter Supplier ID to update: ");
    fgets(updatedID, sizeof(updatedID), stdin);
    updatedID[strcspn(updatedID, "\n")] = '\0';
    while (start) {
        if (strcmp(start->sup_ID, updatedID) == 0) {
            printf("Enter new Category ID: "); 
            fgets(start->cat_ID, sizeof(start->cat_ID), stdin); 
            start->cat_ID[strcspn(start->cat_ID, "\n")] = '\0';
            printf("Enter new Category Name: "); 
            fgets(start->cat_name, sizeof(start->cat_name), stdin); 
            start->cat_name[strcspn(start->cat_name, "\n")] = '\0';
            printf("Enter new Supplier Name: "); 
            fgets(start->name, sizeof(start->name), stdin); 
            start->name[strcspn(start->name, "\n")] = '\0';
            printf("Enter new Phone: "); 
            fgets(start->phone, sizeof(start->phone), stdin); 
            start->phone[strcspn(start->phone, "\n")] = '\0';
            printf("Enter new Address: "); 
            fgets(start->address, sizeof(start->address), stdin); 
            start->address[strcspn(start->address, "\n")] = '\0';
            SaveSupplier(start);
            printf("Supplier updated.\n");
            return;
        }
        start = start->next;
    }
    printf("Supplier ID not found. Please re-check again!\n");
}

//to delete a supplier
void DeleteSupplier(SupplierNode **ref) {
    char updatedID[10];
    printf("Enter Supplier ID to delete: ");
    fgets(updatedID, sizeof(updatedID), stdin);
    updatedID[strcspn(updatedID, "\n")] = '\0';

    SupplierNode *current = *ref, *prev = NULL;
    while (current) {
        if (strcmp(current->sup_ID, updatedID) == 0) {
            if (!prev) *ref = current->next;
            else prev->next = current->next;
            free(current);
            SaveSupplier(*ref);
            printf("Supplier deleted.\n");
            return;
        }
        prev = current; current = current->next;
    }
    printf("Supplier ID not found. Please re-check again!\n");
}

//free up the supplier list from linked list
void RemoveSupplier(SupplierNode *start) {
    while (start) {
        SupplierNode *temp = start;
        start = start->next;
        free(temp);
    }
}

//user list
UserNode* UserLists() {
    FILE *fp = fopen("records.txt", "r");
    if (!fp) return NULL;
    UserNode *start = NULL, *end = NULL;
    while (1) {
        UserNode *r = malloc(sizeof(UserNode));
        if (fscanf(fp, "%d,%49[^,],%19[^,],%d,%49[^,],%d,%19[^\n]\n",
                   &r->userId, r->name, r->password, &r->transId, r->itemName, &r->quantity, r->status) != 7) {
            free(r); break;
        }
        r->next = NULL;
        if (!start) start = end = r;
        else { end->next = r; end = r; }
    }
    fclose(fp);
    return start;
}

//show the user list
void ShowUsers(UserNode *start) {
    printf("\n=== User and Transaction List ===\n");
    while (start) {
        printf("UserID: %d | Name: %s | TransID: %d | Item: %s | Quantity: %d | Status: %s\n",
               start->userId, start->name, start->transId, start->itemName, start->quantity, start->status);
        start = start->next;
    }
}

//save the user list
void SaveUser(UserNode *start) {
    FILE *fp = fopen("records.txt", "w");
    if (!fp) return;
    while (start) {
        fprintf(fp, "%d,%s,%s,%d,%s,%d,%s\n",
                start->userId, start->name, start->password,
                start->transId, start->itemName, start->quantity, start->status);
        start = start->next;
    }
    fclose(fp);
}

//update the user list
void UpdateUser(UserNode *start) {
    int updatedID;
    printf("Enter User ID to update: ");
    scanf("%d", &updatedID); 
    getchar();

    while (start) {
        if (start->userId == updatedID) {
            printf("Enter new name: "); 
            fgets(start->name, sizeof(start->name), stdin); 
            start->name[strcspn(start->name, "\n")] = '\0';
            printf("Enter new password: "); 
            fgets(start->password, sizeof(start->password), stdin); 
            start->password[strcspn(start->password, "\n")] = '\0';
            printf("Enter new transaction ID: "); 
            scanf("%d", &start->transId); 
            getchar();
            printf("Enter new item name: "); 
            fgets(start->itemName, sizeof(start->itemName), stdin); 
            start->itemName[strcspn(start->itemName, "\n")] = '\0';
            printf("Enter new quantity: "); 
            scanf("%d", &start->quantity); 
            getchar();
            printf("Enter new status: ");
            fgets(start->status, sizeof(start->status), stdin); start->status[strcspn(start->status, "\n")] = '\0';
            SaveUser(start);
            printf("User updated.\n");
            return;
        }
        start = start->next;
    }
    printf("User ID not found. Please re-check again!\n");
}

//delete a user
void DeleteUser(UserNode **ref) {
    int updatedID;
    printf("Enter User ID to delete: ");
    scanf("%d", &updatedID); 
    getchar();

    UserNode *current = *ref, *prev = NULL;
    while (current) {
        if (current->userId == updatedID) {
            if (!prev) *ref = current->next;
            else prev->next = current->next;
            free(current);
            SaveUser(*ref);
            printf("User deleted.\n");
            return;
        }
        prev = current; current = current->next;
    }
    printf("User ID not found. Please re-check again!\n");
}

//free up the user list from the linked list
void RemoveUser(UserNode *start) {
    while (start) {
        UserNode *temp = start;
        start = start->next;
        free(temp);
    }
}

//as an additional feature to create a pause after using a function
void pause() {
    printf("\nPress Enter to continue");
    while (getchar() != '\n');
}

//main menu for file operations menu
int file_operations_menu() {
    int choice;

    do {
        printf("\n=== File Control Menu ===\n");
        printf("1. View Products\n");
        printf("2. View Inventory\n");
        printf("3. View Suppliers and Categories\n");
        printf("4. View Users & Transactions\n");
        printf("==================\n");
        printf("5. Update Product\n");
        printf("6. Update Inventory\n");
        printf("7. Update Supplier\n");
        printf("8. Update User\n");
        printf("==================\n");
        printf("9. Delete Product\n");
        printf("10. Delete Inventory\n");
        printf("11. Delete Supplier\n");
        printf("12. Delete User\n");
        printf("13. Exit to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice); 
        getchar();

        switch (choice) {
            case 1: {
                ProductNode *p = ProductLists();
                if (p) ShowProducts(p);
                else printf("No products found. Please check if you have the correct file!\n");
                RemoveProduct(p);
                break;
            }
            case 2: {
                StockNode *item = InventoryLists();
                if (item) ShowInventory(item);
                else printf("No inventory records found. Please check if you have the correct file!\n");
                RemoveInventory(item);
                break;
            }
            case 3: {
                SupplierNode *s = SupplierLists();
                if (s) ShowSuppliers(s);
                else printf("No supplier records found. Please check if you have the correct file!\n");
                RemoveSupplier(s);
                break;
            }
            case 4: {
                UserNode *r = UserLists();
                if (r) ShowUsers(r);
                else printf("No user records found. Please check if you have the correct file!\n");
                RemoveUser(r);
                break;
            }
            case 5: {
                ProductNode *p = ProductLists();
                if (p) UpdateProduct(p);
                else printf("Unable to update, products.txt missing!\n");
                RemoveProduct(p);
                break;
            }
            case 6: {
                StockNode *item = InventoryLists();
                if (item) UpdateInventory(item);
                else printf("Unable to update, inventory.txt missing!\n");
                RemoveInventory(item);
                break;
            }
            case 7: {
                SupplierNode *s = SupplierLists();
                if (s) UpdateSuppliers(s);
                else printf("Unable to update, suppliers.txt missing!\n");
                RemoveSupplier(s);
                break;
            }
            case 8: {
                UserNode *u = UserLists();
                if (u) UpdateUser(u);
                else printf("Unable to update, records.txt missing!\n");
                RemoveUser(u);
                break;
            }
            case 9: {
                ProductNode *p = ProductLists();
                if (p) DeleteProduct(&p);
                else printf("Unable to delete, products.txt missing!\n");
                RemoveProduct(p);
                break;
            }
            case 10: {
                StockNode *item = InventoryLists();
                if (item) DeleteInventory(&item);
                else printf("Unable to delete, inventory.txt missing!\n");
                RemoveInventory(item);
                break;
            }
            case 11: {
                SupplierNode *s = SupplierLists();
                if (s) DeleteSupplier(&s);
                else printf("Unable to delete, suppliers.txt missing!\n");
                RemoveSupplier(s);
                break;
            }
            case 12: {
                UserNode *u = UserLists();
                if (u) DeleteUser(&u);
                else printf("Unable to delete, records.txt missing!\n");
                RemoveUser(u);
                break;
            }
            case 13:
                printf("Exiting to The Main Menu.\n");
                break;

            default:
                printf("Invalid option. Please choose a number between 1 - 13!\n");
        }
        if(choice != 13) pause();
    } while (choice != 13);
    return 0;
}

//the main menu
void mainMenu(){
    int choice;

    do {
        printf("Choose role\n");
        printf("1. Core System and Product Management\n");
        printf("2. Inventory and Stock Management\n");
        printf("3. Category and Supplier Management\n");
        printf("4. User and Transaction Management\n");
        printf("5. File Operations and Advanced Features\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: product_menu(); break;
            case 2: inventory_menu(); break;
            case 3: supplier_menu(); break;
            case 4: user_menu(); break;
            case 5: file_operations_menu(); break;
            case 6: printf("Exiting..\n"); break;
            default: printf("Invalid choice. Select (1-6)\n");
        }
    } while (choice >= 1 && choice <= 5);

    return 0;
}

int main() {
    mainMenu();
    return 0;
}
