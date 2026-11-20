# Library Management System (C)

A console-based Library Management System developed in C that manages books, library members, book issuing, returns, and fine calculation. The application uses dynamic memory allocation to manage records at runtime and binary file handling to preserve data between program executions.

## Features

### Book Management
- Add new books to the library
- Increase quantity of existing books
- Display all available books
- Delete books
- Update book details
- Search books by name or subject

### Member Management
- Register new members
- Store and manage member information
- Search members using Member ID

### Book Issue & Return
- Issue books to registered members
- Track issued books
- Return books
- Maintain book availability automatically

### Fine Management
- Calculate fines for overdue books
- One-week borrowing period
- Fine of ₹10 per day after the allowed borrowing period

### Data Persistence
- Store books, members, and issue records in binary files
- Load existing records when the program starts
- Save updated records after operations
- Maintain data across program restarts

## Technologies Used

- C Programming
- Structures
- Pointers
- Dynamic Memory Allocation (`malloc`, `realloc`, `free`)
- File Handling (`fread`, `fwrite`)
- Binary File Storage
- Git & GitHub

## Project Structure

```text
Library-Management-System/
│
├── main.c
├── library.c
├── library.h
├── .gitignore
└── book.dat / member.dat / issue.dat
```

## How to Run

### Prerequisites
- GCC compiler
- Windows, Linux, or another GCC-supported environment

### Compile

```bash
gcc main.c library.c -o library
```

### Run on Windows

```bash
./library.exe
```

### Run on Linux

```bash
./library
```

## Data Files

The program uses the following binary files for persistent storage:

| File | Description |
|---|---|
| `book.dat` | Stores book records and quantities |
| `member.dat` | Stores member records |
| `issue.dat` | Stores book issue and return records |

These files are generated and managed by the application.

## Learning Objectives

This project was developed to practice:

- Dynamic memory management
- Structures and structure pointers
- CRUD operations
- Binary file handling
- Data persistence
- Input validation
- Modular programming in C

## Author

**Prashant Chauhan**

