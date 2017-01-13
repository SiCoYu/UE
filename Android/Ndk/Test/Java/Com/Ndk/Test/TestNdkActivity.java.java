package Com.Ndk.Test;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

public class TestNdkActivity extends Activity {
    static {
        System.loadLibrary("TestNdk");
    }

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
		//setContentView(R.layout.main);
        
        //��һ�������������������û����������ֱ�ӷ���hello jni�����ù�
        String str = JniClient.AddStr("test", "test");
        
        //�ڶ���������ʱ��ʵ��
        //  int iSum = JniClient.AddInt(5, 2);        
		// String strSum = "5 + 7 = " + iSum;
        
        TextView tv1 = new TextView(this);
        tv1.setText(str);
        setContentView(tv1);
    }
}