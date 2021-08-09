package com.example.androidchat2;

public class Message {
    private String userView;
    private String messageView;

    public Message(String userView, String messageView) {
       this.messageView = messageView;
       this.userView = userView;
    }

    public String getUserView() {
        return userView;
    }
    public String getMessageView() {
        return messageView;
    }

}
