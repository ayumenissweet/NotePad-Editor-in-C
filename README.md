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
### Normal Mode (commands to consider):

#### Line Manipulation:
- `:n`         → move to line number n  
- `:dl`        → delete the current line  
- `:swap n m`  → swap line n with line m  
- `:u`         → undo the last action  
- `:r`         → redo the last undone action  
- `:md n`      → move line n down  
- `:mu n`      → move line n up  
- `:write`     → save the content to a `.txt` file  
- `:quit`      → close the program  

---
#### Word Manipulation:
(To be discussed)

---
## Concepts:

**Lines**:  
Each line is represented as a node in a linked list.  
The full text (the "Buffer") is a linked list of lines, where each node contains:
- the current line’s content  
- a pointer to the previous line  
- a pointer to the next line  

**Words**:  
Each word does not necessarily need to be a linked list. This is still under discussion and may instead be handled using string manipulation.

**Output:**
The output is saved into a `name.txt` file

---
![[Concept.png|697]]

### Work : 
#### Aymen : 
- [ ] Find
- [ ] Write
- [ ] Input
#### Miryam : 
- [ ] Insert
- [ ] Delete
- [ ] Modify
#### Youcef : 
- [ ] Create List
- [ ] Read `.txt` file
- [ ] Display