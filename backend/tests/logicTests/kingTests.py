import subprocess
import os

os.path.dirname(os.path.realpath(__file__))
fileName = 'tests/logicTests/kingTests.py'
cwd = os.path.realpath(__file__)
fullLen = len(cwd)
backend_loc = cwd[:fullLen-len(fileName)]
class kingTests:
    def __init__(self):
        '''
        RNBQKBXR
        PPPPXPPP
        XXXXXXXX
        XXXXPXXN
        XXXXpXkX
        XXXXXXXX
        ppppXppp
        rnbqXbnr
        '''
        subprocess.run(['game_cache\\backend.exe', 'new' ,'4', '6', '4', '4'],capture_output=True,cwd=backend_loc,shell=True)# does the pawn move forward?
        subprocess.run(['game_cache\\backend.exe', 'cache' ,'4', '1', '4', '2'],capture_output=True,cwd=backend_loc,shell=True)
        testStandard1 =  subprocess.run(['game_cache\\backend.exe', 'cache' ,'4', '7', '4', '6'],capture_output=True,cwd=backend_loc,shell=True)
        if testStandard1.stdout == b'RNBQKBNRPPPPXPPPXXXXXXXXXXXXPXXXXXXXpXXXXXXXXXXXppppkppprnbqXbnr':
            print('Test 1 (King Standard): Passed')

        else:
            print('Test 1 (King Standard): Failed')
            print(testStandard1)
        testStandard2 =  subprocess.run(['game_cache\\backend.exe', 'cache' ,'4', '7', '4', '6'],capture_output=True,cwd=backend_loc,shell=True)
        if testStandard2.stdout == b'InvalidMove':
            print('Test 2 (King Standard): Passed')
        else:
            print('Test 2 (King Standard): Failed')
            print(testStandard2)
        testStandard3 =  subprocess.run(['game_cache\\backend.exe', 'cache' ,'6', '0', '5', '2'],capture_output=True,cwd=backend_loc,shell=True)
        if testStandard3.stdout == b'RNBQKBXRPPPPXPPPXXXXXNXXXXXXPXXXXXXXpXXXXXXXXXXXppppkppprnbqXbnr':
            print('Test 3 (King Standard): Passed')
        else:
            print('Test 3 (King Standard): Failed')
            print(testStandard3)
        testStandard4 =  subprocess.run(['game_cache\\backend.exe', 'cache' ,'4', '6', '5', '5'],capture_output=True,cwd=backend_loc,shell=True)
        if testStandard4.stdout == b'RNBQKBXRPPPPXPPPXXXXXNXXXXXXPXXXXXXXpXXXXXXXXkXXppppXppprnbqXbnr':
            print('Test 4 (King Standard): Passed')
        else:
            print('Test 4 (King Standard): Failed')
            print(testStandard1)
        testStandard5 =  subprocess.run(['game_cache\\backend.exe', 'cache' ,'5', '2', '7', '3'],capture_output=True,cwd=backend_loc,shell=True)
        if testStandard5.stdout == b'RNBQKBXRPPPPXPPPXXXXXXXXXXXXPXXNXXXXpXXXXXXXXkXXppppXppprnbqXbnr':
            print('Test 5 (King Standard): Passed')
        else:

            print('Test 5 (King Standard): Failed')
            print(testStandard5)
        testStandard6 =  subprocess.run(['game_cache\\backend.exe', 'cache' ,'5', '5', '6', '5'],capture_output=True,cwd=backend_loc,shell=True)
        if testStandard6.stdout == b'InvalidMove':
            print('Test 6 (King Standard): Passed')
        else:
            print('Test 6 (King Standard): Failed')
            print(testStandard6)
        testStandard7 =  subprocess.run(['game_cache\\backend.exe', 'cache' ,'5', '5', '6', '4'],capture_output=True,cwd=backend_loc,shell=True)
        if testStandard7.stdout == b'RNBQKBXRPPPPXPPPXXXXXXXXXXXXPXXNXXXXpXkXXXXXXXXXppppXppprnbqXbnr':
            print('Test 7 (King Standard): Passed')
        else:
            print('Test 7 (King Standard): Failed')
            print(testStandard7)
