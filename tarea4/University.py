import threading
import time
import random
from datetime import datetime

#LOCKS DEFIDER
global lockDefider
lockDefider = threading.Lock()
conditionDefider = threading.Condition(lock=lockDefider)

global filaDefider
filaDefider = []

#LOCKS DMAT
global lockDMAT
lockDMAT = threading.Lock()
conditionDMAT = threading.Condition(lock=lockDMAT)

global filaDMAT
filaDMAT = []

#LOCKS DINF
global lockDINF
lockDINF = threading.Lock()
conditionDINF = threading.Condition(lock=lockDINF)

global filaDINF
filaDINF = []

#LOCKS DFIS
global lockDFIS
lockDFIS = threading.Lock()
conditionDFIS = threading.Condition(lock=lockDFIS)

global filaDFIS
filaDFIS = []

#LOCKS DQUIM
global lockDQUIM
lockDQUIM = threading.Lock()
conditionDQUIM = threading.Condition(lock=lockDQUIM)

global filaDQUIM
filaDQUIM = []

#LOCKS DMEC
global lockDMEC
lockDMEC = threading.Lock()
conditionDefider = threading.Condition(lock=lockDMEC)

global filaDMEC
filaDMEC = []

#LOCKS DMIN
global lockDMIN
lockDMIN = threading.Lock()
conditionDMIN = threading.Condition(lock=lockDMIN)

global filaDMIN
filaDMIN = []

#DEFIDER FUNCS
def defiderConsulta(thread, nDepto):

    time.sleep(1)
    print("Salida de {}".format(thread))
    return

def defider(threadNum, nDepto):
    global filaDefider, lockDefider
    print("soy {} y entré".format(threadNum))
    lockDefider.acquire()
    print(threadNum)
    if (len(filaDefider) == 6):
        lockDefider.release()
        return 0 #en caso de error se retira del departamento y se salta la apelación xD

    else:
        print("Guardo")
        in_fila = datetime.now().strftime("%H:%M:%S:%f")
        filaDefider.append(threadNum)

        if (len(filaDefider) >= 5):
            for i in range(5):
                in_dpto = datetime.now().strftime("%H:%M:%S:%f")
                
                defiderConsulta(filaDefider[i],nDepto) #Funcion definida para procesar las consultas
                out = filaDefider[i]
                f = open("DEFIDER.txt","a")
                f.write("persona " + str(filaDefider[i]) + ", " + str(in_fila) + ", " + str(in_dpto) + ", " + str(nDepto) + "\n")
                f.close()
            for i in range(5):
                popped = filaDefider.pop(0)
    
    print(filaDefider)
    lockDefider.release()

    return 1

#DMAT FUNCS
def dmatConsulta(thread, nDepto):
    time.sleep(9)
    print("Salida de {}".format(thread))
    return

def dMat(threadNum, nDepto):
    global filaDMAT, lockDMAT
    print("soy {} y entré".format(threadNum))
    lockDMAT.acquire()
    print(threadNum)
    if (len(filaDMAT) == 20):
        lockDMAT.release()
        return 0 #en caso de error se retira del departamento y se salta la apelación xD

    else:
        print("Guardo")
        in_fila = datetime.now().strftime("%H:%M:%S:%f")
        filaDMAT.append(threadNum)

        if (len(filaDMAT) >= 10):
            for i in range(10):
                in_dpto = datetime.now().strftime("%H:%M:%S:%f")
                
                dmatConsulta(filaDMAT[i],nDepto) #Funcion definida para procesar las consultas
                out = filaDMAT[i]
                f = open("Departamento_de_matematicas.txt","a")
                f.write("persona " + str(out) + ", " + str(in_fila) + ", " + str(in_dpto) + ", " + str(nDepto) + "\n")
                f.close()
            for i in range(10):
                filaDMAT.pop(0)
                
    print(filaDMAT)
    lockDMAT.release()

    return 1

#DINF FUNCS
def dinfConsulta(thread, nDepto):
    time.sleep(5)
    print("Salida de {}".format(thread))
    return

