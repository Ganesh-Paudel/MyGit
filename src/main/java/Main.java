
public class Main {

    public static void main(String[] args) {

        /**
         * Implementation of Git,
         * Basics and building on the complexity
         */

        if(args.length < 1){
            System.err.println("Usage: java -jar Main.jar <command> [<args>]");
            System.exit(1);
        }

        if(args.length == 1){
            if(args[0].equals("init")){
                Commands.initializeGit();
            }
        }

    }
}
