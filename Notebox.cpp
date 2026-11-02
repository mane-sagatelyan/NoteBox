#include "Notebox.h"
#include <iostream>
#include <cstring>
#include <ctime>

void view_Notes(NoteBox* box) {
    pthread_mutex_lock(&box->mutex);
    for (int i = 0; i < MAX_NOTES; ++i) {
        if (box->notes[i].active) {
            std::cout << "[" << i << "] by " << box->notes[i].author << " at " << box->notes[i].timestamp << "\n";
            std::cout << box->notes[i].text << "\n";
        }
    }
    pthread_mutex_unlock(&box->mutex);
}
void add_Note(NoteBox* box, const std::string& author, const std::string& text) {
  pthread_mutex_lock(&box->mutex);
  int found = -1;
  for (int i = 0; i < MAX_NOTES; ++i) {
    if (!box->notes[i].active) {
      found = i;
      break;
    }
  }
  if(found == -1) {
    std::cerr << "NoteBox is full. Cannot add new note.\n";
  }
  else {
   	Note& note = box->notes[found];
    strncpy(note.author, author.c_str(), sizeof(note.author) - 1);
    note.author[sizeof(note.author) - 1] = '\0';

    std::time_t now = std::time(nullptr);
    std::strftime(note.timestamp, sizeof(note.timestamp), "%Y-%m-%d %H:%M", std::localtime(&now));

    strncpy(note.text, text.c_str(), sizeof(note.text) - 1);
    note.text[sizeof(note.text) - 1] = '\0';

    note.active = 1;
    std::cout << "Note added successfully.\n";
  }
  pthread_mutex_unlock(&box->mutex);
}
void delete_Note(NoteBox* box, int index, const std::string& author) {
    if (index < 0 || index >= MAX_NOTES) {
        std::cout << "Invalid note index.\n";
        return;
    }

    pthread_mutex_lock(&box->mutex);
    Note& note = box->notes[index];

    if (!note.active) {
        std::cout << "Invalid note index.\n";
    } else if (author != note.author) {
        std::cout << "You can only delete your own notes.\n";
    } else {
        note.active = 0;
        std::cout << "Note deleted successfully.\n";
    }

    pthread_mutex_unlock(&box->mutex);
}
