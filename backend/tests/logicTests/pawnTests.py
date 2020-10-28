import subprocess
import os

os.path.dirname(os.path.realpath(__file__))
cwd = os.path.dirname(os.path.realpath(__file__))

#Test 1: check if pawn moves
class CheckPawn:
    def __init__(self):
        #initboard = 'RNBQKBNRPPPPPPPPXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXpppppppprnbqkbnr'
        testStandard = subprocess.run(['.../game_cache/backend.exe', 'new' ,'4', '6', '4', '5'],capture_output=True  )# does the pawn move forward?
        if testStandard.std_out == 'RNBQKBNRPPPPPPPPXXXXXXXXXXXXXXXXXXXXpXXXXXXXXXXXppppXppprnbqkbnr':
            print('Test 1 (Pawn Standard): Passed')

        else:
            print('Test 1 (Pawn Standard): Failed')
            print(testStandard)
        test1stMove = subprocess.run(['.../game_cache/backend.exe', 'new' ,'4', '6', '4', '4'],capture_output=True )# does the pawn move correct for the 1st move?
        if test1stMove.std_out == 'RNBQKBNRPPPPPPPPXXXXXXXXXXXXXXXXXXXXXXXXXXXXpXXXppppXppprnbqkbnr':
            print('Test 2 (Pawn 1st Move): Passed')
        else:
            print('Test 2 (Pawn 1st Move): Failed')
            print(test1stMove)
        subprocess.run(['.../game_cache/backend.exe', 'new' ,'4', '6', '4', '4'])
        subprocess.run(['.../game_cache/backend.exe', 'new' ,'5', '1', '5', '3'])
        testCaptureMove = subprocess.run(['/game_cache/backend.exe', 'cache' ,'4', '4', '5', '3'],capture_output=True )
        if testCaptureMove == 'RNBQKBNRPPPPPPPPXXXXXXXXXXXXXXXXXXXXXXXXXXXXpXXXppppXppprnbqkbnr':
            print('Test 3 (Capture): Passed')
        else:
            print('Test 3 (Capture): Failed')
            print(testCaptureMove)


#Test 2: check if bishop moves

#Test 3: check if knight moves

#Test 4: check if rook moves

#Test 4: check if queen moves
CheckPawn()
