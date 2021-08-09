package gk.company;

import java.io.IOException;
import java.io.InputStream;
import java.net.Socket;
import java.util.Scanner;

public class HTTPRequest {

    public HTTPRequest() {

    }

    public String[] parseRequest(Socket clientSocket) throws IOException {
        InputStream input = clientSocket.getInputStream();
        Scanner scanner = new Scanner(input);
        scanner.useDelimiter(" ");
        String tempRequest = scanner.nextLine();
        String[] request = tempRequest.split(" ");
        System.out.println(request[1] + 1);
        return request;
    }
}
