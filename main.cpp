#include <iostream>
#include "Notebox.h"
#include "Shared_mem.h"
#include <string>

void showMenu() {
    std::cout << "Welcome to NoteBox!\n";
    std::cout << "1. View all notes\n";
    std::cout << "2. Add a new note\n";
    std::cout << "3. Delete one of my notes\n";
    std::cout << "4. Exit\n";
    std::cout << "Enter your choice: ";
}

int getChoice() {
    int choice;
    std::cin >> choice;
    std::cin.ignore(); // Consume leftover newline
    return choice;
}

int main() {
    NoteBox* box = Shared_memory_create();
    if (!box) {
        std::cerr << "Failed to connect to shared memory.\n";
        return 1;
    }

    std::string author;
    std::cout << "Enter your name: ";
    std::getline(std::cin, author);

    while (true) {
        showMenu();
        int choice = getChoice();

        switch (choice) {
            case 1:
                view_Notes(box);
            break;

            case 2: {
                std::string text;
                std::cout << "Enter your note: ";
                std::getline(std::cin, text);
                add_Note(box, author, text);
                break;
            }

            case 3: {
                int index;
                std::cout << "Enter index of your note to delete: ";
                std::cin >> index;
                std::cin.ignore(); // Clean up newline
                delete_Note(box, index, author);
                break;
            }

            case 4:
                std::cout << "Exiting...\n";
            return 0;

            default:
                std::cout << "Invalid choice. Please enter 1–4.\n";
        }
    }
}
// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.