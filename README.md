# Task Manager 
A fullstack desktop application built with **Qt 6** (**C++/Qt Widgets**) that connects to a **Django REST API** backend powered by **PostgreSQL**.
The app provides a modern GUI for managing tasks while performing CRUD operations (create, read, update, delete) through API calls.

<img width="472" height="524" alt="image" src="https://github.com/user-attachments/assets/e7fc90ed-2d76-435a-aa03-92aa84c0fefa" />

<br>
<img width="356" height="332" alt="image" src="https://github.com/user-attachments/assets/3daef90b-8efe-4ed0-9bb8-2f3bbdf3b9a6" />
<img width="356" height="332" alt="image" src="https://github.com/user-attachments/assets/f9d24cc8-23dd-481f-82ec-059434c98c26" />

## 🚀 Features

- 📥 Fetch tasks from a REST API (/api/tasks/)
- ✏️ Update existing tasks via API requests
- ➕ Create new tasks with user input
- ❌ Delete tasks from the list and backend
- 💻 Qt GUI for simple and responsive task management

## 🛠️ Tech Stack

- C++17 / C++20
- Qt 6 (Qt Widgets, Qt Network)
- CMake build system
- Django REST Framework (backend)
- PostgreSQL (database)

## 📡 API Endpoints

The app communicates with endpoints like:

- GET /api/tasks/ → Fetch all tasks
- POST /api/tasks/ → Create a new task
- PUT /api/tasks/{id}/ → Update an existing task
- DELETE /api/tasks/{id}/ → Delete a task
