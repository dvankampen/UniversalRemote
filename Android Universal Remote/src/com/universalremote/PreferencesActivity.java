package com.universalremote;

import android.app.Activity;
import android.content.SharedPreferences;
import android.content.SharedPreferences.OnSharedPreferenceChangeListener;
import android.os.Bundle;
import android.preference.Preference;
import android.preference.PreferenceActivity;
import android.preference.PreferenceManager;

public class PreferencesActivity extends PreferenceActivity implements OnSharedPreferenceChangeListener {

	public static final String KEY_PREF_IP = "pref_arduinoIP";
	public static final String KEY_PREF_BT = "pref_bluetooth";

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		addPreferencesFromResource(R.xml.preferences);
		// Set result CANCELED incase the user backs out
		setResult(Activity.RESULT_CANCELED);
		Preference connectionPref = findPreference(PreferencesActivity.KEY_PREF_IP);
			
	}

	public void onResume(){
		super.onResume();
		getPreferenceScreen().getSharedPreferences()
		.registerOnSharedPreferenceChangeListener(this);
	}

	@Override
	protected void onPause() {
		super.onPause();
		getPreferenceScreen().getSharedPreferences()
		.unregisterOnSharedPreferenceChangeListener(this);
		finish();
	}

	public void onSharedPreferenceChanged(SharedPreferences sharedPreferences,
			String key) {
		if (key.equals(KEY_PREF_IP)) {
			Preference connectionPref = findPreference(key);
			// Set summary to be the user-description for the selected value
			connectionPref.setSummary(sharedPreferences.getString(key, ""));
			//tell our calling activity that something changed!
			setResult(Activity.RESULT_OK);
		}else if (key.equals(KEY_PREF_BT)) {
			//tell our calling activity that something changed!
			setResult(Activity.RESULT_OK);
		}
	}
}