def dInf(threadNum, nDepto):
    global filaDINF, lockDINF
    print("soy {} y entré".format(threadNum))
    lockDINF.acquire()
    print(threadNum)
    if (len(filaDINF) == 8):
        lockDINF.release()
        return 0 #en caso de error se retira del departamento y se salta la apelación xD

    else:
        print("Guardo")
        in_fila = datetime.now().strftime("%H:%M:%S:%f")
        filaDINF.append(threadNum)

        if (len(filaDINF) >= 2):
            for i in range(2):
                in_dpto = datetime.now().strftime("%H:%M:%S:%f")
                dmatConsulta(filaDINF[i],nDepto) #Funcion definida para procesar las consultas
                out = filaDINF[i]
                f = open("Departamento_de_informatica.txt","a")
                f.write("persona " + str(out) + ", " + str(in_fila) + ", " + str(in_dpto) + ", " + str(nDepto) + "\n")
                f.close()
            for i in range(2):
                filaDINF.pop(0)
                
    print(filaDINF)
    lockDINF.release()

    return 1

#DFIS FUNCS
def dFisConsulta(thread, nDepto):
    time.sleep(7)
    print("Salida de {}".format(thread))
    return

def dFis(threadNum, nDepto):
    global filaDFIS, lockDFIS
    print("soy {} y entré".format(threadNum))
    lockDFIS.acquire()
    print(threadNum)
    if (len(filaDFIS) == 15):
        lockDFIS.release()
        return 0 #en caso de error se retira del departamento y se salta la apelación xD

    else:
        print("Guardo")
        in_fila = datetime.now().strftime("%H:%M:%S:%f")
        filaDFIS.append(threadNum)

        if (len(filaDFIS) >= 5):
            for i in range(5):
                in_dpto = datetime.now().strftime("%H:%M:%S:%f")
                dFisConsulta(filaDFIS[i],nDepto) #Funcion definida para procesar las consultas
                out = filaDFIS[i]
                f = open("Departamento_de_fisica.txt","a")
                f.write("persona " + str(out) + ", " + str(in_fila) + ", " + str(in_dpto) + ", " + str(nDepto) + "\n")
                f.close()
            for i in range(5):
                filaDFIS.pop(0)
                
    print(filaDFIS)
    lockDFIS.release()

    return 1

#DQUIM FUNCS
def dQuimConsulta(thread, nDepto):
    time.sleep(4)
    print("Salida de {}".format(thread))
    return

def dQuim(threadNum, nDepto):
    global filaDQUIM, lockDQUIM
    print("soy {} y entré".format(threadNum))
    lockDQUIM.acquire()
    print(threadNum)
    if (len(filaDQUIM) == 6):
        lockDQUIM.release()
        return 0 #en caso de error se retira del departamento y se salta la apelación xD

    else:
        print("Guardo")
        in_fila = datetime.now().strftime("%H:%M:%S:%f")
        filaDQUIM.append(threadNum)

        if (len(filaDQUIM) >= 3):
            for i in range(3):
                in_dpto = datetime.now().strftime("%H:%M:%S:%f")
                dQuimConsulta(filaDQUIM[i],nDepto) #Funcion definida para procesar las consultas
                out = filaDQUIM[i]
                f = open("Departamento_de_quimica.txt","a")
                f.write("persona " + str(out) + ", " + str(in_fila) + ", " + str(in_dpto) + ", " + str(nDepto) + "\n")
                f.close()
            for i in range(3):
                filaDQUIM.pop(0)
                
    print(filaDQUIM)
    lockDQUIM.release()

    return 1

#DMEC FUNCS
def dMecConsulta(thread, nDepto):
    time.sleep(7)
    print("Salida de {}".format(thread))
    return

def dMec(threadNum, nDepto):
    global filaDMEC, lockDMEC
    print("soy {} y entré".format(threadNum))
    lockDMEC.acquire()
    print(threadNum)
    if (len(filaDMEC) == 9):
        lockDMEC.release()
        return 0 #en caso de error se retira del departamento y se salta la apelación xD

    else:
        print("Guardo")
        in_fila = datetime.now().strftime("%H:%M:%S:%f")
        filaDMEC.append(threadNum)

        if (len(filaDMEC) >= 4):
            for i in range(4):
                in_dpto = datetime.now().strftime("%H:%M:%S:%f")
                dMecConsulta(filaDMEC[i],nDepto) #Funcion definida para procesar las consultas
                out = filaDMEC[i]
                f = open("Departamento_de_mecanica.txt","a")
                f.write("persona " + str(out) + ", " + str(in_fila) + ", " + str(in_dpto) + ", " + str(nDepto) + "\n")
                f.close()
            for i in range(4):
                filaDMEC.pop(0)
                
    print(filaDMEC)
    lockDMEC.release()

    return 1


