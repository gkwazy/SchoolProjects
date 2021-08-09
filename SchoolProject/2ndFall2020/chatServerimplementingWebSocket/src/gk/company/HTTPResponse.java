package gk.company;

import java.io.*;
import java.net.Socket;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Base64;
import java.util.HashMap;
import java.util.Scanner;

public class HTTPResponse {

    public HTTPResponse(){

    }

     public void openWebSocket(HashMap<String, String> requestMap,Socket client) throws NoSuchAlgorithmException, IOException {
        OutputStream out = client.getOutputStream();
        byte[] response = ("HTTP/1.1 101 Switching Protocols\r\n"
                + "Connection: Upgrade\r\n"
                + "Upgrade: websocket\r\n"
                + "Sec-WebSocket-Accept: "
                + Base64.getEncoder().encodeToString(MessageDigest.getInstance("SHA-1").digest((requestMap.get("Sec-WebSocket-Key") + "258EAFA5-E914-47DA-95CA-C5AB0DC85B11").getBytes("UTF-8")))
                + "\r\n\r\n").getBytes("UTF-8");
         out.write(response, 0, response.length);
         System.out.println("Connected to client");
    }

    public void sendInfo(Socket clientSocket, String request) throws IOException, InterruptedException {
        OutputStream outputStream = clientSocket.getOutputStream();
        PrintWriter printWriter = new PrintWriter((outputStream));
        String contentType;
        switch (request) {
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
            case "/FrontEnd.js":
                wantedFile = "./resources/FrontEnd.js";
                contentType = "application/javascript";
                HTTPFileSent(clientSocket,wantedFile, contentType);
                break;
            default:
                printWriter.println("HTTP/1.1 404 Not Found");
                printWriter.println("Content-Length : 12");
                printWriter.println("Content-Type: text");
                printWriter.println("");
                printWriter.println("404 Page Not Found");
                printWriter.flush();
                System.out.println("Sent...." + Thread.currentThread().getId());

        }
    }

    public void HTTPFileSent(Socket clientSocket, String wantedFile, String contentType) throws IOException, InterruptedException {
        String outputFileString = "";
        OutputStream outputStream = clientSocket.getOutputStream();
        PrintWriter printWriter = new PrintWriter((outputStream));

        Scanner userScanner = new Scanner(new FileInputStream(wantedFile));
        while (userScanner.hasNextLine()) {
            outputFileString += userScanner.nextLine();
            outputFileString += "\n";
        }
        System.out.println("Connected to " + clientSocket.getRemoteSocketAddress());
        printWriter.println("HTTP/1.1 200 OK");
        printWriter.println("Content-Length : " + outputFileString.getBytes().length);
        printWriter.println("Content-Type: " + contentType);
        printWriter.println("");
        printWriter.println(outputFileString);
        printWriter.flush();
    }

}
