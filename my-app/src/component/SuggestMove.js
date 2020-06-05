
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
    //this.getMove = this.getMove.bind(this);
  }
  /*
  getMove(){
    var form = new FormData();
    form.append("player",this.props.player);
    form.append("depth",this.state.depth);
    form.append("board",this.props.board);
    const response = axios.post(EngineCon, form, {
      headers: { 'Content-Type': 'multipart/form-data' },})
      .then((response) => {
          this.setState({move:response['data']["move"],isLoaded:true});
      },
      (error) => {
        this.setState({isLoaded: true,error:error});
      });
  }
  */
  oppPlayer(c){
    if(c=='w'){
      return 'b';
    }
    else if(c=='b'){
      return 'w';
    }
  }
  shouldComponentUpdate(nextProps,nextState){
    if(nextProps.board !== this.props.board && nextProps.player !== this.props.player){
      var form = new FormData();
      form.append("player",this.oppPlayer(this.props.player));
      form.append("depth",this.state.depth);
      form.append("board",this.props.board);
      const response = axios.post(EngineCon, form, {
        headers: { 'Content-Type': 'multipart/form-data' },})
        .then((response) => {
            this.setState({move:response['data']["move"],isLoaded:true});
        },
        (error) => {
          this.setState({isLoaded: true,error:error});
        });
      return true;
    }
    if(nextState.move != this.state.move){

      return true;
    }
    return false;


  }
  componentDidMount(){
    var form = new FormData();
    form.append("player",this.props.player);
    form.append("depth",this.state.depth);
    form.append("board",this.props.board);
    const response = axios.post(EngineCon, form, {
      headers: { 'Content-Type': 'multipart/form-data' },})
      .then((response) => {
          this.setState({move:response['data']["move"],isLoaded:true});
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

        <h2 className="EngineSug">Suggested Move (Using Depth of {this.state.depth}):<br/>{s}</h2>
      );
    }

  }



}

export default SuggestMove;
