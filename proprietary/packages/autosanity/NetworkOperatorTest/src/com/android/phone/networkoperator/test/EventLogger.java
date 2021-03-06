package com.android.phone.networkoperator.test;

import android.util.Log;

import java.util.ArrayList;
import java.util.HashMap;

public class EventLogger {
    private String mTag;
    private HashMap<Event, EventObj> mEventMap = new HashMap<Event, EventObj>();

    public static enum Event {
        PHONE_RESTART,
        SELECT_NETWORK_MODE,
        START_SEARCH_OPERATORS,
        FINISH_SEARCH_OPERATORS,
    }

    private class EventObj {
        private long mLastTimeMillis = -1;
        private String mDescription;
        private ArrayList<EventObj> mRelatedEvents = new ArrayList<EventObj>();
        private StringBuilder mStringBuilder = new StringBuilder();
        public EventObj(String description) {
            mDescription = description;
        }
        public void addRelatedEvent(EventObj target) {
            mRelatedEvents.add(target);
        }
        public void doLog() {
            long currentTimeMillis = System.currentTimeMillis();
            if (mLastTimeMillis < 0) {
                mLastTimeMillis = currentTimeMillis;
            }

            mStringBuilder.setLength(0);
            mStringBuilder.append(mDescription).append(", ");
            mStringBuilder.append(diffSec(mLastTimeMillis, currentTimeMillis))
                    .append(" s since last ").append(mDescription).append(", ");

            mLastTimeMillis = currentTimeMillis;

            for (EventObj related : mRelatedEvents) {
                mStringBuilder.append(diffSec(related))
                        .append(" s since last ").append(related.mDescription).append(", ");
            }

            log(mStringBuilder.toString());
        }

        private long diffSec(long time1, long time2) {
            if (time1 < 0 || time2 < 0) {
                return -1;
            }
            long diffMillis = time1 > time2 ? time1 - time2 : time2 - time1;
            return diffMillis / 1000;
        }
        private long diffSec(EventObj target) {
            return diffSec(target.mLastTimeMillis, mLastTimeMillis);
        }
    }
    public EventLogger(String tag) {
        mTag = tag;
        init();
    }

    public void logEvent(Event event) {
        mEventMap.get(event).doLog();
    }

    private void init() {
        EventObj phoneRestart = new EventObj("[PhoneRestart]");
        EventObj selectNetworkMode = new EventObj("[SelectNetworkMode]");
        EventObj startSearchOperators = new EventObj("[StartSearchOperators]");
        EventObj finishSearchOperators = new EventObj("[FinishSearchOperators]");

        selectNetworkMode.addRelatedEvent(phoneRestart);
        startSearchOperators.addRelatedEvent(selectNetworkMode);
        startSearchOperators.addRelatedEvent(phoneRestart);
        finishSearchOperators.addRelatedEvent(startSearchOperators);
        finishSearchOperators.addRelatedEvent(phoneRestart);

        mEventMap.put(Event.PHONE_RESTART, phoneRestart);
        mEventMap.put(Event.SELECT_NETWORK_MODE, selectNetworkMode);
        mEventMap.put(Event.START_SEARCH_OPERATORS, startSearchOperators);
        mEventMap.put(Event.FINISH_SEARCH_OPERATORS, finishSearchOperators);
    }

    private void log(String msg) {
        Log.i(mTag, "[EventLogger]" + msg);
    }
}
