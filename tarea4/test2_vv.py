import threading
import time
import random
from datetime import datetime

global lockDefider
lockDefider = threading.Lock()
conditionDefider = threading.Condition(lock=lockDefider)

global filaDefider
filaDefider = []

def defiderConsulta(thread, nDepto):
    global defiderLocks

    time.sleep(1)
    print("Salida de {}".format(thread))
    return

def defider(threadNum, nDepto):
    global filaDefider, lockDefider, defiderLocks
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
                f = open("DEFIDER.txt","a")
                f.write("persona " + str(threadNum) + ", " + str(in_fila) + ", " + str(in_dpto) + ", " + str(nDepto) + "\n")
                f.close()
            for i in range(5):
                filaDefider.pop(0)
    
    print(filaDefider)
    lockDefider.release()

    
    return 1

    #if (lockDefider.locked()):
    #    conditionDefider.wait()
    #
    #conditionDefider.acquire()

#    time.sleep(9)

#    conditionDefider.release()
  #  conditionDefider.notify()
    

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
    entrance_t = datetime.now().strftime("%H:%M:%S:%f")
    assign1 = 0 #random.randint(0,6)
    match assign1:
        case 0:
            fst_assign = "defider"                   
        case 1:
            fst_assign = "dInf"
        case 2:
            fst_assign = "dFis"
        case 3:
            fst_assign = "DMat"
        case 4:
            fst_assign = "dQuim"
        case 5:
            fst_assign = "dMec"
        case 6:
            fst_assign = "dMinas"
    
    in_dep1 = datetime.now().strftime("%H:%M:%S:%f")
    func_array[assign1](threadNum,1)
    #out_dep2 = time.now()

    assign2 = 0#random.randint(0,6)
    #while (assign2 == assign1):
    #    assign2 = random.randint(0,6)

    match assign2:
        case 0:
            snd_assign = "defider"
        case 1:
            snd_assign = "dInf"
        case 2:
            snd_assign = "dFis"
        case 3:
            snd_assign = "DMat"
        case 4:
            snd_assign = "dQuim"
        case 5:
            snd_assign = "dMec"
        case 6:
            snd_assign = "dMinas"

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

for thrd in range(0,20):
    t = threading.Thread(target=patioLamps,args=(thrd,))
    count = count + 1
    thread_list.append(t)

print("threads created: " + str(count))

for thrd in range(0,20):
    thread_list[thrd].start()
    #time.sleep(2)