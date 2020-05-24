import React from 'react';
import logo from './logo.svg';
import './App.css';
import Board from "./ChessBoard.js";
function App() {
  return (
    <div className="App">
      <header className="App-header">
        <p>Welcome</p>
        <a
          className="App-link"
          href="https://github.com/jom9/cppchess"
          target="_blank"
          rel="noopener noreferrer"
        >
          Source:
        </a>
      </header>
      <Board/>
    </div>


  );
}

export default App;
