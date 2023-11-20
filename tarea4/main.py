import threading
import time

#def prtest(threadNum):
#    print("{} is printing".format(threadNum))
#    res = 1
#    print(str(res) + " " + str(threadNum))
#    return

def defider(threadNum):
    print(1)
    return

def dInf(threadNum):
    return

def dFis(threadNum):
    return

def dMat(threadNum):
    return

def dQuim(threadNum):
    return

def dMec(threadNum):
    return

def dMinas(threadNum):
    return

func_list = [defider,dInf,dFis,dMat,dQuim,dMec,dMinas]
count = 0

thread_list = []
p_assign = []

for thrd in range(0,20):
    t = threading.Thread()
    count = count + 1
    thread_list.append(t)

print("threads created: " + str(count))

for thrd in range(0,20):
    thread_list[thrd].run(defider, args=(1,))
    thread_list[thrd].start()
    time.sleep(2)