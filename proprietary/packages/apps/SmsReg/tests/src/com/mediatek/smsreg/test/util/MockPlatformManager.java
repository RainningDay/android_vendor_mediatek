package com.mediatek.smsreg.test.util;

import android.app.PendingIntent;
import android.content.Context;
import android.util.Log;

import com.android.internal.telephony.PhoneConstants;
import com.mediatek.smsreg.PlatformManager;
import com.mediatek.smsreg.SmsRegConst;

public class MockPlatformManager extends PlatformManager {
    private static final String TAG = "SmsReg/MockPlatformManager";

    public static final String VALUE_IMEI = "863581010061401";
    public static final String VALUE_VERSION = "ALPS.W10.24.p0";
    public static final String VALUE_MANUFACTURER = "MTK1";
    public static final String VALUE_PRODUCT = "MTK";
    private static final String VALUE_COUNTRY = "cn";

    public static final String OPERATOR_NUMBER_1 = "46007";
    public static final String OPERATOR_NUMBER_2 = "46002";

    public static final String CMCC_IMSI_0 = "460078116137041";
    public static final String CMCC_IMSI_1 = "460028116137032";

    private String mSimOperator[];
    private String mSimImsi[];
    private String mSavedImsi = "";
    private String mMessageInfo;

    public MockPlatformManager() {
        this(new String[] { OPERATOR_NUMBER_1, OPERATOR_NUMBER_2 }, new String[] { CMCC_IMSI_0,
                CMCC_IMSI_1 }, null);
    }

    public MockPlatformManager(String[] simOperator, String[] simImsi, String savedImsi) {
        mSimOperator = simOperator;
        mSimImsi = simImsi;
        mSavedImsi = savedImsi;
    }

    @Override
    public String getSavedImsi() {
        Log.i(TAG, "Saved imsi is " + mSavedImsi);
        return mSavedImsi;
    }

    @Override
    public void setSavedImsi(String arg0) {
        mSavedImsi = arg0;
    }

    private int getIndexFromSimId(int simId) {
        int index = simId - PhoneConstants.SIM_ID_1;
        return index;
    }

    private int getIndexFromSubId(long subId) {
        long index = subId - PhoneConstants.SIM_ID_1;
        return (int) index;
    }

    @Override
    public void sendDataMessage(String dstAddr, short dstPort, Short srcPort, byte[] data,
            PendingIntent sentIntent, long subId) {
        mMessageInfo = new String(data);
        Log.i(TAG, "Send data message " + mMessageInfo + " to " + dstAddr);
    }

    public String getMessageInfo() {
        return mMessageInfo;
    }

    // ********************************************
    // Telephony related
    // ********************************************
    @Override
    public String getNetworkCountryIso(long subId) {
        return VALUE_COUNTRY;
    }

    @Override
    public String getSubCountryIso(long subId) {
        return VALUE_COUNTRY;
    }

    @Override
    public String getSubImsi(long subId) {
        Log.i(TAG, "Sim " + subId + "' imsi is " + mSimImsi[getIndexFromSubId(subId)]);
        return mSimImsi[getIndexFromSubId(subId)];
    }

    @Override
    public String getSubOperator(long subId) {
        Log.i(TAG, "Sim " + subId + "'operator is " + mSimOperator[getIndexFromSubId(subId)]);
        return mSimOperator[getIndexFromSubId(subId)];
    }

    @Override
    public int getSubState(long subId) {
        Log.i(TAG, "Sim " + subId + "'state is " + SmsRegConst.SIM_STATE_READY);
        return SmsRegConst.SIM_STATE_READY;
    }

    @Override
    public boolean hasSimCard(long slotId) {
        int simId = (int) slotId;
        Log.i(TAG, "Sim " + slotId + " has sim? " + (mSimImsi[getIndexFromSimId(simId)] != null));
        return mSimImsi[getIndexFromSimId(simId)] != null;
    }

    // ********************************************
    // Registered Message related
    // ********************************************
    @Override
    public String getDeviceImei() {
        Log.i(TAG, "IMEI is " + VALUE_IMEI);
        return VALUE_IMEI;
    }

    @Override
    public String getDeviceVersion() {
        Log.i(TAG, "Version is " + VALUE_VERSION);
        return VALUE_VERSION;
    }

    @Override
    public String getManufacturerName() {
        Log.i(TAG, "Manufacturer is " + VALUE_MANUFACTURER);
        return VALUE_MANUFACTURER;
    }

    @Override
    public String getProductName() {
        Log.i(TAG, "Product is " + VALUE_PRODUCT);
        return VALUE_PRODUCT;
    }

    // ********************************************
    // Alarm related
    // ********************************************
    /**
     * Start an alarm with certain intent
     */
    public void startAlarm(Context context, PendingIntent pendingIntent, long delay) {
        Log.i(TAG,
                "Start alarm, delay " + (delay / 1000) + "s, intent " + pendingIntent.getIntent());
    }

    /**
     * Start an alarm with certain intent
     */
    public void cancelAlarm(Context context, PendingIntent pendingIntent) {
        Log.i(TAG, "Cancel alarm , intent " + pendingIntent.getIntent());
    }
}
