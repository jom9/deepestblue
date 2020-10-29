# This File looks to play a few test games
import subprocess
import os

os.path.dirname(os.path.realpath(__file__))
fileName = 'tests/logicTests/gameTests.py'
cwd = os.path.realpath(__file__)
fullLen = len(cwd)
backend_loc = cwd[:fullLen-len(fileName)]
class gameTests:
    def __init__(self):
        print('TEST')




if __file__=='__main__':
    gameTests()
