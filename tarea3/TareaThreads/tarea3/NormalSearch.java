public class NormalSearch {
    char[][] matrix;
    String word;
    int length;
    int dim;
    public NormalSearch(char[][] matrix, String Word, int length, int dim){
        this.matrix = matrix;
        this.word = Word;
        this.length = length;
        this.dim = dim;
    }

    public void search() {
        short count = 0;
        for (int i = 0; i < dim; i++){
            for (int j = 0 ; j < dim ; j++){
                if (matrix[i][j] == word.charAt(count) ) count++;
                else count = 0;
                if (count == length ){
                    System.err.println("Fila "+ i + ", columna "+(j-length+1));
                    i = dim;
                    break;
                }
            }
        }

        count = 0;
        for (int i = 0; i < dim; i++){
            for (int j = 0 ; j < dim ; j++){
                if (matrix[j][i] == word.charAt(count) ) count++;
                else count = 0;
                if (count == length ){
                    System.err.println("Fila "+ (j-length+1) + ", columna "+i);
                    i = dim;
                    break;
                }
            }
        }


    }
}
