import threading
import time
import random

sem_FilaDefider = threading.BoundedSemaphore(value=6)

sem_consultaDefider = threading.Semaphore(value=0)

lockDefider = threading.Lock()
conditionDefider = threading.Condition(lock=lockDefider)

global filaDefider
filaDefider = []

global defiderLocks
defiderLocks = []

global defiderConsulta
defiderConsulta = []

for lock in range(0,5):
    lock = threading.Lock()
    defiderLocks.append(lock)

for index in range (0,5):
    cond = threading.Condition(lock=defiderLocks[index])
    defiderConsulta.append(cond)

def defider(threadNum):
    #if (lockDefider.locked()):
    #    conditionDefider.wait()
    #
    #conditionDefider.acquire()

#    time.sleep(9)

#    conditionDefider.release()
  #  conditionDefider.notify()
    return 1
    

def dInf(threadNum):
    print("2")
    return

def dFis(threadNum):
    print("3")
    return

def dMat(threadNum):
    print("5")
    return

def dQuim(threadNum):
    print("6")
    return

def dMec(threadNum):
    print("7")
    return

def dMinas(threadNum):
    print("8")
    return

func_array = [defider,dInf,dFis,dMat,dQuim,dMec,dMinas]
count = 0

def patioLamps(threadNum):
    global filaDefider
    assign1 = 0 #random.randint(0,6)
    match assign1:
        case 0:
            fst_assign = "defider"
            sem_FilaDefider.acquire()
            filaDefider.append(threadNum)            
            
        case 1:
            fst_assign = "dInf"
            func_array[assign1](threadNum)
        case 2:
            fst_assign = "dFis"
            func_array[assign1](threadNum)
        case 3:
            fst_assign = "DMat"
            func_array[assign1](threadNum)
        case 4:
            fst_assign = "dQuim"
            func_array[assign1](threadNum)
        case 5:
            fst_assign = "dMec"
            func_array[assign1](threadNum)
        case 6:
            fst_assign = "dMinas"
            func_array[assign1](threadNum)
    
    func_array[assign1](threadNum)
    #assign2 = random.randint(0,6)
    #match assign2:
    #    case 0:
    #        snd_assign = "defider"
    #    case 1:
    #        snd_assign = "dInf"
    #    case 2:
    #        snd_assign = "dFis"
    #    case 3:
    #        snd_assign = "DMat"
    #    case 4:
    #        snd_assign = "dQuim"
    #    case 5:
    #        snd_assign = "dMec"
    #    case 6:
    #        snd_assign = "dMinas"
    #func_array[assign2](threadNum)
    return

thread_list = []
#f_lamps = open("PdLamparas.txt","x")
#f_dMat = open("Departamento_de_matematicas.txt","x")
#f_defider = open("DEFIDER.txt","x")
#f_dMin = open("Departamento_de_minas.txt","x")
#f_salida = open("salidas.txt","x")
#f_dMec = open("Departamento_de_mecanica.txt","x")
#f_dQuim = open("Departamento_de_quimica.txt","x")
#f_dFis = open("Departamento_de_fisica.txt","x")
#f_dInf = open("Departamento_de_informatica.txt","x")

#f_lamps.close()
#f_dMat.close()
#f_defider.close()
#f_dMin.close()
#f_dMec.close()
#f_dQuim.close()
#f_dFis.close()
#f_dInf.close()
#f_salida.close()

for thrd in range(0,20):
    t = threading.Thread(target=patioLamps,args=(thrd,))
    count = count + 1
    thread_list.append(t)

print("threads created: " + str(count))

for thrd in range(0,20):
    thread_list[thrd].start()
    time.sleep(2)