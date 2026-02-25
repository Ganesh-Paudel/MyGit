import java.io.IOException;
import java.io.PrintWriter;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class Commands {


    public static int initializeGit(){
        try {
            Path currentDirectory = Paths.get("./.myGit").toAbsolutePath();
            Path[] dependDirectories = {Paths.get("./.myGit/objects").toAbsolutePath(), Paths.get("./.myGit/refs/heads").toAbsolutePath()};

            Files.createDirectories(currentDirectory);

            Files.createDirectories(dependDirectories[0]);
            Files.createDirectories(dependDirectories[1]);

            Path headFile = Paths.get("./myGit/HEAD");
            if(Files.notExists(headFile)){
                Files.createFile(headFile);
            }

            try(PrintWriter out = new PrintWriter(Files.newOutputStream(headFile))) {
                System.out.println("In the printwriter");
                out.printf("ref: refs/heads/master");
            } catch (IOException e) {
                e.printStackTrace();
                return 0;
            }

            System.out.println("Initialized empty Git repository in .myGit");
            return 1;

        } catch (IOException e){
            System.err.println("Error creating the .git directory");
            return 0;
        }
    }

}
