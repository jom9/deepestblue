
import React from 'react';
import axios from 'axios';
var EngineCon ="http://localhost:8000/engine/SuggestMove.php";

class SuggestMove extends React.Component{
  constructor(props){
    super(props);
    this.state ={
      depth:5,
      board:this.props.board,
      player:this.props.player,
      move:"Test",
      error:null,
      isLoaded:false
    };
  }
  componentDidMount(){

    var form = new FormData();
    form.append("player",this.state.player);
    form.append("depth",this.state.depth);
    form.append("board",this.state.board);
    const response = axios.post(EngineCon, form, {
      headers: { 'Content-Type': 'multipart/form-data' },})
      .then((response) => {
          this.setState({move:response['data']["move"],isLoaded:true})
      },
      (error) => {
        this.setState({isLoaded: true,error:error});
      });
  }

  render(){


    if (this.state.error) {
      return <h2>Error: {this.state.error.message}</h2>;
    } else if (!this.state.isLoaded) {
      return <h2>Loading...</h2>;
    } else {
      var ranks = "ABCDEFGH";
      var xs = this.state.move.charAt(0);
      var ys = this.state.move.charAt(2);
      var xd = this.state.move.charAt(4);
      var yd = this.state.move.charAt(6);
      var s  = ranks.charAt(xs)+(8-ys)+"=>"+ranks.charAt(xd)+(8-yd);
      return (

        <h2>Suggested Move (Using Depth of {this.state.depth}) is {s} :</h2>
      );
    }

  }



}

export default SuggestMove;