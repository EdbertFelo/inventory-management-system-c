# Inventory Management System in C

A console-based **Inventory Management System** developed in **C** that manages products, stock, suppliers, users, and transactions through a menu-driven interface. The program stores data in text files and includes linked-list-based file reading for advanced file operations.

## Features

This system is divided into 5 main modules:

### 1. Product Management
- Add product
- Update product
- Delete product
- View all products

### 2. Inventory and Stock Management
- Add stock items
- Update stock quantity
- Remove stock items
- View inventory
- Generate inventory report
- Check low stock items based on threshold

### 3. Category and Supplier Management
- Add supplier
- View suppliers
- Update supplier
- Delete supplier

### 4. User and Transaction Management
- Add user and transaction records
- Update user information
- Update transaction information
- Delete user records
- View user details and transaction history

### 5. File Operations and Advanced Features
- Read product, inventory, supplier, and user records from text files
- Store data using linked lists
- Display records loaded from files
- Free dynamically allocated memory after use

## Technologies Used
- **Language:** C
- **Concepts:** Structures, linked lists, file handling, dynamic memory allocation, menu-driven programming
- **Storage:** Text files (`.txt`)

## File Structure

The program uses the following files to store data:

- `products.txt` → Stores product records
- `inventory.txt` → Stores stock and inventory records
- `suppliers.txt` → Stores supplier and category records
- `records.txt` → Stores user and transaction records

Temporary files may also be created during update/delete operations:
- `temp.txt`
- `temp_product.txt`
- `tmp.txt`

## How It Works

When the program starts, the user is shown a main menu with 5 roles/modules:

1. Core System and Product Management  
2. Inventory and Stock Management  
3. Category and Supplier Management  
4. User and Transaction Management  
5. File Operations and Advanced Features  

Each module contains its own submenu with CRUD-style operations and file-based record management.

## How to Compile and Run

### Using GCC
```bash
gcc -o inventory_system "Assignment ALL PARTS.c"
./inventory_system
