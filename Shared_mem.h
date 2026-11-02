#ifndef SHARED_MEM_H
#define SHARED_MEM_H

#include "Notebox.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <iostream>
#include <cstring>

#define SHM_KEY 0x1234

NoteBox* Shared_memory_create() {
    int shm_id = shmget(SHM_KEY, sizeof(NoteBox), IPC_CREAT | IPC_EXCL | 0666);
    void* ptr = nullptr;

    if (shm_id == -1) {
        if (errno == EEXIST) {
            shm_id = shmget(SHM_KEY, sizeof(NoteBox), 0666);
            if (shm_id == -1) {
                std::cerr << "Failed to open existing shared memory: " << strerror(errno) << std::endl;
                return nullptr;
            }
        }
        else {
            std::cerr << "Failed to create shared memory: " << strerror(errno) << std::endl;
            return nullptr;
        }
    }

    ptr = shmat(shm_id, NULL, 0);
    if (ptr == (void*)-1) {
        std::cerr << "Error attaching to shared memory: " << strerror(errno) << std::endl;
        return nullptr;
    }

    return static_cast<NoteBox*>(ptr);
}

void cleanupSharedMemory() {
    int shm_id = shmget(SHM_KEY, sizeof(NoteBox), 0666);
    if (shm_id != -1) {
        shmctl(shm_id, IPC_RMID, nullptr);
    } else {
        std::cerr << "Failed to find shared memory to remove: " << strerror(errno) << std::endl;
    }
}

#endif // SHARED_MEM_H
