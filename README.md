# 🎵 C-Unplugged: Terminal Music Suite
### *CPro’25 Assignment 2 | IIIT Hyderabad*

**C-Unplugged** is a high-performance, modular CLI application built in C to manage song libraries, persistent albums, and interactive playlists. It leverages custom **Linked List** architectures to ensure optimal space-time complexity while maintaining a seamless user experience across sessions.

---

## 👤 Developer Profile
* **Name:** PANCHOTIYA DAKSH DIPAKBHAI
* **Roll Number:** 2025101132
* **Section:** B
* **Institution:** International Institute of Information Technology, Hyderabad

---

## 🏗 System Architecture

The project follows a **Modular Design Pattern**, strictly separating data structures from the user interface logic to ensure clean compilation and easy debugging.

### 📁 Directory Structure
```text
assignment_2/
├── .c_files/           # Implementation logic
│   ├── main.c          # Central CLI Menu & Event Loop
│   ├── song.c          # Song Library & Metadata handling
│   ├── album.c         # Persistent Album Storage logic
│   ├── queue.c         # Playlist Management logic
│   └── history.c       # Global Session Logging
├── header_file/        # Interface definitions
│   ├── song.h          # Song structs & Library prototypes
│   ├── album.h         # Album linked list definitions
│   └── queue.h         # Playlist navigation prototypes
└── .txt_files/         # Data persistence (Database)
    ├── song.txt        # Master Song Metadata
    ├── my_albums.txt   # User-created Album records
    ├── my_history.txt  # Global command history (Cross-session)
    └── log.txt         # Internal system logs


