import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class DataExtractor{
    private File targetFile;
    private char[][] matrix;
    private int dimension;
    private String targetWord;

    public DataExtractor(String Path){
        this.targetFile = new File(Path);
        //System.out.println(targetFile.getName());
    }

    public char[][] getMatrix(){
        return matrix;
    }

    public int getDim(){
        return dimension;
    }

    public String getTargetWord(){
        return targetWord;
    }

    public void Extract(){
        try{ 
            Scanner reader = new Scanner(this.targetFile);

            String dimensionStr = reader.nextLine();
            this.dimension = Integer.parseInt(dimensionStr);
            //System.out.println(dimension);

            this.targetWord = reader.nextLine();
            //System.out.println(targetWord);
                
            this.matrix = new char[dimension][dimension];

            String readStr;
            char[] aux = new char[dimension*2-1];
            int i;
            int k;
            int counter;
            for (i = 0; i<dimension; i++){
                readStr = reader.nextLine();
                aux = readStr.toCharArray();
                counter = 0;
                for (k = 0; k<dimension*2-1; k++){
                    if (aux[k] != ' '){
                        this.matrix[i][counter] = aux[k];
                        counter++; 
                    }
                }
            }
        
        } catch (FileNotFoundException e) {
            System.out.println("error reading file");
            e.printStackTrace();
        }
    }
}