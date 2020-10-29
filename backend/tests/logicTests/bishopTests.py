import subprocess
import os

os.path.dirname(os.path.realpath(__file__))
fileName = 'tests/logicTests/bishopTests.py'
cwd = os.path.realpath(__file__)
fullLen = len(cwd)
backend_loc = cwd[:fullLen-len(fileName)]

class bishopTests:
    def __init__(self):
        #initboard = 'RNBQKBNRPPPPPPPPXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXpppppppprnbqkbnr'
        '''
        RNBQKBNR
        PPPPPPPP
        XXXXXXXX
        XXXXXXXX
        XXXXXXXX
        XXXXXXXX
        pppppppp
        rnbqkbnr
        '''
        '''
        RNBQKBNR
        PPPPXPPP
        XXXXXXXX
        XbXXPXXX
        XXXXpXXX
        XXXXXXXX
        ppppXppp
        rnbqkbnr
        '''
        subprocess.run(['game_cache\\backend.exe', 'new' ,'4', '6', '4', '4'],capture_output=True,cwd=backend_loc,shell=True)# does the pawn move forward?
        subprocess.run(['game_cache\\backend.exe', 'cache' ,'4', '1', '4', '2'],capture_output=True,cwd=backend_loc,shell=True)
        testStandard1 =  subprocess.run(['game_cache\\backend.exe', 'cache' ,'5', '7', '4', '3'],capture_output=True,cwd=backend_loc,shell=True)
        if testStandard1.stdout == b'RNBQKXNRPPPPBPPPXXXXXXXXXbXXPXXXXXXXpXXXXXXXXXXXppppXppprnbqkbnr':
            print('Test 1 (Bishop Standard): Passed')

        else:
            print('Test 1 (Bishop Standard): Failed')
            print(testStandard1)
        testStandard2 =  subprocess.run(['game_cache\\backend.exe', 'cache' ,'5', '7', '6', '0'],capture_output=True,cwd=backend_loc,shell=True)
        if testStandard2.stdout == b'InvalidMove':
            print('Test 2 (Bishop Standard): Passed')
        else:
            print('Test 2 (Bishop Standard): Failed')
