import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class Main{
    public static void main(String[] args){
        //String targetWord = inputFilePath[0];
        //File wordSearchMatrix = new File(inputFilePath[1]);

        String path = "./input/sopa_de_letras.txt";
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





    }

}