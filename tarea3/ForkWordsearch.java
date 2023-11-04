import java.util.concurrent.ForkJoinPool; 
import java.util.concurrent.RecursiveTask; 

class ForkWordSearch extends RecursiveTask<Integer[]> {
    char[][] matrix;
    String targetWord;
    int dim, stX, stY, minSize, actualSize;

    ForkWordSearch(char[][] matrix, String targetWord, int stX, int stY, int dim, int minSize, int actualSize){
        this.matrix = matrix;
        this.stX = stX;
        this.stY = stY;
        this.minSize = minSize;
        this.actualSize = actualSize;
        this.dim = dim;
        this.targetWord = targetWord;
    }

    @Override
    protected Integer[] compute(){
        //System.out.println(this.targetWord);
        Integer[] finalPos = new Integer[3];
        finalPos[0] = -1;
        finalPos[1] = -1;
        finalPos[2] = 0; //0 dado que no hay dirección donde haya sido encontrada la palabra

        if (actualSize <= minSize){
            //System.out.println("stX: " + this.stX + " stY: " + this.stY);
            int i,k, j, coincid;
            char[] aux = targetWord.toCharArray();
            int counter = 0;
            boolean flag = false;

            coincid = 0;
            //System.out.println("vertical search");
            for (i = this.stY; i<(this.stY + actualSize); i++){
                for (k=this.stX;k<(this.stX + actualSize);k++){
                    if (matrix[i][k] == aux[0]){
                        coincid = 1;
                        //System.out.println(matrix[i][k]);
                        for (j=1;j<this.targetWord.length();j++){
                            //System.out.println("start iterate");
                            if ((i+j) < this.dim){
                                //System.out.println(matrix[i+j][k]);
                                if (matrix[i+j][k] != aux[j]){
                                    coincid = 0;
                                    //System.out.println("break");
                                    break;
                                }
                                coincid++;
                            }else{
                                coincid = 0;
                                //System.out.println("break");
                                break;
                            }
                        }
                        //System.out.println("end iterate: " + j + "coincid: " + coincid);
                        if (coincid == minSize){
                            //System.out.println("found at " + i + " " + k);
                            flag = true;
                            finalPos[0] = i;
                            finalPos[1] = k;
                            finalPos[2] = 1; //encontrado en vertical
                            break;
                        }
                    }
                }
                if (flag){
                    break;
                }
            }
            

            if (flag == false){
                //System.out.println("horizontal search");
                for (i = this.stY; i<(this.stY + actualSize); i++){
                    for (k=this.stX;k<(this.stX + actualSize);k++){
                        if (matrix[i][k] == aux[0]){
                            coincid = 1;
                            //System.out.println(matrix[i][k]);
                            for (j=1;j<this.targetWord.length();j++){
                                if ((k+j) < this.dim){
                                    //System.out.println(matrix[i][k+j]);
                                    if (matrix[i][k+j] != aux[j]){
                                        coincid = 0;
                                        //System.out.println("break");
                                        break;
                                    }
                                    coincid++;
                                }else{
                                    coincid = 0;
                                    //System.out.println("break");
                                    break;
                                }
                            }
                            //System.out.println("end iterate: " + j + "coincid: " + coincid);
                            if (coincid == minSize){
                                //System.out.println("found at " + i + " " + k);
                                flag = true;
                                finalPos[0] = i;
                                finalPos[1] = k;
                                finalPos[2] = 2; //encontrado horizontal
                                break;
                            }
                        }
                    }
                    if (flag){
                        break;
                    }
                }
            }
            //System.out.println("FINAL I K " + finalPos[0] + " " + finalPos[1]);
        } else {
            int middle = actualSize / 2;  //no importa -> matriz cuadrada
            
            ForkWordSearch subtaskA = new ForkWordSearch(matrix, this.targetWord, this.stX, this.stY, this.dim, this.minSize, middle);
            ForkWordSearch subtaskB = new ForkWordSearch(matrix, this.targetWord, (this.stX + middle), this.stY, this.dim, this.minSize, middle);
            ForkWordSearch subtaskC = new ForkWordSearch(matrix, this.targetWord, this.stX, (this.stY + middle), this.dim, this.minSize, middle);
            ForkWordSearch subtaskD = new ForkWordSearch(matrix, this.targetWord, (this.stX + middle), (this.stY + middle), this.dim, this.minSize, middle);

            subtaskA.fork();
            subtaskB.fork();
            subtaskC.fork();
            subtaskD.fork();

            Integer[][] results = new Integer[4][2];

            results[0] = subtaskA.join();
            results[1] = subtaskB.join();
            results[2] = subtaskC.join();
            results[3] = subtaskD.join();

            for (int i = 0; i<4;i++){
                if (results[i][0] != -1){
                    finalPos[0] = results[i][0];
                    finalPos[1] = results[i][1];
                    finalPos[2] = results[i][2];
                    break;
                }
            }
        
        }
        return finalPos;
    }

}