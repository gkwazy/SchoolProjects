package com.example.androidchat2;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;

public class MainActivity extends AppCompatActivity {

    public static final String EXTRA_MESSAGE = "";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void submit(View view) {
        Intent intent = new Intent(this, ChatRoom.class);
        EditText userInput = (EditText) findViewById(R.id.userInput);
        EditText roomInput = (EditText) findViewById(R.id.roomInput);
        String message = userInput.getText().toString() + " " + roomInput.getText().toString();
        intent.putExtra(EXTRA_MESSAGE, message);
        startActivity(intent);
    }
}