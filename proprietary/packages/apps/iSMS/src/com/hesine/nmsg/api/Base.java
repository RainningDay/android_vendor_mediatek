package com.hesine.nmsg.api;

import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.security.InvalidAlgorithmParameterException;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;

import javax.crypto.NoSuchPaddingException;

import org.xml.sax.SAXException;

import com.alibaba.fastjson.JSON;
import com.hesine.nmsg.common.EnumConstants;
import com.hesine.nmsg.http.Http;
import com.hesine.nmsg.http.RequestTask;
import com.hesine.nmsg.interfacee.Pipe;
import com.hesine.nmsg.util.AESCoder;
import com.hesine.nmsg.util.MLog;

public abstract class Base<T_C, T_P> implements Pipe {

	private static final int 		PROTOCOL 		= 1;
	protected boolean 				isRequesting 	= false;
	RequestTask 					task 			= null;
	protected Pipe 					listener 		= null;

	public void setListener(Pipe listener) {
		this.listener = listener;
	}

	public boolean isRequesting() {
		return this.isRequesting;
	}

	public void request() {
		if (this.isRequesting) {
			return;
		}
		isRequesting = true;
		task = Http.instance().post(getUrl(), constructData(), this);
	}
	
	public abstract T_C contentObject();

	//maybe need override
	public void procRequestDataStore(T_C submitData){
	}
	
    private byte[] constructData() {
    	T_C contentObj = contentObject();
    	procRequestDataStore(contentObj);
        String jsonString = JSON.toJSONString(contentObj);
        MLog.trace("nmsg api send data: \n\t", jsonString);
        byte[] returnByteData = null;
        try {
            AESCoder aes = new AESCoder();
            byte[] jsonData = aes.rnmEncrypt(jsonString);

            ByteArrayOutputStream os = new ByteArrayOutputStream();
            DataOutputStream dos = new DataOutputStream(os);
            dos.writeLong(0);
            dos.writeInt(PROTOCOL);
            dos.writeLong(0);
            dos.write(jsonData);
            dos.flush();

            returnByteData = os.toByteArray();
            os.close();
        } catch (InvalidKeyException e) {
            e.printStackTrace();
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        } catch (NoSuchPaddingException e) {
            e.printStackTrace();
        } catch (InvalidAlgorithmParameterException e) {
            e.printStackTrace();
        } catch (Exception e) {
            e.printStackTrace();
        }

        return returnByteData;
    }

	public abstract T_P parseObject();

	protected T_P parseData(byte[] response) {
    	T_P parseObj = null;
        try {
            AESCoder aes = new AESCoder();
            byte[] jsonBody = aes.rnmDecrypt(response);
            parseObj = JSON.parseObject(jsonBody, parseObject().getClass());
        } catch (InvalidKeyException e) {
            e.printStackTrace();
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        } catch (NoSuchPaddingException e) {
            e.printStackTrace();
        } catch (InvalidAlgorithmParameterException e) {
            e.printStackTrace();
        } catch (SAXException e) {
            e.printStackTrace();
        } catch (Exception e) {
            e.printStackTrace();
        }

        return parseObj;
    }
	
	public void cancel() {
		if (null != task) {
			task.setListener(null);
			Http.instance().cancel(task);
			task = null;
		}
		this.isRequesting = false;
	}

	public void start() {
		request();
	}

	public void close() {
		cancel();
	}
	
	public abstract void procReplyDataStore(T_P parseData, int success);

	@Override
	public void complete(Object owner, Object data, int success) {
		isRequesting = false;
		RequestTask t = (RequestTask) owner;
		byte[] retData = t.getParseData(); 
		T_P parse 	= null;
		int retCode = Pipe.NET_FAIL;
		if (null == retData) {
			retCode = Pipe.NET_FAIL;
			MLog.trace("nmsg api recieve data fail: \n\t", "network unavailable, check local network, or server can't connect!");
		} else {
			parse = parseData(t.getParseData());
			if (parse != null) {
				com.hesine.nmsg.bean.response.Base reply = (com.hesine.nmsg.bean.response.Base) parse;
				com.hesine.nmsg.bean.ResultInfo resultInfo = reply.getResultInfo();
				if(null != resultInfo) {
					if (resultInfo.getCode() != 1) {
						retCode = Pipe.SERVER_ERROR;
						MLog.trace("nmsg api recieve data fail: \n\t", 
								"server error, and result info : " + "< result code : " + resultInfo.getCode() 
								+ ", " + "result msg : " + resultInfo.getMessage() + " >" );
					} else {
						retCode = Pipe.NET_SUCCESS;
				        MLog.trace("nmsg api recieve data success: \n\t", JSON.toJSONString(parse));
					}					
				} else {
					retCode = Pipe.PARSE_FAIL;
			        MLog.trace("nmsg api recieve data fail: \n\t", "json parse fail, result info null!");
				}
			} else {
				retCode = Pipe.PARSE_FAIL;
		        MLog.trace("nmsg api recieve data fail: \n\t", "json data can't parse, check data format from server!");
			}
		}
		procReplyDataStore(parse, retCode);
		if(null != listener) {
			listener.complete(this, parse, retCode);
		}
	}
	
	public String getUrl() {
		return EnumConstants.BASE_URL;
	}
}
