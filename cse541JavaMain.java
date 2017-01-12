package com.example.arduinocontroller_0;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
//import java.util.Scanner;

import android.os.Bundle;
import android.os.StrictMode;
import android.annotation.SuppressLint;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.view.Menu;
import android.view.View;
import android.widget.Button;

public class MainActivity extends Activity {
	Socket       soc;
	InputStream  in;
	OutputStream out;

// connect to network
	public void connect()
       {
         try{
                 soc = new Socket("192.168.1.11",23);
                 in  = soc.getInputStream();
                 out = soc.getOutputStream();
         }catch(Exception e)
         {
             new AlertDialog.Builder(this)
             .setTitle("Error")
             .setMessage("There was a problem connecting to the Arduino")
             .setPositiveButton("Reconnect", new DialogInterface.OnClickListener() {

                 public void onClick(DialogInterface dialog, int which) {
                             connect();
           
                 }
             })
             .setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
                 public void onClick(DialogInterface dialog, int which) {
                     System.exit(0);         }
             })
             .show();
         }
       }

		@SuppressLint("NewApi") protected void onCreate(Bundle savedInstanceState) {
			super.onCreate(savedInstanceState);
			
			//code for android restriction
			//==========================
			StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
			StrictMode.setThreadPolicy(policy);
			
			setContentView(R.layout.activity_main);
			
			connect();
			final Button upButton    = (Button) findViewById(R.id.upButton);
			final Button backButton  = (Button) findViewById(R.id.backButton);
			final Button leftButton  = (Button) findViewById(R.id.leftButton);
			final Button rightButton = (Button) findViewById(R.id.rightButton);
			final Button stopButton  = (Button) findViewById(R.id.stopButton);
			final Button incButton   = (Button) findViewById(R.id.incButton);
			final Button decButton   = (Button) findViewById(R.id.decButton);
			

			decButton.setOnClickListener(new View.OnClickListener() {
				@Override
				public void onClick(View v) {
					try {
						out.write('d');
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			});
			
			incButton.setOnClickListener(new View.OnClickListener() {
				@Override
				public void onClick(View v) {
					try {
						out.write('i');
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			});
			
			upButton.setOnClickListener(new View.OnClickListener() {
				@Override
				public void onClick(View v) {
					try {
						out.write('f');
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			});

			backButton.setOnClickListener(new View.OnClickListener() {
				@Override
				public void onClick(View v) {
					try {
						out.write('b');
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			});

			leftButton.setOnClickListener(new View.OnClickListener() {
				@Override
				public void onClick(View v) {
					try {
						out.write('l');
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			});

			rightButton.setOnClickListener(new View.OnClickListener() {
				@Override
				public void onClick(View v) {
					try {
						out.write('r');
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			});

			stopButton.setOnClickListener(new View.OnClickListener() {
				@Override
				public void onClick(View v) {
					try {
						out.write('s');
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			});
		}
		
    protected void onCreate1(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }
    
}
