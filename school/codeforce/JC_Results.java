import java.io.BufferedReader;
import java.io.FileReader;
import java.util.HashMap;

// TODO: Create a way of storing the mandatory subject codes and CSPE. X
//       We need a function that reads the data from an input file (not sure what is the most efficient way)
//       need to then select the data from the datatype it is stored in
//       then calculate what the average of those five is

class JC_Results {

    // The mandatory subjects that we need and CSPE that we need to remove every
    // time
    final int Irish = 1;
    final int English = 2;
    final int Maths = 3;
    final int CSPE = 218;
    final int largestCode = 569;
    HashMap<Integer, HashMap<Integer, Integer>> grades; // this hashmap will have the key be a student number and the value be a hashmap that has its keys be a subject code and the values be the grades for said subjects

    JC_Results() {
        this.grades = new HashMap<Integer, HashMap<Integer, Integer>>();    // initializes the grades hashmap
    }

    public int[] selectFiveGrades(int[] codes, int[] grades) {
        int[] results = new int[5];
        int selectedGrades = 0;
        int largestNonMandatory = 0;
        int secondLargestNonMandatory = 0;

        int i = 0;
        while (i < codes.length) {
            if (codes[i] != CSPE) {  // make sure the code isnt CSPE
                if (codes[i] == Irish || codes[i] == English || codes[i] == Maths) {  // if the code is for a mandatory, add it to results
                    results[selectedGrades] = grades[i];
                    selectedGrades++;
                } else {    // else check if it is one of the highest grades
                    int temp = 0;
                    if(grades[i] > largestNonMandatory) {
                        temp = largestNonMandatory;
                        largestNonMandatory = grades[i];
                        secondLargestNonMandatory = temp;       // if a new highest is found, old highest is now the second highest grade
                    }
                    else if(grades[i] > secondLargestNonMandatory) {
                        secondLargestNonMandatory = grades[i];
                    }
                }
            }
            i++;
        }

        results[selectedGrades] = largestNonMandatory;              // adding the highest non mandatory grades to results
        results[selectedGrades + 1] = secondLargestNonMandatory;

        return results;
    }

    private double calculateAverage(int[] selectedGrades) {     // simple algorithm for getting the average
        double result = 0.0;

        for (int s : selectedGrades) {
            result += s;
        }

        return result / 5;
    }

    private void readInData(String file) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader(file));       // reads the file using a buffered reader to read in one line of the file at a time

        String line = null;

        int studentNumber, code, grade;
        while((line = br.readLine()) != null) { 
            String[] values = line.split(",");  // splits the line up using , as the delimiter, into an array of strings using the built in split function

            studentNumber = Integer.parseInt(values[0]); // uses Integer.parseInt() to turn the string into an int
            HashMap<Integer, Integer> scores = new HashMap<Integer, Integer>(); // this hashmap will have the key be a subject code and value be grade
            for(int i = 1; i < values.length; i+=2) {   // doing it in twos as the codes and grades are grouped
                code = Integer.parseInt(values[i]);
                grade = Integer.parseInt(values[i+1]);
                scores.put(code, grade);
            }
            grades.put(studentNumber, scores);  // then putting the student number and scores hashmap into the grades hashmap
        }
        br.close();
    }

    public void getAllAverage(String file) {        // function wraps all other functions together and prints out all the student numbers and their average score
        try {
            readInData(file);
        } catch (Exception e) {
            e.printStackTrace();
        }

        for(int i : grades.keySet()) {  // cycles through the hashmap assigning i to be the key it is currently on
            HashMap<Integer, Integer> g = grades.get(i);    // the inner hashmap for this student
            int[] codes = new int[g.size()];   
            int[] scores = new int[g.size()];
            int j = 0;
            for(int k : g.keySet()) {   // setting up the codes and scores arrays for the selectFive grades
                codes[j] = k;           // all it does is iterate through the hashmap just like the one above, and then set the key to be codes[j]
                scores[j] = g.get(k);   // and the value to be scores[j], and then increments j
                j++;
            }
            int[] selectedGrades = selectFiveGrades(codes, scores); // get the selected grades
            System.out.println(i + " " + calculateAverage(selectedGrades)); // print the students average
        }
    }

    public static void main(String[] args) {
        // this is used as a basic testing tool, remove once test file is completed, as this is obsolete

        JC_Results j = new JC_Results();

        j.getAllAverage("JC_Results.txt");
    }
}