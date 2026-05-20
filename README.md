# Main Idea: Notepad Editor

## Skills Used:

- Linked Lists
- File I/O
- Structs

---

## Explanation:

A notepad editor that functions similarly to Vim, with two main modes:

- Insert Mode: In this mode, the user can type text, copy, paste, and press Enter to submit a line.
- Normal Mode: Commands are entered by prefixing input with `:`. For example, typing `:5` moves the cursor to line number 5.

---

### Insert Mode:

- Pressing Enter submits the current line.

---

### Normal Mode (commands to consider)

| Command Syntax          | Operation Name    | Description                                                                         |
| :---------------------- | :---------------- | :---------------------------------------------------------------------------------- |
| `i n "text"`            | Line Insertion    | Inserts the specified text at line number `n`.                                      |
| `dl n`                  | Line Deletion     | Deletes line number `n` from the document.                                          |
| `swap n m`              | Line Swap         | Swaps the positions of line `n` and line `m`.                                       |
| `mu n` / `md n`         | Move Up / Down    | Moves line `n` one position up (`mu`) or one position down (`md`).                  |
| `uniq`                  | Remove Duplicates | Removes all duplicate lines across the document. _(Note: Bypasses the undo stack)_. |
| `n`                     | Jump to Line      | Moves the current line pointer to line number `n`.                                  |
| `view` / `view_n`       | View Text         | Displays all text. `view_n` includes line numbering (e.g., Line 1, Line 2).         |
| `view_odd` /`view_even` | View Text         | Display text with a condition : even or odd lines only                              |
| `print`                 | Toggle Print Mode | Toggles print mode; when active, automatically runs `view_n` after every command.   |
| `undo`                  | Undo Action       | Reverts the last text modification command.                                         |
| `redo`                  | Redo Action       | Reapplies the last undone command.                                                  |
| `write`                 | Save File         | Writes and saves the current text buffer into a file.                               |
| `quit`                  | Quit Program      | Closes the editor application.                                                      |
