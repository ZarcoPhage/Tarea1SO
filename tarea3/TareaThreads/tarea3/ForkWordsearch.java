import java.util.concurrent.ForkJoinPool; 
import java.util.concurrent.RecursiveTask; 

class ForkWordSearch extends RecursiveTask<Integer[]> {
    char[][] matrix;
    String targetWord;
    int verticalStart, verticalEnd, horizontalStart, horizontalEnd;

    ForkWordSearch(char[][] matrix, String targetWord, int verticalStart, int verticalEnd, int horizontalStart, int horizontalEnd){
        this.matrix = matrix;
        this.targetWord = targetWord;
        this.verticalStart = verticalStart;
        this.verticalEnd = verticalEnd;
        this.horizontalEnd = horizontalEnd;
        this.horizontalStart = horizontalStart;
    }


    @Override
    protected Integer[] compute(){
        Integer[] finalPos = new Integer[2];
        finalPos[0] = -1;
        finalPos[1] = -1;

        if ((this.verticalEnd - this.verticalStart) <= targetWord.length()){
            int i,k, j;
            char[] aux = targetWord.toCharArray();
            int counter = 0;
            boolean flag = false;
            //horizontal search
            for (i = this.verticalStart; i<=this.verticalEnd; i++){
                for (k = this.verticalStart; k<=this.verticalEnd; k++){
                    if (matrix[i][k] == aux[0]){
                        for (j = 1; j<targetWord.length();j++){
                            if (matrix[i+j][k] != aux[j]){
                                finalPos[0] = -1;
                                finalPos[1] = -1;
                                break;
                            }
                            finalPos[0] = i;
                            finalPos[1] = k;
                        }
                        for (j=1; j<targetWord.length();j++){
                            if (matrix[i][k+j] != aux[j]){
                                finalPos[0] = -1;
                                finalPos[1] = -1;
                                break;
                            }
                            finalPos[0] = i;
                            finalPos[1] = k;
                        }
                    }
                }
            }


        } else {
            int middle = (verticalEnd + verticalStart) / 2;  //no importa -> matriz cuadrada
            
            ForkWordSearch subtaskA = new ForkWordSearch(matrix, this.targetWord, this.verticalStart, middle, this.horizontalStart, middle);
            ForkWordSearch subtaskB = new ForkWordSearch(matrix, this.targetWord, this.verticalStart, middle, middle, this.horizontalEnd);
            ForkWordSearch subtaskC = new ForkWordSearch(matrix, this.targetWord, middle, this.verticalEnd, this.horizontalStart, middle);
            ForkWordSearch subtaskD = new ForkWordSearch(matrix, this.targetWord, middle, this.verticalEnd, middle, this.horizontalEnd);

            subtaskA.fork();
            subtaskB.fork();
            subtaskC.fork();
            subtaskD.fork();

            Integer[][] results = new Integer[4][2];

            results[0] = subtaskA.join();
            results[1] = subtaskB.join();
            results[2] = subtaskC.join();
            results[3] = subtaskD.join();

            for (int i = 0; i<3;i++){
                if (results[i][0] != -1){
                    finalPos[0] = results[i][0];
                    finalPos[1] = results[i][1];
                    break;
                }
            }
        
        }
        return finalPos;
    }

}