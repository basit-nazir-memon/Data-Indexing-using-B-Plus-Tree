# Data Indexing using B+ Tree

This is a C++ program that indexes data files and allows for efficient retrieval using B-tree and B+ tree data structures. The program functions similarly to a database, allowing users to execute queries to select specific data from the indexed files.

## Program Overview

The program provides the following functionalities for data indexing and retrieval:

- **SELECT DATA**: Retrieves all data from the indexed files.
- **SELECT DATA WHERE ID = 5**: Retrieves a specific data row with the given ID.
- **SELECT DATA WHERE ID < 20**: Retrieves a specific portion of data where the ID is less than 20.

## Program Structure

The program consists of the following files:

- `Header1.h`, `Header2.h`, `Header3.h`: These header files contain declarations and definitions related to the B-tree and B+ tree data structures, as well as auxiliary functions and utilities.
- `Source2.cpp`: This source file contains the main implementation of the program, including the user interface and interaction with the B-tree and B+ tree data structures.
- `output.txt`: This text file stores the output of the recently executed queries.
- Data files: The program uses text files to store the data that is indexed and retrieved.

## Compilation

To compile the program, follow these steps:

1. Ensure that you have a C++ compiler installed on your system (e.g., g++ for Linux or MinGW for Windows).
2. Open a terminal or command prompt and navigate to the directory containing the program files.
3. Run the following command to compile the program:

```shell
g++ Source2.cpp -o data_indexing
```

This command compiles `Source2.cpp` and generates an executable named `data_indexing`.

## Usage

To run the program, execute the following command in the terminal or command prompt:

```shell
./data_indexing
```

The program will provide a menu of options for executing queries and interacting with the data indexing functionality. Follow the on-screen instructions to execute the desired queries and retrieve the data.

## Input and Output Files

The program relies on text files to store the data that is indexed and retrieved. Ensure that the required input files are present in the same directory as the program executable. The program may also generate an `output.txt` file that stores the output of the most recently executed queries.

## Contributing

If you would like to contribute to this program, please follow these steps:

1. Fork the repository.
2. Create a new branch for your changes.
3. Make the necessary modifications and improvements.
4. Test your changes thoroughly.
5. Commit and push your changes to your forked repository.
6. Open a pull request, describing the changes you have made.

Your contributions are greatly appreciated!

## License

This program is licensed under the [MIT License](LICENSE). Feel free to modify and distribute it according to the terms of the license.

## Contact

If you have any questions or suggestions regarding this program, please contact basitnazir585@gmail.com.

Thank you for using our Data Indexing using B+ Tree program!
