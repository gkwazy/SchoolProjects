package gk.company;


import java.io.*;
import java.net.Socket;
import java.util.Scanner;

class HTTPResponse extends Thread {


    public HTTPResponse(){

    }


    public void sendInfo(Socket clientSocket, String[] request) throws IOException, InterruptedException {
        OutputStream outputStream = clientSocket.getOutputStream();
        PrintWriter printWriter = new PrintWriter((outputStream));
        String contentType;
        switch (request[1]) {
            case "/":
                String wantedFile = "./resources/index.html";
                contentType = "text/html";
                HTTPFileSent(clientSocket, wantedFile, contentType);
                break;
            case "/index.css":
                wantedFile = "./resources/index.css";
                contentType = "text/css";
                HTTPFileSent(clientSocket,wantedFile, contentType);
                break;
            default:
                System.out.println("Connected to " + clientSocket.getRemoteSocketAddress());
                printWriter.println("HTTP/1.1 404 Not Found");
                printWriter.println("Content-Length : 12");
                printWriter.println("Content-Type: text");
                printWriter.println("");
                printWriter.println("404 Page Not Found");
                printWriter.flush();
                System.out.println("Sent.. .." + Thread.currentThread().getId());

        }
    }

    public void HTTPFileSent(Socket clientSocket, String wantedFile, String contentType) throws IOException, InterruptedException {
        String outputFileString = "";
        OutputStream outputStream = clientSocket.getOutputStream();
        Scanner userScanner = new Scanner(new FileInputStream(wantedFile));
        PrintWriter printWriter = new PrintWriter((outputStream));
        while (userScanner.hasNextLine()) {
            outputFileString += userScanner.nextLine();
//            Thread.sleep(100);
        }
        System.out.println("Connected to " + clientSocket.getRemoteSocketAddress());
        printWriter.println("HTTP/1.1 200 OK");
        printWriter.println("Content-Length : " + outputFileString.getBytes().length);
        printWriter.println("Content-Type: " + contentType);
        printWriter.println("");
        printWriter.println(outputFileString);
        printWriter.flush();
        System.out.println("Sent.." + contentType + "..." + Thread.currentThread().getId());
    }

}
