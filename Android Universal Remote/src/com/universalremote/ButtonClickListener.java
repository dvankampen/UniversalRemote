package com.universalremote;

import java.net.SocketException;

import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.preference.PreferenceManager;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnTouchListener;

public class ButtonClickListener implements OnClickListener, OnTouchListener{

	private Activity main;
	
	private final String TAG = "Main: BCL";
	
	private CommandSender cs;

	public ButtonClickListener(Activity parent){
		main = parent;
		try {
			cs = new CommandSender();
		} catch (SocketException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public void onClick(View v) {
		String command = "TEST COMMAND";
		switch(v.getId()) {
		case R.id.button_tv:
			command = command.concat(" 1");
			cs.sendCommand(command);
			break;
		case R.id.button_receiver:
			Intent myIntent = new Intent(main, ReceiverActivity.class);
			main.startActivity(myIntent);
			break;
		case R.id.button_cable:
			command = command.concat(" 3");
			cs.sendCommand(command);
			break;
		case R.id.button_ps3:
			command = command.concat(" 4");
			cs.sendCommand(command);
			break;
		case R.id.power_receiver:
			cs.sendCommand("r");
			break;
		default:
			break;
		} 
			
		
	}

	public boolean onTouch(View v, MotionEvent arg1) {
		
		switch(v.getId()) {
		case R.id.vol_up_recv:
			cs.sendCommand("+");
			break;
		case R.id.vol_down_recv:
			cs.sendCommand("-");
			break;
		default:
			break;
		}
		// TODO Auto-generated method stub
		return false;
	}
}
