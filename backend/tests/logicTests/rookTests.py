import subprocess
import os

os.path.dirname(os.path.realpath(__file__))
fileName = 'tests/logicTests/rookTests.py'
cwd = os.path.realpath(__file__)
fullLen = len(cwd)
backend_loc = cwd[:fullLen-len(fileName)]
class rookTests:
    def __init__(self):
        testStandard = subprocess.run(['game_cache\\backend.exe', 'new' ,'4', '6', '4', '5'],capture_output=True,cwd=backend_loc,shell=True)# does the pawn move forward?
        if testStandard.stdout == b'InvalidMove':
            print('Test 1 (Pawn Standard): Passed')

        else:
            print('Test 1 (Pawn Standard): Failed')
            print(testStandard)
