import java.util.concurrent.ForkJoinPool; 
import java.util.concurrent.RecursiveTask; 

class ForkWordSearch extends RecursiveTask<Integer[]> {
    char[][] matrix;
    String targetWord;
    int dim, verticalStart, verticalEnd, horizontalStart, horizontalEnd;

    ForkWordSearch(char[][] matrix, String targetWord, int verticalStart, int verticalEnd, int horizontalStart, int horizontalEnd, int dim){
        this.matrix = matrix;
        this.targetWord = targetWord;
        this.verticalStart = verticalStart;
        this.verticalEnd = verticalEnd;
        this.horizontalEnd = horizontalEnd;
        this.horizontalStart = horizontalStart;
        this.dim = dim;
    }

    @Override
    protected Integer[] compute(){
        System.out.println("COMPUTING start:" + this.verticalStart + " " + this.horizontalStart + " end:" + this.verticalEnd + " " + this.horizontalEnd);
        Integer[] finalPos = new Integer[2];
        finalPos[0] = -1;
        finalPos[1] = -1;

        if ((this.verticalEnd - this.verticalStart) <= this.targetWord.length()){
            int i,k, j;
            char[] aux = targetWord.toCharArray();
            int counter = 0;
            boolean flag = false;
            //VERTICAL search
            for (i = this.verticalStart; i<this.verticalEnd; i++){
                for (k = this.horizontalStart; k<this.horizontalEnd; k++){
                    if (matrix[i][k] == aux[0]){
                        System.out.println(i + "," + k + " " + matrix[i][k]);
                    }
                }
            }
            if (flag){
                System.out.println("F O U N D");
            }

        } else {
            int middle = (verticalEnd + verticalStart) / 2;  //no importa -> matriz cuadrada
            
            ForkWordSearch subtaskA = new ForkWordSearch(matrix, this.targetWord, this.verticalStart, middle, this.horizontalStart, middle, this.dim);
            ForkWordSearch subtaskB = new ForkWordSearch(matrix, this.targetWord, this.verticalStart, middle, middle, this.horizontalEnd, this.dim);
            ForkWordSearch subtaskC = new ForkWordSearch(matrix, this.targetWord, middle, this.verticalEnd, this.horizontalStart, middle, this.dim);
            ForkWordSearch subtaskD = new ForkWordSearch(matrix, this.targetWord, middle, this.verticalEnd, middle, this.horizontalEnd, this.dim);

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