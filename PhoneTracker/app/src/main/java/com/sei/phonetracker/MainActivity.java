package com.sei.phonetracker;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

public class MainActivity extends AppCompatActivity {

    private Beacon_RSSI rssi = null;
    final String ap_prefix = "";

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
            rssi.execute(getApplicationContext(), ap_prefix);
        }
    }
}
