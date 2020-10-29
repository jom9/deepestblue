import subprocess
import os

os.path.dirname(os.path.realpath(__file__))
fileName = 'tests/logicTests/pawnTests.py'
cwd = os.path.realpath(__file__)
fullLen = len(cwd)
backend_loc = cwd[:fullLen-len(fileName)]

#Test 1: check if pawn moves
class pawnTests:
    def __init__(self):
        #initboard = 'RNBQKBNRPPPPPPPPXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXpppppppprnbqkbnr'
        testStandard = subprocess.run(['game_cache\\backend.exe', 'new' ,'4', '6', '4', '5'],capture_output=True,cwd=backend_loc,shell=True)# does the pawn move forward?
        if testStandard.stdout == b'RNBQKBNRPPPPPPPPXXXXXXXXXXXXXXXXXXXXXXXXXXXXpXXXppppXppprnbqkbnr':
            print('Test 1 (Pawn Standard): Passed')

        else:
            print('Test 1 (Pawn Standard): Failed')
            print(testStandard)
        test1stMove = subprocess.run(['game_cache\\backend.exe', 'new' ,'4', '6', '4', '4'],capture_output=True,cwd=backend_loc,shell=True )# does the pawn move correct for the 1st move?
        if test1stMove.stdout == b'RNBQKBNRPPPPPPPPXXXXXXXXXXXXXXXXXXXpXXXXXXXXXXXXppppXppprnbqkbnr':
            print('Test 2 (Pawn 1st Move): Passed')
        else:
            print('Test 2 (Pawn 1st Move): Failed')
            print(test1stMove)
        subprocess.run(['game_cache\\backend.exe', 'new' ,'4', '6', '4', '4'],capture_output=True,cwd=backend_loc,shell=True)
        subprocess.run(['game_cache\\backend.exe', 'cache' ,'5', '1', '5', '3'],capture_output=True,cwd=backend_loc,shell=True)#3 captures captures
        testCaptureMove = subprocess.run(['game_cache\\backend.exe', 'cache' ,'4', '4', '5', '3'],capture_output=True,cwd=backend_loc,shell=True )
        if testCaptureMove.stdout == b'RNBQKBNRPPPPPPPPXXXXXXXXXXXXXXXXXXXXXXXXXXXXpXXXppppXppprnbqkbnr':
            print('Test 3 (Capture): Passed')
        else:
            print('Test 3 (Capture): Failed')
            print(testCaptureMove)
        moveIncorrectly = subprocess.run(['game_cache\\backend.exe', 'new' ,'4', '6', '0', '0'],capture_output=True,cwd=backend_loc,shell=True )
        if moveIncorrectly.stdout == b'InvalidMove':
            print('Test 4 (Capture): Passed')
        else:
            print('Test 4 (Capture): Failed')
            print(moveIncorrectly)
        takeFriendlyPiece = subprocess.run(['game_cache\\backend.exe', 'new' ,'4', '6', '5', '6'],capture_output=True,cwd=backend_loc,shell=True )
        if takeFriendlyPiece.stdout == b'InvalidMove':
            print('Test 5 (Capture): Passed')
        else:
            print('Test 5 (Capture): Failed')
            print(takeFriendlyPiece)

if __file__=='__main__':
    pawnTests()
