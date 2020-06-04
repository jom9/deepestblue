import React from 'react';
import './ChessBoard.css';
class MovesList extends React.Component{

  constructor(props){
    super(props);

    this.state={
        moves :[]
    };

  }
  render(){
    this.state.moves = this.props.moves;
    this.state.ls = [...Array(this.props.moves.length).keys()].map((move) =><li className ="move" key={move}>{this.props.moves[move]}</li>);
   return (<ol  className = "movelist" >{this.state.ls}</ol>);
  }


}
export default MovesList;
