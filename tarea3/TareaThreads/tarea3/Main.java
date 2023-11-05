import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.concurrent.ForkJoinPool;

public class Main{
    public static void main(String[] args){
        //String targetWord = inputFilePath[0];
        //File wordSearchMatrix = new File(inputFilePath[1]);

        String path = "D:\\U\\2023 2\\SO\\TareaThreads\\tarea3\\tests\\LAMBDA\\sopa_de_letras.txt";
        DataExtractor extractor = new DataExtractor(path);
        extractor.Extract();

        System.out.println(extractor.getDim());
        System.out.println(extractor.getTargetWord());
        char[][] matrix = extractor.getMatrix();

        int i,k;
        for (i = 0; i<extractor.getDim(); i++){
            for (k=0; k<extractor.getDim();k++){
                System.out.print(matrix[i][k]);
            }
            System.out.println(" ");
        }
        System.err.println("tamaño ="+ extractor.getTargetWord().length());
        matrixsize first = new matrixsize(matrix, extractor.getTargetWord(),extractor.getDim(), extractor.getTargetWord().length(), 0, 0);
        first.start();
        while(matrixsize.getSignal()!=1){
            System.err.println();
        }
        System.err.println("Encontrado");
        NormalSearch second = new NormalSearch(matrix, extractor.getTargetWord(), extractor.getTargetWord().length(),extractor.getDim());
        second.search();



    }

}