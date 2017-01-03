package com.sei.phonetracker;

import android.content.Context;
import android.net.wifi.ScanResult;
import android.net.wifi.WifiManager;
import android.os.AsyncTask;
import android.os.Debug;
import android.util.Log;

import java.util.List;

/**
 * Created by xismy on 3/01/17.
 */

public class Beacon_RSSI extends AsyncTask<Object, ScanResult, Integer> {
    private boolean measure = true;

    public synchronized void stop(){
        measure = false;
    }

    @Override
    protected Integer doInBackground(Object... params) {
        Context context = (Context)params[0];
        String prefix = (String) params[1];
        WifiManager wifiManager = (WifiManager) context.getSystemService(Context.WIFI_SERVICE);

        while(measure){
            List<ScanResult> aps = wifiManager.getScanResults();

            for(ScanResult ap:aps){
                if(ap.BSSID.startsWith(prefix))
                    publishProgress(ap);
            }
        }
        return 0;
    }

    @Override
    protected void onProgressUpdate(ScanResult... value) {
        super.onProgressUpdate(value);
        Log.d(value[0].BSSID, ""+value[0].level);
    }
}
