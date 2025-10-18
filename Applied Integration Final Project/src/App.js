import { useState, useEffect } from 'react';
import './App.css';

function App() {
  const [players, setPlayers] = useState([]);
  const [loading, setLoading] = useState(true);
  const [form, setForm] = useState(null);
  const [view, setView] = useState(null);
  const [filter, setFilter] = useState('All');
  const [msg, setMsg] = useState('');

  const roles = ['All', 'Batsman', 'Bowler', 'All-Rounder', 'Wicket-Keeper'];

  useEffect(() => {
    fetch('/api/players')
      .then(r => r.json())
      .then(data => {
        setPlayers(data);
        setLoading(false);
      })
      .catch(() => setLoading(false));
  }, []);

  function showMsg(text) {
    setMsg(text);
    setTimeout(() => setMsg(''), 3000);
  }

  function add() {
    setForm({
      _id: null,
      name: '',
      age: '',
      role: 'Batsman',
      batting_style: '',
      bowling_style: '',
      matches_played: '',
      total_runs: '',
      total_wickets: '',
      nationality: ''
    });
    setView(null);
  }

  function edit(player) {
    setForm({ ...player });
    setView(null);
  }

  function cancel() {
    setForm(null);
  }

  function submit(e) {
    e.preventDefault();
    if (!form.name || !form.age || !form.role) {
      showMsg('Fill required fields');
      return;
    }

    const method = form._id ? 'PUT' : 'POST';
    const url = form._id ? `/api/players/${form._id}` : '/api/players';

    fetch(url, {
      method,
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify(form)
    })
      .then(r => r.json())
      .then(data => {
        if (form._id) {
          setPlayers(players.map(p => p._id === data._id ? data : p));
          showMsg('Updated');
        } else {
          setPlayers([...players, data]);
          showMsg('Added');
        }
        setForm(null);
      });
  }

  function remove(id) {
    if (!window.confirm('Delete this player?')) return;

    fetch(`/api/players/${id}`, { method: 'DELETE' })
      .then(() => {
        setPlayers(players.filter(p => p._id !== id));
        setView(null);
        showMsg('Deleted');
      });
  }

  function open(player) {
    setView(player);
    setForm(null);
  }

  function close() {
    setView(null);
  }

  const filtered = filter === 'All' ? players : players.filter(p => p.role === filter);

  if (loading) return <div className="loading">Loading...</div>;

  return (
    <div className="app">
      <header>
        <h1>🏏 Sunrisers Hyderabad</h1>
        <button onClick={add} className="btn-add">+ Add Player</button>
      </header>

      {msg && <div className="msg">{msg}</div>}

      {form && (
        <div className="modal">
          <div className="modal-content">
            <h2>{form._id ? 'Edit Player' : 'New Player'}</h2>
            <form onSubmit={submit}>
              <input
                placeholder="Player Name *"
                value={form.name}
                onChange={e => setForm({ ...form, name: e.target.value })}
              />
              <div className="row">
                <input
                  type="number"
                  placeholder="Age *"
                  value={form.age}
                  onChange={e => setForm({ ...form, age: e.target.value })}
                />
                <select
                  value={form.role}
                  onChange={e => setForm({ ...form, role: e.target.value })}
                >
                  {roles.filter(r => r !== 'All').map(r => (
                    <option key={r} value={r}>{r}</option>
                  ))}
                </select>
              </div>
              <input
                placeholder="Batting Style"
                value={form.batting_style}
                onChange={e => setForm({ ...form, batting_style: e.target.value })}
              />
              <input
                placeholder="Bowling Style"
                value={form.bowling_style}
                onChange={e => setForm({ ...form, bowling_style: e.target.value })}
              />
              <div className="row">
                <input
                  type="number"
                  placeholder="Matches"
                  value={form.matches_played}
                  onChange={e => setForm({ ...form, matches_played: e.target.value })}
                />
                <input
                  type="number"
                  placeholder="Runs"
                  value={form.total_runs}
                  onChange={e => setForm({ ...form, total_runs: e.target.value })}
                />
                <input
                  type="number"
                  placeholder="Wickets"
                  value={form.total_wickets}
                  onChange={e => setForm({ ...form, total_wickets: e.target.value })}
                />
              </div>
              <input
                placeholder="Nationality"
                value={form.nationality}
                onChange={e => setForm({ ...form, nationality: e.target.value })}
              />
              <div className="actions">
                <button type="submit" className="btn-save">Save</button>
                <button type="button" onClick={cancel} className="btn-cancel">Cancel</button>
              </div>
            </form>
          </div>
        </div>
      )}

      {view && (
        <div className="modal">
          <div className="modal-content view">
            <button onClick={close} className="close">×</button>
            <h2>{view.name}</h2>
            <div className="badge">{view.role}</div>
            <div className="stats">
              <div className="stat">
                <span className="label">Age</span>
                <span className="value">{view.age}</span>
              </div>
              <div className="stat">
                <span className="label">Nationality</span>
                <span className="value">{view.nationality}</span>
              </div>
            </div>
            <div className="details">
              <div className="detail">
                <strong>Batting Style:</strong> {view.batting_style}
              </div>
              <div className="detail">
                <strong>Bowling Style:</strong> {view.bowling_style}
              </div>
            </div>
            <div className="stats">
              <div className="stat">
                <span className="label">Matches</span>
                <span className="value">{view.matches_played}</span>
              </div>
              <div className="stat">
                <span className="label">Runs</span>
                <span className="value">{view.total_runs}</span>
              </div>
              <div className="stat">
                <span className="label">Wickets</span>
                <span className="value">{view.total_wickets}</span>
              </div>
            </div>
            <div className="actions">
              <button onClick={() => edit(view)} className="btn-edit">Edit</button>
              <button onClick={() => remove(view._id)} className="btn-delete">Delete</button>
            </div>
          </div>
        </div>
      )}

      <div className="filters">
        {roles.map(r => (
          <button
            key={r}
            onClick={() => setFilter(r)}
            className={filter === r ? 'active' : ''}
          >
            {r}
          </button>
        ))}
      </div>

      {filtered.length === 0 ? (
        <div className="empty">
          <p>No players yet. Add your first one!</p>
        </div>
      ) : (
        <div className="grid">
          {filtered.map(player => (
            <div key={player._id} className="card" onClick={() => open(player)}>
              <h3>{player.name}</h3>
              <div className="badge">{player.role}</div>
              <div className="info">
                <span>Age: {player.age}</span>
                <span>Matches: {player.matches_played}</span>
              </div>
              <div className="stats-mini">
                <span>🏏 {player.total_runs} runs</span>
                <span>🎯 {player.total_wickets} wickets</span>
              </div>
            </div>
          ))}
        </div>
      )}
    </div>
  );
}

export default App;
