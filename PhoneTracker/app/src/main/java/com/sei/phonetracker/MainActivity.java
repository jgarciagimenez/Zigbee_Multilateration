package com.sei.phonetracker;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import java.net.Socket;

public class MainActivity extends AppCompatActivity {

    private Beacon_RSSI rssi = null;
    final String ap_prefix = "Node_MCU_";
    final String IP = "192.168.1.1";
    final int PORT = 65090;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    @Override
    protected void onStart() {
        super.onStart();

        if (rssi == null) {
            rssi = new Beacon_RSSI();
            rssi.execute(this, ap_prefix);
        }
    }
}
