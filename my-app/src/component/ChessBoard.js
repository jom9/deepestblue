
import React from 'react';
import './ChessBoard.css';

function StartPos(x,y){
  if(y == '1'){
    return "\u265F" ;// black pawns
  }else if (y==6) {

    return "\u2659";// white pawns
  }
  else if(y==0){
    if(x==0 || x==7){
      return "\u265C";/// black rooks
    }else if( x== 1 || x == 6){
      return "\u265E";
    }
    else if( x== 2 || x == 5 ){
      return "\u265D";
    }
    else if( x== 3){
      return "\u265B";
    }
    else if ( x == 4){
      return "\u265A";
    }
  }
  else if(y == 7){
    if(x==0 || x==7){
      return "\u2656";
    }else if( x== 1 || x == 6){
      return "\u2658";
    }
    else if( x== 2 || x == 5 ){
      return "\u2657";
    }
    else if( x== 3){
      return "\u2655";
    }
    else if ( x == 4){
      return "\u2654";
    }
  }
  else{
    return "";
  }
}

class Square extends React.Component{
  constructor(props){
    super(props);
    this.state ={
      x : this.props.x,
      y : this.props.y,


    };
    this.state.piece = StartPos(this.state.x,this.state.y);
    if(this.state.x%2==this.state.y%2){
      this.state.color = "black";
    }
    else{
      this.state.color = "white";
    }
  }

  render(){
    return(
      <button class = {this.state.color} onClick={this.props.func.bind(this,this.state.x,this.state.y)}  >{this.state.piece}</button>
    );
  }

}
class Board extends React.Component{
  constructor(props){
    super(props);
    this.state={
      x : -1,
      y : -1
    };

    this.SetMove = this.SetMove.bind(this);
  }
  SetMove(i,j){
    this.setState({x:i,y:j})
  }
  renderSquare(i,j){
    return (<th><Square x={i} y={j} func = {this.SetMove}/></th>);
  }
  renderRow(i){
    return [0,1,2,3,4,5,6,7].map( n=> this.renderSquare(n,i) );
  }
  renderBoard(){
    var L = new Array([]);
    var i;

    for(i=0;i<8;i++){
      L[i] = [<tr>{this.renderRow(i)}</tr>] ;

    }

    return L;
  }

  render(){
    return(

    <div >

    <div>  <h2>Current Move: {this.state.x}, {this.state.y}</h2></div>


      <div class = "chessboard"><table  >{this.renderBoard()}</table></div>


    </div>
    );
  }
}
export default  Board;
