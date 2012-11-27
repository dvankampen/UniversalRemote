package com.universalremote;

import android.os.Bundle;
import android.preference.PreferenceManager;
import android.app.Activity;
import android.content.Intent;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Button;

public class ReceiverActivity extends Activity {
	
	private ButtonClickListener bcl;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.receiver_commands);
        
      //set default preference values
		//last argument as false means it will not override any
		//saved preferences, if they exist
		PreferenceManager.setDefaultValues(this, R.xml.preferences, false);
		
		bcl = new ButtonClickListener(this);
		
		final Button power = (Button) findViewById(R.id.power_receiver);
		power.setOnClickListener(bcl);
		
		final Button vol_up = (Button) findViewById(R.id.vol_up_recv);
		vol_up.setOnTouchListener(bcl);
		
		final Button vol_down = (Button) findViewById(R.id.vol_down_recv);
		vol_down.setOnTouchListener(bcl);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu, menu);
        return true;
    }
    
    @Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle item selection
		switch (item.getItemId()) {
		case R.id.menu_settings:
			// Launch the configuration settings menu
			Intent intent = new Intent(this, PreferencesActivity.class);
			startActivityForResult(intent, 1);
			return true;
		default:
			return super.onOptionsItemSelected(item);
		}
	}
    
}
