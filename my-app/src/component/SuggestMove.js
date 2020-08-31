
import React from 'react';
import axios from 'axios';

var EngineCon ="https://web.njit.edu/~jom9/deepestblue/engine/SuggestMove.php";//location of engine api
function GetPiece(c){

  if(c === 'P'){
    return '\u265F';
  }
  else if (c==='p') {
    return '\u2659';
  }
  else if (c==='R') {
    return '\u265C';
  }
  else if(c==='r'){
    return '\u2656';
  }
  else if(c === 'K'){
    return '\u265A';
  }
  else if (c === 'k') {
    return '\u2654';
  }
  else if(c === 'N'){
    return '\u265E';
  }
  else if(c === 'n'){
    return '\u2658';
  }
  else if (c==='Q'){
    return '\u265B';
  }
  else if(c === 'q'){
      return '\u2655';
  }
  else if (c === 'B') {
    return '\u265D';
  }
  else if(c === 'b'){
    return '\u2657';
  }
  else{
    return "";
  }
}
class SuggestMove extends React.Component{
  constructor(props){
    super(props);
    this.state ={
      depth:25, // depth of search
      board:this.props.board, // board is sent
      player:this.props.player,// player who's on the play
      move:"Test",// initially the move is empty, once it gets a response back, its put here
      error:null,
      isLoaded:false,// did we get a response back yet?
      xs:-1,
      ys:-1,
      xd:-1,
      yd:-1,
      piece:''
    };
  }

  oppPlayer(c){// this function swaps the player
    if(c==='w'){
      return 'b';
    }
    else if(c==='b'){
      return 'w';
    }
  }
  shouldComponentUpdate(nextProps,nextState){ //when ever the board is changed, an api call is made
    if(nextProps.board !== this.props.board && nextProps.player !== this.props.player){
      var form = new FormData();

      form.append("player",this.oppPlayer(this.props.player));
      form.append("depth",this.state.depth);
      form.append("board",nextProps.board);
      const response = axios.post(EngineCon, form, {
        headers: { 'Content-Type': 'multipart/form-data' },})
        .then((response) => {
            this.setState({move:response['data']["move"],isLoaded:true});
            var xs = this.state.move.charAt(0); // source position
            var ys = this.state.move.charAt(2);
            var xd = this.state.move.charAt(4);// destiantion
            var yd = this.state.move.charAt(6);


            this.props.func(Number(xs),Number(ys),Number(xd),Number(yd));
            var piece = GetPiece(  nextProps.board.charAt(Number(xs) +  Number(ys*8))  );

            this.setState({xs:xs,ys:ys,xd:xd,yd:yd, board:nextProps.board,piece:piece});
            console.log(this.state)
        },
        (error) => {
          this.setState({isLoaded: true,error:error});
        });
      return true;
    }
    if(nextState.move !== this.state.move){

      return true;
    }
    return false;


  }
  componentDidMount(){ // first call
    var form = new FormData();
    form.append("player",this.props.player);
    form.append("depth",this.state.depth);
    form.append("board",this.props.board);
    const response = axios.post(EngineCon, form, {
      headers: { 'Content-Type': 'multipart/form-data' },})
      .then((response) => {
          this.setState({move:response['data']["move"],isLoaded:true});
          var xs = this.state.move.charAt(0);
          var ys = this.state.move.charAt(2);
          var xd = this.state.move.charAt(4);
          var yd = this.state.move.charAt(6);
          var piece = GetPiece( this.props.board.charAt(Number(xs) +  Number(ys*8)  ) );
          this.setState({xs:xs,ys:ys,xd:xd,yd:yd,piece:piece});
          this.props.func(xs,ys,xd,yd);

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
      var piece = GetPiece( this.props.board.charAt(Number(xs) +  Number(ys*8)  ) );


      var s  = piece + ranks.charAt(xs)+(8-ys)+"=>"+ranks.charAt(xd)+(8-yd);

      return (

        <h2 className="EngineSug">Suggested Move (Using Depth of {this.state.depth}):<br/>{s}</h2>// displays suggestion
      );
    }

  }



}

export default SuggestMove;
