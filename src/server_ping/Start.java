package server_ping;

import java.io.*;
import java.net.*;


public class Start {
    public static void main(String[] args) throws Exception {
        String status = getStatus("https://www.google.co.uk");
        System.out.println("The website is: " + status);
    }
    public static String getStatus(String url) throws IOException {
        String result = "";
        try {
            HttpURLConnection connection = getConnection(url);
            int code = getCode(connection);
            if (code != HttpURLConnection.HTTP_OK) {
                 while (code == HttpURLConnection.HTTP_MOVED_TEMP
                        || code == HttpURLConnection.HTTP_MOVED_PERM
                        || code == HttpURLConnection.HTTP_SEE_OTHER){
                    String newUrl = getRedirectURL(connection);
                    HttpURLConnection newConnection = getConnection(newUrl);
                    code = getCode(newConnection);
                 }
            }
            result = "Red";
            System.out.println(code);
            if (code == HttpURLConnection.HTTP_OK) {
                result = "Green";
            }
        } catch (Exception e) {
            System.out.println(e.getMessage());
            result = "Red";
        }
        return result;
    }
    public static HttpURLConnection getConnection(String url) throws Exception{
        URL siteURL = new URL(url);
        HttpURLConnection connection = (HttpURLConnection) siteURL.openConnection();
        return connection;
    }

    public static int getCode(HttpURLConnection connection)throws Exception{
        connection.setRequestMethod("GET");
        connection.connect();
        int code = connection.getResponseCode();
        return code;
    }

    public static String getRedirectURL(HttpURLConnection connection){
        String newUrl = connection.getHeaderField("Location");
        return newUrl;
    }
}