#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

class Contact {
public:
    string name, address, phone;

    void getInput() {
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Address: ";
        getline(cin, address);
        cout << "Enter Phone Number: ";
        getline(cin, phone);
    }

    void display() const {
        cout << left << setw(20) << name << setw(30) << address << setw(15) << phone << endl;
    }
};

void addRecord() {
    Contact contact;
    ofstream outFile("directory.dat", ios::binary | ios::app);
    contact.getInput();
    outFile.write(reinterpret_cast<char*>(&contact), sizeof(contact));
    outFile.close();
    cout << "Record added successfully.\n";
}

void viewRecords() {
    Contact contact;
    ifstream inFile("directory.dat", ios::binary);
    if (!inFile) {
        cout << "No records found.\n";
        return;
    }
    cout << left << setw(20) << "Name" << setw(30) << "Address" << setw(15) << "Phone Number" << endl;
    while (inFile.read(reinterpret_cast<char*>(&contact), sizeof(contact))) {
        contact.display();
    }
    inFile.close();
}

void searchRecord() {
    Contact contact;
    string searchName;
    bool found = false;
    ifstream inFile("directory.dat", ios::binary);
    if (!inFile) {
        cout << "No records found.\n";
        return;
    }
    cout << "Enter the name to search: ";
    cin.ignore();
    getline(cin, searchName);
    while (inFile.read(reinterpret_cast<char*>(&contact), sizeof(contact))) {
        if (contact.name == searchName) {
            cout << "Record found:\n";
            contact.display();
            found = true;
            break;
        }
    }
    inFile.close();
    if (!found) {
        cout << "Record not found.\n";
    }
}

void modifyRecord() {
    Contact contact;
    string searchName;
    bool found = false;
    fstream file("directory.dat", ios::binary | ios::in | ios::out);
    if (!file) {
        cout << "No records found.\n";
        return;
    }
    cout << "Enter the name to modify: ";
    cin.ignore();
    getline(cin, searchName);
    while (file.read(reinterpret_cast<char*>(&contact), sizeof(contact))) {
        if (contact.name == searchName) {
            cout << "Existing Record:\n";
            contact.display();
            cout << "Enter new details:\n";
            contact.getInput();
            int pos = (-1) * static_cast<int>(sizeof(contact));
            file.seekp(pos, ios::cur);
            file.write(reinterpret_cast<char*>(&contact), sizeof(contact));
            found = true;
            cout << "Record updated successfully.\n";
            break;
        }
    }
    file.close();
    if (!found) {
        cout << "Record not found.\n";
    }
}

void deleteRecord() {
    Contact contact;
    string searchName;
    bool found = false;
    ifstream inFile("directory.dat", ios::binary);
    ofstream tempFile("temp.dat", ios::binary);
    if (!inFile) {
        cout << "No records found.\n";
        return;
    }
    cout << "Enter the name to delete: ";
    cin.ignore();
    getline(cin, searchName);
    while (inFile.read(reinterpret_cast<char*>(&contact), sizeof(contact))) {
        if (contact.name != searchName) {
            tempFile.write(reinterpret_cast<char*>(&contact), sizeof(contact));
        } else {
            found = true;
        }
    }
    inFile.close();
    tempFile.close();
    remove("directory.dat");
    rename("temp.dat", "directory.dat");
    if (found) {
        cout << "Record deleted successfully.\n";
    } else {
        cout << "Record not found.\n";
    }
}

int main() {
    int choice;
    do {
        cout << "\nTelephone Directory System\n";
        cout << "1. Add Record\n";
        cout << "2. View Records\n";
        cout << "3. Search Record\n";
        cout << "4. Modify Record\n";
        cout << "5. Delete Record\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addRecord();
            break;
        case 2:
            viewRecords();
            break;
        case 3:
            searchRecord();
            break;
        case 4:
            modifyRecord();
            break;
        case 5:
            deleteRecord();
            break;
        case 6:
            cout << "Exiting the program.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