#DMIN FUNCS
def dMinConsulta(thread, nDepto):
    time.sleep(5)
    print("Salida de {}".format(thread))
    return

def dMin(threadNum, nDepto):
    global filaDMIN, lockDMIN
    print("soy {} y entré".format(threadNum))
    lockDMIN.acquire()
    print(threadNum)
    if (len(filaDMIN) == 7):
        lockDMIN.release()
        return 0 #en caso de error se retira del departamento y se salta la apelación xD

    else:
        print("Guardo")
        in_fila = datetime.now().strftime("%H:%M:%S:%f")
        filaDMIN.append(threadNum)

        if (len(filaDMIN) >= 2):
            for i in range(2):
                in_dpto = datetime.now().strftime("%H:%M:%S:%f")
                dMinConsulta(filaDMIN[i],nDepto) #Funcion definida para procesar las consultas
                out = filaDMIN[i]
                f = open("Departamento_de_minas.txt","a")
                f.write("persona " + str(out) + ", " + str(in_fila) + ", " + str(in_dpto) + ", " + str(nDepto) + "\n")
                f.close()
            for i in range(2):
                filaDMIN.pop(0)
                
    print(filaDMIN)
    lockDMIN.release()

    return 1

func_array = [defider,dMat,dInf,dFis,dQuim,dMec,dMin]
count = 0

def patioLamps(threadNum):
    entrance_t = datetime.now().strftime("%H:%M:%S:%f")
    assign1 = random.randint(0,6)
    match assign1:
        case 0:
            fst_assign = "DEFIDER"                   
        case 1:
            fst_assign = "Departamento de Matematicas"
        case 2:
            fst_assign = "Departamento de Informatica"
        case 3:
            fst_assign = "Departamento de Fisica"
        case 4:
            fst_assign = "Departamento de Quimica"
        case 5:
            fst_assign = "Departamento de Mecanica"
        case 6:
            fst_assign = "Departamento de Minas"
    
    in_dep1 = datetime.now().strftime("%H:%M:%S:%f")
    func_array[assign1](threadNum,1)
    #out_dep2 = time.now()

    assign2 = random.randint(0,6)
    while (assign2 == assign1):
        assign2 = random.randint(0,6)

    match assign2:
        case 0:
            snd_assign = "DEFIDER"                   
        case 1:
            snd_assign = "Departamento de Matematicas"
        case 2:
            snd_assign = "Departamento de Informatica"
        case 3:
            snd_assign = "Departamento de Fisica"
        case 4:
            snd_assign = "Departamento de Quimica"
        case 5:
            snd_assign = "Departamento de Mecanica"
        case 6:
            snd_assign = "Departamento de Minas"

    in_dep2 = datetime.now().strftime("%H:%M:%S:%f")
    func_array[assign2](threadNum,2)
    #out_dep2 = time.now()

    f = open("PdLamparas.txt","a")
    f.write("persona " + str(threadNum) + ", " + str(entrance_t) + ", " + fst_assign + ", " + str(in_dep1) + ", " + snd_assign + ", " + str(in_dep2) + "\n")
    f.close()

    out = datetime.now().strftime("%H:%M:%S:%f")
    f = open("salidas.txt","a")
    f.write("persona " + str(threadNum) + ", " + str(out) + "\n")
    return

thread_list = []
f_lamps = open("PdLamparas.txt","x")
f_dMat = open("Departamento_de_matematicas.txt","x")
f_defider = open("DEFIDER.txt","x")
f_dMin = open("Departamento_de_minas.txt","x")
f_salida = open("salidas.txt","x")
f_dMec = open("Departamento_de_mecanica.txt","x")
f_dQuim = open("Departamento_de_quimica.txt","x")
f_dFis = open("Departamento_de_fisica.txt","x")
f_dInf = open("Departamento_de_informatica.txt","x")

f_lamps.close()
f_dMat.close()
f_defider.close()
f_dMin.close()
f_dMec.close()
f_dQuim.close()
f_dFis.close()
f_dInf.close()
f_salida.close()

for thrd in range(0,500):
    t = threading.Thread(target=patioLamps,args=(thrd,))
    count = count + 1
    thread_list.append(t)

print("threads created: " + str(count))

for thrd in range(0,500):
    thread_list[thrd].start()
    #time.sleep(2)