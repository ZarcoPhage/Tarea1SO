public class Multithreading extends Thread{
    int size;
    int goal;
    int x;
    int y;
    char[][] matrix;
    String Word;
    public  Multithreading(char[][] matrix, String Word ,int size, int goal, int x, int y){
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
            Multithreading sub = new Multithreading(matrix, Word, nn, goal, x, y);
            Multithreading sub2 = new Multithreading(matrix, Word, nn, goal, x+nn, y);
            Multithreading sub3 = new Multithreading(matrix, Word, nn, goal, x, y + nn );
            Multithreading sub4 = new Multithreading(matrix, Word, nn, goal, x+nn , y + nn);
            sub.start();
            sub2.start();
            sub3.start();
            sub4.start();
            while(sub.isAlive()||sub2.isAlive()||sub3.isAlive()||sub4.isAlive());
        }
        else {
            int count = 0;
            for (int i = 0; i < goal; i++){
                for (int j = 0 ; j < goal ; j++){
                    if (matrix[y+i][x+j] == Word.charAt(count) ) count++;
                    else {
                        count = 0;
                        j = goal;
                    }
                }
                if (count == goal){
                    System.err.println("PALABRA ENCONTRADA EN Fila "+(y+i)+",  columna ["+(x)+", "+ (x+goal-1)+"].");
                    return;
                }
            }
            count = 0;
            for (int i = 0; i < goal; i++){
                for (int j = 0 ; j < goal ; j++){
                    if (matrix[y+j][x+i] == Word.charAt(count) ) count++;
                    else {
                        count = 0;
                        j = goal;
                    }
                }
                if (count == goal){
                    System.err.println("PALABRA ENCONTRADA EN Fila ["+y+", "+ (y+goal-1)+ "],  columna "+(x+i)+".");
                    return;
                }
                
            }
    }


    }
}
