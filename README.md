# File Access Monitor

## Overview

File Access Monitor is a C-based utility that leverages the Linux `inotify` API to monitor a specific file for access, modification, creation, deletion, or opening events. When such events occur, the program sends desktop notifications using the `libnotify` library.

## Features

- Monitors specified files for various file operations:
  - **Access**
  - **Modification**
  - **Creation**
  - **Deletion**
  - **Opening**
- Sends real-time desktop notifications for each detected event.
- Lightweight and efficient, suitable for Linux systems.

## Requirements

To build and run the program, ensure the following dependencies are installed:

- GCC (GNU Compiler Collection)
- `libnotify` development files
- Linux operating system (with `inotify` support)

### Installing Dependencies

On Debian-based systems (like Ubuntu):

```bash
sudo apt update
sudo apt install build-essential libnotify-dev
```

## Building the Program

Compile the program using `gcc`:

```bash
make
```

## Usage

Run the program with the path of the file to monitor:

```bash
./main <file-here>
```

### Example

```bash
./file_monitor /home/user/documents/example.txt
```

When an event occurs on the specified file, the program sends a desktop notification indicating the type of event.

## How It Works

1. The program initializes an `inotify` instance.
2. Adds a watch for the specified file to monitor all events (`IN_ALL_EVENTS`).
3. Waits for events in a loop and reads them using `read`.
4. When an event is detected, it processes the event and sends a notification using `libnotify`.

## Error Handling

- If the file cannot be watched or `inotify` initialization fails, the program provides an appropriate error message.
- Ensure the file exists and the program has necessary permissions to monitor the file.

## License

This project is licensed under the terms of the license available on the [MIT-LICENSE](LICENSE).

## Contribution

Contributions are welcome! Feel free to fork the repository, create a new branch, and submit a pull request.

## Acknowledgments

- The Linux `inotify` API documentation.
- The developers and maintainers of `libnotify`.


