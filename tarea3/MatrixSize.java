public class MatrixSize extends Thread{
    int size;
    int goal;
    int x;
    int y;
    char[][] matrix;
    String Word;
    public MatrixSize(char[][] matrix, String Word ,int size, int goal, int x, int y){
        this.size = size;
        this.goal = goal;
        this.x = x;
        this.y = y;
        this.matrix = matrix;
        this.Word = Word;
    }
    @Override
    public void run() {
        if (size>goal){
            int nn =  size/2;
            MatrixSize sub = new MatrixSize(matrix, Word, nn, goal, x, y);
            MatrixSize sub2 = new MatrixSize(matrix, Word, nn, goal, x+nn, y);
            MatrixSize sub3 = new MatrixSize(matrix, Word, nn, goal, x, y + nn );
            MatrixSize sub4 = new MatrixSize(matrix, Word, nn, goal, x+nn , y + nn);
            sub.start();
            sub2.start();
            sub3.start();
            sub4.start();
        }
        else {
            //System.err.println("listo " + x +", "+ y);
            for (int i = 0; i < goal; i++){
                Horizontal newHorizontal = new Horizontal(matrix, Word, goal, x, y+i);
                newHorizontal.start();

            }
            for (int i = 0; i < goal; i++){
                Vertical newVertical = new Vertical(matrix, Word, goal, x+i, y);
                newVertical.start();
                
            }
    }


    }
}
