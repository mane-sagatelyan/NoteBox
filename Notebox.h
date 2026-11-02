#ifndef NOTEBOX_H
#define NOTEBOX_H
#define MAX_NOTES 20
#define MAX_TEXT 200

#include <pthread.h>
#include <string>
typedef struct {char author[32];
    char timestamp[32];
    char text[MAX_TEXT];
    int active;
} Note;
typedef struct {
    Note notes[MAX_NOTES];
    pthread_mutex_t mutex;
} NoteBox;

void view_Notes(NoteBox *notebox);
void add_Note(NoteBox *notebox, const std::string& author, const std::string& text);
void delete_Note(NoteBox* box, int index, const std::string& author);
#endif //NOTEBOX_H
