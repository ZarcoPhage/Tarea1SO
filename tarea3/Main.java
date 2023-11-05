import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.concurrent.ForkJoinPool;

public class Main{
    public static void main(String[] args){
        //String targetWord = inputFilePath[0];
        //File wordSearchMatrix = new File(inputFilePath[1]);

        String path = "./input/sopa_de_letras.txt";
        DataExtractor extractor = new DataExtractor(path);
        extractor.Extract();

        //System.out.println(extractor.getDim());
        //System.out.println(extractor.getTargetWord());
        char[][] matrix = extractor.getMatrix();

        /*
        int i,k;
        for (i = 0; i<extractor.getDim(); i++){
            for (k=0; k<extractor.getDim();k++){
                System.out.print(matrix[i][k]);
            }
            System.out.println(" ");
        }*/

        long forkStart = System.currentTimeMillis();

        ForkWordSearch task = new ForkWordSearch(matrix, extractor.getTargetWord(), 0, 0, extractor.getDim(), extractor.getTargetWord().length(), extractor.getDim());
        ForkJoinPool pool = new ForkJoinPool();
        Integer[] res = pool.invoke(task);

        long forkEnd = System.currentTimeMillis() - forkStart;

        System.out.println("PALABRA ENCONTRADA EN FILA: " + res[0] + " COLUMNA: " + res[1]);

        System.out.println("TIEMPO FORK: " + forkEnd);

        long threadStart = System.currentTimeMillis();
        Multithreading first = new Multithreading(matrix, extractor.getTargetWord(), extractor.getDim(), extractor.getTargetWord().length(), 0, 0);
        first.start();
        while(first.isAlive());
        long threadEnd = System.currentTimeMillis() - threadStart;

        System.out.println("TIEMPO THREADS: " + threadEnd);

        long normalStart = System.currentTimeMillis();
        NormalSearch second = new NormalSearch(matrix, extractor.getTargetWord(), extractor.getTargetWord().length(),extractor.getDim());
        second.search();
        long normalEnd = System.currentTimeMillis() - normalStart;

        System.out.println("TIEMPO PROGRAMA SECUENCIAL: " + normalEnd);

    }

}