package com.universalremote;

import android.os.Bundle;
import android.preference.PreferenceManager;
import android.app.Activity;
import android.content.Intent;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Button;

public class TVActivity extends Activity {
	
	private ButtonClickListener bcl;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
      //set default preference values
		//last argument as false means it will not override any
		//saved preferences, if they exist
		PreferenceManager.setDefaultValues(this, R.xml.preferences, false);
		
		bcl = new ButtonClickListener(this);
		
		final Button tv = (Button) findViewById(R.id.button_tv);
		tv.setOnClickListener(bcl);
		
		final Button receiver = (Button) findViewById(R.id.button_receiver);
		receiver.setOnClickListener(bcl);
		
		final Button cable = (Button) findViewById(R.id.button_cable);
		cable.setOnClickListener(bcl);
		
		final Button ps3 = (Button) findViewById(R.id.button_ps3);
		ps3.setOnClickListener(bcl);
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
