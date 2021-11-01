import java.io.File;
import java.io.IOException;
import java.util.Map;
import java.util.HashMap;

public class code {
    public static void main(String[] args) {
        Map<Integer, String> m = new HashMap<Integer, String>();
        m.put(1,"s");
        m.put(2, "u");
        m.put(3, "p");

        Map<String, HashMap<Integer, String>> cm = new HashMap<String, HashMap<Integer, String>>();
        
        cm.put("Lex", new HashMap<Integer, String>());
        var toUpdate = cm.get("Lex");
        toUpdate.put(1, "Inter");
        System.out.println(cm);

        Bark b = new Bark();

        b.makeSound();
        
        for (var x : m.entrySet()) {
            System.out.println(x.getValue());
        }
    }
}

interface AnimalSounds {
    public void makeSound();
}

class Bark implements AnimalSounds {
    private String bark;

    public Bark() {
        bark = "Bark";
    }

    public void makeSound() {
        System.out.println(this.bark);
    }
}