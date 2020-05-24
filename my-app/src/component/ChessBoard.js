
import React from 'react';
import './ChessBoard.css';
var xs = -1;
var ys = -1;

class Square extends React.Component{
  constructor(props){
    super(props);
    this.state ={
      x : this.props.x,
      y : this.props.y


    };

    if(this.state.x%2==this.state.y%2){
      this.state.color = "black";
    }
    else{
      this.state.color = "white";
    }
  }

  render(){
    return(
      <button class = {this.state.color} onClick={this.props.func.bind(this,this.state.x,this.state.y)}  ></button>
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

    for(i=1;i<8;i++){
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
