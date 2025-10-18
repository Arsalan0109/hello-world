# Cricket Team Manager

This web app is designed to manage players in a cricket team. You can add players, see their statistics, complete updates, and remove them from your team. 

This app allows you to track players in your cricket team. You can view each player's style of batting and bowling, number of matches played, runs scored, and wickets taken. You can filter by position such as batsman and bowler and view other statistics.

## How To Run

First install everything:

```
npm install
```

Then open two command windows.

In the first window, start the server:

```
npm run server
```

In the second window, start the app:

```
npm start
```

The app will open in your browser at http://localhost:3000

## How To Use

To add a new player, please click on the Add Player button. You'll need to enter their name, age, and role. You can also specify their batting and bowling styles in addition to their stats.

You can click on any player card to access all of the player's details. You'll be able to edit their details or delete them there.

You'll find filter buttons at the top of the players list. You can click these to filter for batsmen, bowlers, all-rounders, and wicket keepers.

## What's Inside

The application is divided into two parts: the front end, which is created with React to show the player cards and forms, and the back end, which is built with Node.js and Express to save data to MongoDB.

Data for all players is saved in MongoDB Atlas so it stays saved after the app is closed.

## API Routes

The server has these routes:

- GET /api/players - Get all players
- GET /api/players/:id - Get one player
- POST /api/players - Add new player
- PUT /api/players/:id - Update player
- DELETE /api/players/:id - Delete player

## Tech Used

React for the frontend
Node.js and Express for the backend
MongoDB Atlas for the database
Plain CSS for styling
