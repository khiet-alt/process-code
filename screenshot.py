import sys
import pyautogui

args = sys.argv[1:]

myScreenshot = pyautogui.screenshot()
myScreenshot.save(r'photos/screenshot_{}.png'.format(args[0]))