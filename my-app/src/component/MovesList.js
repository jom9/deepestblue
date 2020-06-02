import React from 'react';
import './ChessBoard.css';
class MovesList extends React.Component{

  constructor(props){
    super(props);

    this.state={
        moves :[]
    };

  }
  componentDidMount() {

  }
  render(){
    this.state.moves = this.props.moves;
    this.state.ls = this.props.moves.map((move) =><li className ="move">{move}</li>);
   return (<ol  className = "movelist" >{this.state.ls}</ol>);
  }


}
export default MovesList;
