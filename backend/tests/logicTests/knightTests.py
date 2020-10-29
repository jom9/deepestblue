import subprocess
import os

os.path.dirname(os.path.realpath(__file__))
fileName = 'tests/logicTests/knightTests.py'
cwd = os.path.realpath(__file__)
fullLen = len(cwd)
backend_loc = cwd[:fullLen-len(fileName)]

class knightTests:
    def __init__(self):
        '''
        RNBQKBNR
        PPPPXPPP
        XXXXXXXX
        XXXXPXXX
        XXXXpXXX
        XXXXXnXX
        ppppXppp
        rnbqkbnr
        '''
        testStandard = subprocess.run(['game_cache\\backend.exe', 'new' ,'6', '7', '4', '5'],capture_output=True,cwd=backend_loc,shell=True)# does the knight move forward?
        if testStandard.stdout == b'RNBQKBNRPPPPPPPPXXXXXXXXXXXXXXXXXXXXXXXXXXXXXnXXpppppppprnbqkbXr':
            print('Test 1 (Pawn Standard): Passed')

        else:
            print('Test 1 (Pawn Standard): Failed')
            print(testStandard)
