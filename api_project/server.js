const express = require('express');
const mongoose = require('mongoose');
const cors = require('cors');

const app = express();
const port = 5000;

app.use(cors());
app.use(express.json());

mongoose.connect('mongodb+srv://arsalanbinayub_db_user:Cricket%402025@cluster0.o9sk7qs.mongodb.net/Cricket-Team?retryWrites=true&w=majority&appName=Cluster0');

const db = mongoose.connection;
db.on('error', console.error.bind(console, 'connection error:'));
db.once('open', () => {
  console.log('Connected to MongoDB');
});

const playerSchema = new mongoose.Schema({
  name: { type: String, required: true },
  age: { type: Number, required: true },
  role: { type: String, required: true },
  batting_style: String,
  bowling_style: String,
  matches_played: Number,
  total_runs: Number,
  total_wickets: Number,
  nationality: String
}, { collection: 'Sunrisers hyderbad' });

const Player = mongoose.model('Player', playerSchema);

app.get('/api/players', async (req, res) => {
  try {
    const players = await Player.find();
    res.json(players);
  } catch (err) {
    res.status(500).json({ error: err.message });
  }
});

app.get('/api/players/:id', async (req, res) => {
  try {
    const player = await Player.findById(req.params.id);
    if (!player) return res.status(404).json({ error: 'not found' });
    res.json(player);
  } catch (err) {
    res.status(500).json({ error: err.message });
  }
});

app.post('/api/players', async (req, res) => {
  try {
    const { name, age, role, batting_style, bowling_style, matches_played, total_runs, total_wickets, nationality } = req.body;
    if (!name || !age || !role) {
      return res.status(400).json({ error: 'missing fields' });
    }
    const player = new Player({
      name,
      age,
      role,
      batting_style: batting_style || '',
      bowling_style: bowling_style || '',
      matches_played: matches_played || 0,
      total_runs: total_runs || 0,
      total_wickets: total_wickets || 0,
      nationality: nationality || ''
    });
    await player.save();
    res.status(201).json(player);
  } catch (err) {
    res.status(400).json({ error: err.message });
  }
});

app.put('/api/players/:id', async (req, res) => {
  try {
    const { name, age, role, batting_style, bowling_style, matches_played, total_runs, total_wickets, nationality } = req.body;
    const player = await Player.findByIdAndUpdate(
      req.params.id,
      { name, age, role, batting_style, bowling_style, matches_played, total_runs, total_wickets, nationality },
      { new: true, runValidators: true }
    );
    if (!player) return res.status(404).json({ error: 'not found' });
    res.json(player);
  } catch (err) {
    res.status(400).json({ error: err.message });
  }
});

app.delete('/api/players/:id', async (req, res) => {
  try {
    const player = await Player.findByIdAndDelete(req.params.id);
    if (!player) return res.status(404).json({ error: 'not found' });
    res.status(204).send();
  } catch (err) {
    res.status(500).json({ error: err.message });
  }
});

app.listen(port, () => {
  console.log(`Server running on port ${port}`);
});
