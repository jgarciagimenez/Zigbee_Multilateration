package com.sei.phonetracker;

import android.content.Context;
import android.net.wifi.ScanResult;
import android.net.wifi.WifiManager;
import android.os.AsyncTask;
import android.os.Debug;
import android.util.Log;
import android.widget.TextView;
import android.widget.Toast;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by xismy on 3/01/17.
 */

public class Beacon_RSSI extends AsyncTask<Object, Object, Integer> {
    private boolean measure = true;
    private MainActivity mainActivity = null;

    public synchronized void stop(){
        measure = false;
    }

    private ArrayList<Double> power = new ArrayList<Double>();

    @Override
    protected Integer doInBackground(Object... params) {
        mainActivity = (MainActivity)params[0];
        Context context = mainActivity.getApplicationContext();
        String prefix = (String) params[1];
        WifiManager wifiManager = (WifiManager) context.getSystemService(Context.WIFI_SERVICE);
        Socket socket;
        PrintWriter out;

        try {
            socket = new Socket(mainActivity.IP, mainActivity.PORT);
            out = new PrintWriter(socket.getOutputStream(), false);
        }
        catch (IOException exc){
            Log.d("Error Socket", exc.toString());
            return 1;
        }

        while(measure){
            power = new ArrayList<Double>();
            for(int i=0;i<5;i++) {
                wifiManager.startScan();
                List<ScanResult> aps = wifiManager.getScanResults();

                for (ScanResult ap : aps) {
                    if (ap.SSID.startsWith(prefix)) {
                        int apIndex = Integer.parseInt(ap.SSID.substring(prefix.length()))-1;
                        while(power.size()<apIndex+1)
                            power.add(0.0);
                        power.set(apIndex, 0.2*power.get(apIndex) + 0.8*ap.level);
                    }


                    try {
                        Thread.sleep(50);
                    } catch (InterruptedException ex) {

                    }
                }
            }

            for(int i=0; i<power.size();i++){
                out.printf("dist %d %.2f\n", i, power.get(i));
                out.flush();
                Log.d("Medida", ""+power.get(i));
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException ex) {

                }
            }
            out.println("loc ");
            try {
                Thread.sleep(1000);
            } catch (InterruptedException ex) {

            }
            out.flush();
            Log.d("Orden", "Medir");
        }

        try {
            socket.close();
        }
        catch (IOException exc){}
        return 0;
    }

    @Override
    protected void onProgressUpdate(Object... value) {
        super.onProgressUpdate(value);

        ((TextView)mainActivity.findViewById(R.id.power)).setText(value[0].toString());
    }
}
