package com.mediatek.settings.plugin;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Context;
import android.view.View;
import android.widget.Switch;

import com.mediatek.common.PluginImpl;
import com.mediatek.op03.plugin.R;
import com.mediatek.settings.ext.DefaultDataUsageSummaryExt;
import com.mediatek.xlog.Xlog;

@PluginImpl(interfaceName="com.mediatek.settings.ext.IDataUsageSummaryExt")
public class OP03DataUsageSummaryExt extends DefaultDataUsageSummaryExt {

    private static final String TAG = "OP03DataUsageSummaryExt";
    private Context mContext;
    private DialogInterface.OnClickListener mDialogListener;
    private Switch mDataEnabled;
    private Activity mActivity;

    private View.OnClickListener mClickListener = new View.OnClickListener() {
        @Override
        public void onClick(View v) {
        Xlog.d(TAG, "mDataEnabled = " + mDataEnabled);
        int message = (mDataEnabled.isChecked() ?
                R.string.networksettings_tips_data_disabled
                : R.string.networksettings_tips_data_enabled);
        AlertDialog.Builder dialogBuild = new AlertDialog.Builder(mActivity);
        dialogBuild.setMessage(mContext.getText(message))
        .setTitle(android.R.string.dialog_alert_title)
        .setIcon(android.R.drawable.ic_dialog_alert)
        .setPositiveButton(android.R.string.yes, mDialogListener)
        .setNegativeButton(android.R.string.no, null)
        .create();
        dialogBuild.show();
        }
    };

    public OP03DataUsageSummaryExt(Context context) {
        super(context);
        mContext = context;
    }

    public boolean setDataEnableClickListener(Activity activity, View dataEnabledView,
            Switch dataEnabled, DialogInterface.OnClickListener dataEnabledDialogListerner) {
        Xlog.d(TAG, "setDataEnableClickListener: isChecked " + dataEnabled.isChecked() + "dataEnabledDialogListerner " + dataEnabledDialogListerner);
        mActivity = activity;
        dataEnabledView.setOnClickListener(mClickListener);
        mDataEnabled = dataEnabled;
        mDialogListener = dataEnabledDialogListerner;
        return true;
    }
    
    public boolean needToShowDialog() {
            return false;
    }
    
    public void resetData() {
        mActivity = null;
        mDialogListener = null;
        mDataEnabled = null;
    }
}
