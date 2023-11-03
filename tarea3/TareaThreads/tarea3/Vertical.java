public class Vertical extends Thread{
    char[][] matrix;
    String word;
    int length;
    int x;
    int y;
    public Vertical(char[][] matrix, String Word, int length, int x, int y){
        this.matrix = matrix;
        this.word = Word;
        this.length = length;
        this.x = x;
        this.y = y;

    }
    public void run(){
        short count = 0;
        for (int i = 0 ; i < length ; i++){
            if (matrix[y+i][x] == word.charAt(i) ) count++;
            else count=0;
        }
        if (count == length){
            System.err.println("Palabra Vertical encontrada en ("+y+", "+x+").");
        }
    }

}
