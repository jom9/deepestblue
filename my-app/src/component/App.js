import React from 'react';
import logo from './logo.svg';
import './App.css';
import Board from "./ChessBoard.js";
import axios from 'axios';
class InfoBox extends React.Component{
  constructor(props){
    super(props);
    this.state={
      text:"Mistakes were made! We'll get back to you on that...",
      url:"http://localhost:8000/my-app/public/info.php"
    };
  }
  componentDidMount(){

    const response = axios.get(this.state.url, {
      headers: {}})
      .then((response) => {

            this.setState({text:response["data"]});
      }, (error) => {
        console.log(error);
      });
  }
  createMarkup(){ return {__html: this.state.text}; };
  render(){
    return(
        <div className = "App-header-text" dangerouslySetInnerHTML={this.createMarkup()} />

    );
  }
}
function App() {
  return (
    <div className="App">
      <header className="App-header">
        <p>Welcome!</p>
        <a
          className="App-link"
          href="https://github.com/jom9/cppchess"
          target="_blank"
          rel="noopener noreferrer"
        >
          Source if you are so inclined
        </a>
      </header>
      <InfoBox/>
      <Board/>
    </div>


  );
}

export default App;
