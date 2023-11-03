public class Horizontal extends Thread{
    char[][] matrix;
    String word;
    int length;
    int x;
    int y;
    public Horizontal(char[][] matrix, String Word, int length, int x, int y){
        this.matrix = matrix;
        this.word = Word;
        this.length = length;
        this.x = x;
        this.y = y;
    }
    public void run(){
        short count = 0;
        for (int i = 0 ; i < length ; i++){
            
            if (matrix[y][x+i] == word.charAt(i) ) count++;
            else count=0;
        }
        if (count == length){
            System.err.println("Palabra Horizontal encontrada en ("+y+", "+x+").");
        }
    }
}
