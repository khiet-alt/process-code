from tkinter import *
from threading import Thread, local
import subprocess
import sys

from pass_work import get_pass_work
from Time import check_time_use, time_can_use, clock

flag = False
num_enter_pass_work = 0     # Number of times re-entered incorrect password

## string type
p_pass_work, c_pass_work = get_pass_work("passwork.txt")


def shut_down(seconds):
    ''''''
    clock(seconds)
    global flag
    if flag:
        subprocess.Popen("shut_dow.bat")


def main():

    # Create Tkinter User Interface
    screen = Tk()
    for i in range(3):
        screen.columnconfigure(i, weight=1, minsize=76)
    for i in range(15):
        screen.rowconfigure(i, weight=1, minsize=50)
    screen.attributes('-fullscreen', True)

    ### luu mat khau cua ô login
    pass_work = StringVar()

    def login(scr):
        '''
        This function is called when user enter password and click "Login" button
        '''
        global flag, num_enter_pass_work
        if pass_work.get() == p_pass_work:  # Check for entered password
            '''
            This is when parent entered correct password
            '''
            # global flag
            flag = False
            clock(2)
            scr.destroy()   ### turn off login screen 
            ## idle for 60 seconds before requiring password parent
            clock(60)
            ##
            main()
        else:
            '''
            Incorrect parent password, there are 2 situations:
            - In using time permission:
                - If not children password, lock 10minutes after re-entering incorrect passsword 3 times
                - If password childrent is correct:
                    - Notify how many time remain permitted using computer.
                    - convert program into background running and Create 3 concurrent processes:
                        - take screenshot after 1 minutes, saved into log file
                        - check for changes using computer in times.txt file
                        - Before shutdown 1 minute, notify users about time range permission.
            - Not permitted time using computer:
                - Create 2 processes: notify user and shutdown
            '''
            # note = Tk()
            # windowWidth = note.winfo_reqwidth()
            # windowHeight = note.winfo_reqheight()
        
            #     # Gets both half the screen width/height and window width/height
            # positionRight = int(note.winfo_screenwidth()/2 - windowWidth/2)
            # positionDown = int(note.winfo_screenheight()/2 - windowHeight/2)
        
            #     # Positions the window in the center of the page.
            # note.geometry("+{}+{}".format(positionRight, positionDown))
                
            if check_time_use():
                '''
                trong tgian su dung
                '''
                if pass_work.get() == c_pass_work: # ktra đúng password của trẻ hay ko
                    pass
                else:
                    '''
                    nếu đúng khung tgian, và sai password, ko thuộc child, parrent
                    cho user nhập 3 lần, nếu sai thì khóa máy và shutdown
                    '''
                    num_enter_pass_work += 1
                    if num_enter_pass_work >= 3:
                        flag = True
                        scr.destroy()
                        lock_screen = Tk()
                        lock_screen.attributes('-fullscreen', True)
                        ## Chia theo grid, 
                        lock_screen.columnconfigure(0, weight=1, minsize=76)
                        lock_screen.rowconfigure(0, weight=1, minsize=50)
                        ## create div label
                        label_lock = Label(lock_screen, text="Lock")
                        label_lock.grid(row=0, column=0)
                        '''
                        Lock screen 10 minutes
                        run new concurrent thread
                        '''
                        Thread(target=shut_down, args=(6, )).start()
                        lock_screen.mainloop()
            else:
                '''
                Đang trong thời gian không được sử dụng máy
                '''
                # global flag
                flag = True
                label_3 = Label(scr, text="Cumputer can't use now!\n" + time_can_use("time.txt"))
                label_3.grid(row=7, column=1)
                Thread(target=shut_down, args=(15, )).start()
                # note.mainloop()
                scr.mainloop()
                clock(1)
                try:
                    scr.destroy()
                except:
                    pass
            

    label_1 = Label(screen, text="Enter passwork")
    label_1.grid(row=3, column=1)

    entry_1 = Entry(screen, textvariable=pass_work)
    entry_1.grid(row=4, column=1)

    button_1 = Button(screen, text="Login", command=lambda:login(screen))
    button_1.grid(row=5, column=1)

    screen.mainloop()

if __name__ == "__main__":
    main()
    # pass