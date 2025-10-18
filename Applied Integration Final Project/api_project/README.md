# Recipe Manager

Full stack recipe management app with CRUD operations, RESTful API, and data persistence.

## Features

- Create, read, update, and delete recipes
- Store recipe details including ingredients, instructions, prep time, cook time, and servings
- Categorize recipes by meal type
- Filter recipes by category
- Responsive design
- Data persists to JSON file

## Tech Stack

- Frontend: React
- Backend: Node.js with Express
- Storage: JSON file
- Styling: CSS

## Setup

Install dependencies:

```
npm install
```

## Running the App

You need two terminals running at the same time.

Terminal 1 - Start the backend server:

```
npm run server
```

Terminal 2 - Start the React frontend:

```
npm start
```

The frontend will open at http://localhost:3000 and connects to the backend at http://localhost:5000.

## API Endpoints

All endpoints use `/api/recipes` as the base path.

- GET `/api/recipes` - Get all recipes
- GET `/api/recipes/:id` - Get single recipe
- POST `/api/recipes` - Create new recipe
- PUT `/api/recipes/:id` - Update recipe
- DELETE `/api/recipes/:id` - Delete recipe

## Data Storage

Recipes are stored in `data.json` in the root directory. The file is created automatically when you add your first recipe.

## Usage

1. Click "Add Recipe" to create a new recipe
2. Fill in the form with recipe details (name, ingredients, and instructions are required)
3. Click on any recipe card to view full details
4. Use Edit button to modify a recipe
5. Use Delete button to remove a recipe
6. Filter recipes by category using the filter buttons

## Project Structure

```
src/
  App.js - Main React component with all functionality
  App.css - All styling
server.js - Express API server
data.json - Recipe storage
```
